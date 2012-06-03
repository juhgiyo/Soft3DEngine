///////////////////////////////////////////////////////////
//                                                       //
//                    WgMatrix4.cpp                      //
//                                                       //
//  - Implementation for Matrix4 class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////


#include "WgFoundationPCH.h"
#include "WgMatrix4.h"
namespace WGSoft3D
{
	
template<> const Matrix4<float> Matrix4<float>::ZERO(
    0.0f,0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,0.0f);
template<> const Matrix4<float> Matrix4<float>::IDENTITY(
    1.0f,0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,0.0f,
    0.0f,0.0f,1.0f,0.0f,
    0.0f,0.0f,0.0f,1.0f);

template<> const Matrix4<double> Matrix4<double>::ZERO(
    0.0,0.0,0.0,0.0,
    0.0,0.0,0.0,0.0,
    0.0,0.0,0.0,0.0,
    0.0,0.0,0.0,0.0);
template<> const Matrix4<double> Matrix4<double>::IDENTITY(
    1.0,0.0,0.0,0.0,
    0.0,1.0,0.0,0.0,
    0.0,0.0,1.0,0.0,
    0.0,0.0,0.0,1.0);

const Matrix4x Matrix4x::ZERO(
	fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
	fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
	fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
	fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO));
const Matrix4x Matrix4x::IDENTITY(
	fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
	fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
	fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),
	fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE));


//----------------------------------------------------------------------------
//
// Fixed Matrix 4 Implementation
//
//----------------------------------------------------------------------------
Matrix4x::Matrix4x (bool bZero)
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

Matrix4x::Matrix4x (const Matrix4x& rkM)
{
    m_afEntry[ 0] = rkM.m_afEntry[ 0];
    m_afEntry[ 1] = rkM.m_afEntry[ 1];
    m_afEntry[ 2] = rkM.m_afEntry[ 2];
    m_afEntry[ 3] = rkM.m_afEntry[ 3];
    m_afEntry[ 4] = rkM.m_afEntry[ 4];
    m_afEntry[ 5] = rkM.m_afEntry[ 5];
    m_afEntry[ 6] = rkM.m_afEntry[ 6];
    m_afEntry[ 7] = rkM.m_afEntry[ 7];
    m_afEntry[ 8] = rkM.m_afEntry[ 8];
    m_afEntry[ 9] = rkM.m_afEntry[ 9];
    m_afEntry[10] = rkM.m_afEntry[10];
    m_afEntry[11] = rkM.m_afEntry[11];
    m_afEntry[12] = rkM.m_afEntry[12];
    m_afEntry[13] = rkM.m_afEntry[13];
    m_afEntry[14] = rkM.m_afEntry[14];
    m_afEntry[15] = rkM.m_afEntry[15];
}
//----------------------------------------------------------------------------

Matrix4x::Matrix4x (fixed fM00, fixed fM01, fixed fM02, fixed fM03,
    fixed fM10, fixed fM11, fixed fM12, fixed fM13, fixed fM20, fixed fM21,
    fixed fM22, fixed fM23, fixed fM30, fixed fM31, fixed fM32, fixed fM33)
{
    m_afEntry[ 0] = fM00;
    m_afEntry[ 1] = fM01;
    m_afEntry[ 2] = fM02;
    m_afEntry[ 3] = fM03;
    m_afEntry[ 4] = fM10;
    m_afEntry[ 5] = fM11;
    m_afEntry[ 6] = fM12;
    m_afEntry[ 7] = fM13;
    m_afEntry[ 8] = fM20;
    m_afEntry[ 9] = fM21;
    m_afEntry[10] = fM22;
    m_afEntry[11] = fM23;
    m_afEntry[12] = fM30;
    m_afEntry[13] = fM31;
    m_afEntry[14] = fM32;
    m_afEntry[15] = fM33;
}
//----------------------------------------------------------------------------

Matrix4x::Matrix4x (const fixed afEntry[16], bool bRowMajor)
{
    if (bRowMajor)
    {
        m_afEntry[ 0] = afEntry[ 0];
        m_afEntry[ 1] = afEntry[ 1];
        m_afEntry[ 2] = afEntry[ 2];
        m_afEntry[ 3] = afEntry[ 3];
        m_afEntry[ 4] = afEntry[ 4];
        m_afEntry[ 5] = afEntry[ 5];
        m_afEntry[ 6] = afEntry[ 6];
        m_afEntry[ 7] = afEntry[ 7];
        m_afEntry[ 8] = afEntry[ 8];
        m_afEntry[ 9] = afEntry[ 9];
        m_afEntry[10] = afEntry[10];
        m_afEntry[11] = afEntry[11];
        m_afEntry[12] = afEntry[12];
        m_afEntry[13] = afEntry[13];
        m_afEntry[14] = afEntry[14];
        m_afEntry[15] = afEntry[15];
    }
    else
    {
        m_afEntry[ 0] = afEntry[ 0];
        m_afEntry[ 1] = afEntry[ 4];
        m_afEntry[ 2] = afEntry[ 8];
        m_afEntry[ 3] = afEntry[12];
        m_afEntry[ 4] = afEntry[ 1];
        m_afEntry[ 5] = afEntry[ 5];
        m_afEntry[ 6] = afEntry[ 9];
        m_afEntry[ 7] = afEntry[13];
        m_afEntry[ 8] = afEntry[ 2];
        m_afEntry[ 9] = afEntry[ 6];
        m_afEntry[10] = afEntry[10];
        m_afEntry[11] = afEntry[14];
        m_afEntry[12] = afEntry[ 3];
        m_afEntry[13] = afEntry[ 7];
        m_afEntry[14] = afEntry[11];
        m_afEntry[15] = afEntry[15];
    }
}
//----------------------------------------------------------------------------

void Matrix4x::MakeZero ()
{
    m_afEntry[ 0] = FIXED_ZERO;
    m_afEntry[ 1] = FIXED_ZERO;
    m_afEntry[ 2] = FIXED_ZERO;
    m_afEntry[ 3] = FIXED_ZERO;
    m_afEntry[ 4] = FIXED_ZERO;
    m_afEntry[ 5] = FIXED_ZERO;
    m_afEntry[ 6] = FIXED_ZERO;
    m_afEntry[ 7] = FIXED_ZERO;
    m_afEntry[ 8] = FIXED_ZERO;
    m_afEntry[ 9] = FIXED_ZERO;
    m_afEntry[10] = FIXED_ZERO;
    m_afEntry[11] = FIXED_ZERO;
    m_afEntry[12] = FIXED_ZERO;
    m_afEntry[13] = FIXED_ZERO;
    m_afEntry[14] = FIXED_ZERO;
    m_afEntry[15] = FIXED_ZERO;
}
//----------------------------------------------------------------------------

void Matrix4x::MakeIdentity ()
{
    m_afEntry[ 0] = FIXED_ONE;
    m_afEntry[ 1] = FIXED_ZERO;
    m_afEntry[ 2] = FIXED_ZERO;
    m_afEntry[ 3] = FIXED_ZERO;
    m_afEntry[ 4] = FIXED_ZERO;
    m_afEntry[ 5] = FIXED_ONE;
    m_afEntry[ 6] = FIXED_ZERO;
    m_afEntry[ 7] = FIXED_ZERO;
    m_afEntry[ 8] = FIXED_ZERO;
    m_afEntry[ 9] = FIXED_ZERO;
    m_afEntry[10] = FIXED_ONE;
    m_afEntry[11] = FIXED_ZERO;
    m_afEntry[12] = FIXED_ZERO;
    m_afEntry[13] = FIXED_ZERO;
    m_afEntry[14] = FIXED_ZERO;
    m_afEntry[15] = FIXED_ONE;
}
//----------------------------------------------------------------------------

void Matrix4x::SetRow (int iRow, const Vector4x& rkV)
{
    int i0 = 4*iRow, i1 = i0+1, i2 = i1+1, i3 = i2+1;
    m_afEntry[i0] = rkV[0];
    m_afEntry[i1] = rkV[1];
    m_afEntry[i2] = rkV[2];
    m_afEntry[i3] = rkV[3];
}
//----------------------------------------------------------------------------

Vector4x Matrix4x::GetRow (int iRow) const
{
    int i0 = 4*iRow, i1 = i0+1, i2 = i1+1, i3 = i2+1;
    return Vector4x(m_afEntry[i0],m_afEntry[i1],m_afEntry[i2],
        m_afEntry[i3]);
}
//----------------------------------------------------------------------------

void Matrix4x::SetColumn (int iCol, const Vector4x& rkV)
{
    m_afEntry[iCol] = rkV[0];
    m_afEntry[iCol+4] = rkV[1];
    m_afEntry[iCol+8] = rkV[2];
    m_afEntry[iCol+12] = rkV[3];
}
//----------------------------------------------------------------------------

Vector4x Matrix4x::GetColumn (int iCol) const
{
    return Vector4x(m_afEntry[iCol],m_afEntry[iCol+4],m_afEntry[iCol+8],
        m_afEntry[iCol+12]);
}
//----------------------------------------------------------------------------

void Matrix4x::GetColumnMajor (fixed* afCMajor) const
{
    afCMajor[ 0] = m_afEntry[ 0];
    afCMajor[ 1] = m_afEntry[ 4];
    afCMajor[ 2] = m_afEntry[ 8];
    afCMajor[ 3] = m_afEntry[12];
    afCMajor[ 4] = m_afEntry[ 1];
    afCMajor[ 5] = m_afEntry[ 5];
    afCMajor[ 6] = m_afEntry[ 9];
    afCMajor[ 7] = m_afEntry[13];
    afCMajor[ 8] = m_afEntry[ 2];
    afCMajor[ 9] = m_afEntry[ 6];
    afCMajor[10] = m_afEntry[10];
    afCMajor[11] = m_afEntry[14];
    afCMajor[12] = m_afEntry[ 3];
    afCMajor[13] = m_afEntry[ 7];
    afCMajor[14] = m_afEntry[11];
    afCMajor[15] = m_afEntry[15];
}
//----------------------------------------------------------------------------

int Matrix4x::CompareArrays (const Matrix4x& rkM) const
{
    return memcmp(m_afEntry,rkM.m_afEntry,16*sizeof(fixed));
}
//----------------------------------------------------------------------------

bool Matrix4x::operator== (const Matrix4x& rkM) const
{
    return CompareArrays(rkM) == 0;
}
//----------------------------------------------------------------------------

bool Matrix4x::operator!= (const Matrix4x& rkM) const
{
    return CompareArrays(rkM) != 0;
}
//----------------------------------------------------------------------------

bool Matrix4x::operator<  (const Matrix4x& rkM) const
{
    return CompareArrays(rkM) < 0;
}
//----------------------------------------------------------------------------

bool Matrix4x::operator<= (const Matrix4x& rkM) const
{
    return CompareArrays(rkM) <= 0;
}
//----------------------------------------------------------------------------

bool Matrix4x::operator>  (const Matrix4x& rkM) const
{
    return CompareArrays(rkM) > 0;
}
//----------------------------------------------------------------------------

bool Matrix4x::operator>= (const Matrix4x& rkM) const
{
    return CompareArrays(rkM) >= 0;
}
//----------------------------------------------------------------------------

Matrix4x Matrix4x::Transpose () const
{
    return Matrix4x(
        m_afEntry[ 0],
        m_afEntry[ 4],
        m_afEntry[ 8],
        m_afEntry[12],
        m_afEntry[ 1],
        m_afEntry[ 5],
        m_afEntry[ 9],
        m_afEntry[13],
        m_afEntry[ 2],
        m_afEntry[ 6],
        m_afEntry[10],
        m_afEntry[14],
        m_afEntry[ 3],
        m_afEntry[ 7],
        m_afEntry[11],
        m_afEntry[15]);
}
//----------------------------------------------------------------------------

Matrix4x Matrix4x::TransposeTimes (const Matrix4x& rkM) const
{
    // P = A^T*B
    return Matrix4x(
        m_afEntry[ 0]*rkM.m_afEntry[ 0] +
        m_afEntry[ 4]*rkM.m_afEntry[ 4] +
        m_afEntry[ 8]*rkM.m_afEntry[ 8] +
        m_afEntry[12]*rkM.m_afEntry[12],

        m_afEntry[ 0]*rkM.m_afEntry[ 1] +
        m_afEntry[ 4]*rkM.m_afEntry[ 5] +
        m_afEntry[ 8]*rkM.m_afEntry[ 9] +
        m_afEntry[12]*rkM.m_afEntry[13],

        m_afEntry[ 0]*rkM.m_afEntry[ 2] +
        m_afEntry[ 4]*rkM.m_afEntry[ 6] +
        m_afEntry[ 8]*rkM.m_afEntry[10] +
        m_afEntry[12]*rkM.m_afEntry[14],

        m_afEntry[ 0]*rkM.m_afEntry[ 3] +
        m_afEntry[ 4]*rkM.m_afEntry[ 7] +
        m_afEntry[ 8]*rkM.m_afEntry[11] +
        m_afEntry[12]*rkM.m_afEntry[15],

        m_afEntry[ 1]*rkM.m_afEntry[ 0] +
        m_afEntry[ 5]*rkM.m_afEntry[ 4] +
        m_afEntry[ 9]*rkM.m_afEntry[ 8] +
        m_afEntry[13]*rkM.m_afEntry[12],

        m_afEntry[ 1]*rkM.m_afEntry[ 1] +
        m_afEntry[ 5]*rkM.m_afEntry[ 5] +
        m_afEntry[ 9]*rkM.m_afEntry[ 9] +
        m_afEntry[13]*rkM.m_afEntry[13],

        m_afEntry[ 1]*rkM.m_afEntry[ 2] +
        m_afEntry[ 5]*rkM.m_afEntry[ 6] +
        m_afEntry[ 9]*rkM.m_afEntry[10] +
        m_afEntry[13]*rkM.m_afEntry[14],

        m_afEntry[ 1]*rkM.m_afEntry[ 3] +
        m_afEntry[ 5]*rkM.m_afEntry[ 7] +
        m_afEntry[ 9]*rkM.m_afEntry[11] +
        m_afEntry[13]*rkM.m_afEntry[15],

        m_afEntry[ 2]*rkM.m_afEntry[ 0] +
        m_afEntry[ 6]*rkM.m_afEntry[ 4] +
        m_afEntry[10]*rkM.m_afEntry[ 8] +
        m_afEntry[14]*rkM.m_afEntry[12],

        m_afEntry[ 2]*rkM.m_afEntry[ 1] +
        m_afEntry[ 6]*rkM.m_afEntry[ 5] +
        m_afEntry[10]*rkM.m_afEntry[ 9] +
        m_afEntry[14]*rkM.m_afEntry[13],

        m_afEntry[ 2]*rkM.m_afEntry[ 2] +
        m_afEntry[ 6]*rkM.m_afEntry[ 6] +
        m_afEntry[10]*rkM.m_afEntry[10] +
        m_afEntry[14]*rkM.m_afEntry[14],

        m_afEntry[ 2]*rkM.m_afEntry[ 3] +
        m_afEntry[ 6]*rkM.m_afEntry[ 7] +
        m_afEntry[10]*rkM.m_afEntry[11] +
        m_afEntry[14]*rkM.m_afEntry[15],

        m_afEntry[ 3]*rkM.m_afEntry[ 0] +
        m_afEntry[ 7]*rkM.m_afEntry[ 4] +
        m_afEntry[11]*rkM.m_afEntry[ 8] +
        m_afEntry[15]*rkM.m_afEntry[12],

        m_afEntry[ 3]*rkM.m_afEntry[ 1] +
        m_afEntry[ 7]*rkM.m_afEntry[ 5] +
        m_afEntry[11]*rkM.m_afEntry[ 9] +
        m_afEntry[15]*rkM.m_afEntry[13],

        m_afEntry[ 3]*rkM.m_afEntry[ 2] +
        m_afEntry[ 7]*rkM.m_afEntry[ 6] +
        m_afEntry[11]*rkM.m_afEntry[10] +
        m_afEntry[15]*rkM.m_afEntry[14],

        m_afEntry[ 3]*rkM.m_afEntry[ 3] +
        m_afEntry[ 7]*rkM.m_afEntry[ 7] +
        m_afEntry[11]*rkM.m_afEntry[11] +
        m_afEntry[15]*rkM.m_afEntry[15]);
}
//----------------------------------------------------------------------------

Matrix4x Matrix4x::TimesTranspose (const Matrix4x& rkM) const
{
    // P = A*B^T
    return Matrix4x(
        m_afEntry[ 0]*rkM.m_afEntry[ 0] +
        m_afEntry[ 1]*rkM.m_afEntry[ 1] +
        m_afEntry[ 2]*rkM.m_afEntry[ 2] +
        m_afEntry[ 3]*rkM.m_afEntry[ 3],

        m_afEntry[ 0]*rkM.m_afEntry[ 4] +
        m_afEntry[ 1]*rkM.m_afEntry[ 5] +
        m_afEntry[ 2]*rkM.m_afEntry[ 6] +
        m_afEntry[ 3]*rkM.m_afEntry[ 7],

        m_afEntry[ 0]*rkM.m_afEntry[ 8] +
        m_afEntry[ 1]*rkM.m_afEntry[ 9] +
        m_afEntry[ 2]*rkM.m_afEntry[10] +
        m_afEntry[ 3]*rkM.m_afEntry[11],

        m_afEntry[ 0]*rkM.m_afEntry[12] +
        m_afEntry[ 1]*rkM.m_afEntry[13] +
        m_afEntry[ 2]*rkM.m_afEntry[14] +
        m_afEntry[ 3]*rkM.m_afEntry[15],

        m_afEntry[ 4]*rkM.m_afEntry[ 0] +
        m_afEntry[ 5]*rkM.m_afEntry[ 1] +
        m_afEntry[ 6]*rkM.m_afEntry[ 2] +
        m_afEntry[ 7]*rkM.m_afEntry[ 3],

        m_afEntry[ 4]*rkM.m_afEntry[ 4] +
        m_afEntry[ 5]*rkM.m_afEntry[ 5] +
        m_afEntry[ 6]*rkM.m_afEntry[ 6] +
        m_afEntry[ 7]*rkM.m_afEntry[ 7],

        m_afEntry[ 4]*rkM.m_afEntry[ 8] +
        m_afEntry[ 5]*rkM.m_afEntry[ 9] +
        m_afEntry[ 6]*rkM.m_afEntry[10] +
        m_afEntry[ 7]*rkM.m_afEntry[11],

        m_afEntry[ 4]*rkM.m_afEntry[12] +
        m_afEntry[ 5]*rkM.m_afEntry[13] +
        m_afEntry[ 6]*rkM.m_afEntry[14] +
        m_afEntry[ 7]*rkM.m_afEntry[15],

        m_afEntry[ 8]*rkM.m_afEntry[ 0] +
        m_afEntry[ 9]*rkM.m_afEntry[ 1] +
        m_afEntry[10]*rkM.m_afEntry[ 2] +
        m_afEntry[11]*rkM.m_afEntry[ 3],

        m_afEntry[ 8]*rkM.m_afEntry[ 4] +
        m_afEntry[ 9]*rkM.m_afEntry[ 5] +
        m_afEntry[10]*rkM.m_afEntry[ 6] +
        m_afEntry[11]*rkM.m_afEntry[ 7],

        m_afEntry[ 8]*rkM.m_afEntry[ 8] +
        m_afEntry[ 9]*rkM.m_afEntry[ 9] +
        m_afEntry[10]*rkM.m_afEntry[10] +
        m_afEntry[11]*rkM.m_afEntry[11],

        m_afEntry[ 8]*rkM.m_afEntry[12] +
        m_afEntry[ 9]*rkM.m_afEntry[13] +
        m_afEntry[10]*rkM.m_afEntry[14] +
        m_afEntry[11]*rkM.m_afEntry[15],

        m_afEntry[12]*rkM.m_afEntry[ 0] +
        m_afEntry[13]*rkM.m_afEntry[ 1] +
        m_afEntry[14]*rkM.m_afEntry[ 2] +
        m_afEntry[15]*rkM.m_afEntry[ 3],

        m_afEntry[12]*rkM.m_afEntry[ 4] +
        m_afEntry[13]*rkM.m_afEntry[ 5] +
        m_afEntry[14]*rkM.m_afEntry[ 6] +
        m_afEntry[15]*rkM.m_afEntry[ 7],

        m_afEntry[12]*rkM.m_afEntry[ 8] +
        m_afEntry[13]*rkM.m_afEntry[ 9] +
        m_afEntry[14]*rkM.m_afEntry[10] +
        m_afEntry[15]*rkM.m_afEntry[11],

        m_afEntry[12]*rkM.m_afEntry[12] +
        m_afEntry[13]*rkM.m_afEntry[13] +
        m_afEntry[14]*rkM.m_afEntry[14] +
        m_afEntry[15]*rkM.m_afEntry[15]);
}
//----------------------------------------------------------------------------

Matrix4x Matrix4x::Inverse () const
{
    fixed fA0 = m_afEntry[ 0]*m_afEntry[ 5] - m_afEntry[ 1]*m_afEntry[ 4];
    fixed fA1 = m_afEntry[ 0]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 4];
    fixed fA2 = m_afEntry[ 0]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 4];
    fixed fA3 = m_afEntry[ 1]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 5];
    fixed fA4 = m_afEntry[ 1]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 5];
    fixed fA5 = m_afEntry[ 2]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 6];
    fixed fB0 = m_afEntry[ 8]*m_afEntry[13] - m_afEntry[ 9]*m_afEntry[12];
    fixed fB1 = m_afEntry[ 8]*m_afEntry[14] - m_afEntry[10]*m_afEntry[12];
    fixed fB2 = m_afEntry[ 8]*m_afEntry[15] - m_afEntry[11]*m_afEntry[12];
    fixed fB3 = m_afEntry[ 9]*m_afEntry[14] - m_afEntry[10]*m_afEntry[13];
    fixed fB4 = m_afEntry[ 9]*m_afEntry[15] - m_afEntry[11]*m_afEntry[13];
    fixed fB5 = m_afEntry[10]*m_afEntry[15] - m_afEntry[11]*m_afEntry[14];

    fixed fDet = fA0*fB5-fA1*fB4+fA2*fB3+fA3*fB2-fA4*fB1+fA5*fB0;
    if (Mathx::FAbs(fDet) <= Mathx::ZERO_TOLERANCE)
    {
        return Matrix4x::ZERO;
    }

    Matrix4x kInv;
    kInv.m_afEntry[ 0] =
        + m_afEntry[ 5]*fB5 - m_afEntry[ 6]*fB4 + m_afEntry[ 7]*fB3;
    kInv.m_afEntry[ 4] =
        - m_afEntry[ 4]*fB5 + m_afEntry[ 6]*fB2 - m_afEntry[ 7]*fB1;
    kInv.m_afEntry[ 8] =
        + m_afEntry[ 4]*fB4 - m_afEntry[ 5]*fB2 + m_afEntry[ 7]*fB0;
    kInv.m_afEntry[12] =
        - m_afEntry[ 4]*fB3 + m_afEntry[ 5]*fB1 - m_afEntry[ 6]*fB0;
    kInv.m_afEntry[ 1] =
        - m_afEntry[ 1]*fB5 + m_afEntry[ 2]*fB4 - m_afEntry[ 3]*fB3;
    kInv.m_afEntry[ 5] =
        + m_afEntry[ 0]*fB5 - m_afEntry[ 2]*fB2 + m_afEntry[ 3]*fB1;
    kInv.m_afEntry[ 9] =
        - m_afEntry[ 0]*fB4 + m_afEntry[ 1]*fB2 - m_afEntry[ 3]*fB0;
    kInv.m_afEntry[13] =
        + m_afEntry[ 0]*fB3 - m_afEntry[ 1]*fB1 + m_afEntry[ 2]*fB0;
    kInv.m_afEntry[ 2] =
        + m_afEntry[13]*fA5 - m_afEntry[14]*fA4 + m_afEntry[15]*fA3;
    kInv.m_afEntry[ 6] =
        - m_afEntry[12]*fA5 + m_afEntry[14]*fA2 - m_afEntry[15]*fA1;
    kInv.m_afEntry[10] =
        + m_afEntry[12]*fA4 - m_afEntry[13]*fA2 + m_afEntry[15]*fA0;
    kInv.m_afEntry[14] =
        - m_afEntry[12]*fA3 + m_afEntry[13]*fA1 - m_afEntry[14]*fA0;
    kInv.m_afEntry[ 3] =
        - m_afEntry[ 9]*fA5 + m_afEntry[10]*fA4 - m_afEntry[11]*fA3;
    kInv.m_afEntry[ 7] =
        + m_afEntry[ 8]*fA5 - m_afEntry[10]*fA2 + m_afEntry[11]*fA1;
    kInv.m_afEntry[11] =
        - m_afEntry[ 8]*fA4 + m_afEntry[ 9]*fA2 - m_afEntry[11]*fA0;
    kInv.m_afEntry[15] =
        + m_afEntry[ 8]*fA3 - m_afEntry[ 9]*fA1 + m_afEntry[10]*fA0;

    fixed fInvDet = (FIXED_ONE)/fDet;
    kInv.m_afEntry[ 0] *= fInvDet;
    kInv.m_afEntry[ 1] *= fInvDet;
    kInv.m_afEntry[ 2] *= fInvDet;
    kInv.m_afEntry[ 3] *= fInvDet;
    kInv.m_afEntry[ 4] *= fInvDet;
    kInv.m_afEntry[ 5] *= fInvDet;
    kInv.m_afEntry[ 6] *= fInvDet;
    kInv.m_afEntry[ 7] *= fInvDet;
    kInv.m_afEntry[ 8] *= fInvDet;
    kInv.m_afEntry[ 9] *= fInvDet;
    kInv.m_afEntry[10] *= fInvDet;
    kInv.m_afEntry[11] *= fInvDet;
    kInv.m_afEntry[12] *= fInvDet;
    kInv.m_afEntry[13] *= fInvDet;
    kInv.m_afEntry[14] *= fInvDet;
    kInv.m_afEntry[15] *= fInvDet;

    return kInv;
}
//----------------------------------------------------------------------------

Matrix4x Matrix4x::Adjoint () const
{
    fixed fA0 = m_afEntry[ 0]*m_afEntry[ 5] - m_afEntry[ 1]*m_afEntry[ 4];
    fixed fA1 = m_afEntry[ 0]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 4];
    fixed fA2 = m_afEntry[ 0]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 4];
    fixed fA3 = m_afEntry[ 1]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 5];
    fixed fA4 = m_afEntry[ 1]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 5];
    fixed fA5 = m_afEntry[ 2]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 6];
    fixed fB0 = m_afEntry[ 8]*m_afEntry[13] - m_afEntry[ 9]*m_afEntry[12];
    fixed fB1 = m_afEntry[ 8]*m_afEntry[14] - m_afEntry[10]*m_afEntry[12];
    fixed fB2 = m_afEntry[ 8]*m_afEntry[15] - m_afEntry[11]*m_afEntry[12];
    fixed fB3 = m_afEntry[ 9]*m_afEntry[14] - m_afEntry[10]*m_afEntry[13];
    fixed fB4 = m_afEntry[ 9]*m_afEntry[15] - m_afEntry[11]*m_afEntry[13];
    fixed fB5 = m_afEntry[10]*m_afEntry[15] - m_afEntry[11]*m_afEntry[14];

    return Matrix4x(
        + m_afEntry[ 5]*fB5 - m_afEntry[ 6]*fB4 + m_afEntry[ 7]*fB3,
        - m_afEntry[ 1]*fB5 + m_afEntry[ 2]*fB4 - m_afEntry[ 3]*fB3,
        + m_afEntry[13]*fA5 - m_afEntry[14]*fA4 + m_afEntry[15]*fA3,
        - m_afEntry[ 9]*fA5 + m_afEntry[10]*fA4 - m_afEntry[11]*fA3,
        - m_afEntry[ 4]*fB5 + m_afEntry[ 6]*fB2 - m_afEntry[ 7]*fB1,
        + m_afEntry[ 0]*fB5 - m_afEntry[ 2]*fB2 + m_afEntry[ 3]*fB1,
        - m_afEntry[12]*fA5 + m_afEntry[14]*fA2 - m_afEntry[15]*fA1,
        + m_afEntry[ 8]*fA5 - m_afEntry[10]*fA2 + m_afEntry[11]*fA1,
        + m_afEntry[ 4]*fB4 - m_afEntry[ 5]*fB2 + m_afEntry[ 7]*fB0,
        - m_afEntry[ 0]*fB4 + m_afEntry[ 1]*fB2 - m_afEntry[ 3]*fB0,
        + m_afEntry[12]*fA4 - m_afEntry[13]*fA2 + m_afEntry[15]*fA0,
        - m_afEntry[ 8]*fA4 + m_afEntry[ 9]*fA2 - m_afEntry[11]*fA0,
        - m_afEntry[ 4]*fB3 + m_afEntry[ 5]*fB1 - m_afEntry[ 6]*fB0,
        + m_afEntry[ 0]*fB3 - m_afEntry[ 1]*fB1 + m_afEntry[ 2]*fB0,
        - m_afEntry[12]*fA3 + m_afEntry[13]*fA1 - m_afEntry[14]*fA0,
        + m_afEntry[ 8]*fA3 - m_afEntry[ 9]*fA1 + m_afEntry[10]*fA0);
}
//----------------------------------------------------------------------------

fixed Matrix4x::Determinant () const
{
    fixed fA0 = m_afEntry[ 0]*m_afEntry[ 5] - m_afEntry[ 1]*m_afEntry[ 4];
    fixed fA1 = m_afEntry[ 0]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 4];
    fixed fA2 = m_afEntry[ 0]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 4];
    fixed fA3 = m_afEntry[ 1]*m_afEntry[ 6] - m_afEntry[ 2]*m_afEntry[ 5];
    fixed fA4 = m_afEntry[ 1]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 5];
    fixed fA5 = m_afEntry[ 2]*m_afEntry[ 7] - m_afEntry[ 3]*m_afEntry[ 6];
    fixed fB0 = m_afEntry[ 8]*m_afEntry[13] - m_afEntry[ 9]*m_afEntry[12];
    fixed fB1 = m_afEntry[ 8]*m_afEntry[14] - m_afEntry[10]*m_afEntry[12];
    fixed fB2 = m_afEntry[ 8]*m_afEntry[15] - m_afEntry[11]*m_afEntry[12];
    fixed fB3 = m_afEntry[ 9]*m_afEntry[14] - m_afEntry[10]*m_afEntry[13];
    fixed fB4 = m_afEntry[ 9]*m_afEntry[15] - m_afEntry[11]*m_afEntry[13];
    fixed fB5 = m_afEntry[10]*m_afEntry[15] - m_afEntry[11]*m_afEntry[14];
    fixed fDet = fA0*fB5-fA1*fB4+fA2*fB3+fA3*fB2-fA4*fB1+fA5*fB0;
    return fDet;
}
//----------------------------------------------------------------------------

fixed Matrix4x::QForm (const Vector4x& rkU,
    const Vector4x& rkV) const
{
    return rkU.Dot((*this)*rkV);
}
//----------------------------------------------------------------------------

void Matrix4x::MakeObliqueProjection (const Vector3x& rkNormal,
    const Vector3x& rkPoint, const Vector3x& rkDirection)
{
    // The projection plane is Dot(N,X-P) = 0 where N is a 3-by-1 unit-length
    // normal vector and P is a 3-by-1 point on the plane.  The projection
    // is oblique to the plane, in the direction of the 3-by-1 vector D.
    // Necessarily Dot(N,D) is not zero for this projection to make sense.
    // Given a 3-by-1 point U, compute the intersection of the line U+t*D
    // with the plane to obtain t = -Dot(N,U-P)/Dot(N,D).  Then
    //
    //   projection(U) = P + [I - D*N^T/Dot(N,D)]*(U-P)
    //
    // A 4-by-4 homogeneous transformation representing the projection is
    //
    //       +-                               -+
    //   M = | D*N^T - Dot(N,D)*I   -Dot(N,P)D |
    //       |          0^T          -Dot(N,D) |
    //       +-                               -+
    //
    // where M applies to [U^T 1]^T by M*[U^T 1]^T.  The matrix is chosen so
    // that M[3][3] > 0 whenever Dot(N,D) < 0 (projection is onto the
    // "positive side" of the plane).

    fixed fNdD = rkNormal.Dot(rkDirection);
    fixed fNdP = rkNormal.Dot(rkPoint);
    m_afEntry[ 0] = rkDirection[0]*rkNormal[0] - fNdD;
    m_afEntry[ 1] = rkDirection[0]*rkNormal[1];
    m_afEntry[ 2] = rkDirection[0]*rkNormal[2];
    m_afEntry[ 3] = -fNdP*rkDirection[0];
    m_afEntry[ 4] = rkDirection[1]*rkNormal[0];
    m_afEntry[ 5] = rkDirection[1]*rkNormal[1] - fNdD;
    m_afEntry[ 6] = rkDirection[1]*rkNormal[2];
    m_afEntry[ 7] = -fNdP*rkDirection[1];
    m_afEntry[ 8] = rkDirection[2]*rkNormal[0];
    m_afEntry[ 9] = rkDirection[2]*rkNormal[1];
    m_afEntry[10] = rkDirection[2]*rkNormal[2] - fNdD;
    m_afEntry[11] = -fNdP*rkDirection[2];
    m_afEntry[12] = FIXED_ZERO;
    m_afEntry[13] = FIXED_ZERO;
    m_afEntry[14] = FIXED_ZERO;
    m_afEntry[15] = -fNdD;
}
//----------------------------------------------------------------------------

void Matrix4x::MakePerspectiveProjection (const Vector3x& rkNormal,
    const Vector3x& rkPoint, const Vector3x& rkEye)
{
    //     +-                                                 -+
    // M = | Dot(N,E-P)*I - E*N^T    -(Dot(N,E-P)*I - E*N^T)*E |
    //     |        -N^t                      Dot(N,E)         |
    //     +-                                                 -+
    //
    // where E is the eye point, P is a point on the plane, and N is a
    // unit-length plane normal.

    fixed fNdEmP = rkNormal.Dot(rkEye-rkPoint);

    m_afEntry[ 0] = fNdEmP - rkEye[0]*rkNormal[0];
    m_afEntry[ 1] = -rkEye[0]*rkNormal[1];
    m_afEntry[ 2] = -rkEye[0]*rkNormal[2];
    m_afEntry[ 3] = -(m_afEntry[0]*rkEye[0] + m_afEntry[1]*rkEye[1] +
        m_afEntry[2]*rkEye[2]);
    m_afEntry[ 4] = -rkEye[1]*rkNormal[0];
    m_afEntry[ 5] = fNdEmP - rkEye[1]*rkNormal[1];
    m_afEntry[ 6] = -rkEye[1]*rkNormal[2];
    m_afEntry[ 7] = -(m_afEntry[4]*rkEye[0] + m_afEntry[5]*rkEye[1] +
        m_afEntry[6]*rkEye[2]);
    m_afEntry[ 8] = -rkEye[2]*rkNormal[0];
    m_afEntry[ 9] = -rkEye[2]*rkNormal[1];
    m_afEntry[10] = fNdEmP- rkEye[2]*rkNormal[2];
    m_afEntry[11] = -(m_afEntry[8]*rkEye[0] + m_afEntry[9]*rkEye[1] +
        m_afEntry[10]*rkEye[2]);
    m_afEntry[12] = -rkNormal[0];
    m_afEntry[13] = -rkNormal[1];
    m_afEntry[14] = -rkNormal[2];
    m_afEntry[15] = rkNormal.Dot(rkEye);
}
//----------------------------------------------------------------------------

void Matrix4x::MakeReflection (const Vector3x& rkNormal,
    const Vector3x& rkPoint)
{
    //     +-                         -+
    // M = | I-2*N*N^T    2*Dot(N,P)*N |
    //     |     0^T            1      |
    //     +-                         -+
    //
    // where P is a point on the plane and N is a unit-length plane normal.

    fixed fTwoNdP = FixedFromFloat((float)2.0)*(rkNormal.Dot(rkPoint));

    m_afEntry[ 0] = FIXED_ONE - FixedFromFloat((float)2.0)*rkNormal[0]*rkNormal[0];
    m_afEntry[ 1] = -FixedFromFloat((float)2.0)*rkNormal[0]*rkNormal[1];
    m_afEntry[ 2] = -FixedFromFloat((float)2.0)*rkNormal[0]*rkNormal[2];
    m_afEntry[ 3] = fTwoNdP*rkNormal[0];
    m_afEntry[ 4] = -FixedFromFloat((float)2.0)*rkNormal[1]*rkNormal[0];
    m_afEntry[ 5] = FIXED_ONE - FixedFromFloat((float)2.0)*rkNormal[1]*rkNormal[1];
    m_afEntry[ 6] = -FixedFromFloat((float)2.0)*rkNormal[1]*rkNormal[2];
    m_afEntry[ 7] = fTwoNdP*rkNormal[1];
    m_afEntry[ 8] = -FixedFromFloat((float)2.0)*rkNormal[2]*rkNormal[0];
    m_afEntry[ 9] = -FixedFromFloat((float)2.0)*rkNormal[2]*rkNormal[1];
    m_afEntry[10] = FIXED_ONE - FixedFromFloat((float)2.0)*rkNormal[2]*rkNormal[2];
    m_afEntry[11] = fTwoNdP*rkNormal[2];
    m_afEntry[12] = FIXED_ZERO;
    m_afEntry[13] = FIXED_ZERO;
    m_afEntry[14] = FIXED_ZERO;
    m_afEntry[15] = FIXED_ONE;
}
//----------------------------------------------------------------------------



}