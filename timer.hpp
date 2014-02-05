#ifndef TIMER_1347352346
#define TIMER_1347352346

#include <boost/asio.hpp>
#include <time.h>

namespace cdr_oracle_loader
{
    struct time_t_traits
    {
        typedef std::time_t time_type;

        struct duration_type
        {
            duration_type() : value(0) {}
            duration_type(std::time_t v) : value(v) {}
            std::time_t value;
        };

        static time_type now()
        {
            return std::time(0);
        }

        static time_type add(const time_type& t, const duration_type& d)
        {
            return t + d.value;
        }

        static duration_type subtract(const time_type& t1, const time_type& t2)
        {
            return duration_type(t1 - t2);
        }

        static bool less_than(const time_type& t1, const time_type& t2)
        {
            return t1 < t2;
        }

        static boost::posix_time::time_duration to_posix_duration(
            const duration_type& d)
        {
            return boost::posix_time::seconds(d.value);
        }
    };

    typedef boost::asio::basic_deadline_timer<
        std::time_t, time_t_traits> timer_t;
}

#endif // TIMER_1347352346
