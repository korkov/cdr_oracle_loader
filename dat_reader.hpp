#ifndef DAT_READER_1346147470
#define DAT_READER_1346147470

#include "xdr_format.hpp"

#include <boost/shared_ptr.hpp>
#include <fstream>

namespace cdr_oracle_loader
{
    struct cdr_buffer;

    struct dat_reader
    {
        explicit dat_reader(std::ifstream& in);
        bool read_next(cdr_buffer const& buffer);

        xdr_format get_format() const;
        size_t get_buffer_size() const;

    private:
        struct impl;
        boost::shared_ptr<impl> pimpl;
    };
}

#endif // DAT_READER_1346147470
