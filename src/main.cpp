//! System includes
#include <iostream>

//! VM Includes
#include "VM.h"
#include "VMObjects.h"

void BasicAllocation()
{
    VM oVM;
    VMObject *object1 = CreateIntObject(1);
    VMObject *object2 = CreatePairObject(CreateIntObject(3), CreateIntObject(4));

    oVM.AllocateObject(object1);
    oVM.AllocateObject(object2);
}

void NestedObjects()
{
    VM oVM;
    VMObject *object1 = CreateIntObject(1);
    VMObject *object2 = CreatePairObject(
        CreatePairObject(CreateIntObject(3), CreateIntObject(4)),
        CreatePairObject(CreatePairObject(CreateIntObject(5), CreateIntObject(6)), CreateIntObject(7)));

    oVM.AllocateObject(object1);
    oVM.AllocateObject(object2);
}

int main()
{
    BasicAllocation();
    NestedObjects();

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