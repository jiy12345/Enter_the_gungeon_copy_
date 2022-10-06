#pragma once
#include "JVector.h"
#include "JShape.h"

enum class CollisionType
{
    C_OUT = 0,
    C_A_IN_B,
    C_B_IN_A,
    C_OVERLAP,
};

template<size_t n>
class JCollision
{
public:
    static CollisionType   CubeToCube(nCube<n>& a, nCube<n>& b);
    static CollisionType   SphereToSphere(nSphere<n>& a, nSphere<n>& b);
};

template<size_t n>
CollisionType JCollision<n>::CubeToCube(nCube<n>& a, nCube<n>& b)
{
    float fMin;    float fMax;
    JVector<n> a_vMax = a.vMax();
    JVector<n> b_vMax = b.vMax();
    for (int i = 0; i < n; i++) {
        fMin = a.m_vLeftTop[i] < b.m_vLeftTop[i] ? a.m_vLeftTop[i] : b.m_vLeftTop[i];
        fMax = a_vMax[i] > b_vMax[i] ? a_vMax[i] : b_vMax[i];
        if ((a.m_vSize[i] + b.m_vSize[i]) < (fMax - fMin))
            return CollisionType::C_OUT;
    }

    JVector<n> m_vLeftTop, m_vMax;
    nCube<n> Intersect;

    for (int i = 0; i < n; i++) {
        m_vLeftTop[i] = a.m_vLeftTop[i] > b.m_vLeftTop[i] ? a.m_vLeftTop[i] : b.m_vLeftTop[i];
        m_vMax[i] = a_vMax[i] < b_vMax[i] ? a_vMax[i] : b_vMax[i];
    }

    Intersect.Set(m_vLeftTop, m_vMax - m_vLeftTop);
    if (Intersect == a)
        return CollisionType::C_B_IN_A;
    if (Intersect == b)
        return CollisionType::C_A_IN_B;
    return CollisionType::C_OVERLAP;
}

template<size_t n>
CollisionType JCollision<n>::SphereToSphere(nSphere<n>& a, nSphere<n>& b)
{
    float fSumRadius = a.m_fRadius + b.m_fRadius;
    float fSubRadius = fabs(a.m_fRadius - b.m_fRadius);
    JVector<n> vDir = a.m_vCenter - b.m_vCenter;
    float fDistance = vDir.length();

    if (fSumRadius < fDistance)
    {
        return CollisionType::C_OUT;
    }
    else if (fSubRadius < fDistance && fDistance <= fSumRadius)
    {
        return CollisionType::C_OVERLAP;
    }
    else {
        if (a.m_fRadius > b.m_fRadius) return CollisionType::C_A_IN_B;
        else                           return CollisionType::C_B_IN_A;
    }
}
