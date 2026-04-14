//! System includes
#include <iostream>

//! VM Includes
#include "VM.h"
#include "VMObjects.h"

int main()
{
    VM oVM;
    VMObject *object = new VMObject;
    object->m_taggedUnionObject = 1;
    oVM.AllocateObject(object);
}