///////////////////////////////////////////////////////////
//                                                       //
//                    WgTriangle3.cpp                    //
//                                                       //
//  - Implementation for Triangle 3 class                //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgTriangle3.h"
namespace WGSoft3D
{
//----------------------------------------------------------------------------

Triangle3x::Triangle3x ()
{
    // uninitialized
}
//----------------------------------------------------------------------------

Triangle3x::Triangle3x (const Vector3x& rkV0,
    const Vector3x& rkV1, const Vector3x& rkV2)
{
    V[0] = rkV0;
    V[1] = rkV1;
    V[2] = rkV2;
}
//----------------------------------------------------------------------------

Triangle3x::Triangle3x (const Vector3x akV[3])
{
    for (int i = 0; i < 3; i++)
    {
        V[i] = akV[i];
    }
}
//----------------------------------------------------------------------------

fixed Triangle3x::DistanceTo (const Vector3x& rkQ) const
{
    Vector3x kDiff = V[0] - rkQ;
    Vector3x kE0 = V[1] - V[0], kE1 = V[2] - V[0];
    fixed fA00 = kE0.SquaredLength();
    fixed fA01 = kE0.Dot(kE1);
    fixed fA11 = kE1.SquaredLength();
    fixed fB0 = kDiff.Dot(kE0);
    fixed fB1 = kDiff.Dot(kE1);
    fixed fC = kDiff.SquaredLength();
    fixed fDet = Mathx::FAbs(fA00*fA11-fA01*fA01);
    fixed fS = fA01*fB1-fA11*fB0;
    fixed fT = fA01*fB0-fA00*fB1;
    fixed fSqrDist;

    if (fS + fT <= fDet)
    {
        if (fS < FIXED_ZERO)
        {
            if (fT < FIXED_ZERO)  // region 4
            {
                if (fB0 < FIXED_ZERO)
                {
                    if (-fB0 >= fA00)
                    {
                        fSqrDist = fA00+FixedFromFloat((float)2.0)*fB0+fC;
                    }
                    else
                    {
                        fSqrDist = fC-fB0*fB0/fA00;
                    }
                }
                else
                {
                    if (fB1 >= FIXED_ZERO)
                    {
                        fSqrDist = fC;
                    }
                    else if (-fB1 >= fA11)
                    {
                        fSqrDist = fA11+FixedFromFloat((float)2.0)*fB1+fC;
                    }
                    else
                    {
                        fSqrDist = fC-fB1*fB1/fA11;
                    }
                }
            }
            else  // region 3
            {
                if (fB1 >= FIXED_ZERO)
                {
                    fSqrDist = fC;
                }
                else if (-fB1 >= fA11)
                {
                    fSqrDist = fA11+FixedFromFloat((float)2.0)*fB1+fC;
                }
                else
                {
                    fSqrDist = fC-fB1*fB1/fA11;
                }
            }
        }
        else if (fT < FIXED_ZERO)  // region 5
        {
            if (fB0 >= FIXED_ZERO)
            {
                fSqrDist = fC;
            }
            else if (-fB0 >= fA00)
            {
                fSqrDist = fA00+FixedFromFloat((float)2.0)*fB0+fC;
            }
            else
            {
                fSqrDist = fC-fB0*fB0/fA00;
            }
        }
        else  // region 0
        {
            // minimum at interior point
            fixed fInvDet = FIXED_ONE/fDet;
            fS *= fInvDet;
            fT *= fInvDet;
            fSqrDist = fS*(fA00*fS+fA01*fT+FixedFromFloat((float)2.0)*fB0) +
                fT*(fA01*fS+fA11*fT+FixedFromFloat((float)2.0)*fB1)+fC;
        }
    }
    else
    {
        fixed fTmp0, fTmp1, fNumer, fDenom;

        if (fS < FIXED_ZERO)  // region 2
        {
            fTmp0 = fA01 + fB0;
            fTmp1 = fA11 + fB1;
            if (fTmp1 > fTmp0)
            {
                fNumer = fTmp1 - fTmp0;
                fDenom = fA00-FixedFromFloat((float)2.0f)*fA01+fA11;
                if (fNumer >= fDenom)
                {
                    fSqrDist = fA00+FixedFromFloat((float)2.0)*fB0+fC;
                }
                else
                {
                    fS = fNumer/fDenom;
                    fT = FIXED_ONE - fS;
                    fSqrDist = fS*(fA00*fS+fA01*fT+2.0f*fB0) +
                        fT*(fA01*fS+fA11*fT+FixedFromFloat((float)2.0)*fB1)+fC;
                }
            }
            else
            {
                if (fTmp1 <= FIXED_ZERO)
                {
                    fSqrDist = fA11+FixedFromFloat((float)2.0)*fB1+fC;
                }
                else if (fB1 >= FIXED_ZERO)
                {
                    fSqrDist = fC;
                }
                else
                {
                    fSqrDist = fC-fB1*fB1/fA11;
                }
            }
        }
        else if (fT < FIXED_ZERO)  // region 6
        {
            fTmp0 = fA01 + fB1;
            fTmp1 = fA00 + fB0;
            if (fTmp1 > fTmp0)
            {
                fNumer = fTmp1 - fTmp0;
                fDenom = fA00-FixedFromFloat((float)2.0)*fA01+fA11;
                if (fNumer >= fDenom)
                {
                    fT = FIXED_ONE;
                    fS = FIXED_ZERO;
                    fSqrDist = fA11+FixedFromFloat((float)2.0)*fB1+fC;
                }
                else
                {
                    fT = fNumer/fDenom;
                    fS = FIXED_ONE - fT;
                    fSqrDist = fS*(fA00*fS+fA01*fT+FixedFromFloat((float)2.0)*fB0) +
                        fT*(fA01*fS+fA11*fT+FixedFromFloat((float)2.0)*fB1)+fC;
                }
            }
            else
            {
                if (fTmp1 <= FIXED_ZERO)
                {
                    fSqrDist = fA00+FixedFromFloat((float)2.0)*fB0+fC;
                }
                else if (fB0 >= FIXED_ZERO)
                {
                    fSqrDist = fC;
                }
                else
                {
                    fSqrDist = fC-fB0*fB0/fA00;
                }
            }
        }
        else  // region 1
        {
            fNumer = fA11 + fB1 - fA01 - fB0;
            if (fNumer <= FIXED_ZERO)
            {
                fSqrDist = fA11+FixedFromFloat((float)2.0)*fB1+fC;
            }
            else
            {
                fDenom = fA00-FixedFromFloat((float)2.0)*fA01+fA11;
                if (fNumer >= fDenom)
                {
                    fSqrDist = fA00+FixedFromFloat((float)2.0)*fB0+fC;
                }
                else
                {
                    fS = fNumer/fDenom;
                    fT = FIXED_ONE - fS;
                    fSqrDist = fS*(fA00*fS+fA01*fT+FixedFromFloat((float)2.0)*fB0) +
                        fT*(fA01*fS+fA11*fT+FixedFromFloat((float)2.0)*fB1)+fC;
                }
            }
        }
    }

    return Mathx::Sqrt(Mathx::FAbs(fSqrDist));
}
//----------------------------------------------------------------------------
}