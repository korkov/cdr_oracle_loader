#ifndef ORACLE_LOADER_1346165270
#define ORACLE_LOADER_1346165270

#include <string>
#include <boost/shared_ptr.hpp>

namespace cdr_oracle_loader
{
    typedef std::string conn_data;

    struct cdr_buffer;

    struct oracle_loader
    {
        oracle_loader(conn_data const& conn_data, size_t bulksize);
        bool load(cdr_buffer const& buffer);
        void flush();

    private:
        struct impl;
        boost::shared_ptr<impl> pimpl;
    };
}

#endif // ORACLE_LOADER_1346165270
