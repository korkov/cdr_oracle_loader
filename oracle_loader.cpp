#include "oracle_loader.hpp"
#include "cdr_buffer.hpp"
#include "log.hpp"
#include "xdr_format.hpp"
#include "cdr_parser/CDRparser.h"
#include "otl.hpp"
#include "loader_base.hpp"
#include "loaders.hpp"

#include <boost/typeof/typeof.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread/once.hpp>
#include <boost/foreach.hpp>
#include <time.h>

#pragma warning( disable : 4355 )

namespace cdr_oracle_loader
{
    char const sql_cdr_errors[] =
        "insert into cdr_errors ( buffer_size, description, buffer )"
        " values ( :buffer_size<unsigned>, :description<char[255]>, :buffer<raw[1024]> )";

    using NCdr::CDRParser;

    boost::once_flag initialize_otl_flag = BOOST_ONCE_INIT;

    void initialize_otl()
    {
        /// 1 - multi-threaded mode
        otl_connect::otl_initialize(1);
    }

    struct otl_connect_wrapper
    {
        explicit otl_connect_wrapper(conn_data const& conn)
        {
            boost::call_once(initialize_otl, initialize_otl_flag);
            m_db.rlogon(conn.c_str());
            m_db.set_max_long_size(std::max(xdr_format_6_size, xdr_format_9_size));
        }

        otl_connect& get()
        {
            return m_db;
        }

    private:
        otl_connect m_db;
    };

    struct oracle_loader::impl
    {
        impl(conn_data const& conn, size_t bulksize)
            : m_db(conn)
            , out_errors(new otl_stream(bulksize, sql_cdr_errors, m_db.get()))
            , m_loaders(
                boost::assign::map_list_of
                    (CDRParser::CDR6, loader_base_ptr(new basic_loader<loader_6>()))
                    (CDRParser::CDR9, loader_base_ptr(new basic_loader<loader_9>()))
                )
        {
            try
            {
                BOOST_FOREACH(loaders_map::value_type const& val, m_loaders)
                    val.second->init_stream(bulksize, m_db.get());
            }
            catch (otl_exception const& err)
            {
                throw std::runtime_error((fmt(_("OTL exception: %1%")) % err.msg).str());
            }
        }

        bool load(cdr_buffer const& buffer)
        {
            assert(buffer.data());
            assert(buffer.size());

            bool loaded = false;

            std::string error_str;

            CDRParser parser;
            if (parser.Parse(buffer.data().get(), buffer.size()))
            {
                BOOST_AUTO(const found, m_loaders.find(parser.GetFormat()));
                assert(found != m_loaders.end() && "No such loader, add the loader for this format.");

                if (found != m_loaders.end())
                {
                    try
                    {
                        found->second->load(parser, buffer);
                        loaded = true;
                    }
                    catch (otl_exception const& err)
                    {
                        error_str = (fmt(_("OTL exception: %1%")) % err.msg).str();
                        assert(false);
                    }
                    catch (std::exception const& err)
                    {
                        error_str = (fmt(_("Cannot load row: %1%")) % err.what()).str();
                    }
                }
                else
                {
                    error_str = (_("Unknown cdr format"));
                }
            }
            else
            {
                error_str = (_("Cannot parse buffer"));
            }

            if (!error_str.empty())
                PRINT_ERROR(error_str);

            if (!loaded)
            {
                try
                {
                    load_error(error_str, buffer);
                }
                catch (otl_exception const& err)
                {
                    PRINT_ERROR(fmt(_("OTL exception (2): %1%")) % err.msg);
                    assert(false);
                }
                catch (std::exception const& err)
                {
                    PRINT_ERROR(fmt(_("Cannot load row (2): %1%")) % err.what());
                }
            }

            return loaded;
        }

        void flush()
        {
            BOOST_FOREACH(loaders_map::value_type const& val, m_loaders)
                val.second->flush();
        }

    private:
        void load_error(std::string const& error_str, cdr_buffer const& buffer)
        {
            otl_stream& out = *out_errors;

            const size_t raw_size = buffer.size();

            out << raw_size;
            out << error_str.c_str();

            otl_long_string raw(raw_size);
            for (size_t idx = 0; idx < raw_size; idx++)
                raw[idx] = buffer.data()[idx];
            raw.set_len(raw_size);

            out << raw;
        }

        otl_connect_wrapper m_db;

        typedef std::map<CDRParser::eCDRType, const loader_base_ptr> loaders_map;
        const loaders_map m_loaders;

        boost::shared_ptr<otl_stream> out_errors;
    };

    oracle_loader::oracle_loader(conn_data const& conn_data, size_t bulksize)
        : pimpl(new impl(conn_data, bulksize))
    {
    }

    bool oracle_loader::load(cdr_buffer const& buffer)
    {
        return pimpl->load(buffer);
    }

    void oracle_loader::flush()
    {
        return pimpl->flush();
    }
}
