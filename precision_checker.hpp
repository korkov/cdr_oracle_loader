#ifndef PRECISION_CHECKER_1346745472
#define PRECISION_CHECKER_1346745472

#include <assert.h>
#include <stdexcept>
#include <string>
#include <boost/cstdint.hpp>
#include <boost/format.hpp>

namespace cdr_oracle_loader
{
    namespace precision_checker_impl
    {
        template <unsigned precision, typename T>
        struct get_limit
        {
            static boost::uint64_t const value = get_limit<precision - 1, T>::value * 10;
        };

        template <typename T>
        struct get_limit<0, T>
        {
            static boost::uint64_t const value = 1;
        };

        template <unsigned precision>
        struct precision_checker
        {
            template <typename T>
            static T const& check(T const& val)
            {
#ifndef NDEBUG
                boost::uint64_t const abs_limit = get_limit<precision, T>::value;
                assert(val < abs_limit);

                if (val >= abs_limit)
                    throw std::runtime_error(
                        (boost::format("%d >= %d, limit error (1)") % val % abs_limit).str());
#endif
                return val;
            }

            template <>
            static std::string const& check<std::string>(std::string const& val)
            {
#ifndef NDEBUG
                assert(val.size() <= precision);

                if (val.size() > precision)
                    throw std::runtime_error(
                        (boost::format("'%s' size: %d > %d, limit error (2)") % val % val.size() % precision).str());
#endif
                return val;
            }
        };
    }

    using precision_checker_impl::precision_checker;
}

#endif // PRECISION_CHECKER_1346745472
