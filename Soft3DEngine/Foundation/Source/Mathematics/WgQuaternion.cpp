///////////////////////////////////////////////////////////
//                                                       //
//                    WgQuaternion.cpp                   //
//                                                       //
//  - Implementation for Quaternion class                //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgFoundationPCH.h"
#include "WgQuaternion.h"
using namespace WGSoft3D;

template<> const Quaternion<float>
    Quaternion<float>::IDENTITY(1.0f,0.0f,0.0f,0.0f);
template<> const Quaternion<float>
    Quaternion<float>::ZERO(0.0f,0.0f,0.0f,0.0f);
template<> int Quaternion<float>::ms_iNext[3] = { 1, 2, 0 };

template<> const Quaternion<double>
    Quaternion<double>::IDENTITY(1.0,0.0,0.0,0.0);
template<> const Quaternion<double>
    Quaternion<double>::ZERO(0.0,0.0,0.0,0.0);
template<> int Quaternion<double>::ms_iNext[3] = { 1, 2, 0 };

const Quaternionx Quaternionx::IDENTITY(FIXED_ONE,FIXED_ZERO,FIXED_ZERO,FIXED_ZERO);
const Quaternionx Quaternionx::ZERO(FIXED_ZERO,FIXED_ZERO,FIXED_ZERO,FIXED_ZERO);
int Quaternionx::ms_iNext[3] = { 1, 2, 0 };





//----------------------------------------------------------------------------

Quaternionx::Quaternionx ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------

Quaternionx::Quaternionx (fixed fW, fixed fX, fixed fY, fixed fZ)
{
    m_afTuple[0] = fW;
    m_afTuple[1] = fX;
    m_afTuple[2] = fY;
    m_afTuple[3] = fZ;
}
//----------------------------------------------------------------------------

Quaternionx::Quaternionx (const Quaternionx& rkQ)
{
    size_t uiSize = 4*sizeof(fixed);
    System::Memcpy(m_afTuple,uiSize,rkQ.m_afTuple,uiSize);
}
//----------------------------------------------------------------------------

Quaternionx::Quaternionx (const Matrix3x& rkRot)
{
    FromRotationMatrix(rkRot);
}
//----------------------------------------------------------------------------

Quaternionx::Quaternionx (const Vector3x& rkAxis, fixed fAngle)
{
    FromAxisAngle(rkAxis,fAngle);
}
//----------------------------------------------------------------------------

Quaternionx::Quaternionx (const Vector3x akRotColumn[3])
{
    FromRotationMatrix(akRotColumn);
}
//----------------------------------------------------------------------------

Quaternionx::operator const fixed* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------

Quaternionx::operator fixed* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------

fixed Quaternionx::operator[] (int i) const
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------

fixed& Quaternionx::operator[] (int i)
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------

fixed Quaternionx::W () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------

fixed& Quaternionx::W ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------

fixed Quaternionx::X () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------

fixed& Quaternionx::X ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------

fixed Quaternionx::Y () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------

fixed& Quaternionx::Y ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------

fixed Quaternionx::Z () const
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------

fixed& Quaternionx::Z ()
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::operator= (const Quaternionx& rkQ)
{
    size_t uiSize = 4*sizeof(fixed);
    System::Memcpy(m_afTuple,uiSize,rkQ.m_afTuple,uiSize);
    return *this;
}
//----------------------------------------------------------------------------

int Quaternionx::CompareArrays (const Quaternionx& rkQ) const
{
    return memcmp(m_afTuple,rkQ.m_afTuple,4*sizeof(fixed));
}
//----------------------------------------------------------------------------

bool Quaternionx::operator== (const Quaternionx& rkQ) const
{
    return CompareArrays(rkQ) == 0;
}
//----------------------------------------------------------------------------

bool Quaternionx::operator!= (const Quaternionx& rkQ) const
{
    return CompareArrays(rkQ) != 0;
}
//----------------------------------------------------------------------------

bool Quaternionx::operator< (const Quaternionx& rkQ) const
{
    return CompareArrays(rkQ) < 0;
}
//----------------------------------------------------------------------------

bool Quaternionx::operator<= (const Quaternionx& rkQ) const
{
    return CompareArrays(rkQ) <= 0;
}
//----------------------------------------------------------------------------

bool Quaternionx::operator> (const Quaternionx& rkQ) const
{
    return CompareArrays(rkQ) > 0;
}
//----------------------------------------------------------------------------

bool Quaternionx::operator>= (const Quaternionx& rkQ) const
{
    return CompareArrays(rkQ) >= 0;
}
//----------------------------------------------------------------------------

Quaternionx Quaternionx::operator+ (const Quaternionx& rkQ) const
{
    Quaternionx kSum;
    for (int i = 0; i < 4; i++)
    {
        kSum.m_afTuple[i] = m_afTuple[i] + rkQ.m_afTuple[i];
    }
    return kSum;
}
//----------------------------------------------------------------------------

Quaternionx Quaternionx::operator- (const Quaternionx& rkQ) const
{
    Quaternionx kDiff;
    for (int i = 0; i < 4; i++)
    {
        kDiff.m_afTuple[i] = m_afTuple[i] - rkQ.m_afTuple[i];
    }
    return kDiff;
}
//----------------------------------------------------------------------------

Quaternionx Quaternionx::operator* (const Quaternionx& rkQ) const
{
    // NOTE:  Multiplication is not generally commutative, so in most
    // cases p*q != q*p.

    Quaternionx kProd;

    kProd.m_afTuple[0] =
        m_afTuple[0]*rkQ.m_afTuple[0] -
        m_afTuple[1]*rkQ.m_afTuple[1] -
        m_afTuple[2]*rkQ.m_afTuple[2] -
        m_afTuple[3]*rkQ.m_afTuple[3];

    kProd.m_afTuple[1] =
        m_afTuple[0]*rkQ.m_afTuple[1] +
        m_afTuple[1]*rkQ.m_afTuple[0] +
        m_afTuple[2]*rkQ.m_afTuple[3] -
        m_afTuple[3]*rkQ.m_afTuple[2];

    kProd.m_afTuple[2] =
        m_afTuple[0]*rkQ.m_afTuple[2] +
        m_afTuple[2]*rkQ.m_afTuple[0] +
        m_afTuple[3]*rkQ.m_afTuple[1] -
        m_afTuple[1]*rkQ.m_afTuple[3];

    kProd.m_afTuple[3] =
        m_afTuple[0]*rkQ.m_afTuple[3] +
        m_afTuple[3]*rkQ.m_afTuple[0] +
        m_afTuple[1]*rkQ.m_afTuple[2] -
        m_afTuple[2]*rkQ.m_afTuple[1];

    return kProd;
}
//----------------------------------------------------------------------------

Quaternionx Quaternionx::operator* (fixed fScalar) const
{
    Quaternionx kProd;
    for (int i = 0; i < 4; i++)
    {
        kProd.m_afTuple[i] = fScalar*m_afTuple[i];
    }
    return kProd;
}
//----------------------------------------------------------------------------

Quaternionx Quaternionx::operator/ (fixed fScalar) const
{
    Quaternionx kQuot;
    int i;

    if (fScalar != FIXED_ZERO)
    {
        fixed fInvScalar = (FIXED_ONE)/fScalar;
        for (i = 0; i < 4; i++)
        {
            kQuot.m_afTuple[i] = fInvScalar*m_afTuple[i];
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            kQuot.m_afTuple[i] = Mathx::MAX_REAL;
        }
    }

    return kQuot;
}
//----------------------------------------------------------------------------

Quaternionx Quaternionx::operator- () const
{
    Quaternionx kNeg;
    for (int i = 0; i < 4; i++)
    {
        kNeg.m_afTuple[i] = -m_afTuple[i];
    }
    return kNeg;
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::operator+= (const Quaternionx& rkQ)
{
    for (int i = 0; i < 4; i++)
    {
        m_afTuple[i] += rkQ.m_afTuple[i];
    }
    return *this;
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::operator-= (const Quaternionx& rkQ)
{
    for (int i = 0; i < 4; i++)
    {
        m_afTuple[i] -= rkQ.m_afTuple[i];
    }
    return *this;
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::operator*= (fixed fScalar)
{
    for (int i = 0; i < 4; i++)
    {
        m_afTuple[i] *= fScalar;
    }
    return *this;
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::operator/= (fixed fScalar)
{
    int i;

    if (fScalar != FIXED_ZERO)
    {
        fixed fInvScalar = (FIXED_ONE)/fScalar;
        for (i = 0; i < 4; i++)
        {
            m_afTuple[i] *= fInvScalar;
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            m_afTuple[i] = Mathx::MAX_REAL;
        }
    }

    return *this;
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::FromRotationMatrix (
    const Matrix3x& rkRot)
{
    // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
    // article "Quaternionx Calculus and Fast Animation".

    fixed fTrace = rkRot(0,0) + rkRot(1,1) + rkRot(2,2);
    fixed fRoot;

    if (fTrace > FIXED_ZERO)
    {
        // |w| > 1/2, may as well choose w > 1/2
        fRoot = Mathx::Sqrt(fTrace + FIXED_ONE);  // 2w
        m_afTuple[0] = (FIXED_HALF)*fRoot;
        fRoot = (FIXED_HALF)/fRoot;  // 1/(4w)
        m_afTuple[1] = (rkRot(2,1)-rkRot(1,2))*fRoot;
        m_afTuple[2] = (rkRot(0,2)-rkRot(2,0))*fRoot;
        m_afTuple[3] = (rkRot(1,0)-rkRot(0,1))*fRoot;
    }
    else
    {
        // |w| <= 1/2
        int i = 0;
        if (rkRot(1,1) > rkRot(0,0))
        {
            i = 1;
        }
        if (rkRot(2,2) > rkRot(i,i))
        {
            i = 2;
        }
        int j = ms_iNext[i];
        int k = ms_iNext[j];

        fRoot = Mathx::Sqrt(rkRot(i,i)-rkRot(j,j)-rkRot(k,k)+FIXED_ONE);
        fixed* apfQuat[3] = { &m_afTuple[1], &m_afTuple[2], &m_afTuple[3] };
        *apfQuat[i] = (FIXED_HALF)*fRoot;
        fRoot = (FIXED_HALF)/fRoot;
        m_afTuple[0] = (rkRot(k,j)-rkRot(j,k))*fRoot;
        *apfQuat[j] = (rkRot(j,i)+rkRot(i,j))*fRoot;
        *apfQuat[k] = (rkRot(k,i)+rkRot(i,k))*fRoot;
    }

    return *this;
}
//----------------------------------------------------------------------------

void Quaternionx::ToRotationMatrix (Matrix3x& rkRot) const
{
    fixed fTx  = (FixedFromFloat(2.0f))*m_afTuple[1];
    fixed fTy  = (FixedFromFloat(2.0f))*m_afTuple[2];
    fixed fTz  = (FixedFromFloat(2.0f))*m_afTuple[3];
    fixed fTwx = fTx*m_afTuple[0];
    fixed fTwy = fTy*m_afTuple[0];
    fixed fTwz = fTz*m_afTuple[0];
    fixed fTxx = fTx*m_afTuple[1];
    fixed fTxy = fTy*m_afTuple[1];
    fixed fTxz = fTz*m_afTuple[1];
    fixed fTyy = fTy*m_afTuple[2];
    fixed fTyz = fTz*m_afTuple[2];
    fixed fTzz = fTz*m_afTuple[3];

    rkRot(0,0) = FIXED_ONE-(fTyy+fTzz);
    rkRot(0,1) = fTxy-fTwz;
    rkRot(0,2) = fTxz+fTwy;
    rkRot(1,0) = fTxy+fTwz;
    rkRot(1,1) = FIXED_ONE-(fTxx+fTzz);
    rkRot(1,2) = fTyz-fTwx;
    rkRot(2,0) = fTxz-fTwy;
    rkRot(2,1) = fTyz+fTwx;
    rkRot(2,2) = FIXED_ONE-(fTxx+fTyy);
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::FromRotationMatrix (
    const Vector3x akRotColumn[3])
{
    Matrix3x kRot;
    for (int iCol = 0; iCol < 3; iCol++)
    {
        kRot(0,iCol) = akRotColumn[iCol][0];
        kRot(1,iCol) = akRotColumn[iCol][1];
        kRot(2,iCol) = akRotColumn[iCol][2];
    }
    return FromRotationMatrix(kRot);
}
//----------------------------------------------------------------------------

void Quaternionx::ToRotationMatrix (Vector3x akRotColumn[3]) const
{
    Matrix3x kRot;
    ToRotationMatrix(kRot);
    for (int iCol = 0; iCol < 3; iCol++)
    {
        akRotColumn[iCol][0] = kRot(0,iCol);
        akRotColumn[iCol][1] = kRot(1,iCol);
        akRotColumn[iCol][2] = kRot(2,iCol);
    }
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::FromAxisAngle (
    const Vector3x& rkAxis, fixed fAngle)
{
    // assert:  axis[] is unit length
    //
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    fixed fHalfAngle = (FIXED_HALF)*fAngle;
    fixed fSin = Mathx::Sin(fHalfAngle);
    m_afTuple[0] = Mathx::Cos(fHalfAngle);
    m_afTuple[1] = fSin*rkAxis[0];
    m_afTuple[2] = fSin*rkAxis[1];
    m_afTuple[3] = fSin*rkAxis[2];

    return *this;
}
//----------------------------------------------------------------------------

void Quaternionx::ToAxisAngle (Vector3x& rkAxis, fixed& rfAngle)
    const
{
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    fixed fSqrLength = m_afTuple[1]*m_afTuple[1] + m_afTuple[2]*m_afTuple[2]
        + m_afTuple[3]*m_afTuple[3];
    if (fSqrLength > Mathx::ZERO_TOLERANCE)
    {
        rfAngle = (FixedFromFloat(2.0f))*Mathx::ACos(m_afTuple[0]);
        fixed fInvLength = Mathx::InvSqrt(fSqrLength);
        rkAxis[0] = m_afTuple[1]*fInvLength;
        rkAxis[1] = m_afTuple[2]*fInvLength;
        rkAxis[2] = m_afTuple[3]*fInvLength;
    }
    else
    {
        // angle is 0 (mod 2*pi), so any axis will do
        rfAngle = FIXED_ZERO;
        rkAxis[0] = FIXED_ONE;
        rkAxis[1] = FIXED_ZERO;
        rkAxis[2] = FIXED_ZERO;
    }
}
//----------------------------------------------------------------------------

fixed Quaternionx::Length () const
{
    return Mathx::Sqrt(
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2] +
        m_afTuple[3]*m_afTuple[3]);
}
//----------------------------------------------------------------------------

fixed Quaternionx::SquaredLength () const
{
    return
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2] +
        m_afTuple[3]*m_afTuple[3];
}
//----------------------------------------------------------------------------

fixed Quaternionx::Dot (const Quaternionx& rkQ) const
{
    fixed fDot = FIXED_ZERO;
    for (int i = 0; i < 4; i++)
    {
        fDot += m_afTuple[i]*rkQ.m_afTuple[i];
    }
    return fDot;
}
//----------------------------------------------------------------------------

fixed Quaternionx::Normalize ()
{
    fixed fLength = Length();
    int i;

    if (fLength > Mathx::ZERO_TOLERANCE)
    {
        fixed fInvLength = (FIXED_ONE)/fLength;
        for (i = 0; i < 4; i++)
        {
            m_afTuple[i] *= fInvLength;
        }
    }
    else
    {
        fLength = FIXED_ZERO;
        for (i = 0; i < 4; i++)
        {
            m_afTuple[i] = FIXED_ZERO;
        }
    }

    return fLength;
}
//----------------------------------------------------------------------------

Quaternionx Quaternionx::Inverse () const
{
    Quaternionx kInverse;

    fixed fNorm = FIXED_ZERO;
    int i;
    for (i = 0; i < 4; i++)
    {
        fNorm += m_afTuple[i]*m_afTuple[i];
    }

    if (fNorm > FIXED_ZERO)
    {
        fixed fInvNorm = (FIXED_ONE)/fNorm;
        kInverse.m_afTuple[0] = m_afTuple[0]*fInvNorm;
        kInverse.m_afTuple[1] = -m_afTuple[1]*fInvNorm;
        kInverse.m_afTuple[2] = -m_afTuple[2]*fInvNorm;
        kInverse.m_afTuple[3] = -m_afTuple[3]*fInvNorm;
    }
    else
    {
        // return an invalid result to flag the error
        for (i = 0; i < 4; i++)
        {
            kInverse.m_afTuple[i] = FIXED_ZERO;
        }
    }

    return kInverse;
}
//----------------------------------------------------------------------------

Quaternionx Quaternionx::Conjugate () const
{
    return Quaternionx(m_afTuple[0],-m_afTuple[1],-m_afTuple[2],
        -m_afTuple[3]);
}
//----------------------------------------------------------------------------

Quaternionx Quaternionx::Exp () const
{
    // If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
    // use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

    Quaternionx kResult;

    fixed fAngle = Mathx::Sqrt(m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2] + m_afTuple[3]*m_afTuple[3]);

    fixed fSin = Mathx::Sin(fAngle);
    kResult.m_afTuple[0] = Mathx::Cos(fAngle);

    int i;

    if (Mathx::FAbs(fSin) >= Mathx::ZERO_TOLERANCE)
    {
        fixed fCoeff = fSin/fAngle;
        for (i = 1; i <= 3; i++)
        {
            kResult.m_afTuple[i] = fCoeff*m_afTuple[i];
        }
    }
    else
    {
        for (i = 1; i <= 3; i++)
        {
            kResult.m_afTuple[i] = m_afTuple[i];
        }
    }

    return kResult;
}
//----------------------------------------------------------------------------

Quaternionx Quaternionx::Log () const
{
    // If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
    // sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

    Quaternionx kResult;
    kResult.m_afTuple[0] = FIXED_ZERO;

    int i;

    if (Mathx::FAbs(m_afTuple[0]) < FIXED_ONE)
    {
        fixed fAngle = Mathx::ACos(m_afTuple[0]);
        fixed fSin = Mathx::Sin(fAngle);
        if (Mathx::FAbs(fSin) >= Mathx::ZERO_TOLERANCE)
        {
            fixed fCoeff = fAngle/fSin;
            for (i = 1; i <= 3; i++)
            {
                kResult.m_afTuple[i] = fCoeff*m_afTuple[i];
            }
            return kResult;
        }
    }

    for (i = 1; i <= 3; i++)
    {
        kResult.m_afTuple[i] = m_afTuple[i];
    }
    return kResult;
}
//----------------------------------------------------------------------------

Vector3x Quaternionx::Rotate (const Vector3x& rkVector) const
{
    // Given a vector u = (x0,y0,z0) and a unit length quaternion
    // q = <w,x,y,z>, the vector v = (x1,y1,z1) which represents the
    // rotation of u by q is v = q*u*q^{-1} where * indicates quaternion
    // multiplication and where u is treated as the quaternion <0,x0,y0,z0>.
    // Note that q^{-1} = <w,-x,-y,-z>, so no real work is required to
    // invert q.  Now
    //
    //   q*u*q^{-1} = q*<0,x0,y0,z0>*q^{-1}
    //     = q*(x0*i+y0*j+z0*k)*q^{-1}
    //     = x0*(q*i*q^{-1})+y0*(q*j*q^{-1})+z0*(q*k*q^{-1})
    //
    // As 3-vectors, q*i*q^{-1}, q*j*q^{-1}, and 2*k*q^{-1} are the columns
    // of the rotation matrix computed in Quaternionx::ToRotationMatrix.
    // The vector v is obtained as the product of that rotation matrix with
    // vector u.  As such, the quaternion representation of a rotation
    // matrix requires less space than the matrix and more time to compute
    // the rotated vector.  Typical space-time tradeoff...

    Matrix3x kRot;
    ToRotationMatrix(kRot);
    return kRot*rkVector;
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::Slerp (fixed fT, const Quaternionx& rkP,
    const Quaternionx& rkQ)
{
    fixed fCos = rkP.Dot(rkQ);
    fixed fAngle = Mathx::ACos(fCos);

    if (Mathx::FAbs(fAngle) >= Mathx::ZERO_TOLERANCE)
    {
        fixed fSin = Mathx::Sin(fAngle);
        fixed fInvSin = (FIXED_ONE)/fSin;
        fixed fCoeff0 = Mathx::Sin((FIXED_ONE-fT)*fAngle)*fInvSin;
        fixed fCoeff1 = Mathx::Sin(fT*fAngle)*fInvSin;
        *this = fCoeff0*rkP + fCoeff1*rkQ;
    }
    else
    {
        *this = rkP;
    }

    return *this;
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::SlerpExtraSpins (fixed fT,
    const Quaternionx& rkP, const Quaternionx& rkQ, int iExtraSpins)
{
    fixed fCos = rkP.Dot(rkQ);
    fixed fAngle = Mathx::ACos(fCos);

    if (Mathx::FAbs(fAngle) >= Mathx::ZERO_TOLERANCE)
    {
        fixed fSin = Mathx::Sin(fAngle);
        fixed fPhase = Mathx::PI*iExtraSpins*fT;
        fixed fInvSin = (FIXED_ONE)/fSin;
        fixed fCoeff0 = Mathx::Sin((FIXED_ONE-fT)*fAngle-fPhase)*fInvSin;
        fixed fCoeff1 = Mathx::Sin(fT*fAngle + fPhase)*fInvSin;
        *this = fCoeff0*rkP + fCoeff1*rkQ;
    }
    else
    {
        *this = rkP;
    }

    return *this;
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::Intermediate (const Quaternionx& rkQ0,
    const Quaternionx& rkQ1, const Quaternionx& rkQ2)
{
    // assert:  Q0, Q1, Q2 all unit-length
    Quaternionx kQ1Inv = rkQ1.Conjugate();
    Quaternionx kP0 = kQ1Inv*rkQ0;
    Quaternionx kP2 = kQ1Inv*rkQ2;
    Quaternionx kArg = -(FixedFromFloat(0.25f))*(kP0.Log()+kP2.Log());
    Quaternionx kA = rkQ1*kArg.Exp();
    *this = kA;

    return *this;
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::Squad (fixed fT, const Quaternionx& rkQ0,
    const Quaternionx& rkA0, const Quaternionx& rkA1, const Quaternionx& rkQ1)
{
    fixed fSlerpT = (FixedFromFloat(2.0f))*fT*(FIXED_ONE-fT);
    Quaternionx kSlerpP = Slerp(fT,rkQ0,rkQ1);
    Quaternionx kSlerpQ = Slerp(fT,rkA0,rkA1);
    return Slerp(fSlerpT,kSlerpP,kSlerpQ);
}
//----------------------------------------------------------------------------

Quaternionx& Quaternionx::Align (const Vector3x& rkV1,
    const Vector3x& rkV2)
{
    // If V1 and V2 are not parallel, the axis of rotation is the unit-length
    // vector U = Cross(V1,V2)/Length(Cross(V1,V2)).  The angle of rotation,
    // A, is the angle between V1 and V2.  The quaternion for the rotation is
    // q = cos(A/2) + sin(A/2)*(ux*i+uy*j+uz*k) where U = (ux,uy,uz).
    //
    // (1) Rather than extract A = acos(Dot(V1,V2)), multiply by 1/2, then
    //     compute sin(A/2) and cos(A/2), we reduce the computational costs by
    //     computing the bisector B = (V1+V2)/Length(V1+V2), so cos(A/2) =
    //     Dot(V1,B).
    //
    // (2) The rotation axis is U = Cross(V1,B)/Length(Cross(V1,B)), but
    //     Length(Cross(V1,B)) = Length(V1)*Length(B)*sin(A/2) = sin(A/2), in
    //     which case sin(A/2)*(ux*i+uy*j+uz*k) = (cx*i+cy*j+cz*k) where
    //     C = Cross(V1,B).
    //
    // If V1 = V2, then B = V1, cos(A/2) = 1, and U = (0,0,0).  If V1 = -V2,
    // then B = 0.  This can happen even if V1 is approximately -V2 using
    // floating point arithmetic, since Vector3x::Normalize checks for
    // closeness to zero and returns the zero vector accordingly.  The test
    // for exactly zero is usually not recommend for floating point
    // arithmetic, but the implementation of Vector3x::Normalize guarantees
    // the comparison is robust.  In this case, the A = pi and any axis
    // perpendicular to V1 may be used as the rotation axis.

    Vector3x kBisector = rkV1 + rkV2;
    kBisector.Normalize();

    fixed fCosHalfAngle = rkV1.Dot(kBisector);
    Vector3x kCross;

    m_afTuple[0] = fCosHalfAngle;

    if (fCosHalfAngle != FIXED_ZERO)
    {
        kCross = rkV1.Cross(kBisector);
        m_afTuple[1] = kCross.X();
        m_afTuple[2] = kCross.Y();
        m_afTuple[3] = kCross.Z();
    }
    else
    {
        fixed fInvLength;
        if (Mathx::FAbs(rkV1[0]) >= Mathx::FAbs(rkV1[1]))
        {
            // V1.x or V1.z is the largest magnitude component
            fInvLength = Mathx::InvSqrt(rkV1[0]*rkV1[0] +
                rkV1[2]*rkV1[2]);
            m_afTuple[1] = -rkV1[2]*fInvLength;
            m_afTuple[2] = FIXED_ZERO;
            m_afTuple[3] = +rkV1[0]*fInvLength;
        }
        else
        {
            // V1.y or V1.z is the largest magnitude component
            fInvLength = Mathx::InvSqrt(rkV1[1]*rkV1[1] +
                rkV1[2]*rkV1[2]);
            m_afTuple[1] = FIXED_ZERO;
            m_afTuple[2] = +rkV1[2]*fInvLength;
            m_afTuple[3] = -rkV1[1]*fInvLength;
        }
    }

    return *this;
}
//----------------------------------------------------------------------------

void Quaternionx::DecomposeTwistTimesSwing (
    const Vector3x& rkV1, Quaternionx& rkTwist, Quaternionx& rkSwing)
{
    Vector3x kV2 = Rotate(rkV1);
    rkSwing = Align(rkV1,kV2);
    rkTwist = (*this)*rkSwing.Conjugate();
}
//----------------------------------------------------------------------------

void Quaternionx::DecomposeSwingTimesTwist (
    const Vector3x& rkV1, Quaternionx& rkSwing, Quaternionx& rkTwist)
{
    Vector3x kV2 = Rotate(rkV1);
    rkSwing = Align(rkV1,kV2);
    rkTwist = rkSwing.Conjugate()*(*this);
}
