#pragma once

//! System includes
#include <functional>
#include <string>
#include <vector>
#include <variant>

struct VMObject;

using VMInt = int;
using VMPair = std::pair<VMObject *, VMObject *>;
using VMArray = std::vector<VMObject *>;
using VMString = std::string;

enum class EObjectType
{
    Int,
    Pair,
    Array,
    String
};

struct ObjectDescriptor
{
    void (*m_fnTrace)(VMObject *p_pVMObject, const std::function<void(VMObject *)> &p_fnVisitChild);
    unsigned int (*m_fnDestroy)(VMObject *p_pVMObject);
    const char *m_szName;
};

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

    bool m_bMarked{false};
    EObjectType m_eObjectType;
    std::variant<VMInt, VMPair, VMArray, VMString> m_taggedUnionObject;
    static unsigned long long m_ullCreatedInstances;
};

const ObjectDescriptor &GetObjectDescriptor(EObjectType p_eObjectType);

VMObject *CreateIntObject(int p_iVal);
VMObject *CreatePairObject(VMObject *p_pFirst, VMObject *p_pSecond);
VMObject *CreateArrayObject(const VMArray &p_vecElements);
VMObject *CreateStringObject(const VMString &p_strValue);
