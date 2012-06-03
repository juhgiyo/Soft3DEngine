///////////////////////////////////////////////////////////////
//                                                           //
//                    WgIntrRay3Sphere3.cpp                  //
//                                                           //
//  - Implementation for Intersection Ray3 Sphere3 class     //
//                                                           //
//  - Written By Woong Gyu La a.k.a. Chris                   //
//       on 2009.10.06                                       //
//                                                           //
///////////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgIntrRay3Sphere3.h"

namespace WGSoft3D
{


//----------------------------------------------------------------------------

IntrRay3Sphere3x::IntrRay3Sphere3x (const Ray3x& rkRay,
    const Sphere3x& rkSphere)
    :
    m_rkRay(rkRay),
    m_rkSphere(rkSphere)
{
    m_iQuantity = 0;
}
//----------------------------------------------------------------------------

const Ray3x& IntrRay3Sphere3x::GetRay () const
{
    return m_rkRay;
}
//----------------------------------------------------------------------------

const Sphere3x& IntrRay3Sphere3x::GetSphere () const
{
    return m_rkSphere;
}
//----------------------------------------------------------------------------

bool IntrRay3Sphere3x::Test ()
{
    Vector3x kDiff = m_rkRay.Origin - m_rkSphere.Center;
    fixed fA0 = kDiff.Dot(kDiff) - m_rkSphere.Radius*m_rkSphere.Radius;
    if (fA0 <= FIXED_ZERO)
    {
        // P is inside the sphere
        return true;
    }
    // else: P is outside the sphere

    fixed fA1 = m_rkRay.Direction.Dot(kDiff);
    if (fA1 >= FIXED_ZERO)
    {
        return false;
    }

    // quadratic has a fixed root if discriminant is nonnegative
    return fA1*fA1 >= fA0;
}
//----------------------------------------------------------------------------

bool IntrRay3Sphere3x::Find ()
{
    Vector3x kDiff = m_rkRay.Origin - m_rkSphere.Center;
    fixed fA0 = kDiff.Dot(kDiff) - m_rkSphere.Radius*m_rkSphere.Radius;
    fixed fA1, fDiscr, fRoot;
    if (fA0 <= FIXED_ZERO)
    {
        // P is inside the sphere
        m_iQuantity = 1;
        fA1 = m_rkRay.Direction.Dot(kDiff);
        fDiscr = fA1*fA1 - fA0;
        fRoot = Mathx::Sqrt(fDiscr);
        m_afRayT[0] = -fA1 + fRoot;
        m_akPoint[0] = m_rkRay.Origin + m_afRayT[0]*m_rkRay.Direction;
        return true;
    }
    // else: P is outside the sphere

    fA1 = m_rkRay.Direction.Dot(kDiff);
    if (fA1 >= FIXED_ZERO)
    {
        m_iQuantity = 0;
        return false;
    }

    fDiscr = fA1*fA1 - fA0;
    if (fDiscr < FIXED_ZERO)
    {
        m_iQuantity = 0;
    }
    else if (fDiscr >= Mathx::ZERO_TOLERANCE)
    {
        fRoot = Mathx::Sqrt(fDiscr);
        m_afRayT[0] = -fA1 - fRoot;
        m_afRayT[1] = -fA1 + fRoot;
        m_akPoint[0] = m_rkRay.Origin + m_afRayT[0]*m_rkRay.Direction;
        m_akPoint[1] = m_rkRay.Origin + m_afRayT[1]*m_rkRay.Direction;
        m_iQuantity = 2;
    }
    else
    {
        m_afRayT[0] = -fA1;
        m_akPoint[0] = m_rkRay.Origin + m_afRayT[0]*m_rkRay.Direction;
        m_iQuantity = 1;
    }

    return m_iQuantity > 0;
}
//----------------------------------------------------------------------------

int IntrRay3Sphere3x::GetQuantity () const
{
    return m_iQuantity;
}
//----------------------------------------------------------------------------

const Vector3x& IntrRay3Sphere3x::GetPoint (int i) const
{
    assert(0 <= i && i < m_iQuantity);
    return m_akPoint[i];
}
//----------------------------------------------------------------------------

fixed IntrRay3Sphere3x::GetRayT (int i) const
{
    assert(0 <= i && i < m_iQuantity);
    return m_afRayT[i];
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// explicit instantiation
//----------------------------------------------------------------------------
template WG3D_FOUNDATION_ITEM
class IntrRay3Sphere3<float>;

template WG3D_FOUNDATION_ITEM
class IntrRay3Sphere3<double>;
//----------------------------------------------------------------------------
}

