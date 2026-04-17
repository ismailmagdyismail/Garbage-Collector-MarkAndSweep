#include "VMObjects.h"

#include <array>
#include <stdexcept>

unsigned long long VMObject::m_ullCreatedInstances = 0;

namespace
{
void TraceInt(VMObject * /*p_pVMObject*/, const std::function<void(VMObject *)> & /*p_fnVisitChild*/)
{
}

void TracePair(VMObject *p_pVMObject, const std::function<void(VMObject *)> &p_fnVisitChild)
{
    auto &pairVal = std::get<VMPair>(p_pVMObject->m_taggedUnionObject);
    p_fnVisitChild(pairVal.first);
    p_fnVisitChild(pairVal.second);
}

void TraceArray(VMObject *p_pVMObject, const std::function<void(VMObject *)> &p_fnVisitChild)
{
    auto &vecElements = std::get<VMArray>(p_pVMObject->m_taggedUnionObject);
    for (VMObject *pElement : vecElements)
    {
        p_fnVisitChild(pElement);
    }
}

void TraceString(VMObject * /*p_pVMObject*/, const std::function<void(VMObject *)> & /*p_fnVisitChild*/)
{
}

unsigned int DestroyObject(VMObject *p_pVMObject)
{
    delete p_pVMObject;
    return 1;
}

constexpr std::size_t OBJECT_TYPE_COUNT = 4;
}

const ObjectDescriptor &GetObjectDescriptor(EObjectType p_eObjectType)
{
    static const std::array<ObjectDescriptor, OBJECT_TYPE_COUNT> arrDescriptors{
        ObjectDescriptor{TraceInt, DestroyObject, "Int"},
        ObjectDescriptor{TracePair, DestroyObject, "Pair"},
        ObjectDescriptor{TraceArray, DestroyObject, "Array"},
        ObjectDescriptor{TraceString, DestroyObject, "String"}};

    const std::size_t uiIndex = static_cast<std::size_t>(p_eObjectType);
    if (uiIndex >= arrDescriptors.size())
    {
        throw std::runtime_error("Invalid VM Object type encountered");
    }

    return arrDescriptors[uiIndex];
}

VMObject *CreateIntObject(int p_iVal)
{
    VMObject *pvmObject = new VMObject;
    pvmObject->m_eObjectType = EObjectType::Int;
    pvmObject->m_taggedUnionObject = p_iVal;
    return pvmObject;
}

VMObject *CreatePairObject(VMObject *p_pFirst, VMObject *p_pSecond)
{
    VMObject *pvmObject = new VMObject;
    pvmObject->m_eObjectType = EObjectType::Pair;
    pvmObject->m_taggedUnionObject = std::make_pair(p_pFirst, p_pSecond);
    return pvmObject;
}

VMObject *CreateArrayObject(const VMArray &p_vecElements)
{
    VMObject *pvmObject = new VMObject;
    pvmObject->m_eObjectType = EObjectType::Array;
    pvmObject->m_taggedUnionObject = p_vecElements;
    return pvmObject;
}

VMObject *CreateStringObject(const VMString &p_strValue)
{
    VMObject *pvmObject = new VMObject;
    pvmObject->m_eObjectType = EObjectType::String;
    pvmObject->m_taggedUnionObject = p_strValue;
    return pvmObject;
}
