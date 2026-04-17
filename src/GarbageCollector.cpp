//! VM Includes
#include "GarbageCollector.h"
#include "VMObjects.h"

unsigned int GarbageCollector::ReclaimElement(VMObject *p_pVMObject)
{
    delete p_pVMObject;
    return 1;
}

unsigned int GarbageCollector::Mark(const std::vector<VMObject *> &p_vecRechableObjects)
{
    unsigned int uiReachableElements{0};
    for (auto &pObject : p_vecRechableObjects)
    {
        uiReachableElements += Mark(pObject);
    }
    return uiReachableElements;
}

unsigned int GarbageCollector::Mark(VMObject *p_pVMObject)
{
    if (p_pVMObject == nullptr)
    {
        return 0;
    }

    if (p_pVMObject->m_bMarked)
    {
        return 0;
    }

    p_pVMObject->m_bMarked = true;

    unsigned int uiReachableObjects = 1;
    p_pVMObject->Trace(
        [&](VMObject *p_pChildObject)
        {
            uiReachableObjects += Mark(p_pChildObject);
        });
    return uiReachableObjects;
}

unsigned int GarbageCollector::Sweep(std::list<VMObject *> &p_listAllocatedObjects)
{
    unsigned int uiSweptElements{0};
    for (auto it = p_listAllocatedObjects.begin(); it != p_listAllocatedObjects.end();)
    {
        VMObject *pVMObject = *it;
        if (!pVMObject->m_bMarked)
        {
            uiSweptElements += ReclaimElement(pVMObject);
            it = p_listAllocatedObjects.erase(it);
        }
        else
        {
            //! Reset it for next GC pause
            pVMObject->m_bMarked = false;
            ++it;
        }
    }
    return uiSweptElements;
}
