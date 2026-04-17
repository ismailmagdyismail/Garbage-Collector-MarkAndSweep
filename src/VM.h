#pragma once

//! System Includes
#include <list>
#include <string>
#include <vector>

//! VM includes
#include "VMStack.h"
#include "VMObjects.h"

class VM
{
public:
    VM(unsigned int p_uiMaxAllocationThreshold);
    ~VM();

    VMObject *CreateInt(int p_iValue);
    VMObject *CreatePair(VMObject *p_pFirst, VMObject *p_pSecond);
    VMObject *CreateArray(const std::vector<VMObject *> &p_vecElements);
    VMObject *CreateString(const std::string &p_strValue);

    void PopStack();

private:
    VMObject *AllocateObject(VMObject *p_pObject);
    void DeAllocateAll();

    unsigned int m_uiMaxAllocationThreshold;
    std::list<VMObject *> m_listAllocatedObjects;
    VMStack m_oVMStack;
};
