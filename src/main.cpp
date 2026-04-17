//! System includes
#include <iostream>
#include <vector>

//! VM Includes
#include "VM.h"
#include "VMObjects.h"

void BasicAllocation()
{
    VM oVM(1000);
    VMObject *object1 = oVM.CreateInt(1);
    VMObject *object2 = oVM.CreatePair(oVM.CreateInt(3), oVM.CreateInt(4));

    static_cast<void>(object1);
    static_cast<void>(object2);
}

void NestedObjects()
{
    VM oVM(10000);
    VMObject *object1 = oVM.CreateInt(1);
    VMObject *object2 = oVM.CreatePair(
        oVM.CreatePair(oVM.CreateInt(3), oVM.CreateInt(4)),
        oVM.CreatePair(oVM.CreatePair(oVM.CreateInt(5), oVM.CreateInt(6)), oVM.CreateInt(7)));

    static_cast<void>(object1);
    static_cast<void>(object2);
}

void NewTypesRegisterThroughDescriptors()
{
    VM oVM(10000);
    VMObject *object1 = oVM.CreateString("root");
    VMObject *object2 = oVM.CreateArray({oVM.CreateInt(10), oVM.CreateInt(20), oVM.CreatePair(oVM.CreateInt(30), object1)});

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
    oVM.CreateInt(1);
    oVM.CreateInt(2);
    oVM.CreateInt(3);
    oVM.CreateInt(4);
    oVM.CreateInt(5);
    oVM.CreateInt(6);
    oVM.PopStack();
    oVM.CreateInt(7);
    oVM.CreateInt(8);
    std::cout << "Descriptor-based GC run complete" << std::endl;
}

int main()
{
    TestDestructionReclaimation();
    NewTypesRegisterThroughDescriptors();
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
