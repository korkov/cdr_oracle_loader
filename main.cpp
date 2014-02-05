#include "log.hpp"
#include "monitor.hpp"
#include "options.hpp"
#include "load_one_file.hpp"
#include "cdr_parser/CDRparser.h"

#include <stdlib.h>
#include <string>
#include <boost/bind.hpp>

namespace
{
    void init_cdr_parser(std::string const& path)
    {
        /// создаём неиспользуемый CDRParser, чтобы инициализировать
        /// безопасно его конфиг в одном треде
        NCdr::CDRParser p(path);
    }
}

int main(int argc, char** argv)
{
    STSLOG_WRAPPER::LogSystemScope	log_system;
    if(!log_system.Start(NULL))
    {
        std::cerr << "Can't initialize STSLog." << std::endl;
    }

    using namespace cdr_oracle_loader;

    try
    {
        options const opts = get_options(argc, argv);

        if (opts.exit)
            return EXIT_FAILURE;

        init_cdr_parser(opts.parser);

        boost::asio::io_service io_service;
        boost::asio::io_service::work work(io_service); 

        PRINT_NONE(fmt(_("=================== %1% started ===================")) % APP_NAME);
        monitor mon(io_service, opts.dir, boost::bind(load_one_file, _1, opts.ora, opts.bulksize));

        io_service.run(); 
    }
    catch (std::exception const& err)
    {
        PRINT_FATAL(fmt(_("Fatal exception: %1%")) % err.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
