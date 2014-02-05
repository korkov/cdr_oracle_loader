#include "cdr_parser/CDRparser.h"
#include "dat_reader.hpp"
#include "cdr_buffer.hpp"
#include "log.hpp"

#include <map>
#include <vector>
#include <boost/cstdint.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/assign/list_of.hpp>

namespace cdr_oracle_loader
{
    std::map<char, xdr_format> xdr_format_map = boost::assign::map_list_of
        ('6', xdr_format_6)
        ('9', xdr_format_9)
        ;

    std::map<xdr_format, size_t> xdr_size_map = boost::assign::map_list_of
        (xdr_format_6, xdr_format_6_size)
        (xdr_format_9, xdr_format_9_size)
        ;

    std::map<xdr_format, char const*> xdr_description_map = boost::assign::map_list_of
        (xdr_format_6, "cdr 6")
        (xdr_format_9, "edr 9")
        ;

    struct dat_reader::impl
    {
        impl(std::ifstream& in)
            : m_in(in)
        {
            boost::uint16_t header_size = 0;
            in.read((char*)&header_size, sizeof(header_size));

            char format = '\0';
            in.read(&format, sizeof(format));

            if (!in)
                throw std::runtime_error("cannot read stream");

            if (header_size != 17)
            {
                header_size = 17;
                format = '6';
            }

            m_format = xdr_format_map[format];
            m_buffer_size = xdr_size_map[m_format];

            m_in.seekg(header_size, std::ios_base::beg);
        }

        bool read_next(cdr_buffer const& buffer)
        {
            assert(buffer.data());
            assert(buffer.size() == m_buffer_size);
            bool const ok = m_in.read((char*)buffer.data().get(), buffer.size()) != NULL;
            return ok;
        }

        xdr_format get_format() const
        {
            return m_format;
        }

        size_t get_buffer_size() const
        {
            return m_buffer_size;
        }

    private:
        std::ifstream& m_in;
        xdr_format m_format;
        size_t m_buffer_size;
    };

    
    dat_reader::dat_reader(std::ifstream& in)
        : pimpl(new impl(in))
    {
    }

    bool dat_reader::read_next(cdr_buffer const& buffer)
    {
        return pimpl->read_next(buffer);
    }

    xdr_format dat_reader::get_format() const
    {
        return pimpl->get_format();
    }

    size_t dat_reader::get_buffer_size() const
    {
        return pimpl->get_buffer_size();
    }
}
