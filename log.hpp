#ifndef LOG_1346228044
#define LOG_1346228044

#include <iostream>
#include <string.h>
#include <errno.h>
#include <stdexcept>
#include <boost/format.hpp>

#include "logging/log.h"

namespace cdr_oracle_loader
{
    typedef boost::format fmt;
    const char APP_NAME[] = "CDR oracle loader";
}

#define _(WHAT) (WHAT)
#define ERRNO_STRING ((errno) ? (std::string(" - ") + strerror(errno)) : std::string())
#define RUNTIME_ERROR(WHAT) (std::runtime_error(std::string(WHAT) + ERRNO_STRING))

#include <sstream>

#define PRINT(WHAT, LEVEL) do { std::stringstream e; e << WHAT; STSLOG_WRAPPER::Log( STSLOG_WRAPPER::tLogMain ).LEVEL("%s", e.str().c_str()); } while (false)

#define PRINT_NONE(WHAT) PRINT(WHAT, None)
#define PRINT_FATAL(WHAT) PRINT(WHAT, Fatal)
#define PRINT_ERROR(WHAT) PRINT(WHAT, Error)
#define PRINT_WARNING(WHAT) PRINT(WHAT, Warning)
#define PRINT_INFO(WHAT) PRINT(WHAT, Info)
#define PRINT_DEBUG(WHAT) PRINT(WHAT, Debug0)

#endif // LOG_1346228044
