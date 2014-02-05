#include "loaders.hpp"
#include "cdr_field.hpp"
#include "sql_cdr_6.hpp"
#include "sql_cdr_9.hpp"

namespace cdr_oracle_loader
{
    void loader_6::load(otl_stream& out, CDRParser const& parser, cdr_buffer const& buffer)
    {
        field<field_uint8, 3>::put(out, parser, 2);
        field<field_uint8, 1>::put(out, parser, 3);
        out << (unsigned)0; // HDCD_SERVICE_DATA
        field<field_uint32, 9>::put(out, parser, 5);
        field<field_uint32, 2>::put(out, parser, 6);
        field<field_uint32, 9>::put(out, parser, 8);
        field<field_uint32, 2>::put(out, parser, 9);
        field<field_uint8, 3>::put(out, parser, 10);
        field<field_uint8, 2>::put(out, parser, 12);
        field<field_uint8, 1>::put(out, parser, 13);
        field<field_uint8, 1>::put(out, parser, 14);
        out << (unsigned)0; // BSRV_EXTENSION_INDICATOR
        field<field_uint8, 3>::put(out, parser, 16);
        out << (unsigned)0; // BSRV_EXTENSION_INDICATOR_2
        field<field_uint8, 3>::put(out, parser, 17);
        field<field_string, 34>::put(out, parser, 24);
        field<field_string, 34>::put(out, parser, 29);
        out << ""; // MSC Id
        field<field_date, 2>::put(out, parser, 31);
        field<field_uint16, 5>::put(out, parser, 32);
        field<field_uint16, 5>::put(out, parser, 33);
        field<field_uint16, 5>::put(out, parser, 34);
        field<field_uint32, 10>::put(out, parser, 35);
        field<field_uint32, 10>::put(out, parser, 82);
        field<field_uint64, 20>::put(out, parser, 36);
        field<field_uint16, 5>::put(out, parser, 38);
        field<field_uint16, 5>::put(out, parser, 39);
        field<field_uint8, 1>::put(out, parser, 41);
        field<field_uint8, 2>::put(out, parser, 42);
        field<field_uint8, 2>::put(out, parser, 44);
        field<field_uint8, 2>::put(out, parser, 45);
        field<field_uint8, 3>::put(out, parser, 46);
        field<field_uint8, 3>::put(out, parser, 47);
        field<field_uint32, 10>::put(out, parser, 48);
        field<field_uint32, 3>::put(out, parser, 49);
        field<field_uint32, 10>::put(out, parser, 50);
        field<field_uint32, 10>::put(out, parser, 51);
        field<field_uint64, 20>::put(out, parser, 52);
        field<field_uint64, 20>::put(out, parser, 53);
        field<field_uint32, 10>::put(out, parser, 54);
        field<field_uint32, 10>::put(out, parser, 55);
        field<field_uint64, 20>::put(out, parser, 56);
        field<field_uint32, 10>::put(out, parser, 57);
        field<field_uint32, 10>::put(out, parser, 58);
        field<field_uint32, 10>::put(out, parser, 59);
        field<field_uint64, 20>::put(out, parser, 60);
        field<field_uint32, 10>::put(out, parser, 61);
        field<field_uint64, 20>::put(out, parser, 62);
        field<field_date, 2>::put(out, parser, 63);
        field<field_uint8, 3>::put(out, parser, 64);
        out << (unsigned)0; // FLAG ???
        field<field_uint8, 1>::put(out, parser, 71);
        field<field_uint8, 1>::put(out, parser, 72);
        field<field_uint8, 3>::put(out, parser, 73);
        field<field_uint64, 20>::put(out, parser, 74);
        field<field_uint32, 10>::put(out, parser, 75);
        field<field_uint64, 20>::put(out, parser, 76);
        field<field_string, 4>::put(out, parser, 77);
        field<field_uint32, 10>::put(out, parser, 78);
        field<field_uint32, 10>::put(out, parser, 79);
        field<field_uint8, 3>::put(out, parser, 80);
        field<field_uint8, 3>::put(out, parser, 81);
        field<field_uint32, 10>::put(out, parser, 82);
        field<field_uint64, 20>::put(out, parser, 83);

        const size_t raw_size = buffer.size();
        otl_long_string raw(raw_size);
        for (size_t idx = 0; idx < raw_size; idx++)
            raw[idx] = buffer.data()[idx];
        raw.set_len(raw_size);

        out << raw;
    }

    char const* loader_6::sql_string()
    {
        return sql_cdr_6;
    }


    void loader_9::load(otl_stream& out, CDRParser const& parser, cdr_buffer const& buffer)
    {
        field<field_uint8, 3>::put(out, parser, 2);
        field<field_uint8, 1>::put(out, parser, 3);
        field<field_uint32, 9>::put(out, parser, 5);
        field<field_uint32, 2>::put(out, parser, 6);
        field<field_date, 2>::put(out, parser, 7);
        field<field_uint8, 3>::put(out, parser, 8);
        field<field_uint8, 3>::put(out, parser, 9);
        field<field_uint8, 3>::put(out, parser, 10);
        field<field_string, 10>::put(out, parser, 11);
        field<field_string, 10>::put(out, parser, 12);
        field<field_uint8, 3>::put(out, parser, 13);
        field<field_uint8, 3>::put(out, parser, 14);
        field<field_uint32, 10>::put(out, parser, 15);
        field<field_string, 40>::put(out, parser, 16);
        field<field_string, 40>::put(out, parser, 17);
        field<field_uint32, 10>::put(out, parser, 18);
        field<field_uint32, 10>::put(out, parser, 19);
        field<field_string, 8>::put(out, parser, 20);
        field<field_uint64, 20>::put(out, parser, 21);
        field<field_uint8, 3>::put(out, parser, 22);
        field<field_string, 150>::put(out, parser, 23);
        field<field_date, 2>::put(out, parser, 24);
        field<field_uint16, 5>::put(out, parser, 25);
        field<field_uint8, 3>::put(out, parser, 26);
        field<field_uint64, 20>::put(out, parser, 27);
        field<field_string, 20>::put(out, parser, 28);
        field<field_string, 20>::put(out, parser, 29);
        field<field_uint32, 10>::put(out, parser, 30);
        field<field_uint32, 10>::put(out, parser, 31);
        field<field_string, 8>::put(out, parser, 32);
        field<field_date, 2>::put(out, parser, 33);
        field<field_date, 2>::put(out, parser, 34);
        field<field_string, 12>::put(out, parser, 35);
        field<field_uint8, 3>::put(out, parser, 36);
        field<field_uint16, 5>::put(out, parser, 37);
        field<field_uint16, 5>::put(out, parser, 38);
        field<field_uint16, 5>::put(out, parser, 39);
        field<field_string, 10>::put(out, parser, 40);
        field<field_date, 2>::put(out, parser, 41);
        field<field_uint8, 3>::put(out, parser, 42);
        field<field_string, 8>::put(out, parser, 43);
        field<field_uint16, 5>::put(out, parser, 44);
        field<field_uint32, 10>::put(out, parser, 45);
        field<field_date, 2>::put(out, parser, 46);
        field<field_uint32, 10>::put(out, parser, 47);
        field<field_uint32, 10>::put(out, parser, 48);
        field<field_uint32, 10>::put(out, parser, 49);
        field<field_uint32, 10>::put(out, parser, 50);
        field<field_uint64, 20>::put(out, parser, 51);
        field<field_uint32, 10>::put(out, parser, 52);
        field<field_uint64, 20>::put(out, parser, 53);
        field<field_uint64, 20>::put(out, parser, 54);
        field<field_uint32, 10>::put(out, parser, 55);
        field<field_uint64, 20>::put(out, parser, 56);
        field<field_uint32, 10>::put(out, parser, 57);
        field<field_uint32, 10>::put(out, parser, 58);
        field<field_uint32, 10>::put(out, parser, 59);
        field<field_uint64, 20>::put(out, parser, 60);
        field<field_uint32, 10>::put(out, parser, 61);
        field<field_string, 5>::put(out, parser, 62);
        field<field_uint32, 10>::put(out, parser, 63);
        field<field_uint64, 20>::put(out, parser, 64);

        const size_t raw_size = buffer.size();
        otl_long_string raw(raw_size);
        for (size_t idx = 0; idx < raw_size; idx++)
            raw[idx] = buffer.data()[idx];
        raw.set_len(raw_size);

        out << raw;
    }

    char const* loader_9::sql_string()
    {
        return sql_cdr_9;
    }

}