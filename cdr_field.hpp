#ifndef CDR_FIELD_1346745194
#define CDR_FIELD_1346745194

#include "cdr_parser/CDRparser.h"
#include "precision_checker.hpp"
#include "otl.hpp"

#include <assert.h>
#include <boost/typeof/typeof.hpp>

namespace cdr_oracle_loader
{
    using NCdr::CDRParser;

    namespace
    {
        CDRParser::CDRField const& get_field(CDRParser const& parser, size_t idx)
        {
            BOOST_AUTO(iter, parser.GetFields().find(idx));
            assert(iter != parser.GetFields().end());
            return iter->second;
        }
    }

    enum field_type
    {
        field_uint8,
        field_uint16,
        field_uint32,
        field_uint64,
        field_string,
        field_date,
    };


    template <field_type type, unsigned precision>
    struct field;

    template <unsigned precision>
    struct field<field_uint8, precision>
    {
        static void put(otl_stream& out, CDRParser const& parser, size_t idx)
        {
            BOOST_AUTO(f, get_field(parser, idx));
            out << (precision_checker<precision>::check((boost::uint32_t)f.intValue));
        }
    };

    template <unsigned precision>
    struct field<field_uint16, precision>
    {
        static void put(otl_stream& out, CDRParser const& parser, size_t idx)
        {
            BOOST_AUTO(f, get_field(parser, idx));
            out << precision_checker<precision>::check((boost::uint32_t)f.intValue);
        }
    };

    template <unsigned precision>
    struct field<field_uint32, precision>
    {
        static void put(otl_stream& out, CDRParser const& parser, size_t idx)
        {
            BOOST_AUTO(f, get_field(parser, idx));
            out << precision_checker<precision>::check((boost::uint32_t)f.intValue);
        }
    };


    template <unsigned precision>
    struct field<field_uint64, precision>
    {
        static void put(otl_stream& out, CDRParser const& parser, size_t idx)
        {
            BOOST_AUTO(f, get_field(parser, idx));
            out << f.textValue.c_str();
        }
    };

    template <unsigned precision>
    struct field<field_string, precision>
    {
        static void put(otl_stream& out, CDRParser const& parser, size_t idx)
        {
            BOOST_AUTO(f, get_field(parser, idx));
            out << precision_checker<precision>::check(f.textValue).c_str();
        }
    };

    template <unsigned precision>
    struct field<field_date, precision>
    {
        static void put(otl_stream& out, CDRParser const& parser, size_t idx)
        {
            BOOST_AUTO(f, get_field(parser, idx));
            BOOST_AUTO(const& time, f.dateValue);

            otl_datetime ret;
            ret.year = time.tm_year;
            ret.month = time.tm_mon;
            ret.day = time.tm_mday;
            ret.hour = time.tm_hour;
            ret.minute = time.tm_min;
            ret.second = time.tm_sec;

            out << ret;
        }
    };

}


#endif // CDR_FIELD_1346745194
