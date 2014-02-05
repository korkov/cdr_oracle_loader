#ifndef CDR_FILE_SPLITTER_1346239402
#define CDR_FILE_SPLITTER_1346239402

#include "cdr_buffer.hpp"

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

namespace cdr_oracle_loader
{
    struct cdr_file_splitter
    {
        explicit cdr_file_splitter(boost::filesystem::path const& path);

        cdr_buffer get_next();

    private:
        struct impl;
        boost::shared_ptr<impl> pimpl;
    };
}

#endif // CDR_FILE_SPLITTER_1346239402
