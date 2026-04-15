//! System Includes
#include "variant"

//! VM Includes
#include "GarbageCollector.h"
#include "VMObjects.h"

unsigned int GarbageCollector::ReclaimElement(VMObject *p_pVMObject)
{
    if (auto *intVal = std::get_if<VMInt>(&p_pVMObject->m_taggedUnionObject))
    {
        delete p_pVMObject;
        return 1;
    }
    else if (auto *pairVal = std::get_if<VMPair>(&p_pVMObject->m_taggedUnionObject))
    {
        unsigned int uiFirstReclaimedElements = ReclaimElement(pairVal->first);
        unsigned int uiSecondReclaimedElements = ReclaimElement(pairVal->second);
        unsigned int uiReclaimedElements = 1 + uiFirstReclaimedElements + uiSecondReclaimedElements;
        delete p_pVMObject;
        return uiReclaimedElements;
    }
    else
    {
        throw std::runtime_error("Invalid VM Object type encountered");
    }
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
    if (p_pVMObject->m_bMarked)
    {
        return 0;
    }
    if (auto *intVal = std::get_if<VMInt>(&p_pVMObject->m_taggedUnionObject))
    {
        p_pVMObject->m_bMarked = true;
        return 1;
    }
    else if (auto *pairVal = std::get_if<VMPair>(&p_pVMObject->m_taggedUnionObject))
    {
        unsigned int uiFirstReachableElements = Mark(pairVal->first);
        unsigned int uiSecondReachableElements = Mark(pairVal->second);
        p_pVMObject->m_bMarked = true;
        return 1 + uiFirstReachableElements + uiSecondReachableElements;
    }
    else
    {
        throw std::runtime_error("Invalid VM Object type encountered");
    }
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
