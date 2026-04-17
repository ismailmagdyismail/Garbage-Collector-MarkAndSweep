#pragma once

//! System includes
#include <vector>
#include <variant>

struct VMObject;

using VMInt = int;
using VMPair = std::pair<VMObject *, VMObject *>;

//! Could be changed to IVMObject with Mark() = 0, with two subclasses [VMInt, VMPair]
//! And use strategy pattern, each sub class
//! But we are using Visitor like pattern instead, since this will mostly be just a data container.
//! Variability will be in terms of behhaviour not data, so we will use visitor / Separate data from behaviour.
struct VMObject
{
    VMObject()
    {
        m_ullCreatedInstances++;
    }

    ~VMObject()
    {
        m_ullCreatedInstances--;
    }

    // void accept(IVisitor);
    bool m_bMarked{false};
    std::variant<VMInt, VMPair> m_taggedUnionObject;
    static unsigned long long m_ullCreatedInstances;
};