#pragma once

//! System Includes
#include <iostream>

//! VM includes
#include "VM.h"
#include "VMObjects.h"

inline void RetainedObjectsAcrossCollections()
{
    VM oVM(3);

    VMObject *pRootLeft = oVM.CreateIntObject(11).m_pAllocatedObject;
    VMObject *pRootRight = oVM.CreateIntObject(22).m_pAllocatedObject;
    VMObject *pRootPair = oVM.CreatePairObject(pRootLeft, pRootRight).m_pAllocatedObject;

    unsigned int uiCollectedObjects = 0;
    uiCollectedObjects += oVM.CreateIntObject(33).m_uiGarbageCollectedObjectsCount;
    uiCollectedObjects += oVM.CreatePairObject(pRootPair, oVM.CreateIntObject(44).m_pAllocatedObject).m_uiGarbageCollectedObjectsCount;
    uiCollectedObjects += oVM.CreateIntObject(55).m_uiGarbageCollectedObjectsCount;

    std::cout << "[retained] collected_while_root_alive=" << uiCollectedObjects << '\n';

    //! Not used
    static_cast<void>(pRootPair);
}
