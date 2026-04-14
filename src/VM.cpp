//! VM Includes
#include "VM.h"
#include "VMObjects.h"
#include "GarbageCollector.h"

#define MAX_STACK_SIZE 50000

VM::VM()
    : m_oVMStack(50000)
{
}

VM::~VM()
{
    DeAllocateAll();
}

void VM::AllocateObject(VMObject *p_pVMObject)
{
    m_listAllocatedObjects.push_back(p_pVMObject);
    m_oVMStack.Push(p_pVMObject);
}

void VM::DeAllocateAll()
{
    //! Removes Stack access to any of the allocated elements
    m_oVMStack.PopAll();

    //! Garbage collect any remaining Elements.
    while (!m_listAllocatedObjects.empty())
    {
        GarbageCollector::ReclaimElement(m_listAllocatedObjects.back());
        m_listAllocatedObjects.pop_back();
    }
}