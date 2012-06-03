///////////////////////////////////////////////////////////
//                                                       //
//                    WgVector2.cpp                      //
//                                                       //
//  - Implementation for Vector2 class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgVector2.h"
namespace WGSoft3D
{

template<> const Vector2<float> Vector2<float>::ZERO(0.0f,0.0f);
template<> const Vector2<float> Vector2<float>::UNIT_X(1.0f,0.0f);
template<> const Vector2<float> Vector2<float>::UNIT_Y(0.0f,1.0f);
template<> const Vector2<float> Vector2<float>::ONE(1.0f,1.0f);

template<> const Vector2<double> Vector2<double>::ZERO(0.0,0.0);
template<> const Vector2<double> Vector2<double>::UNIT_X(1.0,0.0);
template<> const Vector2<double> Vector2<double>::UNIT_Y(0.0,1.0);
template<> const Vector2<double> Vector2<double>::ONE(1.0,1.0);

const Vector2x Vector2x::ZERO(fixed(FIXED_ZERO),fixed(FIXED_ZERO));
const Vector2x Vector2x::UNIT_X(fixed(FIXED_ONE),fixed(FIXED_ZERO));
const Vector2x Vector2x::UNIT_Y(fixed(FIXED_ZERO),fixed(FIXED_ONE));
const Vector2x Vector2x::ONE(fixed(FIXED_ONE),fixed(FIXED_ONE));

//----------------------------------------------------------------------------
//
// Fixed Vector 2 Implementation
//
//----------------------------------------------------------------------------
Vector2x::Vector2x ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------

Vector2x::Vector2x (fixed fX, fixed fY)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
}
//----------------------------------------------------------------------------

Vector2x::Vector2x (const fixed* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
}
//----------------------------------------------------------------------------

Vector2x::Vector2x (const Vector2x& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
}
//----------------------------------------------------------------------------

int Vector2x::CompareArrays (const Vector2x& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,2*sizeof(fixed));
}
//----------------------------------------------------------------------------

bool Vector2x::operator== (const Vector2x& rkV) const
{
    return CompareArrays(rkV) == 0;
}
//----------------------------------------------------------------------------

bool Vector2x::operator!= (const Vector2x& rkV) const
{
    return CompareArrays(rkV) != 0;
}
//----------------------------------------------------------------------------

bool Vector2x::operator< (const Vector2x& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------

bool Vector2x::operator<= (const Vector2x& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------

bool Vector2x::operator> (const Vector2x& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------

bool Vector2x::operator>= (const Vector2x& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------

void Vector2x::GetBarycentrics (const Vector2x& rkV0, const Vector2x& rkV1,
    const Vector2x& rkV2, fixed afBary[3]) const
{
    // Compute the vectors relative to V2 of the triangle.
    Vector2x akDiff[3] =
    {
        rkV0 - rkV2,
        rkV1 - rkV2,
        *this - rkV2
    };

    // If the vertices have large magnitude, the linear system of equations
    // for computing barycentric coordinates can be ill-conditioned.  To avoid
    // this, uniformly scale the triangle edges to be of order 1.  The scaling
    // of all differences does not change the barycentric coordinates.
    fixed fMax = FIXED_ZERO;
    int i;
    for (i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
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
        fInvMax = (FIXED_ONE)/fMax;
        for (i = 0; i < 3; i++)
        {
            akDiff[i] *= fInvMax;
        }
    }

    fixed fDet = akDiff[0].DotPerp(akDiff[1]);
    if (Mathx::FAbs(fDet) > Mathx::ZERO_TOLERANCE)
    {
        fixed fInvDet = (FIXED_ONE)/fDet;
        afBary[0] = akDiff[2].DotPerp(akDiff[1])*fInvDet;
        afBary[1] = akDiff[0].DotPerp(akDiff[2])*fInvDet;
        afBary[2] = FIXED_ONE - afBary[0] - afBary[1];
    }
    else
    {
        // The triangle is a sliver.  Determine the longest edge and
        // compute barycentric coordinates with respect to that edge.
        Vector2x kE2 = rkV0 - rkV1;
        if (fInvMax != FIXED_ZERO)
        {
            kE2 *= fInvMax;
        }

        fixed fMaxSqrLength = kE2.SquaredLength();
        int iMaxIndex = 2;
        fixed fSqrLength = akDiff[1].SquaredLength();
        if (fSqrLength > fMaxSqrLength)
        {
            iMaxIndex = 1;
            fMaxSqrLength = fSqrLength;
        }
        fSqrLength = akDiff[0].SquaredLength();
        if (fSqrLength > fMaxSqrLength)
        {
            iMaxIndex = 0;
            fMaxSqrLength = fSqrLength;
        }

        if (fMaxSqrLength > Mathx::ZERO_TOLERANCE)
        {
            fixed fInvSqrLength = (FIXED_ONE)/fMaxSqrLength;
            if (iMaxIndex == 0)
            {
                // P-V2 = t(V0-V2)
                afBary[0] = akDiff[2].Dot(akDiff[0])*fInvSqrLength;
                afBary[1] = FIXED_ZERO;
                afBary[2] = FIXED_ONE - afBary[0];
            }
            else if (iMaxIndex == 1)
            {
                // P-V2 = t(V1-V2)
                afBary[0] = FIXED_ZERO;
                afBary[1] = akDiff[2].Dot(akDiff[1])*fInvSqrLength;
                afBary[2] = FIXED_ONE - afBary[1];
            }
            else
            {
                // P-V1 = t(V0-V1)
                akDiff[2] = *this - rkV1;
                if (fInvMax != FIXED_ZERO)
                {
                    akDiff[2] *= fInvMax;
                }

                afBary[0] = akDiff[2].Dot(kE2)*fInvSqrLength;
                afBary[1] = FIXED_ONE - afBary[0];
                afBary[2] = FIXED_ZERO;
            }
        }
        else
        {
            // The triangle is a nearly a point, just return equal weights.
            afBary[0] = (FIXED_ONE)/FixedFromFloat((float)3.0);
            afBary[1] = afBary[0];
            afBary[2] = afBary[0];
        }
    }
}
//----------------------------------------------------------------------------

void Vector2x::Orthonormalize (Vector2x& rkU, Vector2x& rkV)
{
    // If the input vectors are v0 and v1, then the Gram-Schmidt
    // orthonormalization produces vectors u0 and u1 as follows,
    //
    //   u0 = v0/|v0|
    //   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
    //
    // where |A| indicates length of vector A and A*B indicates dot
    // product of vectors A and B.

    // compute u0
    rkU.Normalize();

    // compute u1
    fixed fDot0 = rkU.Dot(rkV); 
    rkV -= rkU*fDot0;
    rkV.Normalize();
}
//----------------------------------------------------------------------------

void Vector2x::GenerateOrthonormalBasis (Vector2x& rkU, Vector2x& rkV)
{
    rkV.Normalize();
    rkU = rkV.Perp();
}
//----------------------------------------------------------------------------

void Vector2x::ComputeExtremes (int iVQuantity, const Vector2x* akPoint,
    Vector2x& rkMin, Vector2x& rkMax)
{
    assert(iVQuantity > 0 && akPoint);

    rkMin = akPoint[0];
    rkMax = rkMin;
    for (int i = 1; i < iVQuantity; i++)
    {
        const Vector2x& rkPoint = akPoint[i];
        for (int j = 0; j < 2; j++)
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
std::ostream& operator<< (std::ostream& rkOStr, const Vector2x& rkV)
{
	return rkOStr << FloatFromFixed(rkV.X()) << ' ' << FloatFromFixed(rkV.Y());
}
#endif //_WIN32_WCE
//----------------------------------------------------------------------------

}