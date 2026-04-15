//! VM Includes
#include "VM.h"
#include "VMObjects.h"
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

unsigned int VM::AllocateObject(VMObject *p_pVMObject)
{
    unsigned int uiGCCollectedElements{0};
    if (m_listAllocatedObjects.size() >= m_uiMaxAllocationThreshold)
    {
        GarbageCollector::Mark(m_oVMStack.GetReachableObjects());
        uiGCCollectedElements = GarbageCollector::Sweep(m_listAllocatedObjects);
    }
    m_listAllocatedObjects.push_back(p_pVMObject);
    m_oVMStack.Push(p_pVMObject);
    return uiGCCollectedElements;
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