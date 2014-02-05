#ifndef SAFE_CONTAINER_1347008751
#define SAFE_CONTAINER_1347008751

#include <boost/typeof/typeof.hpp>
#include <boost/thread.hpp>
#include <boost/range/algorithm.hpp>

namespace cdr_oracle_loader
{
    template <typename Container, typename Mutex = boost::mutex>
    struct safe_container
    {
        typedef boost::unique_lock<Mutex> scoped_lock;
        typedef typename Container::value_type value_type;

        /// если файла в списке не было, вставляет файл в список и возвращает true
        bool add(value_type p)
        {
            scoped_lock lock(m_mutex);

            bool const not_found = (boost::find(m_list, p) == boost::end(m_list));
            if (not_found)
                m_list.push_back(p);
            return not_found;
        }

        void del(value_type p)
        {
            scoped_lock lock(m_mutex);

            BOOST_AUTO(const found, boost::find(m_list, p));
            if (found != boost::end(m_list))
                m_list.erase(found);
        }

        size_t size() const
        {
            scoped_lock lock(m_mutex);
            return m_list.size();
        }

    private:
        Container m_list;
        mutable Mutex m_mutex;
    };
}

#endif // SAFE_CONTAINER_1347008751
