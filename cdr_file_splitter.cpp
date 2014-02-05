#include "cdr_file_splitter.hpp"
#include "dat_reader.hpp"
#include "log.hpp"

#include "boost/filesystem/fstream.hpp"

namespace fs = boost::filesystem;

namespace cdr_oracle_loader
{
    struct cdr_file_splitter::impl
    {
        template <typename T>
        struct logical_check
        {
            logical_check(T& obj, const std::string& mess = "")
                : m_obj(obj)
            {
                if (!m_obj)
                    throw RUNTIME_ERROR(std::string("logical check: ") + mess);
            }
            T& get() { return m_obj; }
        private:
            T& m_obj;
        };

        impl(fs::path const& path)
            : m_stream(path, std::ios::binary)
            , m_stream_checker(m_stream)
            , m_reader(m_stream)
        {
        }

        cdr_buffer get_next()
        {
            size_t const size = m_reader.get_buffer_size();
            cdr_buffer buffer(size);

            bool const ok = m_reader.read_next(buffer);
            
            if (!ok)
                m_stream.close();

            return ok ? buffer : cdr_buffer();
        }

    private:
        fs::ifstream m_stream;
        logical_check<fs::ifstream> m_stream_checker;
        dat_reader m_reader;
    };

    cdr_file_splitter::cdr_file_splitter(fs::path const& path)
        : pimpl(new impl(path))
    {
    }

    cdr_buffer cdr_file_splitter::get_next()
    {
        return pimpl->get_next();
    }
}
