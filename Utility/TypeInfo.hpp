/* 
 * File:   TypeInfo.hpp
 * Author: Konstantin
 *
 * Created on March 2, 2016, 10:52 AM
 */

#ifndef TYPEINFO_HPP
#define	TYPEINFO_HPP

#pragma once

#include <memory>

namespace hermes
{
    namespace util
    {
        typedef size_t unique_t;

        template <typename Class, typename T, size_t ID = 0>
        static std::shared_ptr<T> GetGlobalInstance () noexcept
        {
            static std::shared_ptr<T> global_instance;
            if (!global_instance)
            {
                global_instance.reset(new T());
            }
            return global_instance;
        }

        struct RuntimeTypeInformation
        {
            typedef RuntimeTypeInformation this_t;
            
            static unique_t CreateUniqueId () noexcept
            {
                static auto unique_id = GetGlobalInstance<this_t, unique_t>();
                return ++(*unique_id);
            }

            static unique_t CurrentUniqueId () noexcept
            {
                static auto unique_id = GetGlobalInstance<this_t, unique_t>();
                return *unique_id;
            }
        };
        
        template <typename Ret, typename... Args>
        struct NativeFunctionWrapper
        {
            typedef NativeFunctionWrapper this_t;
        public:
            NativeFunctionWrapper()
            {};
        };
        
        struct TypeInformation
        {
            
        };
    }
}

#endif	/* TYPEINFO_HPP */

