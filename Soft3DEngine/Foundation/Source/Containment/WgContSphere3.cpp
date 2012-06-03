///////////////////////////////////////////////////////////
//                                                       //
//                    WgContSphere3.cpp                  //
//                                                       //
//  - Implementation for Containment Sphere 3 class      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgContSphere3.h"
namespace WGSoft3D
{
Sphere3x ContSphereOfAABB (int iQuantity, const Vector3x* akPoint,
								const bool* abValid)
{
    Sphere3x kSphere(Vector3x::ZERO,fixed(FIXED_ZERO));
    int i;
	
    Vector3x kMin = akPoint[0], kMax = kMin;
    if (!abValid)
    {
        for (i = 1; i < iQuantity; i++)
        {
            if (akPoint[i].X() < kMin.X())
            {
                kMin.X() = akPoint[i].X();
            }
            else if (akPoint[i].X() > kMax.X())
            {
                kMax.X() = akPoint[i].X();
            }
			
            if (akPoint[i].Y() < kMin.Y())
            {
                kMin.Y() = akPoint[i].Y();
            }
            else if (akPoint[i].Y() > kMax.Y())
            {
                kMax.Y() = akPoint[i].Y();
            }
			
            if (akPoint[i].Z() < kMin.Z())
            {
                kMin.Z() = akPoint[i].Z();
            }
            else if (akPoint[i].Z() > kMax.Z())
            {
                kMax.Z() = akPoint[i].Z();
            }
        }
    }
    else
    {
        for (i = 0; i < iQuantity; i++)
        {
            if (abValid[i])
            {
                kMin = akPoint[i];
                kMax = kMin;
                break;
            }
        }
        if (i == iQuantity)
        {
            kSphere.Radius = FIXED_NEG_ONE;
            return kSphere;
        }
		
        for (++i; i < iQuantity; i++)
        {
            if (abValid[i])
            {
                if (akPoint[i].X() < kMin.X())
                {
                    kMin.X() = akPoint[i].X();
                }
                else if (akPoint[i].X() > kMax.X())
                {
                    kMax.X() = akPoint[i].X();
                }
				
                if (akPoint[i].Y() < kMin.Y())
                {
                    kMin.Y() = akPoint[i].Y();
                }
                else if (akPoint[i].Y() > kMax.Y())
                {
                    kMax.Y() = akPoint[i].Y();
                }
				
                if (akPoint[i].Z() < kMin.Z())
                {
                    kMin.Z() = akPoint[i].Z();
                }
                else if (akPoint[i].Z() > kMax.Z())
                {
                    kMax.Z() = akPoint[i].Z();
                }
            }
        }
    }
	
    kSphere.Center = (FIXED_HALF)*(kMax + kMin);
    Vector3x kHalfDiagonal = (FIXED_HALF)*(kMax - kMin);
    kSphere.Radius = kHalfDiagonal.Length();
    return kSphere;
}
Sphere3x ContSphereAverage (int iQuantity, const Vector3x* akPoint,
								 const bool* abValid)
{
    Sphere3x kSphere(Vector3x::ZERO,fixed(FIXED_ZERO));
    int i;
    Vector3x kDiff;
    fixed fRadiusSqr;
	
    if (!abValid)
    {
        kSphere.Center = akPoint[0];
        for (i = 1; i < iQuantity; i++)
        {
            kSphere.Center += akPoint[i];
        }
        kSphere.Center /= FixedFromInt(iQuantity);
		
        for (i = 0; i < iQuantity; i++)
        {
            kDiff = akPoint[i] - kSphere.Center;
            fRadiusSqr = kDiff.SquaredLength();
            if (fRadiusSqr > kSphere.Radius)
            {
                kSphere.Radius = fRadiusSqr;
            }
        }
    }
    else
    {
        int iValidQuantity = 0;
        for (i = 0; i < iQuantity; i++)
        {
            if (abValid[i])
            {
                kSphere.Center += akPoint[i];
                iValidQuantity++;
            }
        }
        if (iValidQuantity == 0)
        {
            kSphere.Radius = FIXED_NEG_ONE;
            return kSphere;
        }
        kSphere.Center /= FixedFromInt(iValidQuantity);
		
        for (i = 0; i < iQuantity; i++)
        {
            if (abValid[i])
            {
                kDiff = akPoint[i] - kSphere.Center;
                fRadiusSqr = kDiff.SquaredLength();
                if (fRadiusSqr > kSphere.Radius)
                {
                    kSphere.Radius = fRadiusSqr;
                }
            }
        }
    }
	
    kSphere.Radius = Mathx::Sqrt(kSphere.Radius);
    return kSphere;
}
//----------------------------------------------------------------------------

Sphere3x MergeSpheres (const Sphere3x& rkSphere0,
							const Sphere3x& rkSphere1)
{
    Vector3x kCDiff = rkSphere1.Center - rkSphere0.Center;
    fixed fLSqr = kCDiff.SquaredLength();
    fixed fRDiff = rkSphere1.Radius - rkSphere0.Radius;
    fixed fRDiffSqr = fRDiff*fRDiff;
	
    if (fRDiffSqr >= fLSqr)
    {
        return (fRDiff >= FIXED_ZERO ? rkSphere1 : rkSphere0);
    }
	
    fixed fLength = Mathx::Sqrt(fLSqr);
    Sphere3x kSphere;
	
    if (fLength > Mathx::ZERO_TOLERANCE)
    {
        fixed fCoeff = (fLength + fRDiff)/(FixedFromFloat((float)2.0)*fLength);
        kSphere.Center = rkSphere0.Center + fCoeff*kCDiff;
    }
    else
    {
        kSphere.Center = rkSphere0.Center;
    }
	
    kSphere.Radius = (FIXED_HALF)*(fLength + rkSphere0.Radius +
        rkSphere1.Radius);
	
    return kSphere;
}

bool InSphere (const Vector3x& rkPoint, const Sphere3x& rkSphere)
{
    Vector3x kDiff = rkPoint - rkSphere.Center;
    return kDiff.Length() <= rkSphere.Radius;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// MinSphere3x
//
// All internal minimal sphere calculations store the squared radius in the
// radius member of Sphere3x.  Only at the end is a sqrt computed.
//----------------------------------------------------------------------------

MinSphere3x::MinSphere3x (int iQuantity, const Vector3x* akPoint,
    Sphere3x& rkMinimal, fixed fEpsilon)
{
    m_fEpsilon = fEpsilon;
    m_aoUpdate[0] = 0;
    m_aoUpdate[1] = &MinSphere3x::UpdateSupport1;
    m_aoUpdate[2] = &MinSphere3x::UpdateSupport2;
    m_aoUpdate[3] = &MinSphere3x::UpdateSupport3;
    m_aoUpdate[4] = &MinSphere3x::UpdateSupport4;

    Support kSupp;
    fixed fDistDiff;

    if (iQuantity >= 1)
    {
        // create identity permutation (0,1,...,iQuantity-1)
        Vector3x** apkPerm = WG_NEW Vector3x*[iQuantity];
        int i;
        for (i = 0; i < iQuantity; i++)
        {
            apkPerm[i] = (Vector3x*)&akPoint[i];
        }

        // generate random permutation
        for (i = iQuantity-1; i > 0; i--)
        {
            int j = rand() % (i+1);
            if (j != i)
            {
                Vector3x* pSave = apkPerm[i];
                apkPerm[i] = apkPerm[j];
                apkPerm[j] = pSave;
            }
        }

        rkMinimal = ExactSphere1(*apkPerm[0]);
        kSupp.Quantity = 1;
        kSupp.Index[0] = 0;
        i = 1;
        while (i < iQuantity)
        {
            if (!kSupp.Contains(i,apkPerm,m_fEpsilon))
            {
                if (!Contains(*apkPerm[i],rkMinimal,fDistDiff))
                {
                    UpdateFunction oUpdate = m_aoUpdate[kSupp.Quantity];
                    Sphere3x kSph =(this->*oUpdate)(i,apkPerm,kSupp);
                    if (kSph.Radius > rkMinimal.Radius)
                    {
                        rkMinimal = kSph;
                        i = 0;
                        continue;
                    }
                }
            }
            i++;
        }

        WG_DELETE[] apkPerm;
    }
    else
    {
        assert(false);
    }

    rkMinimal.Radius = Mathx::Sqrt(rkMinimal.Radius);
}
//----------------------------------------------------------------------------

bool MinSphere3x::Contains (const Vector3x& rkP,
    const Sphere3x& rkS, fixed& rfDistDiff)
{
    Vector3x kDiff = rkP - rkS.Center;
    fixed fTest = kDiff.SquaredLength();

    // NOTE:  In this algorithm, Sphere3x is storing the *squared radius*,
    // so the next line of code is not in error.
    rfDistDiff = fTest - rkS.Radius;

    return rfDistDiff <= FIXED_ZERO;
}
//----------------------------------------------------------------------------

Sphere3x MinSphere3x::ExactSphere1 (const Vector3x& rkP)
{
    Sphere3x kMinimal;
    kMinimal.Center = rkP;
    kMinimal.Radius = FIXED_ZERO;
    return kMinimal;
}
//----------------------------------------------------------------------------

Sphere3x MinSphere3x::ExactSphere2 (const Vector3x& rkP0,
    const Vector3x& rkP1)
{
    Sphere3x kMinimal;
    kMinimal.Center = (FIXED_HALF)*(rkP0+rkP1);
    Vector3x kDiff = rkP1 - rkP0;
    kMinimal.Radius = FixedFromFloat((float)0.25)*kDiff.SquaredLength();
    return kMinimal;
}
//----------------------------------------------------------------------------

Sphere3x MinSphere3x::ExactSphere3 (const Vector3x& rkP0,
    const Vector3x& rkP1, const Vector3x& rkP2)
{
    // Compute the circle (in 3D) containing p0, p1, and p2.  The Center in
    // barycentric coordinates is K = u0*p0+u1*p1+u2*p2 where u0+u1+u2=1.
    // The Center is equidistant from the three points, so |K-p0| = |K-p1| =
    // |K-p2| = R where R is the radius of the circle.
    //
    // From these conditions,
    //   K-p0 = u0*A + u1*B - A
    //   K-p1 = u0*A + u1*B - B
    //   K-p2 = u0*A + u1*B
    // where A = p0-p2 and B = p1-p2, which leads to
    //   r^2 = |u0*A+u1*B|^2 - 2*Dot(A,u0*A+u1*B) + |A|^2
    //   r^2 = |u0*A+u1*B|^2 - 2*Dot(B,u0*A+u1*B) + |B|^2
    //   r^2 = |u0*A+u1*B|^2
    // Subtracting the last equation from the first two and writing
    // the equations as a linear system,
    //
    // +-                 -++   -+       +-        -+
    // | Dot(A,A) Dot(A,B) || u0 | = 0.5 | Dot(A,A) |
    // | Dot(B,A) Dot(B,B) || u1 |       | Dot(B,B) |
    // +-                 -++   -+       +-        -+
    //
    // The following code solves this system for u0 and u1, then
    // evaluates the third equation in r^2 to obtain r.

    Vector3x kA = rkP0 - rkP2;
    Vector3x kB = rkP1 - rkP2;
    fixed fAdA = kA.Dot(kA);
    fixed fAdB = kA.Dot(kB);
    fixed fBdB = kB.Dot(kB);
    fixed fDet = fAdA*fBdB-fAdB*fAdB;

    Sphere3x kMinimal;

    if (Mathx::FAbs(fDet) > m_fEpsilon)
    {
        fixed fHalfInvDet = (FIXED_HALF)/fDet;
        fixed fU0 = fHalfInvDet*fBdB*(fAdA-fAdB);
        fixed fU1 = fHalfInvDet*fAdA*(fBdB-fAdB);
        fixed fU2 = FIXED_ONE-fU0-fU1;
        kMinimal.Center = fU0*rkP0 + fU1*rkP1 + fU2*rkP2;
        Vector3x kTmp = fU0*kA + fU1*kB;
        kMinimal.Radius = kTmp.SquaredLength();
    }
    else
    {
        kMinimal.Center = Vector3x::ZERO;
        kMinimal.Radius = Mathx::MAX_REAL;
    }

    return kMinimal;
}
//----------------------------------------------------------------------------

Sphere3x MinSphere3x::ExactSphere4 (const Vector3x& rkP0,
    const Vector3x& rkP1, const Vector3x& rkP2,
    const Vector3x& rkP3)
{
    // Compute the sphere containing p0, p1, p2, and p3.  The Center in
    // barycentric coordinates is K = u0*p0+u1*p1+u2*p2+u3*p3 where
    // u0+u1+u2+u3=1.  The Center is equidistant from the three points, so
    // |K-p0| = |K-p1| = |K-p2| = |K-p3| = R where R is the radius of the
    // sphere.
    //
    // From these conditions,
    //   K-p0 = u0*A + u1*B + u2*C - A
    //   K-p1 = u0*A + u1*B + u2*C - B
    //   K-p2 = u0*A + u1*B + u2*C - C
    //   K-p3 = u0*A + u1*B + u2*C
    // where A = p0-p3, B = p1-p3, and C = p2-p3 which leads to
    //   r^2 = |u0*A+u1*B+u2*C|^2 - 2*Dot(A,u0*A+u1*B+u2*C) + |A|^2
    //   r^2 = |u0*A+u1*B+u2*C|^2 - 2*Dot(B,u0*A+u1*B+u2*C) + |B|^2
    //   r^2 = |u0*A+u1*B+u2*C|^2 - 2*Dot(C,u0*A+u1*B+u2*C) + |C|^2
    //   r^2 = |u0*A+u1*B+u2*C|^2
    // Subtracting the last equation from the first three and writing
    // the equations as a linear system,
    //
    // +-                          -++   -+       +-        -+
    // | Dot(A,A) Dot(A,B) Dot(A,C) || u0 | = 0.5 | Dot(A,A) |
    // | Dot(B,A) Dot(B,B) Dot(B,C) || u1 |       | Dot(B,B) |
    // | Dot(C,A) Dot(C,B) Dot(C,C) || u2 |       | Dot(C,C) |
    // +-                          -++   -+       +-        -+
    //
    // The following code solves this system for u0, u1, and u2, then
    // evaluates the fourth equation in r^2 to obtain r.

    Vector3x kE10 = rkP0 - rkP3;
    Vector3x kE20 = rkP1 - rkP3;
    Vector3x kE30 = rkP2 - rkP3;

    fixed aafA[3][3];
    aafA[0][0] = kE10.Dot(kE10);
    aafA[0][1] = kE10.Dot(kE20);
    aafA[0][2] = kE10.Dot(kE30);
    aafA[1][0] = aafA[0][1];
    aafA[1][1] = kE20.Dot(kE20);
    aafA[1][2] = kE20.Dot(kE30);
    aafA[2][0] = aafA[0][2];
    aafA[2][1] = aafA[1][2];
    aafA[2][2] = kE30.Dot(kE30);

    fixed afB[3];
    afB[0] = (FIXED_HALF)*aafA[0][0];
    afB[1] = (FIXED_HALF)*aafA[1][1];
    afB[2] = (FIXED_HALF)*aafA[2][2];

    fixed aafAInv[3][3];
    aafAInv[0][0] = aafA[1][1]*aafA[2][2]-aafA[1][2]*aafA[2][1];
    aafAInv[0][1] = aafA[0][2]*aafA[2][1]-aafA[0][1]*aafA[2][2];
    aafAInv[0][2] = aafA[0][1]*aafA[1][2]-aafA[0][2]*aafA[1][1];
    aafAInv[1][0] = aafA[1][2]*aafA[2][0]-aafA[1][0]*aafA[2][2];
    aafAInv[1][1] = aafA[0][0]*aafA[2][2]-aafA[0][2]*aafA[2][0];
    aafAInv[1][2] = aafA[0][2]*aafA[1][0]-aafA[0][0]*aafA[1][2];
    aafAInv[2][0] = aafA[1][0]*aafA[2][1]-aafA[1][1]*aafA[2][0];
    aafAInv[2][1] = aafA[0][1]*aafA[2][0]-aafA[0][0]*aafA[2][1];
    aafAInv[2][2] = aafA[0][0]*aafA[1][1]-aafA[0][1]*aafA[1][0];
    fixed fDet = aafA[0][0]*aafAInv[0][0] + aafA[0][1]*aafAInv[1][0] +
        aafA[0][2]*aafAInv[2][0];

    Sphere3x kMinimal;

    if (Mathx::FAbs(fDet) > m_fEpsilon)
    {
        fixed fInvDet = (FIXED_ONE)/fDet;
        int iRow, iCol;
        for (iRow = 0; iRow < 3; iRow++)
        {
            for (iCol = 0; iCol < 3; iCol++)
            {
                aafAInv[iRow][iCol] *= fInvDet;
            }
        }
        
        fixed afU[4];
        for (iRow = 0; iRow < 3; iRow++)
        {
            afU[iRow] = FIXED_ZERO;
            for (iCol = 0; iCol < 3; iCol++)
            {
                afU[iRow] += aafAInv[iRow][iCol]*afB[iCol];
            }
        }
        afU[3] = FIXED_ONE - afU[0] - afU[1] - afU[2];
        
        kMinimal.Center = afU[0]*rkP0 + afU[1]*rkP1 + afU[2]*rkP2 +
            afU[3]*rkP3;
        Vector3x kTmp = afU[0]*kE10 + afU[1]*kE20 + afU[2]*kE30;
        kMinimal.Radius = kTmp.SquaredLength();
    }
    else
    {
        kMinimal.Center = Vector3x::ZERO;
        kMinimal.Radius = Mathx::MAX_REAL;
    }

    return kMinimal;
}
//----------------------------------------------------------------------------

Sphere3x MinSphere3x::UpdateSupport1 (int i,
    Vector3x** apkPerm, Support& rkSupp)
{
    const Vector3x& rkP0 = *apkPerm[rkSupp.Index[0]];
    const Vector3x& rkP1 = *apkPerm[i];

    Sphere3x kMinimal = ExactSphere2(rkP0,rkP1);
    rkSupp.Quantity = 2;
    rkSupp.Index[1] = i;

    return kMinimal;
}
//----------------------------------------------------------------------------

Sphere3x MinSphere3x::UpdateSupport2 (int i,
    Vector3x** apkPerm, Support& rkSupp)
{
    const Vector3x& rkP0 = *apkPerm[rkSupp.Index[0]];
    const Vector3x& rkP1 = *apkPerm[rkSupp.Index[1]];
    const Vector3x& rkP2 = *apkPerm[i];

    Sphere3x akS[3];
    fixed fMinRSqr = Mathx::MAX_REAL;
    fixed fDistDiff;
    int iIndex = -1;

    akS[0] = ExactSphere2(rkP0,rkP2);
    if (Contains(rkP1,akS[0],fDistDiff))
    {
        fMinRSqr = akS[0].Radius;
        iIndex = 0;
    }

    akS[1] = ExactSphere2(rkP1,rkP2);
    if (akS[1].Radius < fMinRSqr)
    {
        if (Contains(rkP0,akS[1],fDistDiff))
        {
            fMinRSqr = akS[1].Radius;
            iIndex = 1;
        }
    }

    Sphere3x kMinimal;

    if (iIndex != -1)
    {
        kMinimal = akS[iIndex];
        rkSupp.Index[1-iIndex] = i;
    }
    else
    {
        kMinimal = ExactSphere3(rkP0,rkP1,rkP2);
        assert(kMinimal.Radius <= fMinRSqr);
        rkSupp.Quantity = 3;
        rkSupp.Index[2] = i;
    }

    return kMinimal;
}
//----------------------------------------------------------------------------

Sphere3x MinSphere3x::UpdateSupport3 (int i,
    Vector3x** apkPerm, Support& rkSupp)
{
    const Vector3x& rkP0 = *apkPerm[rkSupp.Index[0]];
    const Vector3x& rkP1 = *apkPerm[rkSupp.Index[1]];
    const Vector3x& rkP2 = *apkPerm[rkSupp.Index[2]];
    const Vector3x& rkP3 = *apkPerm[i];

    Sphere3x akS[6];
    fixed fMinRSqr = Mathx::MAX_REAL;
    fixed fDistDiff;
    int iIndex = -1;

    akS[0] = ExactSphere2(rkP0,rkP3);
    if (Contains(rkP1,akS[0],fDistDiff) && Contains(rkP2,akS[0],fDistDiff))
    {
        fMinRSqr = akS[0].Radius;
        iIndex = 0;
    }

    akS[1] = ExactSphere2(rkP1,rkP3);
    if (akS[1].Radius < fMinRSqr
    &&  Contains(rkP0,akS[1],fDistDiff) && Contains(rkP2,akS[1],fDistDiff))
    {
        fMinRSqr = akS[1].Radius;
        iIndex = 1;
    }

    akS[2] = ExactSphere2(rkP2,rkP3);
    if (akS[2].Radius < fMinRSqr
    &&  Contains(rkP0,akS[2],fDistDiff) && Contains(rkP1,akS[2],fDistDiff))
    {
        fMinRSqr = akS[2].Radius;
        iIndex = 2;
    }

    akS[3] = ExactSphere3(rkP0,rkP1,rkP3);
    if (akS[3].Radius < fMinRSqr && Contains(rkP2,akS[3],fDistDiff))
    {
        fMinRSqr = akS[3].Radius;
        iIndex = 3;
    }

    akS[4] = ExactSphere3(rkP0,rkP2,rkP3);
    if (akS[4].Radius < fMinRSqr && Contains(rkP1,akS[4],fDistDiff))
    {
        fMinRSqr = akS[4].Radius;
        iIndex = 4;
    }

    akS[5] = ExactSphere3(rkP1,rkP2,rkP3);
    if (akS[5].Radius < fMinRSqr && Contains(rkP0,akS[5],fDistDiff))
    {
        fMinRSqr = akS[5].Radius;
        iIndex = 5;
    }

    Sphere3x kMinimal;

    switch (iIndex)
    {
    case 0:
        kMinimal = akS[0];
        rkSupp.Quantity = 2;
        rkSupp.Index[1] = i;
        break;
    case 1:
        kMinimal = akS[1];
        rkSupp.Quantity = 2;
        rkSupp.Index[0] = i;
        break;
    case 2:
        kMinimal = akS[2];
        rkSupp.Quantity = 2;
        rkSupp.Index[0] = rkSupp.Index[2];
        rkSupp.Index[1] = i;
        break;
    case 3:
        kMinimal = akS[3];
        rkSupp.Index[2] = i;
        break;
    case 4:
        kMinimal = akS[4];
        rkSupp.Index[1] = i;
        break;
    case 5:
        kMinimal = akS[5];
        rkSupp.Index[0] = i;
        break;
    default:
        kMinimal = ExactSphere4(rkP0,rkP1,rkP2,rkP3);
        assert(kMinimal.Radius <= fMinRSqr);
        rkSupp.Quantity = 4;
        rkSupp.Index[3] = i;
        break;
    }

    return kMinimal;
}
//----------------------------------------------------------------------------

Sphere3x MinSphere3x::UpdateSupport4 (int i,
    Vector3x** apkPerm, Support& rkSupp)
{
    const Vector3x* apkPt[4] =
    {
        apkPerm[rkSupp.Index[0]],
        apkPerm[rkSupp.Index[1]],
        apkPerm[rkSupp.Index[2]],
        apkPerm[rkSupp.Index[3]]
    };

    const Vector3x& rkP4 = *apkPerm[i];

    // permutations of type 1
    int aiT1[4][4] =
    {
        {0, /*4*/ 1,2,3},
        {1, /*4*/ 0,2,3},
        {2, /*4*/ 0,1,3},
        {3, /*4*/ 0,1,2}
    };

    // permutations of type 2
    int aiT2[6][4] =
    {
        {0,1, /*4*/ 2,3},
        {0,2, /*4*/ 1,3},
        {0,3, /*4*/ 1,2},
        {1,2, /*4*/ 0,3},
        {1,3, /*4*/ 0,2},
        {2,3, /*4*/ 0,1}
    };

    // permutations of type 3
    int aiT3[4][4] =
    {
        {0,1,2, /*4*/ 3},
        {0,1,3, /*4*/ 2},
        {0,2,3, /*4*/ 1},
        {1,2,3, /*4*/ 0}
    };

    Sphere3x akS[14];
    fixed fMinRSqr = Mathx::MAX_REAL;
    int iIndex = -1;
    fixed fDistDiff, fMinDistDiff = Mathx::MAX_REAL;
    int iMinIndex = -1;
    int k = 0;  // sphere index

    // permutations of type 1
    int j;
    for (j = 0; j < 4; j++, k++)
    {
        akS[k] = ExactSphere2(*apkPt[aiT1[j][0]],rkP4);
        if (akS[k].Radius < fMinRSqr)
        {
            if (Contains(*apkPt[aiT1[j][1]],akS[k],fDistDiff)
            &&  Contains(*apkPt[aiT1[j][2]],akS[k],fDistDiff)
            &&  Contains(*apkPt[aiT1[j][3]],akS[k],fDistDiff))
            {
                fMinRSqr = akS[k].Radius;
                iIndex = k;
            }
            else if (fDistDiff < fMinDistDiff)
            {
                fMinDistDiff = fDistDiff;
                iMinIndex = k;
            }
        }
    }

    // permutations of type 2
    for (j = 0; j < 6; j++, k++)
    {
        akS[k] = ExactSphere3(*apkPt[aiT2[j][0]],*apkPt[aiT2[j][1]],rkP4);
        if (akS[k].Radius < fMinRSqr)
        {
            if (Contains(*apkPt[aiT2[j][2]],akS[k],fDistDiff)
            &&  Contains(*apkPt[aiT2[j][3]],akS[k],fDistDiff))
            {
                fMinRSqr = akS[k].Radius;
                iIndex = k;
            }
            else if (fDistDiff < fMinDistDiff)
            {
                fMinDistDiff = fDistDiff;
                iMinIndex = k;
            }
        }
    }

    // permutations of type 3
    for (j = 0; j < 4; j++, k++)
    {
        akS[k] = ExactSphere4(*apkPt[aiT3[j][0]],*apkPt[aiT3[j][1]],
            *apkPt[aiT3[j][2]],rkP4);
        if (akS[k].Radius < fMinRSqr)
        {
            if (Contains(*apkPt[aiT3[j][3]],akS[k],fDistDiff))
            {
                fMinRSqr = akS[k].Radius;
                iIndex = k;
            }
            else if (fDistDiff < fMinDistDiff)
            {
                fMinDistDiff = fDistDiff;
                iMinIndex = k;
            }
        }
    }

    // Theoretically, iIndex >= 0 should happen, but floating point round-off
    // error can lead to this.  When this happens, the sphere is chosen that
    // has the minimum absolute errors between points (barely) outside the
    // sphere and the sphere.
    if (iIndex == -1)
    {
        iIndex = iMinIndex;
    }

    Sphere3x kMinimal = akS[iIndex];

    switch (iIndex)
    {
    case 0:
        rkSupp.Quantity = 2;
        rkSupp.Index[1] = i;
        break;
    case 1:
        rkSupp.Quantity = 2;
        rkSupp.Index[0] = i;
        break;
    case 2:
        rkSupp.Quantity = 2;
        rkSupp.Index[0] = rkSupp.Index[2];
        rkSupp.Index[1] = i;
        break;
    case 3:
        rkSupp.Quantity = 2;
        rkSupp.Index[0] = rkSupp.Index[3];
        rkSupp.Index[1] = i;
        break;
    case 4:
        rkSupp.Quantity = 3;
        rkSupp.Index[2] = i;
        break;
    case 5:
        rkSupp.Quantity = 3;
        rkSupp.Index[1] = i;
        break;
    case 6:
        rkSupp.Quantity = 3;
        rkSupp.Index[1] = rkSupp.Index[3];
        rkSupp.Index[2] = i;
        break;
    case 7:
        rkSupp.Quantity = 3;
        rkSupp.Index[0] = i;
        break;
    case 8:
        rkSupp.Quantity = 3;
        rkSupp.Index[0] = rkSupp.Index[3];
        rkSupp.Index[2] = i;
        break;
    case 9:
        rkSupp.Quantity = 3;
        rkSupp.Index[0] = rkSupp.Index[3];
        rkSupp.Index[1] = i;
        break;
    case 10:
        rkSupp.Index[3] = i;
        break;
    case 11:
        rkSupp.Index[2] = i;
        break;
    case 12:
        rkSupp.Index[1] = i;
        break;
    case 13:
        rkSupp.Index[0] = i;
        break;
    }

    return kMinimal;
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// explicit instantiation
//----------------------------------------------------------------------------
template WG3D_FOUNDATION_ITEM
Sphere3<float> ContSphereOfAABB<float> (int, const Vector3<float>*,
    const bool*);

template WG3D_FOUNDATION_ITEM
Sphere3<float> ContSphereAverage<float> (int, const Vector3<float>*,
    const bool*);

template WG3D_FOUNDATION_ITEM
bool InSphere<float> (const Vector3<float>&, const Sphere3<float>&);

template WG3D_FOUNDATION_ITEM
Sphere3<float> MergeSpheres<float> (const Sphere3<float>&,
    const Sphere3<float>&);

template WG3D_FOUNDATION_ITEM
class MinSphere3<float>;

template WG3D_FOUNDATION_ITEM
Sphere3<double> ContSphereOfAABB<double> (int, const Vector3<double>*,
    const bool*);

template WG3D_FOUNDATION_ITEM
Sphere3<double> ContSphereAverage<double> (int, const Vector3<double>*,
    const bool*);

template WG3D_FOUNDATION_ITEM
bool InSphere<double> (const Vector3<double>&, const Sphere3<double>&);

template WG3D_FOUNDATION_ITEM
Sphere3<double> MergeSpheres<double> (const Sphere3<double>&,
    const Sphere3<double>&);

template WG3D_FOUNDATION_ITEM
class MinSphere3<double>;
//----------------------------------------------------------------------------
}

