#ifndef LOADERS_1347619757
#define LOADERS_1347619757

#include "cdr_buffer.hpp"
#include "cdr_parser/CDRparser.h"
#include "otl.hpp"

namespace cdr_oracle_loader
{
    using NCdr::CDRParser;

    struct loader_6
    {
        static void load(otl_stream& out, CDRParser const& parser, cdr_buffer const& buffer);
        static char const* sql_string();
    };

    struct loader_9
    {
        static void load(otl_stream& out, CDRParser const& parser, cdr_buffer const& buffer);
        static char const* sql_string();
    };
}

#endif // LOADERS_1347619757
