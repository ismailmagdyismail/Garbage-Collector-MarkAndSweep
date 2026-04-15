#pragma once

//! System Includes
#include <list>

//! VM includes
#include "VMStack.h"

struct VMObject;

class VM
{
public:
    VM(unsigned int p_uiMaxAllocationThreshold);
    ~VM();
    unsigned int AllocateObject(VMObject *p_oObject);

private:
    void DeAllocateAll();

    unsigned int m_uiMaxAllocationThreshold;
    std::list<VMObject *> m_listAllocatedObjects;
    VMStack m_oVMStack;
};