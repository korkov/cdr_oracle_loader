#ifndef CDR_BUFFER_1346230229
#define CDR_BUFFER_1346230229

#include <boost/shared_array.hpp>

namespace cdr_oracle_loader
{
    struct cdr_buffer
    {
        typedef boost::shared_array<unsigned char> data_type;

        /// empty buffer
        cdr_buffer()
            : m_size(0)
        {
        }

        explicit cdr_buffer(size_t size)
            : m_data(new unsigned char[size]), m_size(size)
        {
        }

        bool empty() const { return m_size == 0; }
        data_type data() const { return m_data; }
        size_t size() const { return m_size; }

    private:
        data_type m_data;
        size_t m_size;
    };
}

#endif // CDR_BUFFER_1346230229
