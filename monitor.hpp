#ifndef MONITOR_1346763615
#define MONITOR_1346763615

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio.hpp>
#include <string>

namespace cdr_oracle_loader
{
    struct monitor
    {
        typedef boost::function<bool (boost::filesystem::path)> handler_type;

        monitor(
            boost::asio::io_service& io,
            std::string const& path,
            handler_type handler
            );

    private:
        struct impl;
        boost::shared_ptr<impl> pimpl;
    };
}

#endif // MONITOR_1346763615
