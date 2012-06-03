///////////////////////////////////////////////////////////
//                                                       //
//                    WgVector3.cpp                      //
//                                                       //
//  - Implementation for Vector3 class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgVector3.h"
namespace WGSoft3D
{
template<> const Vector3<float> Vector3<float>::ZERO(0.0f,0.0f,0.0f);
template<> const Vector3<float> Vector3<float>::UNIT_X(1.0f,0.0f,0.0f);
template<> const Vector3<float> Vector3<float>::UNIT_Y(0.0f,1.0f,0.0f);
template<> const Vector3<float> Vector3<float>::UNIT_Z(0.0f,0.0f,1.0f);
template<> const Vector3<float> Vector3<float>::ONE(1.0f,1.0f,1.0f);

template<> const Vector3<double> Vector3<double>::ZERO(0.0,0.0,0.0);
template<> const Vector3<double> Vector3<double>::UNIT_X(1.0,0.0,0.0);
template<> const Vector3<double> Vector3<double>::UNIT_Y(0.0,1.0,0.0);
template<> const Vector3<double> Vector3<double>::UNIT_Z(0.0,0.0,1.0);
template<> const Vector3<double> Vector3<double>::ONE(1.0,1.0,1.0);

const Vector3x Vector3x::ZERO(fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO));
const Vector3x Vector3x::UNIT_X(fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO));
const Vector3x Vector3x::UNIT_Y(fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO));
const Vector3x Vector3x::UNIT_Z(fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE));
const Vector3x Vector3x::ONE(fixed(FIXED_ONE),fixed(FIXED_ONE),fixed(FIXED_ONE));



//----------------------------------------------------------------------------
//
// Fixed Vector 3 Implementation
//
//----------------------------------------------------------------------------
Vector3x::Vector3x ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------

Vector3x::Vector3x (fixed fX, fixed fY, fixed fZ)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
}
//----------------------------------------------------------------------------
Vector3x::Vector3x (const fixed* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
    m_afTuple[2] = afTuple[2];
}
//----------------------------------------------------------------------------

Vector3x::Vector3x (const Vector3x& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
}
//----------------------------------------------------------------------------

int Vector3x::CompareArrays (const Vector3x& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,3*sizeof(fixed));
}
//----------------------------------------------------------------------------

bool Vector3x::operator== (const Vector3x& rkV) const
{
    return CompareArrays(rkV) == 0;
}
//----------------------------------------------------------------------------

bool Vector3x::operator!= (const Vector3x& rkV) const
{
    return CompareArrays(rkV) != 0;
}
//----------------------------------------------------------------------------

bool Vector3x::operator< (const Vector3x& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------

bool Vector3x::operator<= (const Vector3x& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------

bool Vector3x::operator> (const Vector3x& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------

bool Vector3x::operator>= (const Vector3x& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------

void Vector3x::GetBarycentrics (const Vector3x& rkV0,
    const Vector3x& rkV1, const Vector3x& rkV2,
    const Vector3x& rkV3, fixed afBary[4]) const
{
    // Compute the vectors relative to V3 of the tetrahedron.
    Vector3x akDiff[4] =
    {
        rkV0 - rkV3,
        rkV1 - rkV3,
        rkV2 - rkV3,
        *this - rkV3
    };

    // If the vertices have large magnitude, the linear system of
    // equations for computing barycentric coordinates can be
    // ill-conditioned.  To avoid this, uniformly scale the tetrahedron
    // edges to be of order 1.  The scaling of all differences does not
    // change the barycentric coordinates.
    fixed fMax = FIXED_ZERO;
    int i;
    for (i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            fixed fValue = Mathx::FAbs(akDiff[i][j]);
            if (fValue > fMax)
            {
                fMax = fValue;
            }
        }
    }

    // Scale down only large data.
    fixed fInvMax = FIXED_ZERO;
    if (fMax > FIXED_ONE)
    {
        fInvMax = FIXED_ONE/fMax;
        for (i = 0; i < 4; i++)
        {
            akDiff[i] *= fInvMax;
        }
    }

    fixed fDet = akDiff[0].Dot(akDiff[1].Cross(akDiff[2]));
    Vector3x kE1cE2 = akDiff[1].Cross(akDiff[2]);
    Vector3x kE2cE0 = akDiff[2].Cross(akDiff[0]);
    Vector3x kE0cE1 = akDiff[0].Cross(akDiff[1]);
    if (Mathx::FAbs(fDet) > Mathx::ZERO_TOLERANCE)
    {
        fixed fInvDet = FIXED_ONE/fDet;
        afBary[0] = akDiff[3].Dot(kE1cE2)*fInvDet;
        afBary[1] = akDiff[3].Dot(kE2cE0)*fInvDet;
        afBary[2] = akDiff[3].Dot(kE0cE1)*fInvDet;
        afBary[3] = FIXED_ONE - afBary[0] - afBary[1] - afBary[2];
    }
    else
    {
        // The tetrahedron is potentially flat.  Determine the face of
        // maximum area and compute barycentric coordinates with respect
        // to that face.
        Vector3x kE02 = rkV0 - rkV2;
        Vector3x kE12 = rkV1 - rkV2;
        if (fInvMax != FIXED_ZERO)
        {
            kE02 *= fInvMax;
            kE12 *= fInvMax;
        }

        Vector3x kE02cE12 = kE02.Cross(kE12);
        fixed fMaxSqrArea = kE02cE12.SquaredLength();
        int iMaxIndex = 3;
        fixed fSqrArea = kE0cE1.SquaredLength();
        if (fSqrArea > fMaxSqrArea)
        {
            iMaxIndex = 0;
            fMaxSqrArea = fSqrArea;
        }
        fSqrArea = kE1cE2.SquaredLength();
        if (fSqrArea > fMaxSqrArea)
        {
            iMaxIndex = 1;
            fMaxSqrArea = fSqrArea;
        }
        fSqrArea = kE2cE0.SquaredLength();
        if (fSqrArea > fMaxSqrArea)
        {
            iMaxIndex = 2;
            fMaxSqrArea = fSqrArea;
        }

        if (fMaxSqrArea > Mathx::ZERO_TOLERANCE)
        {
            fixed fInvSqrArea = FIXED_ONE/fMaxSqrArea;
            Vector3x kTmp;
            if (iMaxIndex == 0)
            {
                kTmp = akDiff[3].Cross(akDiff[1]);
                afBary[0] = kE0cE1.Dot(kTmp)*fInvSqrArea;
                kTmp = akDiff[0].Cross(akDiff[3]);
                afBary[1] = kE0cE1.Dot(kTmp)*fInvSqrArea;
                afBary[2] = FIXED_ZERO;
                afBary[3] = FIXED_ONE - afBary[0] - afBary[1];
            }
            else if (iMaxIndex == 1)
            {
                afBary[0] = FIXED_ZERO;
                kTmp = akDiff[3].Cross(akDiff[2]);
                afBary[1] = kE1cE2.Dot(kTmp)*fInvSqrArea;
                kTmp = akDiff[1].Cross(akDiff[3]);
                afBary[2] = kE1cE2.Dot(kTmp)*fInvSqrArea;
                afBary[3] = FIXED_ONE - afBary[1] - afBary[2];
            }
            else if (iMaxIndex == 2)
            {
                kTmp = akDiff[2].Cross(akDiff[3]);
                afBary[0] = kE2cE0.Dot(kTmp)*fInvSqrArea;
                afBary[1] = FIXED_ZERO;
                kTmp = akDiff[3].Cross(akDiff[0]);
                afBary[2] = kE2cE0.Dot(kTmp)*fInvSqrArea;
                afBary[3] = FIXED_ONE - afBary[0] - afBary[2];
            }
            else
            {
                akDiff[3] = *this - rkV2;
                if (fInvMax != FIXED_ZERO)
                {
                    akDiff[3] *= fInvMax;
                }

                kTmp = akDiff[3].Cross(kE12);
                afBary[0] = kE02cE12.Dot(kTmp)*fInvSqrArea;
                kTmp = kE02.Cross(akDiff[3]);
                afBary[1] = kE02cE12.Dot(kTmp)*fInvSqrArea;
                afBary[2] = FIXED_ONE - afBary[0] - afBary[1];
                afBary[3] = FIXED_ZERO;
            }
        }
        else
        {
            // The tetrahedron is potentially a sliver.  Determine the edge of
            // maximum length and compute barycentric coordinates with respect
            // to that edge.
            fixed fMaxSqrLength = akDiff[0].SquaredLength();
            iMaxIndex = 0;  // <V0,V3>
            fixed fSqrLength = akDiff[1].SquaredLength();
            if (fSqrLength > fMaxSqrLength)
            {
                iMaxIndex = 1;  // <V1,V3>
                fMaxSqrLength = fSqrLength;
            }
            fSqrLength = akDiff[2].SquaredLength();
            if (fSqrLength > fMaxSqrLength)
            {
                iMaxIndex = 2;  // <V2,V3>
                fMaxSqrLength = fSqrLength;
            }
            fSqrLength = kE02.SquaredLength();
            if (fSqrLength > fMaxSqrLength)
            {
                iMaxIndex = 3;  // <V0,V2>
                fMaxSqrLength = fSqrLength;
            }
            fSqrLength = kE12.SquaredLength();
            if (fSqrLength > fMaxSqrLength)
            {
                iMaxIndex = 4;  // <V1,V2>
                fMaxSqrLength = fSqrLength;
            }
            Vector3x kE01 = rkV0 - rkV1;
            fSqrLength = kE01.SquaredLength();
            if (fSqrLength > fMaxSqrLength)
            {
                iMaxIndex = 5;  // <V0,V1>
                fMaxSqrLength = fSqrLength;
            }

            if (fMaxSqrLength > Mathx::ZERO_TOLERANCE)
            {
                fixed fInvSqrLength = FIXED_ONE/fMaxSqrLength;
                if (iMaxIndex == 0)
                {
                    // P-V3 = t*(V0-V3)
                    afBary[0] = akDiff[3].Dot(akDiff[0])*fInvSqrLength;
                    afBary[1] = FIXED_ZERO;
                    afBary[2] = FIXED_ZERO;
                    afBary[3] = FIXED_ONE - afBary[0];
                }
                else if (iMaxIndex == 1)
                {
                    // P-V3 = t*(V1-V3)
                    afBary[0] = FIXED_ZERO;
                    afBary[1] = akDiff[3].Dot(akDiff[1])*fInvSqrLength;
                    afBary[2] = FIXED_ZERO;
                    afBary[3] = FIXED_ONE - afBary[1];
                }
                else if (iMaxIndex == 2)
                {
                    // P-V3 = t*(V2-V3)
                    afBary[0] = FIXED_ZERO;
                    afBary[1] = FIXED_ZERO;
                    afBary[2] = akDiff[3].Dot(akDiff[2])*fInvSqrLength;
                    afBary[3] = FIXED_ONE - afBary[2];
                }
                else if (iMaxIndex == 3)
                {
                    // P-V2 = t*(V0-V2)
                    akDiff[3] = *this - rkV2;
                    if (fInvMax != FIXED_ZERO)
                    {
                        akDiff[3] *= fInvMax;
                    }

                    afBary[0] = akDiff[3].Dot(kE02)*fInvSqrLength;
                    afBary[1] = FIXED_ZERO;
                    afBary[2] = FIXED_ONE - afBary[0];
                    afBary[3] = FIXED_ZERO;
                }
                else if (iMaxIndex == 4)
                {
                    // P-V2 = t*(V1-V2)
                    akDiff[3] = *this - rkV2;
                    if (fInvMax !=FIXED_ZERO)
                    {
                        akDiff[3] *= fInvMax;
                    }

                    afBary[0] =FIXED_ZERO;
                    afBary[1] = akDiff[3].Dot(kE12)*fInvSqrLength;
                    afBary[2] = FIXED_ONE - afBary[1];
                    afBary[3] = FIXED_ZERO;
                }
                else
                {
                    // P-V1 = t*(V0-V1)
                    akDiff[3] = *this - rkV1;
                    if (fInvMax != FIXED_ZERO)
                    {
                        akDiff[3] *= fInvMax;
                    }

                    afBary[0] = akDiff[3].Dot(kE01)*fInvSqrLength;
                    afBary[1] = FIXED_ONE - afBary[0];
                    afBary[2] = FIXED_ZERO;
                    afBary[3] = FIXED_ZERO;
                }
            }
            else
            {
                // The tetrahedron is a nearly a point, just return equal
                // weights.
                afBary[0] = FixedFromFloat((float)0.25);
                afBary[1] = afBary[0];
                afBary[2] = afBary[0];
                afBary[3] = afBary[0];
            }
        }
    }
}
//----------------------------------------------------------------------------

void Vector3x::Orthonormalize (Vector3x& rkU, Vector3x& rkV, Vector3x& rkW)
{
    // If the input vectors are v0, v1, and v2, then the Gram-Schmidt
    // orthonormalization produces vectors u0, u1, and u2 as follows,
    //
    //   u0 = v0/|v0|
    //   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
    //   u2 = (v2-(u0*v2)u0-(u1*v2)u1)/|v2-(u0*v2)u0-(u1*v2)u1|
    //
    // where |A| indicates length of vector A and A*B indicates dot
    // product of vectors A and B.

    // compute u0
    rkU.Normalize();

    // compute u1
    fixed fDot0 = rkU.Dot(rkV); 
    rkV -= fDot0*rkU;
    rkV.Normalize();

    // compute u2
    fixed fDot1 = rkV.Dot(rkW);
    fDot0 = rkU.Dot(rkW);
    rkW -= fDot0*rkU + fDot1*rkV;
    rkW.Normalize();
}
//----------------------------------------------------------------------------

void Vector3x::Orthonormalize (Vector3x* akV)
{
    Orthonormalize(akV[0],akV[1],akV[2]);
}
//----------------------------------------------------------------------------
void Vector3x::GenerateOrthonormalBasis(Vector3x& rkU, Vector3x& rkV,Vector3x& rkW)
{
    rkW.Normalize();
    GenerateComplementBasis(rkU,rkV,rkW);
}
//----------------------------------------------------------------------------
void Vector3x::GenerateComplementBasis (Vector3x& rkU, Vector3x& rkV, const Vector3x& rkW)
{
    fixed fInvLength;
	
    if (Mathx::FAbs(rkW.m_afTuple[0]) >=
        Mathx::FAbs(rkW.m_afTuple[1]) )
    {
        // W.x or W.z is the largest magnitude component, swap them
        fInvLength = Mathx::InvSqrt(rkW.m_afTuple[0]*rkW.m_afTuple[0] +
            rkW.m_afTuple[2]*rkW.m_afTuple[2]);
        rkU.m_afTuple[0] = -rkW.m_afTuple[2]*fInvLength;
        rkU.m_afTuple[1] = FIXED_ZERO;
        rkU.m_afTuple[2] = +rkW.m_afTuple[0]*fInvLength;
        rkV.m_afTuple[0] = rkW.m_afTuple[1]*rkU.m_afTuple[2];
        rkV.m_afTuple[1] = rkW.m_afTuple[2]*rkU.m_afTuple[0] -
            rkW.m_afTuple[0]*rkU.m_afTuple[2];
        rkV.m_afTuple[2] = -rkW.m_afTuple[1]*rkU.m_afTuple[0];
    }
    else
    {
        // W.y or W.z is the largest magnitude component, swap them
        fInvLength = Mathx::InvSqrt(rkW.m_afTuple[1]*rkW.m_afTuple[1] +
            rkW.m_afTuple[2]*rkW.m_afTuple[2]);
        rkU.m_afTuple[0] = FIXED_ZERO;
        rkU.m_afTuple[1] = +rkW.m_afTuple[2]*fInvLength;
        rkU.m_afTuple[2] = -rkW.m_afTuple[1]*fInvLength;
        rkV.m_afTuple[0] = rkW.m_afTuple[1]*rkU.m_afTuple[2] -
            rkW.m_afTuple[2]*rkU.m_afTuple[1];
        rkV.m_afTuple[1] = -rkW.m_afTuple[0]*rkU.m_afTuple[2];
        rkV.m_afTuple[2] = rkW.m_afTuple[0]*rkU.m_afTuple[1];
    }
}
//----------------------------------------------------------------------------

void Vector3x::ComputeExtremes (int iVQuantity, const Vector3x* akPoint,
    Vector3x& rkMin, Vector3x& rkMax)
{
    assert(iVQuantity > 0 && akPoint);

    rkMin = akPoint[0];
    rkMax = rkMin;
    for (int i = 1; i < iVQuantity; i++)
    {
        const Vector3x& rkPoint = akPoint[i];
        for (int j = 0; j < 3; j++)
        {
            if (rkPoint[j] < rkMin[j])
            {
                rkMin[j] = rkPoint[j];
            }
            else if (rkPoint[j] > rkMax[j])
            {
                rkMax[j] = rkPoint[j];
            }
        }
    }
}
//----------------------------------------------------------------------------
#ifndef _WIN32_WCE
std::ostream& operator<< (std::ostream& rkOStr, const Vector3x& rkV)
{
	return rkOStr << FloatFromFixed(rkV.X()) << ' ' << FloatFromFixed(rkV.Y()) << ' ' << FloatFromFixed(rkV.Z());
}
#endif //_WIN32_WCE
}