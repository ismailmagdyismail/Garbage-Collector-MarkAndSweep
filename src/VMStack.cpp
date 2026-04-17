//! System includes
#include <cassert>

//! VM Includes
#include "VMStack.h"
#include "VMObjects.h"

VMStack::VMStack(unsigned int p_uiMaxStackSize)
    : m_uiMaxStackSize{p_uiMaxStackSize}
{
    m_arrObjectsStack = new VMObject *[m_uiMaxStackSize];
}

VMStack::~VMStack()
{
    PopAll();
    delete[] m_arrObjectsStack;
}

void VMStack::Push(VMObject *p_oVMObject)
{
    assert(m_uiIndex < m_uiMaxStackSize);
    m_arrObjectsStack[m_uiIndex] = p_oVMObject;
    ++m_uiIndex;
}

VMObject *VMStack::Pop()
{
    assert(m_uiIndex > 0);
    VMObject *pObject = m_arrObjectsStack[m_uiIndex];
    --m_uiIndex;
    return pObject;
}

void VMStack::PopAll()
{
    m_uiIndex = 0;
}

std::vector<VMObject *> VMStack::GetReachableObjects()
{
    std::vector<VMObject *> vecReachableObjects;
    vecReachableObjects.reserve(m_uiIndex);
    for (unsigned int i = 0; i < m_uiIndex; ++i)
    {
        vecReachableObjects.push_back(m_arrObjectsStack[i]);
    }
    return vecReachableObjects;
}