/* 
 * File:   NativeObject.hpp
 * Author: Konstantin
 *
 * Created on March 12, 2016, 3:31 PM
 */

#ifndef NATIVEOBJECT_HPP
#define	NATIVEOBJECT_HPP

#include <memory>

#include "IObject.hpp"
#include "IClass.hpp"

#include "ObjectClass.hpp"
#include "../Utility/Functions.hpp"

namespace hermes
{
    namespace object
    {        
        template <typename T>
        class NativeObject : public interface::IObject
        {
            public:
                typedef std::shared_ptr<T> nativeref_t;
                typedef interface::IObject object_t;
                typedef interface::IClass class_t;
                typedef std::shared_ptr<class_t> classref_t;
                typedef std::weak_ptr<IObject> weakref_t;
                typedef std::shared_ptr<IObject> reference_t;
                
                struct silent_t {};
                
            private:
                NativeObject(const class_t& c, const object_t& x) : m_value(), m_extern(x.copy()), m_class(c.self()), m_self(), m_parent()
                {
                    auto this_ptr = std::shared_ptr<IObject>(this, util::func::nodelete<IObject>);
                    m_self = this_ptr;
                    m_parent = this_ptr;
                }
            public:
                NativeObject(const T& x, silent_t) : m_value(new T(x)), m_extern(), m_class(), m_self(), m_parent() {}
                NativeObject(const T& x) : m_value(new T(x)), m_extern(), m_class(), m_self(), m_parent()
                {
                    auto this_ptr = std::shared_ptr<IObject>(this, util::func::nodelete<IObject>);
                    m_self = this_ptr;
                    m_parent = this_ptr;
                    m_class.reset(new ObjectClass<T>(*this));
                    m_class->self(m_class);
                }
                NativeObject(T&& x) : m_value(new T(x)), m_extern(), m_class(), m_self(), m_parent()
                {
                    auto this_ptr = std::shared_ptr<IObject>(this, util::func::nodelete<IObject>);
                    m_self = this_ptr;
                    m_parent = this_ptr;
                    m_class.reset(new ObjectClass<T>(*this));
                    m_class->self(m_class);
                }
                NativeObject(const object_t& x) : m_value(), m_extern(x.copy()), m_class(x.getClass().self()), m_self(m_extern), m_parent(m_extern) {}
                NativeObject(const NativeObject<T>& x) : m_value(), m_extern(), m_class(x.m_class), m_self(), m_parent()
                {
                    if (x.m_extern)
                    {
                        m_extern = x.m_extern->copy();
                    }
                    else
                    {
                        m_value.reset(new T(*x.m_value));
                    }
                    auto this_ptr = std::shared_ptr<IObject>(this, util::func::nodelete<IObject>);
                    m_self = this_ptr;
                    m_parent = this_ptr;
                }
                NativeObject(NativeObject<T>&& x) : m_value(x.m_value), m_extern(), m_class(x.m_class), m_self(), m_parent()
                {
                    operator=(x);
                    auto this_ptr = std::shared_ptr<IObject>(this, util::func::nodelete<IObject>);
                    m_self = this_ptr;
                    m_parent = this_ptr;
                }
                virtual ~NativeObject() {}
                virtual reference_t copy() const noexcept override
                {
                    if (m_extern)
                    {
                        return m_extern->copy();
                    }
                    else
                    {
                        std::shared_ptr<IObject> created (new NativeObject<T>(*this));
                        created->self(created);
                        created->parent(created);
                        return created;
                    }
                }
                virtual weakref_t self () const override
                {
                    return m_self;
                }
                virtual std::weak_ptr<IObject> parent () const override
                {
                    return m_parent;
                }
                virtual bool hasParent () const noexcept override
                {
                    return m_parent.owner_before(m_self) || m_self.owner_before(m_parent);
                }
                virtual const class_t& getClass () const noexcept override
                {
                    return *m_class;
                }
                virtual IObject& operator= (const IObject& x) override
                {
                    if (&x != this)
                    {
                        if (x.getClass() == *m_class)
                        {
                            const NativeObject<T>& ref = dynamic_cast<const NativeObject<T>&>(x);
                            m_value = std::make_shared<T>(*ref.m_value);
                            m_extern.reset();
                        }
                        else
                        {
                            m_value.reset();
                            m_extern = x.copy();
                            m_class = x.getClass().self();
                        }
                    }
                    return *this;
                }
                virtual IObject& operator= (IObject&& x) override
                {
                    if (x.getClass() == *m_class)
                    {
                        const NativeObject<T>& ref = dynamic_cast<const NativeObject<T>&>(x);
                        m_value = std::make_shared<T>(*ref.m_value);
                        m_extern.reset();
                    }
                    else
                    {
                        m_value.reset();
                        m_extern = x.copy();
                        m_class = x.getClass().self();
                    }
                    return *this;
                }
                virtual IObject& reference() noexcept override
                {
                    if (m_extern)
                    {
                        return *m_extern;
                    }
                    else
                    {
                        return *this;
                    }
                }
                virtual const IObject& reference() const noexcept override
                {
                    if (m_extern)
                    {
                        return *m_extern;
                    }
                    else
                    {
                        return *this;
                    }
                }
                const T& value() const
                {
                    return *m_value;
                }
                T& value()
                {
                    return *m_value;
                }
                virtual void parent (const std::shared_ptr<IObject>& x) override
                {
                    m_parent = x;
                }
                virtual void self (const std::shared_ptr<IObject>& x) override
                {
                    m_self = x;
                }
                virtual void setClass (class_t& x) override
                {
                    if (x.prototype().type() == &typeid(NativeObject<T>))
                    {
                        m_class = x.self();
                    }
                }
                virtual const std::type_info* type() const noexcept
                {
                    if (m_extern)
                    {
                        return m_extern->type();
                    }
                    else
                    {
                        return &typeid(NativeObject<T>);
                    }
                }
                virtual void* pointer() noexcept override
                {
                    if (m_extern)
                    {
                        return m_extern->pointer();
                    }
                    else
                    {
                        return m_value.get();
                    }
                }
                virtual const void* pointer() const noexcept override
                {
                    if (m_extern)
                    {
                        return m_extern->pointer();
                    }
                    else
                    {
                        return m_value.get();
                    }
                }
            private:
                nativeref_t m_value;
                reference_t m_extern;
                classref_t m_class;
                weakref_t m_self;
                weakref_t m_parent;
        };
    }
}

#endif	/* NATIVEOBJECT_HPP */

