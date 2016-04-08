/* 
 * File:   IObject.hpp
 * Author: Konstantin
 *
 * Created on March 12, 2016, 2:33 PM
 */

#ifndef IOBJECT_HPP
#define	IOBJECT_HPP

#include <memory>
#include <typeinfo>

#include "Interfaces.hpp"

namespace hermes
{    
    namespace interface
    {
        struct IObject
        {
        public:
            virtual ~IObject () { }
            virtual std::shared_ptr<IObject> copy() const noexcept = 0;
            virtual std::weak_ptr<IObject> self () const = 0;
            virtual std::weak_ptr<IObject> parent () const = 0;
            virtual bool hasParent () const noexcept = 0;
            virtual const IClass& getClass () const noexcept = 0;
            virtual IObject& operator= (const IObject& x) = 0;
            virtual IObject& operator= (IObject&& x) = 0;
            virtual IObject& reference() noexcept = 0;
            virtual const IObject& reference() const noexcept = 0;
            virtual void parent (const std::shared_ptr<IObject>& x) = 0;
            virtual void self (const std::shared_ptr<IObject>& x) = 0;
            virtual void setClass (IClass& x) = 0;
            virtual const std::type_info* type() const noexcept = 0;
            virtual void* pointer() noexcept = 0;
            virtual const void* pointer() const noexcept = 0;
        };
    }
}

#endif	/* IOBJECT_HPP */

