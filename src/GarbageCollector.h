#pragma once

class VMObject;

//! Visitor on VMObject(s) For Garabge Collection
class GarbageCollector
{
public:
    // static void Mark();
    // static void Sweep();
    static void ReclaimElement(VMObject *p_pVMObject);
};