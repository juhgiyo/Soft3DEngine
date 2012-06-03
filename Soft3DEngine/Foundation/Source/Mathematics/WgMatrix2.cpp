///////////////////////////////////////////////////////////
//                                                       //
//                    WgMatrix2.cpp                      //
//                                                       //
//  - Implementation for Matrix2 class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgMatrix2.h"
namespace WGSoft3D
{
template<> const Matrix2<float> Matrix2<float>::ZERO(
    0.0f,0.0f,
    0.0f,0.0f);
template<> const Matrix2<float> Matrix2<float>::IDENTITY(
    1.0f,0.0f,
    0.0f,1.0f);

template<> const Matrix2<double> Matrix2<double>::ZERO(
    0.0,0.0,
    0.0,0.0);
template<> const Matrix2<double> Matrix2<double>::IDENTITY(
    1.0,0.0,
    0.0,1.0);


const Matrix2x Matrix2x::ZERO(
	fixed(FIXED_ZERO),fixed(FIXED_ZERO),
	fixed(FIXED_ZERO),fixed(FIXED_ZERO));
const Matrix2x Matrix2x::IDENTITY(
	fixed(FIXED_ONE),fixed(FIXED_ZERO),
    fixed(FIXED_ZERO),fixed(FIXED_ONE));


//----------------------------------------------------------------------------
//
// Fixed Matrix 2 Implementation
//
//----------------------------------------------------------------------------
Matrix2x::Matrix2x (bool bZero)
{
    if (bZero)
    {
        MakeZero();
    }
    else
    {
        MakeIdentity();
    }
}
//----------------------------------------------------------------------------

Matrix2x::Matrix2x (const Matrix2x& rkM)
{
    m_afEntry[0] = rkM.m_afEntry[0];
    m_afEntry[1] = rkM.m_afEntry[1];
    m_afEntry[2] = rkM.m_afEntry[2];
    m_afEntry[3] = rkM.m_afEntry[3];
}
//----------------------------------------------------------------------------

Matrix2x::Matrix2x (fixed fM00, fixed fM01, fixed fM10, fixed fM11)
{
    m_afEntry[0] = fM00;
    m_afEntry[1] = fM01;
    m_afEntry[2] = fM10;
    m_afEntry[3] = fM11;
}
//----------------------------------------------------------------------------

Matrix2x::Matrix2x (const fixed afEntry[4], bool bRowMajor)
{
    if (bRowMajor)
    {
        m_afEntry[0] = afEntry[0];
        m_afEntry[1] = afEntry[1];
        m_afEntry[2] = afEntry[2];
        m_afEntry[3] = afEntry[3];
    }
    else
    {
        m_afEntry[0] = afEntry[0];
        m_afEntry[1] = afEntry[2];
        m_afEntry[2] = afEntry[1];
        m_afEntry[3] = afEntry[3];
    }
}
//----------------------------------------------------------------------------

Matrix2x::Matrix2x (const Vector2x& rkU, const Vector2x& rkV,
    bool bColumns)
{
    if (bColumns)
    {
        m_afEntry[0] = rkU[0];
        m_afEntry[1] = rkV[0];
        m_afEntry[2] = rkU[1];
        m_afEntry[3] = rkV[1];
    }
    else
    {
        m_afEntry[0] = rkU[0];
        m_afEntry[1] = rkU[1];
        m_afEntry[2] = rkV[0];
        m_afEntry[3] = rkV[1];
    }
}
//----------------------------------------------------------------------------

Matrix2x::Matrix2x (const Vector2x* akV, bool bColumns)
{
    if (bColumns)
    {
        m_afEntry[0] = akV[0][0];
        m_afEntry[1] = akV[1][0];
        m_afEntry[2] = akV[0][1];
        m_afEntry[3] = akV[1][1];
    }
    else
    {
        m_afEntry[0] = akV[0][0];
        m_afEntry[1] = akV[0][1];
        m_afEntry[2] = akV[1][0];
        m_afEntry[3] = akV[1][1];
    }
}
//----------------------------------------------------------------------------

Matrix2x::Matrix2x (fixed fM00, fixed fM11)
{
    MakeDiagonal(fM00,fM11);
}
//----------------------------------------------------------------------------

Matrix2x::Matrix2x (fixed fAngle)
{
    FromAngle(fAngle);
}
//----------------------------------------------------------------------------

Matrix2x::Matrix2x (const Vector2x& rkU, const Vector2x& rkV)
{
    MakeTensorProduct(rkU,rkV);
}
//----------------------------------------------------------------------------

void Matrix2x::MakeZero ()
{
    m_afEntry[0] = FIXED_ZERO;
    m_afEntry[1] = FIXED_ZERO;
    m_afEntry[2] = FIXED_ZERO;
    m_afEntry[3] = FIXED_ZERO;
}
//----------------------------------------------------------------------------

void Matrix2x::MakeIdentity ()
{
    m_afEntry[0] = FIXED_ONE;
    m_afEntry[1] = FIXED_ZERO;
    m_afEntry[2] = FIXED_ZERO;
    m_afEntry[3] = FIXED_ONE;
}
//----------------------------------------------------------------------------

void Matrix2x::MakeDiagonal (fixed fM00, fixed fM11)
{
    m_afEntry[0] = fM00;
    m_afEntry[1] = FIXED_ZERO;
    m_afEntry[2] = FIXED_ZERO;
    m_afEntry[3] = fM11;
}
//----------------------------------------------------------------------------

void Matrix2x::FromAngle (fixed fAngle)
{
    m_afEntry[0] = Mathx::Cos(fAngle);
    m_afEntry[2] = Mathx::Sin(fAngle);
    m_afEntry[1] = -m_afEntry[2];
    m_afEntry[3] =  m_afEntry[0];
}
//----------------------------------------------------------------------------

void Matrix2x::MakeTensorProduct (const Vector2x& rkU,
    const Vector2x& rkV)
{
    m_afEntry[0] = rkU[0]*rkV[0];
    m_afEntry[1] = rkU[0]*rkV[1];
    m_afEntry[2] = rkU[1]*rkV[0];
    m_afEntry[3] = rkU[1]*rkV[1];
}
//----------------------------------------------------------------------------

void Matrix2x::SetRow (int iRow, const Vector2x& rkV)
{
    int i0 = 2*iRow ,i1 = i0+1;
    m_afEntry[i0] = rkV[0];
    m_afEntry[i1] = rkV[1];
}
//----------------------------------------------------------------------------

Vector2x Matrix2x::GetRow (int iRow) const
{
    int i0 = 2*iRow ,i1 = i0+1;
    return Vector2x(m_afEntry[i0],m_afEntry[i1]);
}
//----------------------------------------------------------------------------

void Matrix2x::SetColumn (int iCol, const Vector2x& rkV)
{
    m_afEntry[iCol] = rkV[0];
    m_afEntry[iCol+2] = rkV[1];
}
//----------------------------------------------------------------------------

Vector2x Matrix2x::GetColumn (int iCol) const
{
    return Vector2x(m_afEntry[iCol],m_afEntry[iCol+2]);
}
//----------------------------------------------------------------------------

void Matrix2x::GetColumnMajor (fixed* afCMajor) const
{
    afCMajor[0] = m_afEntry[0];
    afCMajor[1] = m_afEntry[2];
    afCMajor[2] = m_afEntry[1];
    afCMajor[3] = m_afEntry[3];
}
//----------------------------------------------------------------------------


int Matrix2x::CompareArrays (const Matrix2x& rkM) const
{
    return memcmp(m_afEntry,rkM.m_afEntry,4*sizeof(fixed));
}
//----------------------------------------------------------------------------

bool Matrix2x::operator== (const Matrix2x& rkM) const
{
    return CompareArrays(rkM) == 0;
}
//----------------------------------------------------------------------------

bool Matrix2x::operator!= (const Matrix2x& rkM) const
{
    return CompareArrays(rkM) != 0;
}
//----------------------------------------------------------------------------

bool Matrix2x::operator<  (const Matrix2x& rkM) const
{
    return CompareArrays(rkM) < 0;
}
//----------------------------------------------------------------------------

bool Matrix2x::operator<= (const Matrix2x& rkM) const
{
    return CompareArrays(rkM) <= 0;
}
//----------------------------------------------------------------------------

bool Matrix2x::operator>  (const Matrix2x& rkM) const
{
    return CompareArrays(rkM) > 0;
}
//----------------------------------------------------------------------------

bool Matrix2x::operator>= (const Matrix2x& rkM) const
{
    return CompareArrays(rkM) >= 0;
}
//----------------------------------------------------------------------------

Matrix2x Matrix2x::Transpose () const
{
    return Matrix2x(
        m_afEntry[0],
        m_afEntry[2],
        m_afEntry[1],
        m_afEntry[3]);
}
//----------------------------------------------------------------------------

Matrix2x Matrix2x::TransposeTimes (const Matrix2x& rkM) const
{
    // P = A^T*B
    return Matrix2x(
        m_afEntry[0]*rkM.m_afEntry[0] + m_afEntry[2]*rkM.m_afEntry[2],
        m_afEntry[0]*rkM.m_afEntry[1] + m_afEntry[2]*rkM.m_afEntry[3],
        m_afEntry[1]*rkM.m_afEntry[0] + m_afEntry[3]*rkM.m_afEntry[2],
        m_afEntry[1]*rkM.m_afEntry[1] + m_afEntry[3]*rkM.m_afEntry[3]);
}
//----------------------------------------------------------------------------

Matrix2x Matrix2x::TimesTranspose (const Matrix2x& rkM) const
{
    // P = A*B^T
    return Matrix2x(
        m_afEntry[0]*rkM.m_afEntry[0] + m_afEntry[1]*rkM.m_afEntry[1],
        m_afEntry[0]*rkM.m_afEntry[2] + m_afEntry[1]*rkM.m_afEntry[3],
        m_afEntry[2]*rkM.m_afEntry[0] + m_afEntry[3]*rkM.m_afEntry[1],
        m_afEntry[2]*rkM.m_afEntry[2] + m_afEntry[3]*rkM.m_afEntry[3]);
}
//----------------------------------------------------------------------------

Matrix2x Matrix2x::Inverse () const
{
    Matrix2x kInverse;

    fixed fDet = m_afEntry[0]*m_afEntry[3] - m_afEntry[1]*m_afEntry[2];
    if (Mathx::FAbs(fDet) > Mathx::ZERO_TOLERANCE)
    {
        fixed fInvDet = (FIXED_ONE)/fDet;
        kInverse.m_afEntry[0] =  m_afEntry[3]*fInvDet;
        kInverse.m_afEntry[1] = -m_afEntry[1]*fInvDet;
        kInverse.m_afEntry[2] = -m_afEntry[2]*fInvDet;
        kInverse.m_afEntry[3] =  m_afEntry[0]*fInvDet;
    }
    else
    {
        kInverse.m_afEntry[0] = FIXED_ZERO;
        kInverse.m_afEntry[1] = FIXED_ZERO;
        kInverse.m_afEntry[2] = FIXED_ZERO;
        kInverse.m_afEntry[3] = FIXED_ZERO;
    }

    return kInverse;
}
//----------------------------------------------------------------------------

Matrix2x Matrix2x::Adjoint () const
{
    return Matrix2x(
        m_afEntry[3],
        -m_afEntry[1],
        -m_afEntry[2],
        m_afEntry[0]);
}
//----------------------------------------------------------------------------

fixed Matrix2x::Determinant () const
{
    return m_afEntry[0]*m_afEntry[3] - m_afEntry[1]*m_afEntry[2];
}
//----------------------------------------------------------------------------

fixed Matrix2x::QForm (const Vector2x& rkU,
    const Vector2x& rkV) const
{
    return rkU.Dot((*this)*rkV);
}
//----------------------------------------------------------------------------

void Matrix2x::ToAngle (fixed& rfAngle) const
{
    // assert:  matrix is a rotation
    rfAngle = Mathx::ATan2(m_afEntry[2],m_afEntry[0]);
}
//----------------------------------------------------------------------------

void Matrix2x::Orthonormalize ()
{
    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1], then orthonormal output matrix is Q = [q0|q1],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // compute q0
    fixed fInvLength = Mathx::InvSqrt(m_afEntry[0]*m_afEntry[0] +
        m_afEntry[2]*m_afEntry[2]);

    m_afEntry[0] *= fInvLength;
    m_afEntry[2] *= fInvLength;

    // compute q1
    fixed fDot0 = m_afEntry[0]*m_afEntry[1] + m_afEntry[2]*m_afEntry[3];
    m_afEntry[1] -= fDot0*m_afEntry[0];
    m_afEntry[3] -= fDot0*m_afEntry[2];

    fInvLength = Mathx::InvSqrt(m_afEntry[1]*m_afEntry[1] +
        m_afEntry[3]*m_afEntry[3]);

    m_afEntry[1] *= fInvLength;
    m_afEntry[3] *= fInvLength;
}
//----------------------------------------------------------------------------

void Matrix2x::EigenDecomposition (Matrix2x& rkRot, Matrix2x& rkDiag) const
{
    fixed fTrace = m_afEntry[0] + m_afEntry[3];
    fixed fDiff = m_afEntry[0] - m_afEntry[3];
    fixed fDiscr = Mathx::Sqrt(fDiff*fDiff +
        FixedFromFloat((float)4.0)*m_afEntry[1]*m_afEntry[1]);
    fixed fEVal0 = FIXED_HALF*(fTrace-fDiscr);
    fixed fEVal1 = FIXED_HALF*(fTrace+fDiscr);
    rkDiag.MakeDiagonal(fEVal0,fEVal1);

    fixed fCos, fSin;
    if (fDiff >= FIXED_ZERO)
    {
        fCos = m_afEntry[1];
        fSin = fEVal0 - m_afEntry[0];
    }
    else
    {
        fCos = fEVal0 - m_afEntry[3];
        fSin = m_afEntry[1];
    }
    fixed fTmp = Mathx::InvSqrt(fCos*fCos + fSin*fSin);
    fCos *= fTmp;
    fSin *= fTmp;

    rkRot.m_afEntry[0] = fCos;
    rkRot.m_afEntry[1] = -fSin;
    rkRot.m_afEntry[2] = fSin;
    rkRot.m_afEntry[3] = fCos;
}
//----------------------------------------------------------------------------

}