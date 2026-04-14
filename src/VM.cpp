//! VM Includes
#include "VM.h"
#include "VMObjects.h"

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
    m_oVMStack.PopAll();
    while (!m_listAllocatedObjects.empty())
    {
        delete m_listAllocatedObjects.back();
        m_listAllocatedObjects.pop_back();
    }
}