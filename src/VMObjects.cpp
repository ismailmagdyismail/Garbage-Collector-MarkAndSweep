#include "VMObjects.h"

unsigned long long VMObject::m_ullCreatedInstances = 0;

VMObject *CreateIntObject(int p_iVal)
{
    VMObject *pvmObject = new VMObject;
    pvmObject->m_taggedUnionObject = p_iVal;
    return pvmObject;
}

VMObject *CreatePairObject(VMObject *p_pFirst, VMObject *p_pSecond)
{
    VMObject *pvmObject = new VMObject;
    pvmObject->m_taggedUnionObject = std::make_pair(p_pFirst, p_pSecond);
    return pvmObject;
}