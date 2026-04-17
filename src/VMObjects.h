#pragma once

//! System includes
#include <functional>
#include <string>
#include <vector>

class VMObject
{
public:
    VMObject();
    virtual ~VMObject();

    virtual void Trace(const std::function<void(VMObject *)> &p_fnVisitChild) = 0;

    bool m_bMarked{false};
    static unsigned long long m_ullCreatedInstances;
};

class VMIntObject : public VMObject
{
public:
    explicit VMIntObject(int p_iVal);
    void Trace(const std::function<void(VMObject *)> &p_fnVisitChild) override;

    int m_iValue;
};

class VMPairObject : public VMObject
{
public:
    VMPairObject(VMObject *p_pFirst, VMObject *p_pSecond);
    void Trace(const std::function<void(VMObject *)> &p_fnVisitChild) override;

    VMObject *m_pFirst;
    VMObject *m_pSecond;
};

class VMArrayObject : public VMObject
{
public:
    explicit VMArrayObject(std::vector<VMObject *> p_vecElements);
    void Trace(const std::function<void(VMObject *)> &p_fnVisitChild) override;

    std::vector<VMObject *> m_vecElements;
};

class VMStringObject : public VMObject
{
public:
    explicit VMStringObject(std::string p_strValue);
    void Trace(const std::function<void(VMObject *)> &p_fnVisitChild) override;

    std::string m_strValue;
};
