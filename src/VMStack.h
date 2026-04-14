#pragma once

//! System includes
#include <vector>

class VMObject;

class VMStack
{
public:
    VMStack(unsigned int p_uiMaxStackSize);
    ~VMStack();
    void Push(VMObject *p_pVMObject);
    VMObject *Pop();
    void PopAll();
    std::vector<VMObject *> GetReachableObjects();

private:
    unsigned int m_uiMaxStackSize;
    unsigned int m_uiIndex{0};
    VMObject **m_arrObjectsStack;
};