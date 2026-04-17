//! VM Includes
#include "VM.h"
#include "GarbageCollector.h"

#define MAX_STACK_SIZE 50000

VM::VM(unsigned int p_uiMaxAllocationThreshold)
    : m_uiMaxAllocationThreshold(p_uiMaxAllocationThreshold), m_oVMStack(MAX_STACK_SIZE)
{
}

VM::~VM()
{
    DeAllocateAll();
}

VMObject *VM::CreateInt(int p_iValue)
{
    return RegisterAllocation(new VMIntObject(p_iValue));
}

VMObject *VM::CreatePair(VMObject *p_pFirst, VMObject *p_pSecond)
{
    return RegisterAllocation(new VMPairObject(p_pFirst, p_pSecond));
}

VMObject *VM::CreateArray(const std::vector<VMObject *> &p_vecElements)
{
    return RegisterAllocation(new VMArrayObject(p_vecElements));
}

VMObject *VM::CreateString(const std::string &p_strValue)
{
    return RegisterAllocation(new VMStringObject(p_strValue));
}

VMObject *VM::RegisterAllocation(VMObject *p_pVMObject)
{
    if (m_listAllocatedObjects.size() >= m_uiMaxAllocationThreshold)
    {
        GarbageCollector::Mark(m_oVMStack.GetReachableObjects());
        GarbageCollector::Sweep(m_listAllocatedObjects);
    }
    m_listAllocatedObjects.push_back(p_pVMObject);
    m_oVMStack.Push(p_pVMObject);
    return p_pVMObject;
}

void VM::DeAllocateAll()
{
    //! Removes Stack access to any of the allocated elements
    PopStack();

    //! Garbage collect any remaining Elements.
    while (!m_listAllocatedObjects.empty())
    {
        GarbageCollector::ReclaimElement(m_listAllocatedObjects.back());
        m_listAllocatedObjects.pop_back();
    }
}

void VM::PopStack()
{
    m_oVMStack.PopAll();
}
