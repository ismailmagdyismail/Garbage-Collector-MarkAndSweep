#include "VMObjects.h"

unsigned long long VMObject::m_ullCreatedInstances = 0;

VMObject::VMObject()
{
    ++m_ullCreatedInstances;
}

VMObject::~VMObject()
{
    --m_ullCreatedInstances;
}

VMIntObject::VMIntObject(int p_iVal)
    : m_iValue(p_iVal)
{
}

void VMIntObject::Trace(const std::function<void(VMObject *)> & /*p_fnVisitChild*/)
{
}

VMPairObject::VMPairObject(VMObject *p_pFirst, VMObject *p_pSecond)
    : m_pFirst(p_pFirst), m_pSecond(p_pSecond)
{
}

void VMPairObject::Trace(const std::function<void(VMObject *)> &p_fnVisitChild)
{
    p_fnVisitChild(m_pFirst);
    p_fnVisitChild(m_pSecond);
}

VMArrayObject::VMArrayObject(std::vector<VMObject *> p_vecElements)
    : m_vecElements(std::move(p_vecElements))
{
}

void VMArrayObject::Trace(const std::function<void(VMObject *)> &p_fnVisitChild)
{
    for (VMObject *pObject : m_vecElements)
    {
        p_fnVisitChild(pObject);
    }
}

VMStringObject::VMStringObject(std::string p_strValue)
    : m_strValue(std::move(p_strValue))
{
}

void VMStringObject::Trace(const std::function<void(VMObject *)> & /*p_fnVisitChild*/)
{
}
