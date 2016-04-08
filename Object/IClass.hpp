/* 
 * File:   IClass.hpp
 * Author: Konstantin
 *
 * Created on March 12, 2016, 2:46 PM
 */

#ifndef ICLASS_HPP
#define	ICLASS_HPP

#include <memory>
#include <iostream>

#include "Interfaces.hpp"

namespace hermes
{
    namespace interface
    {
        struct IClass
        {
        public:
            virtual ~IClass() {}
            virtual std::shared_ptr<IClass> self() const noexcept = 0;
            virtual void self(const std::shared_ptr<IClass>& x) noexcept = 0;
            virtual const IObject& prototype() const noexcept = 0;
            virtual void prototype(const IObject& x) noexcept = 0;
            virtual bool operator== (const IClass& x) const noexcept = 0;
            virtual const INamespace& getNamespace() const noexcept = 0;
            virtual void setNamespace(const INamespace& x) = 0;
            virtual std::shared_ptr<IObject> operator() () const noexcept = 0;
            virtual std::ostream& saveBinary(std::ostream& s) const noexcept = 0;
            virtual std::istream& loadBinary(std::istream& s) noexcept = 0;
            virtual std::ostream& saveBinary(std::ostream& s, const IObject& o) const = 0;
            virtual std::istream& loadBinary(std::istream& s, IObject& o) = 0;
            virtual size_t id() const noexcept = 0;
            virtual void id (size_t x) noexcept = 0;
        };
    }
}

#endif	/* ICLASS_HPP */

