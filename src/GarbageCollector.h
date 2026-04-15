#pragma once

//! System Includes
#include <vector>
#include <list>

struct VMObject;

//! Visitor on VMObject(s) For Garabge Collection
class GarbageCollector
{
public:
    static unsigned int Mark(const std::vector<VMObject *> &p_vecRechableObjects);
    static unsigned int Sweep(std::list<VMObject *> &p_listAllocatedObjects);
    static unsigned int ReclaimElement(VMObject *p_pVMObject);

private:
    static unsigned int Mark(VMObject *p_pVMObject);
};