//! System includes
#include <iostream>

//! VM Includes
#include "VM.h"
#include "VMObjects.h"

void BasicAllocation()
{
    VM oVM(1000);
    VMObject *object1 = oVM.CreateIntObject(1).m_pAllocatedObject;
    VMObject *object2 = oVM.CreatePairObject(oVM.CreateIntObject(3).m_pAllocatedObject, oVM.CreateIntObject(4).m_pAllocatedObject).m_pAllocatedObject;

    //! Not used
    static_cast<void>(object1);
    static_cast<void>(object2);
}

void NestedObjects()
{
    VM oVM(10000);
    VMObject *object1 = oVM.CreateIntObject(1).m_pAllocatedObject;
    VMObject *pair1 = oVM.CreatePairObject(oVM.CreateIntObject(3).m_pAllocatedObject, oVM.CreateIntObject(4).m_pAllocatedObject).m_pAllocatedObject;
    VMObject *pair2 = oVM.CreatePairObject(
                             oVM.CreatePairObject(oVM.CreateIntObject(5).m_pAllocatedObject, oVM.CreateIntObject(6).m_pAllocatedObject).m_pAllocatedObject,
                             oVM.CreateIntObject(7).m_pAllocatedObject)
                          .m_pAllocatedObject;
    VMObject *object2 = oVM.CreatePairObject(pair1, pair2).m_pAllocatedObject;

    //! Not Used
    static_cast<void>(object1);
    static_cast<void>(object2);
}

void TestDestructionReclaimation()
{
    BasicAllocation();
    NestedObjects();
}

void TestGCPause()
{
    VM oVM(2);
    unsigned int uiGCCollections = 0;
    uiGCCollections += oVM.CreateIntObject(1).m_uiGarbageCollectedObjectsCount;
    uiGCCollections += oVM.CreateIntObject(2).m_uiGarbageCollectedObjectsCount;
    uiGCCollections += oVM.CreateIntObject(3).m_uiGarbageCollectedObjectsCount;
    uiGCCollections += oVM.CreateIntObject(4).m_uiGarbageCollectedObjectsCount;
    uiGCCollections += oVM.CreateIntObject(5).m_uiGarbageCollectedObjectsCount;
    uiGCCollections += oVM.CreateIntObject(6).m_uiGarbageCollectedObjectsCount;
    oVM.PopStack();
    uiGCCollections += oVM.CreateIntObject(7).m_uiGarbageCollectedObjectsCount;
    uiGCCollections += oVM.CreateIntObject(8).m_uiGarbageCollectedObjectsCount;
    std::cout << "Total GC Objects ReClaimations = " << uiGCCollections << std::endl;
}

int main()
{
    TestDestructionReclaimation();
    TestGCPause();

    std::cout << "Number of VM Objects' Instances Remaining = " << VMObject::m_ullCreatedInstances << std::endl;
    if (VMObject::m_ullCreatedInstances > 0)
    {
        std::cout << "Leak Detected" << std::endl;
    }
    else
    {
        std::cout << "No Leak Detected" << std::endl;
    }
}