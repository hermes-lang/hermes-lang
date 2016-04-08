/* 
 * File:   NativeClass.hpp
 * Author: Konstantin
 *
 * Created on March 14, 2016, 1:42 PM
 */

#ifndef OBJECTCLASS_HPP
#define	OBJECTCLASS_HPP

#include "IClass.hpp"
#include "INamespace.hpp"
#include "../Utility/Endian.hpp"
#include "../Utility/Functions.hpp"
#include "IObject.hpp"

namespace hermes
{
    namespace object
    {
        template <typename T>
        T& cast (hermes::interface::IObject& x)
        {
            return *reinterpret_cast<T*>(x.pointer());
        }

        template <typename T>
        const T& cast (const hermes::interface::IObject& x)
        {
            return *reinterpret_cast<const T*>(x.pointer());
        }

        template <typename T>
        inline std::ostream& writeObject (std::ostream& s, const interface::IObject& o);
        
        template <typename T>
        inline
        typename std::enable_if<std::is_fundamental<T>::value, std::ostream&>::type writeObject (std::ostream& s, const interface::IObject& o)
        {
            util::endian::Serializable<T> object (cast<const T>(o.reference()));
            object.serialize();
            s.write(object.c_str, object.size);
        }
        
        template <>
        inline
        std::ostream& writeObject<std::string> (std::ostream& s, const interface::IObject& o)
        {
            const std::string& str = cast<const std::string>(o.reference());
            util::endian::Serializable<size_t> size (str.size());
            size.serialize();
            s.write(size.c_str, size.size);
            s.write(str.c_str(), str.size());
        }
        
        template <typename T>
        inline std::istream& readObject (std::istream& s, interface::IObject& o);
        
        template <typename T>
        inline
        typename std::enable_if<std::is_fundamental<T>::value, std::istream&>::type readObject (std::istream& s, interface::IObject& o)
        {
            util::endian::Serializable<T> object;
            s.read(object.c_str, object.size);
            object.serialize();
            cast<T&>(o.reference()) = object.value;
        }
        
        template <>
        inline
        std::istream& readObject<std::string> (std::istream& s, interface::IObject& o)
        {
            std::string& str = cast<std::string>(o.reference());
            util::endian::Serializable<size_t> size (str.size());
            s.read(size.c_str, size.size);
            size.serialize();
            char* buffer = new char[size.value];
            s.read(buffer, size.value);
            buffer[size.size] = 0;
            str = buffer;
        }
        
        template <typename T>
        class ObjectClass : public interface::IClass
        {
            typedef interface::IObject object_t;
            typedef interface::IClass class_t;
            typedef interface::INamespace namespace_t;
            typedef std::shared_ptr<object_t> objectref_t;
            typedef std::shared_ptr<class_t> classref_t;
            typedef std::weak_ptr<class_t> weakclassref_t;
            typedef std::shared_ptr<namespace_t> namespaceref_t;
            public:
                ObjectClass() : m_namespace(), m_self(), m_proto(), m_id() {}
                ObjectClass(const object_t& o) : m_namespace(), m_self(), m_proto(o.copy()), m_id()
                {
                    m_proto->setClass(*this);
                }
                ObjectClass(const object_t& o, const namespace_t& ns) : m_namespace(ns.self()), m_self(), m_proto(o.copy()), m_id() {}
                virtual ~ObjectClass() {}
                virtual classref_t self() const noexcept override
                {
                    return m_self.lock();
                }
                virtual const object_t& prototype() const noexcept
                {
                    return *m_proto;
                }
                virtual bool operator== (const class_t& c) const noexcept override
                {
                    return (m_proto->type() == c.prototype().type());
                }
                virtual const namespace_t& getNamespace() const noexcept override
                {
                    return *m_namespace;
                }
                virtual void setNamespace(const namespace_t& ns) override
                {
                    m_namespace = ns.self();
                }
                virtual void self(const classref_t& x) noexcept override
                {
                    m_self = x;
                }
                virtual void prototype(const object_t& x) noexcept override
                {
                    m_proto = x.copy();
                    m_proto->setClass(*this);
                }
                virtual objectref_t operator() () const noexcept override
                {
                    return m_proto->copy();
                }
                virtual std::ostream& saveBinary(std::ostream& s) const noexcept override
                {
                    util::endian::Serializable<size_t> 
                    return writeObject<T>(s, *m_proto);
                }
                virtual std::istream& loadBinary(std::istream& s) noexcept override
                {
                    return readObject<T>(s, *m_proto);
                }
                virtual std::ostream& saveBinary(std::ostream& s, const object_t& o) const override
                {
                    if (o.getClass() == *this)
                    {
                        return writeObject<T>(s, o);
                    }
                    else
                    {
                        throw std::bad_cast();
                    }
                }
                virtual std::istream& loadBinary(std::istream& s, object_t& o) override
                {
                    if (o.getClass() == *this)
                    {
                        return readObject<T>(s, o);
                    }
                    else
                    {
                        throw std::bad_cast();
                    }
                }
                virtual size_t id() const noexcept override
                {
                    return m_id;
                }
                virtual void id (size_t x) noexcept override
                {
                    m_id = x;
                }
            private:
                namespaceref_t m_namespace;
                weakclassref_t m_self;
                objectref_t m_proto;
                size_t m_id;
        };
    }
}

#endif	/* OBJECTCLASS_HPP */

