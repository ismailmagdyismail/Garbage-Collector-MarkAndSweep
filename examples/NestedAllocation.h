#pragma once

//! System Includes
#include <iostream>

//! VM includes
#include "VM.h"
#include "VMObjects.h"

inline void NestedObjects()
{
    VM oVM(10000);
    VMObject *object1 = oVM.CreateIntObject(1).m_pAllocatedObject;
    VMObject *pair1 = oVM.CreatePairObject(oVM.CreateIntObject(3).m_pAllocatedObject, oVM.CreateIntObject(4).m_pAllocatedObject).m_pAllocatedObject;
    VMObject *pair2 = oVM.CreatePairObject(
                             oVM.CreatePairObject(oVM.CreateIntObject(5).m_pAllocatedObject, oVM.CreateIntObject(6).m_pAllocatedObject).m_pAllocatedObject,
                             oVM.CreateIntObject(7).m_pAllocatedObject)
                          .m_pAllocatedObject;
    VMObject *object2 = oVM.CreatePairObject(pair1, pair2).m_pAllocatedObject;

    static_cast<void>(object1);
    static_cast<void>(object2);
    std::cout << "[nested] root_objects=2\n";
    std::cout << "[nested] nested_pairs=3\n";
    std::cout << "[nested] total_live_vm_objects_during_run=" << VMObject::m_ullCreatedInstances << '\n';
}
