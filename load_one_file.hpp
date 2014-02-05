#ifndef CDR_FILE_LOADER_1346834787
#define CDR_FILE_LOADER_1346834787

#include <string>
#include <boost/filesystem.hpp>

namespace cdr_oracle_loader
{
    bool load_one_file(boost::filesystem::path const& path, std::string const& conn, size_t bulksize);
}

#endif // CDR_FILE_LOADER_1346834787
