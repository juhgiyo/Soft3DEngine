///////////////////////////////////////////////////////////////
//                                                           //
//                    WgIntrSphere3Sphere3.cpp               //
//                                                           //
//  - Implementation for Intersection Sphere3 Sphere3 class  //
//                                                           //
//  - Written By Woong Gyu La a.k.a. Chris                   //
//       on 2009.10.06                                       //
//                                                           //
///////////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgIntrSphere3Sphere3.h"

namespace WGSoft3D
{


//----------------------------------------------------------------------------

IntrSphere3Sphere3x::IntrSphere3Sphere3x (const Sphere3x& rkSphere0,
    const Sphere3x& rkSphere1)
    :
    m_rkSphere0(rkSphere0),
    m_rkSphere1(rkSphere1)
{
}
//----------------------------------------------------------------------------

const Sphere3x& IntrSphere3Sphere3x::GetSphere0 () const
{
    return m_rkSphere0;
}
//----------------------------------------------------------------------------

const Sphere3x& IntrSphere3Sphere3x::GetSphere1 () const
{
    return m_rkSphere1;
}
//----------------------------------------------------------------------------

bool IntrSphere3Sphere3x::Test ()
{
    Vector3x kDiff = m_rkSphere1.Center - m_rkSphere0.Center;
    fixed fRSum = m_rkSphere0.Radius + m_rkSphere1.Radius;
    return kDiff.SquaredLength() <= fRSum*fRSum;
}
//----------------------------------------------------------------------------

bool IntrSphere3Sphere3x::Find ()
{
    // plane of intersection must have N as its normal
    m_kNormal = m_rkSphere1.Center - m_rkSphere0.Center;
    fixed fNSqrLen = m_kNormal.SquaredLength();
    fixed fRSum = m_rkSphere0.Radius + m_rkSphere1.Radius;
    if (fNSqrLen > fRSum*fRSum)
    {
        // sphere centers are too far apart for intersection
        return false;
    }

    fixed fR0Sqr = m_rkSphere0.Radius*m_rkSphere0.Radius;
    fixed fR1Sqr = m_rkSphere1.Radius*m_rkSphere1.Radius;
    fixed fInvNSqrLen = FIXED_ONE/fNSqrLen;
    fixed fT = (FIXED_HALF)*(FIXED_ONE+(fR0Sqr-fR1Sqr)*fInvNSqrLen);
    if (fT < FIXED_ZERO || fT > FIXED_ONE)
    {
        return false;
    }

    fixed fRSqr = fR0Sqr - fT*fT*fNSqrLen;
    if (fRSqr < FIXED_ZERO)
    {
        return false;
    }

    // center and radius of circle of intersection
    m_kCenter = m_rkSphere0.Center + fT*m_kNormal;
    m_fRadius = Mathx::Sqrt(fRSqr);

    // compute U and V for plane of circle
    m_kNormal *= Mathx::Sqrt(fInvNSqrLen);
    Vector3x::GenerateComplementBasis(m_kUAxis,m_kVAxis,m_kNormal);

    return true;
}
//----------------------------------------------------------------------------

bool IntrSphere3Sphere3x::Test (fixed fTMax,
    const Vector3x& rkVelocity0, const Vector3x& rkVelocity1)
{
    Vector3x kVDiff = rkVelocity1 - rkVelocity0;
    fixed fA = kVDiff.SquaredLength();
    Vector3x kCDiff = m_rkSphere1.Center - m_rkSphere0.Center;
    fixed fC = kCDiff.SquaredLength();
    fixed fRSum = m_rkSphere0.Radius + m_rkSphere1.Radius;
    fixed fRSumSqr = fRSum*fRSum;

    if (fA > FIXED_ZERO)
    {
        fixed fB = kCDiff.Dot(kVDiff);
        if (fB <= FIXED_ZERO)
        {
            if (-fTMax*fA <= fB)
            {
                return fA*fC - fB*fB <= fA*fRSumSqr;
            }
            else
            {
                return fTMax*(fTMax*fA + FixedFromFloat((float)2.0)*fB) + fC <= fRSumSqr;
            }
        }
    }

    return fC <= fRSumSqr;
}
//----------------------------------------------------------------------------

bool IntrSphere3Sphere3x::Find (fixed fTMax,
    const Vector3x& rkVelocity0, const Vector3x& rkVelocity1)
{
    Vector3x kVDiff = rkVelocity1 - rkVelocity0;
    fixed fA = kVDiff.SquaredLength();
    Vector3x kCDiff = m_rkSphere1.Center - m_rkSphere0.Center;
    fixed fC = kCDiff.SquaredLength();
    fixed fRSum = m_rkSphere0.Radius + m_rkSphere1.Radius;
    fixed fRSumSqr = fRSum*fRSum;

    if (fA > FIXED_ZERO)
    {
        fixed fB = kCDiff.Dot(kVDiff);
        if (fB <= FIXED_ZERO)
        {
            if (-fTMax*fA <= fB
            ||  fTMax*(fTMax*fA + FixedFromFloat((float)2.0)*fB) + fC <= fRSumSqr )
            {
                fixed fCDiff = fC - fRSumSqr;
                fixed fDiscr = fB*fB - fA*fCDiff;
                if (fDiscr >= FIXED_ZERO)
                {
                    if (fCDiff <= FIXED_ZERO)
                    {
                        // The spheres are initially intersecting.  Estimate a
                        // point of contact by using the midpoint of the line
                        // segment connecting the sphere centers.
                        m_fContactTime = FIXED_ZERO;
                        m_kContactPoint = (FIXED_HALF)*(m_rkSphere0.Center +
                            m_rkSphere1.Center);
                    }
                    else
                    {
                        // The first time of contact is in [0,fTMax].
                        m_fContactTime = -(fB + Mathx::Sqrt(fDiscr))/fA;
                        if (m_fContactTime < FIXED_ZERO)
                        {
                            m_fContactTime = FIXED_ZERO;
                        }
                        else if (m_fContactTime > fTMax)
                        {
                            m_fContactTime = fTMax;
                        }

                        Vector3x kNewCDiff = kCDiff +
                            m_fContactTime*kVDiff;

                        m_kContactPoint = m_rkSphere0.Center +
                            m_fContactTime*rkVelocity0 +
                            (m_rkSphere0.Radius/fRSum)*kNewCDiff;
                    }
                    return true;
                }
            }
            return false;
        }
    }

    if (fC <= fRSumSqr)
    {
        // The spheres are initially intersecting.  Estimate a point of
        // contact by using the midpoint of the line segment connecting the
        // sphere centers.
        m_fContactTime = FIXED_ZERO;
        m_kContactPoint = (FIXED_HALF)*(m_rkSphere0.Center +
            m_rkSphere1.Center);
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------

const Vector3x& IntrSphere3Sphere3x::GetCenter () const
{
    return m_kCenter;
}
//----------------------------------------------------------------------------

const Vector3x& IntrSphere3Sphere3x::GetUAxis () const
{
    return m_kUAxis;
}
//----------------------------------------------------------------------------

const Vector3x& IntrSphere3Sphere3x::GetVAxis () const
{
    return m_kVAxis;
}
//----------------------------------------------------------------------------

const Vector3x& IntrSphere3Sphere3x::GetNormal () const
{
    return m_kNormal;
}
//----------------------------------------------------------------------------

fixed IntrSphere3Sphere3x::GetRadius () const
{
    return m_fRadius;
}
//----------------------------------------------------------------------------

const Vector3x& IntrSphere3Sphere3x::GetContactPoint () const
{
    return m_kContactPoint;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// explicit instantiation
//----------------------------------------------------------------------------
template WG3D_FOUNDATION_ITEM
class IntrSphere3Sphere3<float>;

template WG3D_FOUNDATION_ITEM
class IntrSphere3Sphere3<double>;
//----------------------------------------------------------------------------
}

