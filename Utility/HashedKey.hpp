/* 
 * File:   HashedKey.hpp
 * Author: Konstantin
 *
 * Created on March 12, 2016, 2:04 PM
 */

#ifndef HASHEDKEY_HPP
#define	HASHEDKEY_HPP

#include <functional>

namespace hermes
{
    namespace util
    {

        template <typename T, typename H = std::hash<T>>
        class HashedKey
        {
            typedef T key_t;
            typedef H hasher_t;
            typedef decltype(std::declval<hasher_t>()(std::declval<key_t>())) hash_t;
        public:
            
            template <typename... Args>
            HashedKey (Args&&... args, hasher_t h = hasher_t ()) : m_key(std::forward<Args>(args)...), m_hasher(h), m_hash(m_hasher(m_key)) { }

            HashedKey (hasher_t h = hasher_t ()) : m_key (), m_hasher (h), m_hash (m_hasher (m_key)) { }

            HashedKey (const key_t& x, hasher_t h = hasher_t ()) : m_key (x), m_hasher (h), m_hash (m_hasher (x)) { }

            HashedKey (key_t&& x, hasher_t h = hasher_t ()) : m_key (x), m_hasher (h), m_hash (m_hasher (x)) { }

            HashedKey (const hash_t& x) : m_key (), m_hasher (), m_hash (x) { }

            HashedKey (hash_t&& x) : m_key (), m_hasher (), m_hash (x) { }

            ~HashedKey () { }

            HashedKey& operator= (const key_t& x)
            {
                m_key = x;
                m_hash = m_hasher(x);
            }

            HashedKey& operator= (key_t&& x)
            {
                m_key = x;
                m_hash = m_hasher(x);
            }

            HashedKey& operator= (const hash_t& x)
            {
                m_key = key_t();
                m_hash = x;
            }

            HashedKey& operator= (hash_t&& x)
            {
                m_key = key_t();
                m_hash = x;
            }

            const key_t& key () const noexcept
            {
                return m_key;
            }

            const hasher_t& hasher () const noexcept
            {
                return m_hasher;
            }

            const hash_t& hash () const noexcept
            {
                return m_hash;
            }
        private:
            key_t m_key;
            hasher_t m_hasher;
            hash_t m_hash;
        };
        
        template <typename T, typename H>
        bool operator< (const HashedKey<T, H>& l, const HashedKey<T, H>& r)
        {
            return l.hash() < r.hash();
        }
        
        template <typename T, typename H>
        bool operator> (const HashedKey<T, H>& l, const HashedKey<T, H>& r)
        {
            return l.hash() > r.hash();
        }
        
        template <typename T, typename H>
        bool operator== (const HashedKey<T, H>& l, const HashedKey<T, H>& r)
        {
            return l.hash() == r.hash();
        }
        
        template <typename T, typename H>
        bool operator<= (const HashedKey<T, H>& l, const HashedKey<T, H>& r)
        {
            return l.hash() <= r.hash();
        }
        
        template <typename T, typename H>
        bool operator>= (const HashedKey<T, H>& l, const HashedKey<T, H>& r)
        {
            return l.hash() >= r.hash();
        }
        
        template <typename T, typename H>
        bool operator!= (const HashedKey<T, H>& l, const HashedKey<T, H>& r)
        {
            return l.hash() != r.hash();
        }
    }
}

#endif	/* HASHEDKEY_HPP */

