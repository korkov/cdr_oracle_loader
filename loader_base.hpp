#ifndef LOADER_BASE_1347619498
#define LOADER_BASE_1347619498

#include "cdr_parser/CDRparser.h"
#include <boost/shared_ptr.hpp>

class otl_stream;
class otl_connect;

namespace cdr_oracle_loader
{
    struct cdr_buffer;

    using NCdr::CDRParser;

    struct loader_base
    {
        void load(CDRParser const& parser, cdr_buffer const& buffer);
        void init_stream(size_t bulksize, otl_connect& db);
        void flush();

    protected:
        virtual ~loader_base() {}
        boost::shared_ptr<otl_stream> m_out;
    
    private:
        virtual char const* sql_string_impl() = 0;
        virtual void load_impl(CDRParser const& parser, cdr_buffer const& buffer) = 0;
    };

    typedef boost::shared_ptr<loader_base> loader_base_ptr;

    template <typename Policy>
    struct basic_loader: public loader_base
    {
    private:
        char const* sql_string_impl() { return Policy::sql_string(); }

        void load_impl(CDRParser const& parser, cdr_buffer const& buffer)
        {
            Policy::load(*m_out, parser, buffer);
        }

    };
}

#endif // LOADER_BASE_1347619498
