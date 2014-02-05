#include "load_one_file.hpp"

/// Если не включать этот файл явно, то объекты, описанные в нём,
/// не создаются в VC9, в gcc всё ок, перемудрили с фабриками и статичными объектами.
#include "../cdr_parser/xdr/xdr_all_parsers.cpp"

#include "log.hpp"
#include "cdr_buffer.hpp"
#include "dat_reader.hpp"
#include "oracle_loader.hpp"
#include "cdr_file_splitter.hpp"

#include <boost/typeof/typeof.hpp>
#include <boost/filesystem.hpp>

namespace cdr_oracle_loader
{
    namespace fs = boost::filesystem;

    void rename_dat_file(fs::path const p)
    {
        try
        {
            fs::path new_p(p);
            new_p.replace_extension(".wor");

            if (fs::exists(new_p))
                fs::remove(new_p);

            fs::rename(p, new_p);
        }
        catch (std::exception const& err)
        {
            PRINT_ERROR(fmt(_("cannot rename file %1%: %2%")) % p % err.what());
        }
    }

    bool load_one_file(fs::path const& path, conn_data const& conn, size_t bulksize)
    {
        try
        {
            oracle_loader loader(conn, bulksize);

            PRINT_INFO(fmt(_("%1% :loading ...")) % path);

            cdr_file_splitter splitter(path);

            size_t count = 0;

            do 
            {
                cdr_buffer const buffer = splitter.get_next();
                if (buffer.empty())
                    break;

                if (loader.load(buffer))
                    count++;

            } while (true);

            PRINT_INFO(fmt(_("%1% :flush ...")) % path);
            loader.flush();

            PRINT_INFO(fmt(_("%1% :loaded %2% records")) % path % count);

            rename_dat_file(path);
        }
        catch (std::exception const& err)
        {
            PRINT_ERROR(fmt(_("load_one_file ERROR: %1%")) % err.what());
            return false;
        }

        return true;
    }
}
