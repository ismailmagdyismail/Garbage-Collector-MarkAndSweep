//! System Includes
#include "variant"

//! VM Includes
#include "GarbageCollector.h"
#include "VMObjects.h"

void GarbageCollector::ReclaimElement(VMObject *p_pVMObject)
{
    if (p_pVMObject->m_bMarked)
    {
        return;
    }
    if (auto *intVal = std::get_if<VMInt>(&p_pVMObject->m_taggedUnionObject))
    {
        p_pVMObject->m_bMarked = true;
        delete p_pVMObject;
    }
    else if (auto *pairVal = std::get_if<VMPair>(&p_pVMObject->m_taggedUnionObject))
    {
        ReclaimElement(pairVal->first);
        ReclaimElement(pairVal->second);
        p_pVMObject->m_bMarked = true;
        delete p_pVMObject;
    }
    else
    {
        throw std::runtime_error("Invalid VM Object type encountered");
    }
}