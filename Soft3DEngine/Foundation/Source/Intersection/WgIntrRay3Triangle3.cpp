///////////////////////////////////////////////////////////////
//                                                           //
//                    WgIntrRay3Trangle3.cpp                 //
//                                                           //
//  - Implementation for Intersection Ray3 Triangle3 class   //
//                                                           //
//  - Written By Woong Gyu La a.k.a. Chris                   //
//       on 2009.10.06                                       //
//                                                           //
///////////////////////////////////////////////////////////////
#include "WgFoundationPCH.h"
#include "WgIntrRay3Triangle3.h"

namespace WGSoft3D
{


//----------------------------------------------------------------------------

IntrRay3Triangle3x::IntrRay3Triangle3x (const Ray3x& rkRay,
    const Triangle3x& rkTriangle)
    :
    m_rkRay(rkRay),
    m_rkTriangle(rkTriangle)
{
}
//----------------------------------------------------------------------------

const Ray3x& IntrRay3Triangle3x::GetRay () const
{
    return m_rkRay;
}
//----------------------------------------------------------------------------

const Triangle3x& IntrRay3Triangle3x::GetTriangle () const
{
    return m_rkTriangle;
}
//----------------------------------------------------------------------------

bool IntrRay3Triangle3x::Test ()
{
    // compute the offset origin, edges, and normal
    Vector3x kDiff = m_rkRay.Origin - m_rkTriangle.V[0];
    Vector3x kEdge1 = m_rkTriangle.V[1] - m_rkTriangle.V[0];
    Vector3x kEdge2 = m_rkTriangle.V[2] - m_rkTriangle.V[0];
    Vector3x kNormal = kEdge1.Cross(kEdge2);

    // Solve Q + t*D = b1*E1 + b2*E2 (Q = kDiff, D = ray direction,
    // E1 = kEdge1, E2 = kEdge2, N = Cross(E1,E2)) by
    //   |Dot(D,N)|*b1 = sign(Dot(D,N))*Dot(D,Cross(Q,E2))
    //   |Dot(D,N)|*b2 = sign(Dot(D,N))*Dot(D,Cross(E1,Q))
    //   |Dot(D,N)|*t = -sign(Dot(D,N))*Dot(Q,N)
    fixed fDdN = m_rkRay.Direction.Dot(kNormal);
    fixed fSign;
    if (fDdN > Mathx::ZERO_TOLERANCE)
    {
        fSign = FIXED_ONE;
    }
    else if (fDdN < -Mathx::ZERO_TOLERANCE)
    {
        fSign = FIXED_NEG_ONE;
        fDdN = -fDdN;
    }
    else
    {
        // Ray and triangle are parallel, call it a "no intersection"
        // even if the ray does intersect.
        return false;
    }

    fixed fDdQxE2 = fSign*m_rkRay.Direction.Dot(kDiff.Cross(kEdge2));
    if (fDdQxE2 >= FIXED_ZERO)
    {
        fixed fDdE1xQ = fSign*m_rkRay.Direction.Dot(kEdge1.Cross(kDiff));
        if (fDdE1xQ >= FIXED_ZERO)
        {
            if (fDdQxE2 + fDdE1xQ <= fDdN)
            {
                // line intersects triangle, check if ray does
                fixed fQdN = -fSign*kDiff.Dot(kNormal);
                if (fQdN >= FIXED_ZERO)
                {
                    // ray intersects triangle
                    return true;
                }
                // else: t < 0, no intersection
            }
            // else: b1+b2 > 1, no intersection
        }
        // else: b2 < 0, no intersection
    }
    // else: b1 < 0, no intersection

    return false;
}
//----------------------------------------------------------------------------

bool IntrRay3Triangle3x::Find ()
{
    // compute the offset origin, edges, and normal
    Vector3x kDiff = m_rkRay.Origin - m_rkTriangle.V[0];
    Vector3x kEdge1 = m_rkTriangle.V[1] - m_rkTriangle.V[0];
    Vector3x kEdge2 = m_rkTriangle.V[2] - m_rkTriangle.V[0];
    Vector3x kNormal = kEdge1.Cross(kEdge2);

    // Solve Q + t*D = b1*E1 + b2*E2 (Q = kDiff, D = ray direction,
    // E1 = kEdge1, E2 = kEdge2, N = Cross(E1,E2)) by
    //   |Dot(D,N)|*b1 = sign(Dot(D,N))*Dot(D,Cross(Q,E2))
    //   |Dot(D,N)|*b2 = sign(Dot(D,N))*Dot(D,Cross(E1,Q))
    //   |Dot(D,N)|*t = -sign(Dot(D,N))*Dot(Q,N)
    fixed fDdN = m_rkRay.Direction.Dot(kNormal);
    fixed fSign;
    if (fDdN > Mathx::ZERO_TOLERANCE)
    {
        fSign = FIXED_ONE;
    }
    else if (fDdN < -Mathx::ZERO_TOLERANCE)
    {
        fSign = FIXED_NEG_ONE;
        fDdN = -fDdN;
    }
    else
    {
        // Ray and triangle are parallel, call it a "no intersection"
        // even if the ray does intersect.
        return false;
    }

    fixed fDdQxE2 = fSign*m_rkRay.Direction.Dot(kDiff.Cross(kEdge2));
    if (fDdQxE2 >= FIXED_ZERO)
    {
        fixed fDdE1xQ = fSign*m_rkRay.Direction.Dot(kEdge1.Cross(kDiff));
        if (fDdE1xQ >= FIXED_ZERO)
        {
            if (fDdQxE2 + fDdE1xQ <= fDdN)
            {
                // line intersects triangle, check if ray does
                fixed fQdN = -fSign*kDiff.Dot(kNormal);
                if (fQdN >= FIXED_ZERO)
                {
                    // ray intersects triangle
                    fixed fInv = (FIXED_ONE)/fDdN;
                    m_fRayT = fQdN*fInv;
                    m_fTriB1 = fDdQxE2*fInv;
                    m_fTriB2 = fDdE1xQ*fInv;
                    m_fTriB0 = FIXED_ONE - m_fTriB1 - m_fTriB2;
                    return true;
                }
                // else: t < 0, no intersection
            }
            // else: b1+b2 > 1, no intersection
        }
        // else: b2 < 0, no intersection
    }
    // else: b1 < 0, no intersection

    return false;
}
//----------------------------------------------------------------------------

fixed IntrRay3Triangle3x::GetRayT () const
{
    return m_fRayT;
}
//----------------------------------------------------------------------------

fixed IntrRay3Triangle3x::GetTriB0 () const
{
    return m_fTriB0;
}
//----------------------------------------------------------------------------

fixed IntrRay3Triangle3x::GetTriB1 () const
{
    return m_fTriB1;
}
//----------------------------------------------------------------------------

fixed IntrRay3Triangle3x::GetTriB2 () const
{
    return m_fTriB2;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// explicit instantiation
//----------------------------------------------------------------------------
template WG3D_FOUNDATION_ITEM
class IntrRay3Triangle3<float>;

template WG3D_FOUNDATION_ITEM
class IntrRay3Triangle3<double>;
//----------------------------------------------------------------------------
}

