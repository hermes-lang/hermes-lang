/* 
 * File:   INamespace.hpp
 * Author: Konstantin
 *
 * Created on March 13, 2016, 8:58 PM
 */

#ifndef INAMESPACE_HPP
#define	INAMESPACE_HPP

#include "Interfaces.hpp"

namespace hermes
{
    namespace interface
    {
        struct INamespace
        {
            virtual ~INamespace() {}
            virtual std::shared_ptr<INamespace> self() const noexcept = 0;
            virtual INamespace& reference() noexcept = 0;
            virtual const INamespace& reference() const noexcept = 0;
        };
    }
}

#endif	/* INAMESPACE_HPP */

