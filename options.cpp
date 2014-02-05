#include "options.hpp"
#include "log.hpp"
#include "cdr_oracle_loader_version.hpp"

#include <boost/foreach.hpp>
#include <boost/program_options.hpp>

namespace
{
    void print_args(int argc, char** argv)
    {
        std::stringstream res;

        for (size_t idx = 0; idx != argc; idx++)
            res << argv[idx] << " ";
        PRINT_INFO(res.str());
    }

    namespace opts
    {
        char const help[] = "help";
        char const version[] = "version";
        char const ora[] = "ora";
        char const dir[] = "dir";
        char const parser[] = "parser";
        char const bulksize[] = "bulksize";
    }
}

namespace cdr_oracle_loader
{
    options get_options(int argc, char** argv)
    {
        namespace po = boost::program_options;

        print_args(argc, argv);

        options ret;

        po::options_description desc(std::string(APP_NAME) + " " + _("command options"));
        desc.add_options()
            (opts::help, _("Produce help message"))
            (opts::version, _("Print version"))
            (opts::ora, po::value<std::string>(&ret.ora), _("Oracle connection string"))
            (opts::dir, po::value<std::string>(&ret.dir), _("CDR files directory"))
            (opts::parser, po::value<std::string>(&ret.parser)->default_value("parser.xml"), _("XML config for CDR parser"))
            (opts::bulksize, po::value<size_t>(&ret.bulksize)->default_value(1000), _("OTL stream buffer size"))
            ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count(opts::version))
            std::cerr << fmt("%1% version: %2%") % APP_NAME % version::str() << std::endl;
        if (vm.count(opts::help))
            std::cerr << desc << std::endl;

        ret.exit = vm.count(opts::help) || vm.count(opts::version);

        if (!ret.exit)
        {
            if (ret.dir.empty())
                throw std::runtime_error(_("Empty CDR files directory path."));
            if (ret.ora.empty())
                throw std::runtime_error(_("Empty Oracle connection string."));
        }

        return ret;
    }
}
