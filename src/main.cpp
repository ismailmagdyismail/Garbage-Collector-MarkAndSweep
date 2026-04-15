//! System includes
#include <iostream>

//! VM Includes
#include "VM.h"
#include "VMObjects.h"

void BasicAllocation()
{
    VM oVM(1000);
    VMObject *object1 = CreateIntObject(1);
    VMObject *object2 = CreatePairObject(CreateIntObject(3), CreateIntObject(4));

    oVM.AllocateObject(object1);
    oVM.AllocateObject(object2);
}

void NestedObjects()
{
    VM oVM(10000);
    VMObject *object1 = CreateIntObject(1);
    VMObject *object2 = CreatePairObject(
        CreatePairObject(CreateIntObject(3), CreateIntObject(4)),
        CreatePairObject(CreatePairObject(CreateIntObject(5), CreateIntObject(6)), CreateIntObject(7)));

    oVM.AllocateObject(object1);
    oVM.AllocateObject(object2);
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
    uiGCCollections += oVM.AllocateObject(CreateIntObject(1));
    uiGCCollections += oVM.AllocateObject(CreateIntObject(2));
    uiGCCollections += oVM.AllocateObject(CreateIntObject(3));
    uiGCCollections += oVM.AllocateObject(CreateIntObject(4));
    uiGCCollections += oVM.AllocateObject(CreateIntObject(5));
    uiGCCollections += oVM.AllocateObject(CreateIntObject(6));
    oVM.PopStack();
    uiGCCollections += oVM.AllocateObject(CreateIntObject(7));
    uiGCCollections += oVM.AllocateObject(CreateIntObject(8));
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