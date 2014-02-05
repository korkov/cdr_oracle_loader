#ifndef OPTIONS_1346833709
#define OPTIONS_1346833709

#include <string>

namespace cdr_oracle_loader
{
    struct options
    {
        options() : exit(false) {}
        std::string ora;
        std::string dir;
        std::string parser;
        size_t bulksize;

        bool exit;
    };

    options get_options(int argc, char** argv);
}

#endif // OPTIONS_1346833709
