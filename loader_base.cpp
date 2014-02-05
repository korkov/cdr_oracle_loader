#include "loader_base.hpp"
#include "otl.hpp"

namespace cdr_oracle_loader
{
    void loader_base::flush()
    {
        m_out->flush();
    }

    void loader_base::init_stream(size_t bulksize, otl_connect& db)
    {
        m_out.reset(new otl_stream(bulksize, sql_string_impl(), db));
    }

    void loader_base::load(CDRParser const& parser, cdr_buffer const& buffer)
    {
        load_impl(parser, buffer);
    }

}
