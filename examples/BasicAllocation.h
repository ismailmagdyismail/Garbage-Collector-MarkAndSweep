#pragma once

//! System Includes
#include <iostream>

//! VM includes
#include "VM.h"
#include "VMObjects.h"

inline void BasicAllocation()
{
    VM oVM(1000);
    VMObject *object1 = oVM.CreateIntObject(1).m_pAllocatedObject;
    VMObject *object2 = oVM.CreatePairObject(oVM.CreateIntObject(3).m_pAllocatedObject, oVM.CreateIntObject(4).m_pAllocatedObject).m_pAllocatedObject;

    static_cast<void>(object1);
    static_cast<void>(object2);

    std::cout << "[basic] root_objects=2\n";
    std::cout << "[basic] total_live_vm_objects_during_run=" << VMObject::m_ullCreatedInstances << '\n';
}
