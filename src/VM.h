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
    void PopStack();

    struct AllocationResult
    {
        bool m_bSuccess;
        VMObject *m_pAllocatedObject;
        unsigned int m_uiGarbageCollectedObjectsCount{0};
    };

    //! Memory Allocatation Management.
    //! Could be its own module / Builder maybe.
    AllocationResult CreateIntObject(int p_iVal);
    AllocationResult CreatePairObject(VMObject *p_pFirst, VMObject *p_pSecond);

private:
    AllocationResult AllocateObject(VMObject *p_oObject);
    void DeAllocateAll();

    unsigned int m_uiMaxAllocationThreshold;
    std::list<VMObject *> m_listAllocatedObjects;
    VMStack m_oVMStack;
};