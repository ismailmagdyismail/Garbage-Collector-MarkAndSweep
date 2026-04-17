#pragma once

//! System Includes
#include <iostream>

//! VM includes
#include "VM.h"
#include "VMObjects.h"

inline void RepeatedCollections()
{
    VM oVM(2);
    unsigned int uiCollectedObjects = 0;

    for (int i = 0; i < 3; ++i)
    {
        uiCollectedObjects += oVM.CreateIntObject(i + 1).m_uiGarbageCollectedObjectsCount;
        uiCollectedObjects += oVM.CreateIntObject(i + 101).m_uiGarbageCollectedObjectsCount;
        oVM.PopStack();
        uiCollectedObjects += oVM.CreatePairObject(
                                  oVM.CreateIntObject(i + 201).m_pAllocatedObject,
                                  oVM.CreateIntObject(i + 301).m_pAllocatedObject)
                                  .m_uiGarbageCollectedObjectsCount;
        oVM.PopStack();
    }

    std::cout << "[repeated] total_collected=" << uiCollectedObjects << '\n';
}
