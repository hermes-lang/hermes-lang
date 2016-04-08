/* 
 * File:   Externalizer.hpp
 * Author: Konstantin
 *
 * Created on March 30, 2016, 11:21 AM
 */

#ifndef EXTERNALIZER_HPP
#define	EXTERNALIZER_HPP

#include "../Object/Interfaces.hpp"
#include "../Object/NativeObject.hpp"
#include "../Object/ObjectClass.hpp"

namespace hermes
{
    namespace ext
    {
        template <typename T, typename Key, typename Hasher = std::hash<T>>
        std::shared_ptr<interface::IClass> createClass (Key&& _key)
        {
            typedef interface::IClass class_t;
            typedef interface::IObject object_t;
            typedef std::shared_ptr<class_t> classref_t;
            typedef std::shared_ptr<object_t> objectref_t;
            typedef object::NativeObject<T> object_impl;
            typedef object::ObjectClass<T> class_impl;
            
            static Hasher hasher;
            
            class_t* class_ptr = new class_impl;
            class_t& class_ref = *class_ptr;
            classref_t classRef (class_ptr);
            class_ref.self(classRef);
            class_ref.prototype(object_impl(T(), typename object_impl::silent_t()));
            class_ref.id(hasher(std::forward<Key>(_key)));
            return classRef;
        }
    }
}

#endif	/* EXTERNALIZER_HPP */

