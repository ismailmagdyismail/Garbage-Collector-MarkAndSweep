#pragma once

//! System Includes
#include <iostream>

//! VM includes
#include "VM.h"
#include "VMObjects.h"

inline void GCPause()
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
    std::cout << "[gc-pause] total_gc_reclamations=" << uiGCCollections << std::endl;
}
