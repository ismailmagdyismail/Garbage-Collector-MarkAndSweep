#pragma once

//! System Includes
#include <list>

//! VM includes
#include "VMStack.h"

class VMObject;

class VM
{
public:
    VM();
    ~VM();
    void AllocateObject(VMObject *p_oObject);

private:
    void DeAllocateAll();

    std::list<VMObject *> m_listAllocatedObjects;
    VMStack m_oVMStack;
};