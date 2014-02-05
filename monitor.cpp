#include "monitor.hpp"
#include "log.hpp"
#include "safe_container.hpp"

#include "timer.hpp"

#include <boost/typeof/typeof.hpp>
#include <boost/scope_exit.hpp>
#include <boost/foreach.hpp>
#include <dir_monitor.hpp>

namespace fs = boost::filesystem;

namespace
{
    std::vector<fs::path> get_existing_dat_files(fs::path const& path)
    {
        std::vector<fs::path> ret;

        fs::directory_iterator end_itr;
        for (fs::directory_iterator itr(path); itr != end_itr; ++itr)
        {
            fs::path p = itr->path();
            try
            {
                if (fs::is_regular(p) && (p.extension() == ".dat"))
                    ret.push_back(p);
            }
            catch (std::exception const&) {}
        }

        return ret;
    }
}

namespace cdr_oracle_loader
{
    struct monitor::impl
    {
        impl(
            boost::asio::io_service& io,
            std::string const& path,
            handler_type handler
            )
            : m_dm(io)
            , m_timer(io)
            , m_handler(handler)
            , m_dir(path)
        {
            if (!fs::is_directory(m_dir))
                throw std::runtime_error(path + ": no such directory");

            m_dm.add_directory(path);
            start_async();

            process_existing_dat_files();
        }

        void process_existing_dat_files()
        {
            process_files(get_existing_dat_files(m_dir));
        }

        void process_files(std::vector<fs::path> const& files)
        {
            BOOST_FOREACH(fs::path const& p, files)
            {
                PRINT_INFO(fmt(_("%1% :existing")) % p);
                process_file(p);
            }
        }

        void start_async()
        {
            m_dm.async_monitor(
                boost::bind(&impl::dm_handler, this, _1, _2)
                );
        }

        void dm_handler(
            boost::system::error_code const& ec,
            boost::asio::dir_monitor_event const & ev) 
        {
            if (ec)
            {
                PRINT_WARNING(fmt(_("dir_monitor error: %1%")) % ec.message());
            }
            else
            {
                fs::path const p = fs::path(ev.dirname) / ev.filename;

                bool const is_dat_file = (p.extension() == ".dat");
                bool const is_new_file = (ev.type == boost::asio::dir_monitor_event::modified);

                if (is_dat_file && is_new_file)
                {
                    PRINT_INFO(fmt(_("%1% :modified")) % p);
                    process_file(p);
                }
            }

            start_async();
        }

        void process_file(fs::path const& p)
        {
            if (m_list.add(p))
            {
                boost::thread th(&impl::handler, this, p);
            }
            else
            {
                PRINT_INFO(fmt(_("%1% :file already in queue")) % p);
            }
        }

        /// эта функция запускается в отдельном треде
        void handler(fs::path const& p)
        {
            BOOST_SCOPE_EXIT((&m_list)(&p))
            {
                m_list.del(p);
                PRINT_INFO(fmt(_("files in queue: %1%")) % m_list.size());
            } BOOST_SCOPE_EXIT_END

            if (!m_handler(p))
                check_existing_later();
        }

        void check_existing_later()
        {
            /// например, перезапускать проверку непроверенных файлов через timeout секунд
            int const timeout = 10;

            /// отменяем предыдущие таймеры
            m_timer.cancel();
            m_timer.expires_from_now(timeout);
            m_timer.async_wait(boost::bind(&impl::check_existing_later_helper, this, _1));
        }

        void check_existing_later_helper(boost::system::error_code const& error)
        {
            if (error)
                return;

            process_existing_dat_files();
        }

        boost::asio::dir_monitor m_dm;
        timer_t m_timer;
        handler_type m_handler;
        safe_container< std::list<fs::path> > m_list;
        fs::path const m_dir;
    };

    monitor::monitor(
        boost::asio::io_service& io,
        std::string const& path,
        handler_type handler
        )
        : pimpl(new impl(io, path, handler))
    {
    }
}
