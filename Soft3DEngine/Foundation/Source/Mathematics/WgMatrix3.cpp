///////////////////////////////////////////////////////////
//                                                       //
//                    WgMatrix3.cpp                      //
//                                                       //
//  - Implementation for Matrix3 class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////


#include "WgFoundationPCH.h"
#include "WgMatrix3.h"
#include "WgQuaternion.h"
namespace WGSoft3D
{
template<> const Matrix3<float> Matrix3<float>::ZERO(
    0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f);
template<> const Matrix3<float> Matrix3<float>::IDENTITY(
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,0.0f,1.0f);

template<> const Matrix3<double> Matrix3<double>::ZERO(
    0.0,0.0,0.0,
    0.0,0.0,0.0,
    0.0,0.0,0.0);
template<> const Matrix3<double> Matrix3<double>::IDENTITY(
    1.0,0.0,0.0,
    0.0,1.0,0.0,
    0.0,0.0,1.0);

const Matrix3x Matrix3x::ZERO(
	fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
	fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
	fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO));
const Matrix3x Matrix3x::IDENTITY(
	fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
    fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),
	fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE));



//----------------------------------------------------------------------------
//
// Fixed Matrix 3 Implementation
//
//----------------------------------------------------------------------------

Matrix3x::Matrix3x (bool bZero)
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

Matrix3x::Matrix3x (const Matrix3x& rkM)
{
    m_afEntry[0] = rkM.m_afEntry[0];
    m_afEntry[1] = rkM.m_afEntry[1];
    m_afEntry[2] = rkM.m_afEntry[2];
    m_afEntry[3] = rkM.m_afEntry[3];
    m_afEntry[4] = rkM.m_afEntry[4];
    m_afEntry[5] = rkM.m_afEntry[5];
    m_afEntry[6] = rkM.m_afEntry[6];
    m_afEntry[7] = rkM.m_afEntry[7];
    m_afEntry[8] = rkM.m_afEntry[8];
}
//----------------------------------------------------------------------------

Matrix3x::Matrix3x (fixed fM00, fixed fM01, fixed fM02, fixed fM10, fixed fM11,
    fixed fM12, fixed fM20, fixed fM21, fixed fM22)
{
    m_afEntry[0] = fM00;
    m_afEntry[1] = fM01;
    m_afEntry[2] = fM02;
    m_afEntry[3] = fM10;
    m_afEntry[4] = fM11;
    m_afEntry[5] = fM12;
    m_afEntry[6] = fM20;
    m_afEntry[7] = fM21;
    m_afEntry[8] = fM22;
}
//----------------------------------------------------------------------------

Matrix3x::Matrix3x (const fixed afEntry[9], bool bRowMajor)
{
    if (bRowMajor)
    {
        m_afEntry[0] = afEntry[0];
        m_afEntry[1] = afEntry[1];
        m_afEntry[2] = afEntry[2];
        m_afEntry[3] = afEntry[3];
        m_afEntry[4] = afEntry[4];
        m_afEntry[5] = afEntry[5];
        m_afEntry[6] = afEntry[6];
        m_afEntry[7] = afEntry[7];
        m_afEntry[8] = afEntry[8];
    }
    else
    {
        m_afEntry[0] = afEntry[0];
        m_afEntry[1] = afEntry[3];
        m_afEntry[2] = afEntry[6];
        m_afEntry[3] = afEntry[1];
        m_afEntry[4] = afEntry[4];
        m_afEntry[5] = afEntry[7];
        m_afEntry[6] = afEntry[2];
        m_afEntry[7] = afEntry[5];
        m_afEntry[8] = afEntry[8];
    }
}
//----------------------------------------------------------------------------

Matrix3x::Matrix3x (const Vector3x& rkU, const Vector3x& rkV,
    const Vector3x& rkW, bool bColumns)
{
    if (bColumns)
    {
        m_afEntry[0] = rkU[0];
        m_afEntry[1] = rkV[0];
        m_afEntry[2] = rkW[0];
        m_afEntry[3] = rkU[1];
        m_afEntry[4] = rkV[1];
        m_afEntry[5] = rkW[1];
        m_afEntry[6] = rkU[2];
        m_afEntry[7] = rkV[2];
        m_afEntry[8] = rkW[2];
    }
    else
    {
        m_afEntry[0] = rkU[0];
        m_afEntry[1] = rkU[1];
        m_afEntry[2] = rkU[2];
        m_afEntry[3] = rkV[0];
        m_afEntry[4] = rkV[1];
        m_afEntry[5] = rkV[2];
        m_afEntry[6] = rkW[0];
        m_afEntry[7] = rkW[1];
        m_afEntry[8] = rkW[2];
    }
}
//----------------------------------------------------------------------------

Matrix3x::Matrix3x (const Vector3x* akV, bool bColumns)
{
    if (bColumns)
    {
        m_afEntry[0] = akV[0][0];
        m_afEntry[1] = akV[1][0];
        m_afEntry[2] = akV[2][0];
        m_afEntry[3] = akV[0][1];
        m_afEntry[4] = akV[1][1];
        m_afEntry[5] = akV[2][1];
        m_afEntry[6] = akV[0][2];
        m_afEntry[7] = akV[1][2];
        m_afEntry[8] = akV[2][2];
    }
    else
    {
        m_afEntry[0] = akV[0][0];
        m_afEntry[1] = akV[0][1];
        m_afEntry[2] = akV[0][2];
        m_afEntry[3] = akV[1][0];
        m_afEntry[4] = akV[1][1];
        m_afEntry[5] = akV[1][2];
        m_afEntry[6] = akV[2][0];
        m_afEntry[7] = akV[2][1];
        m_afEntry[8] = akV[2][2];
    }
}
//----------------------------------------------------------------------------

Matrix3x::Matrix3x (fixed fM00, fixed fM11, fixed fM22)
{
    MakeDiagonal(fM00,fM11,fM22);
}
//----------------------------------------------------------------------------

Matrix3x::Matrix3x (const Vector3x& rkAxis, fixed fAngle)
{
    FromAxisAngle(rkAxis,fAngle);
}
//----------------------------------------------------------------------------

Matrix3x::Matrix3x (const Vector3x& rkU, const Vector3x& rkV)
{
    MakeTensorProduct(rkU,rkV);
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::MakeZero ()
{
    m_afEntry[0] = FIXED_ZERO;
    m_afEntry[1] = FIXED_ZERO;
    m_afEntry[2] = FIXED_ZERO;
    m_afEntry[3] = FIXED_ZERO;
    m_afEntry[4] = FIXED_ZERO;
    m_afEntry[5] = FIXED_ZERO;
    m_afEntry[6] = FIXED_ZERO;
    m_afEntry[7] = FIXED_ZERO;
    m_afEntry[8] = FIXED_ZERO;
    return *this;
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::MakeIdentity ()
{
    m_afEntry[0] = FIXED_ONE;
    m_afEntry[1] = FIXED_ZERO;
    m_afEntry[2] = FIXED_ZERO;
    m_afEntry[3] = FIXED_ZERO;
    m_afEntry[4] = FIXED_ONE;
    m_afEntry[5] = FIXED_ZERO;
    m_afEntry[6] = FIXED_ZERO;
    m_afEntry[7] = FIXED_ZERO;
    m_afEntry[8] = FIXED_ONE;
    return *this;
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::MakeDiagonal (fixed fM00, fixed fM11, fixed fM22)
{
    m_afEntry[0] = fM00;
    m_afEntry[1] = FIXED_ZERO;
    m_afEntry[2] = FIXED_ZERO;
    m_afEntry[3] = FIXED_ZERO;
    m_afEntry[4] = fM11;
    m_afEntry[5] = FIXED_ZERO;
    m_afEntry[6] = FIXED_ZERO;
    m_afEntry[7] = FIXED_ZERO;
    m_afEntry[8] = fM22;
    return *this;
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::FromAxisAngle (const Vector3x& rkAxis,
    fixed fAngle)
{
    fixed fCos = Mathx::Cos(fAngle);
    fixed fSin = Mathx::Sin(fAngle);
    fixed fOneMinusCos = (FIXED_ONE)-fCos;
    fixed fX2 = rkAxis[0]*rkAxis[0];
    fixed fY2 = rkAxis[1]*rkAxis[1];
    fixed fZ2 = rkAxis[2]*rkAxis[2];
    fixed fXYM = rkAxis[0]*rkAxis[1]*fOneMinusCos;
    fixed fXZM = rkAxis[0]*rkAxis[2]*fOneMinusCos;
    fixed fYZM = rkAxis[1]*rkAxis[2]*fOneMinusCos;
    fixed fXSin = rkAxis[0]*fSin;
    fixed fYSin = rkAxis[1]*fSin;
    fixed fZSin = rkAxis[2]*fSin;
    
    m_afEntry[0] = fX2*fOneMinusCos+fCos;
    m_afEntry[1] = fXYM-fZSin;
    m_afEntry[2] = fXZM+fYSin;
    m_afEntry[3] = fXYM+fZSin;
    m_afEntry[4] = fY2*fOneMinusCos+fCos;
    m_afEntry[5] = fYZM-fXSin;
    m_afEntry[6] = fXZM-fYSin;
    m_afEntry[7] = fYZM+fXSin;
    m_afEntry[8] = fZ2*fOneMinusCos+fCos;

    return *this;
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::MakeTensorProduct (const Vector3x& rkU,
    const Vector3x& rkV)
{
    m_afEntry[0] = rkU[0]*rkV[0];
    m_afEntry[1] = rkU[0]*rkV[1];
    m_afEntry[2] = rkU[0]*rkV[2];
    m_afEntry[3] = rkU[1]*rkV[0];
    m_afEntry[4] = rkU[1]*rkV[1];
    m_afEntry[5] = rkU[1]*rkV[2];
    m_afEntry[6] = rkU[2]*rkV[0];
    m_afEntry[7] = rkU[2]*rkV[1];
    m_afEntry[8] = rkU[2]*rkV[2];
    return *this;
}
//----------------------------------------------------------------------------

void Matrix3x::SetRow (int iRow, const Vector3x& rkV)
{
    int i0 = 3*iRow, i1 = i0+1, i2 = i1+1;
    m_afEntry[i0] = rkV[0];
    m_afEntry[i1] = rkV[1];
    m_afEntry[i2] = rkV[2];
}
//----------------------------------------------------------------------------

Vector3x Matrix3x::GetRow (int iRow) const
{
    int i0 = 3*iRow, i1 = i0+1, i2 = i1+1;
    return Vector3x(m_afEntry[i0],m_afEntry[i1],m_afEntry[i2]);
}
//----------------------------------------------------------------------------

void Matrix3x::SetColumn (int iCol, const Vector3x& rkV)
{
    m_afEntry[iCol] = rkV[0];
    m_afEntry[iCol+3] = rkV[1];
    m_afEntry[iCol+6] = rkV[2];
}
//----------------------------------------------------------------------------

Vector3x Matrix3x::GetColumn (int iCol) const
{
    return Vector3x(m_afEntry[iCol],m_afEntry[iCol+3],m_afEntry[iCol+6]);
}
//----------------------------------------------------------------------------

void Matrix3x::GetColumnMajor (fixed* afCMajor) const
{
    afCMajor[0] = m_afEntry[0];
    afCMajor[1] = m_afEntry[3];
    afCMajor[2] = m_afEntry[6];
    afCMajor[3] = m_afEntry[1];
    afCMajor[4] = m_afEntry[4];
    afCMajor[5] = m_afEntry[7];
    afCMajor[6] = m_afEntry[2];
    afCMajor[7] = m_afEntry[5];
    afCMajor[8] = m_afEntry[8];
}
//----------------------------------------------------------------------------

int Matrix3x::CompareArrays (const Matrix3x& rkM) const
{
    return memcmp(m_afEntry,rkM.m_afEntry,9*sizeof(fixed));
}
//----------------------------------------------------------------------------

bool Matrix3x::operator== (const Matrix3x& rkM) const
{
    return CompareArrays(rkM) == 0;
}
//----------------------------------------------------------------------------

bool Matrix3x::operator!= (const Matrix3x& rkM) const
{
    return CompareArrays(rkM) != 0;
}
//----------------------------------------------------------------------------

bool Matrix3x::operator<  (const Matrix3x& rkM) const
{
    return CompareArrays(rkM) < 0;
}
//----------------------------------------------------------------------------

bool Matrix3x::operator<= (const Matrix3x& rkM) const
{
    return CompareArrays(rkM) <= 0;
}
//----------------------------------------------------------------------------

bool Matrix3x::operator>  (const Matrix3x& rkM) const
{
    return CompareArrays(rkM) > 0;
}
//----------------------------------------------------------------------------

bool Matrix3x::operator>= (const Matrix3x& rkM) const
{
    return CompareArrays(rkM) >= 0;
}
//----------------------------------------------------------------------------

Matrix3x Matrix3x::Transpose () const
{
    return Matrix3x(
        m_afEntry[0],
        m_afEntry[3],
        m_afEntry[6],
        m_afEntry[1],
        m_afEntry[4],
        m_afEntry[7],
        m_afEntry[2],
        m_afEntry[5],
        m_afEntry[8]);
}
//----------------------------------------------------------------------------

Matrix3x Matrix3x::TransposeTimes (const Matrix3x& rkM) const
{
    // P = A^T*B
    return Matrix3x(
        m_afEntry[0]*rkM.m_afEntry[0] +
        m_afEntry[3]*rkM.m_afEntry[3] +
        m_afEntry[6]*rkM.m_afEntry[6],

        m_afEntry[0]*rkM.m_afEntry[1] +
        m_afEntry[3]*rkM.m_afEntry[4] +
        m_afEntry[6]*rkM.m_afEntry[7],

        m_afEntry[0]*rkM.m_afEntry[2] +
        m_afEntry[3]*rkM.m_afEntry[5] +
        m_afEntry[6]*rkM.m_afEntry[8],

        m_afEntry[1]*rkM.m_afEntry[0] +
        m_afEntry[4]*rkM.m_afEntry[3] +
        m_afEntry[7]*rkM.m_afEntry[6],

        m_afEntry[1]*rkM.m_afEntry[1] +
        m_afEntry[4]*rkM.m_afEntry[4] +
        m_afEntry[7]*rkM.m_afEntry[7],

        m_afEntry[1]*rkM.m_afEntry[2] +
        m_afEntry[4]*rkM.m_afEntry[5] +
        m_afEntry[7]*rkM.m_afEntry[8],

        m_afEntry[2]*rkM.m_afEntry[0] +
        m_afEntry[5]*rkM.m_afEntry[3] +
        m_afEntry[8]*rkM.m_afEntry[6],

        m_afEntry[2]*rkM.m_afEntry[1] +
        m_afEntry[5]*rkM.m_afEntry[4] +
        m_afEntry[8]*rkM.m_afEntry[7],

        m_afEntry[2]*rkM.m_afEntry[2] +
        m_afEntry[5]*rkM.m_afEntry[5] +
        m_afEntry[8]*rkM.m_afEntry[8]);
}
//----------------------------------------------------------------------------

Matrix3x Matrix3x::TimesTranspose (const Matrix3x& rkM) const
{
    // P = A*B^T
    return Matrix3x(
        m_afEntry[0]*rkM.m_afEntry[0] +
        m_afEntry[1]*rkM.m_afEntry[1] +
        m_afEntry[2]*rkM.m_afEntry[2],

        m_afEntry[0]*rkM.m_afEntry[3] +
        m_afEntry[1]*rkM.m_afEntry[4] +
        m_afEntry[2]*rkM.m_afEntry[5],

        m_afEntry[0]*rkM.m_afEntry[6] +
        m_afEntry[1]*rkM.m_afEntry[7] +
        m_afEntry[2]*rkM.m_afEntry[8],

        m_afEntry[3]*rkM.m_afEntry[0] +
        m_afEntry[4]*rkM.m_afEntry[1] +
        m_afEntry[5]*rkM.m_afEntry[2],

        m_afEntry[3]*rkM.m_afEntry[3] +
        m_afEntry[4]*rkM.m_afEntry[4] +
        m_afEntry[5]*rkM.m_afEntry[5],

        m_afEntry[3]*rkM.m_afEntry[6] +
        m_afEntry[4]*rkM.m_afEntry[7] +
        m_afEntry[5]*rkM.m_afEntry[8],

        m_afEntry[6]*rkM.m_afEntry[0] +
        m_afEntry[7]*rkM.m_afEntry[1] +
        m_afEntry[8]*rkM.m_afEntry[2],

        m_afEntry[6]*rkM.m_afEntry[3] +
        m_afEntry[7]*rkM.m_afEntry[4] +
        m_afEntry[8]*rkM.m_afEntry[5],

        m_afEntry[6]*rkM.m_afEntry[6] +
        m_afEntry[7]*rkM.m_afEntry[7] +
        m_afEntry[8]*rkM.m_afEntry[8]);
}
//----------------------------------------------------------------------------

Matrix3x Matrix3x::Inverse () const
{
    // Invert a 3x3 using cofactors.  This is faster than using a generic
    // Gaussian elimination because of the loop overhead of such a method.

    Matrix3x kInverse;

    kInverse.m_afEntry[0] =
        m_afEntry[4]*m_afEntry[8] - m_afEntry[5]*m_afEntry[7];
    kInverse.m_afEntry[1] =
        m_afEntry[2]*m_afEntry[7] - m_afEntry[1]*m_afEntry[8];
    kInverse.m_afEntry[2] =
        m_afEntry[1]*m_afEntry[5] - m_afEntry[2]*m_afEntry[4];
    kInverse.m_afEntry[3] =
        m_afEntry[5]*m_afEntry[6] - m_afEntry[3]*m_afEntry[8];
    kInverse.m_afEntry[4] =
        m_afEntry[0]*m_afEntry[8] - m_afEntry[2]*m_afEntry[6];
    kInverse.m_afEntry[5] =
        m_afEntry[2]*m_afEntry[3] - m_afEntry[0]*m_afEntry[5];
    kInverse.m_afEntry[6] =
        m_afEntry[3]*m_afEntry[7] - m_afEntry[4]*m_afEntry[6];
    kInverse.m_afEntry[7] =
        m_afEntry[1]*m_afEntry[6] - m_afEntry[0]*m_afEntry[7];
    kInverse.m_afEntry[8] =
        m_afEntry[0]*m_afEntry[4] - m_afEntry[1]*m_afEntry[3];

    fixed fDet =
        m_afEntry[0]*kInverse.m_afEntry[0] +
        m_afEntry[1]*kInverse.m_afEntry[3] +
        m_afEntry[2]*kInverse.m_afEntry[6];

    if (Mathx::FAbs(fDet) <= Mathx::ZERO_TOLERANCE)
    {
        return ZERO;
    }

    fixed fInvDet = (FIXED_ONE)/fDet;
    kInverse.m_afEntry[0] *= fInvDet;
    kInverse.m_afEntry[1] *= fInvDet;
    kInverse.m_afEntry[2] *= fInvDet;
    kInverse.m_afEntry[3] *= fInvDet;
    kInverse.m_afEntry[4] *= fInvDet;
    kInverse.m_afEntry[5] *= fInvDet;
    kInverse.m_afEntry[6] *= fInvDet;
    kInverse.m_afEntry[7] *= fInvDet;
    kInverse.m_afEntry[8] *= fInvDet;
    return kInverse;
}
//----------------------------------------------------------------------------

Matrix3x Matrix3x::Adjoint () const
{
    return Matrix3x(
        m_afEntry[4]*m_afEntry[8] - m_afEntry[5]*m_afEntry[7],
        m_afEntry[2]*m_afEntry[7] - m_afEntry[1]*m_afEntry[8],
        m_afEntry[1]*m_afEntry[5] - m_afEntry[2]*m_afEntry[4],
        m_afEntry[5]*m_afEntry[6] - m_afEntry[3]*m_afEntry[8],
        m_afEntry[0]*m_afEntry[8] - m_afEntry[2]*m_afEntry[6],
        m_afEntry[2]*m_afEntry[3] - m_afEntry[0]*m_afEntry[5],
        m_afEntry[3]*m_afEntry[7] - m_afEntry[4]*m_afEntry[6],
        m_afEntry[1]*m_afEntry[6] - m_afEntry[0]*m_afEntry[7],
        m_afEntry[0]*m_afEntry[4] - m_afEntry[1]*m_afEntry[3]);
}
//----------------------------------------------------------------------------

fixed Matrix3x::Determinant () const
{
    fixed fCo00 = m_afEntry[4]*m_afEntry[8] - m_afEntry[5]*m_afEntry[7];
    fixed fCo10 = m_afEntry[5]*m_afEntry[6] - m_afEntry[3]*m_afEntry[8];
    fixed fCo20 = m_afEntry[3]*m_afEntry[7] - m_afEntry[4]*m_afEntry[6];
    fixed fDet = m_afEntry[0]*fCo00 + m_afEntry[1]*fCo10 + m_afEntry[2]*fCo20;
    return fDet;
}
//----------------------------------------------------------------------------

fixed Matrix3x::QForm (const Vector3x& rkU, const Vector3x& rkV)
    const
{
    return rkU.Dot((*this)*rkV);
}
//----------------------------------------------------------------------------

Matrix3x Matrix3x::TimesDiagonal (const Vector3x& rkDiag) const
{
    return Matrix3x(
        m_afEntry[0]*rkDiag[0],m_afEntry[1]*rkDiag[1],m_afEntry[2]*rkDiag[2],
        m_afEntry[3]*rkDiag[0],m_afEntry[4]*rkDiag[1],m_afEntry[5]*rkDiag[2],
        m_afEntry[6]*rkDiag[0],m_afEntry[7]*rkDiag[1],m_afEntry[8]*rkDiag[2]);
}
//----------------------------------------------------------------------------

Matrix3x Matrix3x::DiagonalTimes (const Vector3x& rkDiag) const
{
    return Matrix3x(
        rkDiag[0]*m_afEntry[0],rkDiag[0]*m_afEntry[1],rkDiag[0]*m_afEntry[2],
        rkDiag[1]*m_afEntry[3],rkDiag[1]*m_afEntry[4],rkDiag[1]*m_afEntry[5],
        rkDiag[2]*m_afEntry[6],rkDiag[2]*m_afEntry[7],rkDiag[2]*m_afEntry[8]);
}
//----------------------------------------------------------------------------
Matrix3x Matrix3x::Rotation(fixed &xRotAng,fixed &yRotAng,fixed &zRotAng )
{
	Matrix3x CalcMat3;
	fixed Cx, Sx;
	Sx = Mathx::Sin(xRotAng);
	Cx = Mathx::Cos(xRotAng);
	fixed Cy, Sy;
	Sy = Mathx::Sin(yRotAng);
	Cy = Mathx::Cos(yRotAng);

	fixed Cz, Sz;
	Sz = Mathx::Sin(zRotAng);
	Cz = Mathx::Cos(zRotAng);
	
	CalcMat3.m_afEntry[0] =  (Cy * Cz);
	CalcMat3.m_afEntry[1] = -(Cy * Sz);  
	CalcMat3.m_afEntry[2] =  Sy;
	
	CalcMat3.m_afEntry[3] =  (Sx * Sy * Cz) + (Cx * Sz);
	CalcMat3.m_afEntry[4] = -(Sx * Sy * Sz) + (Cx * Cz);
	CalcMat3.m_afEntry[5] = -(Sx * Cy); 
	
	CalcMat3.m_afEntry[6] = -(Cx * Sy * Cz) + (Sx * Sz);
	CalcMat3.m_afEntry[7] =  (Cx * Sy * Sz) + (Sx * Cz);
	CalcMat3.m_afEntry[8] =  (Cx * Cy);
	return Matrix3x(CalcMat3);
}
//----------------------------------------------------------------------------
Matrix3x Matrix3x::RotationX(fixed &rkAngle )
{
	Matrix3x CalcMat3;
	fixed sintheta, costheta;
	sintheta = Mathx::Sin(rkAngle);
	costheta = Mathx::Cos(rkAngle);
	
	CalcMat3.m_afEntry[0] = FIXED_ONE;
	CalcMat3.m_afEntry[3] = FIXED_ZERO;
	CalcMat3.m_afEntry[6] = FIXED_ZERO;
	CalcMat3.m_afEntry[1] = FIXED_ZERO;
	CalcMat3.m_afEntry[4] = costheta;
	CalcMat3.m_afEntry[7] = sintheta;
	CalcMat3.m_afEntry[2] = FIXED_ZERO;
	CalcMat3.m_afEntry[5] = -sintheta;
	CalcMat3.m_afEntry[8] = costheta;
	return Matrix3x(CalcMat3);
}
//----------------------------------------------------------------------------
Matrix3x Matrix3x::RotationY(fixed &rkAngle )
{
	Matrix3x CalcMat3;
	fixed sintheta, costheta;
	sintheta = Mathx::Sin(rkAngle);
	costheta = Mathx::Cos(rkAngle);
		
	CalcMat3.m_afEntry[0] = costheta;
	CalcMat3.m_afEntry[3] = FIXED_ZERO;
	CalcMat3.m_afEntry[6] = -sintheta;
	CalcMat3.m_afEntry[1] = FIXED_ZERO;
	CalcMat3.m_afEntry[4] = FIXED_ONE;
	CalcMat3.m_afEntry[7] = FIXED_ZERO;
	CalcMat3.m_afEntry[2] = sintheta;
	CalcMat3.m_afEntry[5] = FIXED_ZERO;
	CalcMat3.m_afEntry[8] = costheta;
	return Matrix3x(CalcMat3);
}
//----------------------------------------------------------------------------
Matrix3x Matrix3x::RotationZ(fixed &rkAngle )
{
	Matrix3x CalcMat3;
	fixed sintheta, costheta;
	sintheta = Mathx::Sin(rkAngle);
	costheta = Mathx::Cos(rkAngle);
	
	
	CalcMat3.m_afEntry[0] = costheta;
	CalcMat3.m_afEntry[3] = sintheta;
	CalcMat3.m_afEntry[6] = FIXED_ZERO;
	CalcMat3.m_afEntry[1] = -sintheta;
	CalcMat3.m_afEntry[4] = costheta;
	CalcMat3.m_afEntry[7] = FIXED_ZERO;
	CalcMat3.m_afEntry[2] = FIXED_ZERO;
	CalcMat3.m_afEntry[5] = FIXED_ZERO;
	CalcMat3.m_afEntry[8] = FIXED_ONE;
	return Matrix3x(CalcMat3);
}
//----------------------------------------------------------------------------
Matrix3x Matrix3x::RotationWithQuaternion(Quaternionx &pRotQuat )
{
	
	Matrix3x CalcMat3;
	fixed xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;
	
	xs = pRotQuat.X() + pRotQuat.X(); //rotate.x+rotate.x;   
	ys = pRotQuat.Y()+ pRotQuat.Y(); // rotate.y+rotate.y;
	zs = pRotQuat.Z()+ pRotQuat.Z(); // rotate.z+rotate.z;
	wx = pRotQuat.W() * xs; //rotate.w*xs;
	wy = pRotQuat.W()*ys;
	wz = pRotQuat.W()*zs;
	xx = pRotQuat.X()*xs;
	xy = pRotQuat.X()*ys;
	xz = pRotQuat.X()*zs;
	yy = pRotQuat.Y()*ys;
	yz = pRotQuat.Y()*zs;
	zz = pRotQuat.Z()*zs;
	
	CalcMat3.m_afEntry[0] = FIXED_ONE - (yy + zz);
	CalcMat3.m_afEntry[1] = xy - wz;
	CalcMat3.m_afEntry[2] = xz + wy;
	
	CalcMat3.m_afEntry[3] = xy + wz;
	CalcMat3.m_afEntry[4] = FIXED_ONE - (xx + zz);
	CalcMat3.m_afEntry[5] = yz - wx;
	
	CalcMat3.m_afEntry[6] = xz - wy;
	CalcMat3.m_afEntry[7] = yz + wx;
	CalcMat3.m_afEntry[8] = FIXED_ONE - (xx + yy);
	return Matrix3x(CalcMat3);

}
//----------------------------------------------------------------------------
Matrix3x Matrix3x::Scaling(Vector3x &pScale )
{
	Matrix3x CalcMat3;
	CalcMat3.m_afEntry[0] = pScale.X();
	CalcMat3.m_afEntry[3] = FIXED_ZERO;
	CalcMat3.m_afEntry[6] = FIXED_ZERO;
	CalcMat3.m_afEntry[1] = FIXED_ZERO;
	CalcMat3.m_afEntry[4] = pScale.Y();
	CalcMat3.m_afEntry[7] = FIXED_ZERO;
	CalcMat3.m_afEntry[2] = FIXED_ZERO;
	CalcMat3.m_afEntry[5] = FIXED_ZERO;
	CalcMat3.m_afEntry[8] = pScale.Z();
	return Matrix3x(CalcMat3);
}
//----------------------------------------------------------------------------
void Matrix3x::SetRotation(fixed &xRotAng,fixed &yRotAng,fixed &zRotAng)
{
	*this=Rotation(xRotAng,yRotAng,zRotAng);
}
//----------------------------------------------------------------------------
void Matrix3x::SetRotationX(fixed &rkAngle )
{
	*this=RotationX(rkAngle);
}
//----------------------------------------------------------------------------
void Matrix3x::SetRotationY(fixed &rkAngle )
{
	*this=RotationY(rkAngle);
}
//----------------------------------------------------------------------------
void Matrix3x::SetRotationZ(fixed &rkAngle )
{
	*this=RotationZ(rkAngle);
}
//----------------------------------------------------------------------------
void Matrix3x::SetRotationWithQuaternion(Quaternionx &pRotQuat )
{
	*this=RotationWithQuaternion(pRotQuat);
}
//----------------------------------------------------------------------------
void Matrix3x::SetScaling(Vector3x &pScale)
{
	*this=Scaling(pScale);
}
//----------------------------------------------------------------------------

void Matrix3x::ToAxisAngle (Vector3x& rkAxis, fixed& rfAngle) const
{
    // Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
    // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
    // I is the identity and
    //
    //       +-        -+
    //   P = |  0 -z +y |
    //       | +z  0 -x |
    //       | -y +x  0 |
    //       +-        -+
    //
    // If A > 0, R represents a counterclockwise rotation about the axis in
    // the sense of looking from the tip of the axis vector towards the
    // origin.  Some algebra will show that
    //
    //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
    //
    // In the event that A = pi, R-R^t = 0 which prevents us from extracting
    // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
    // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
    // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
    // it does not matter which sign you choose on the square roots.

    fixed fTrace = m_afEntry[0] + m_afEntry[4] + m_afEntry[8];
    fixed fCos = (FIXED_HALF)*(fTrace-FIXED_ONE);
    rfAngle = Mathx::ACos(fCos);  // in [0,PI]

    if (rfAngle > FIXED_ZERO)
    {
        if (rfAngle < Mathx::PI)
        {
            rkAxis[0] = m_afEntry[7]-m_afEntry[5];
            rkAxis[1] = m_afEntry[2]-m_afEntry[6];
            rkAxis[2] = m_afEntry[3]-m_afEntry[1];
            rkAxis.Normalize();
        }
        else
        {
            // angle is PI
            fixed fHalfInverse;
            if (m_afEntry[0] >= m_afEntry[4])
            {
                // r00 >= r11
                if (m_afEntry[0] >= m_afEntry[8])
                {
                    // r00 is maximum diagonal term
                    rkAxis[0] = (FIXED_HALF)*Mathx::Sqrt(m_afEntry[0] -
                        m_afEntry[4] - m_afEntry[8] + FIXED_ONE);
                    fHalfInverse = (FIXED_HALF)/rkAxis[0];
                    rkAxis[1] = fHalfInverse*m_afEntry[1];
                    rkAxis[2] = fHalfInverse*m_afEntry[2];
                }
                else
                {
                    // r22 is maximum diagonal term
                    rkAxis[2] = (FIXED_HALF)*Mathx::Sqrt(m_afEntry[8] -
                        m_afEntry[0] - m_afEntry[4] + FIXED_ONE);
                    fHalfInverse = (FIXED_HALF)/rkAxis[2];
                    rkAxis[0] = fHalfInverse*m_afEntry[2];
                    rkAxis[1] = fHalfInverse*m_afEntry[5];
                }
            }
            else
            {
                // r11 > r00
                if (m_afEntry[4] >= m_afEntry[8])
                {
                    // r11 is maximum diagonal term
                    rkAxis[1] = (FIXED_HALF)*Mathx::Sqrt(m_afEntry[4] -
                        m_afEntry[0] - m_afEntry[8] + FIXED_ONE);
                    fHalfInverse  = (FIXED_HALF)/rkAxis[1];
                    rkAxis[0] = fHalfInverse*m_afEntry[1];
                    rkAxis[2] = fHalfInverse*m_afEntry[5];
                }
                else
                {
                    // r22 is maximum diagonal term
                    rkAxis[2] = (FIXED_HALF)*Mathx::Sqrt(m_afEntry[8] -
                        m_afEntry[0] - m_afEntry[4] + FIXED_ONE);
                    fHalfInverse = (FIXED_HALF)/rkAxis[2];
                    rkAxis[0] = fHalfInverse*m_afEntry[2];
                    rkAxis[1] = fHalfInverse*m_afEntry[5];
                }
            }
        }
    }
    else
    {
        // The angle is 0 and the matrix is the identity.  Any axis will
        // work, so just use the x-axis.
        rkAxis[0] = FIXED_ONE;
        rkAxis[1] = FIXED_ZERO;
        rkAxis[2] = FIXED_ZERO;
    }
}
//----------------------------------------------------------------------------

void Matrix3x::Orthonormalize ()
{
    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // compute q0
    fixed fInvLength = Mathx::InvSqrt(m_afEntry[0]*m_afEntry[0] +
        m_afEntry[3]*m_afEntry[3] + m_afEntry[6]*m_afEntry[6]);

    m_afEntry[0] *= fInvLength;
    m_afEntry[3] *= fInvLength;
    m_afEntry[6] *= fInvLength;

    // compute q1
    fixed fDot0 = m_afEntry[0]*m_afEntry[1] + m_afEntry[3]*m_afEntry[4] +
        m_afEntry[6]*m_afEntry[7];

    m_afEntry[1] -= fDot0*m_afEntry[0];
    m_afEntry[4] -= fDot0*m_afEntry[3];
    m_afEntry[7] -= fDot0*m_afEntry[6];

    fInvLength = Mathx::InvSqrt(m_afEntry[1]*m_afEntry[1] +
        m_afEntry[4]*m_afEntry[4] + m_afEntry[7]*m_afEntry[7]);

    m_afEntry[1] *= fInvLength;
    m_afEntry[4] *= fInvLength;
    m_afEntry[7] *= fInvLength;

    // compute q2
    fixed fDot1 = m_afEntry[1]*m_afEntry[2] + m_afEntry[4]*m_afEntry[5] +
        m_afEntry[7]*m_afEntry[8];

    fDot0 = m_afEntry[0]*m_afEntry[2] + m_afEntry[3]*m_afEntry[5] +
        m_afEntry[6]*m_afEntry[8];

    m_afEntry[2] -= fDot0*m_afEntry[0] + fDot1*m_afEntry[1];
    m_afEntry[5] -= fDot0*m_afEntry[3] + fDot1*m_afEntry[4];
    m_afEntry[8] -= fDot0*m_afEntry[6] + fDot1*m_afEntry[7];

    fInvLength = Mathx::InvSqrt(m_afEntry[2]*m_afEntry[2] +
        m_afEntry[5]*m_afEntry[5] + m_afEntry[8]*m_afEntry[8]);

    m_afEntry[2] *= fInvLength;
    m_afEntry[5] *= fInvLength;
    m_afEntry[8] *= fInvLength;
}
//----------------------------------------------------------------------------

void Matrix3x::EigenDecomposition (Matrix3x& rkRot, Matrix3x& rkDiag) const
{
    // Factor M = R*D*R^T.  The columns of R are the eigenvectors.  The
    // diagonal entries of D are the corresponding eigenvalues.
    fixed afDiag[3], afSubd[2];
    rkRot = *this;
    bool bReflection = rkRot.Tridiagonalize(afDiag,afSubd);
    bool bConverged = rkRot.QLAlgorithm(afDiag,afSubd);
    assert(bConverged);

    // (insertion) sort eigenvalues in increasing order, d0 <= d1 <= d2
    int i;
    fixed fSave;

    if (afDiag[1] < afDiag[0])
    {
        // swap d0 and d1
        fSave = afDiag[0];
        afDiag[0] = afDiag[1];
        afDiag[1] = fSave;

        // swap V0 and V1
        for (i = 0; i < 3; i++)
        {
            fSave = rkRot[i][0];
            rkRot[i][0] = rkRot[i][1];
            rkRot[i][1] = fSave;
        }
        bReflection = !bReflection;
    }

    if (afDiag[2] < afDiag[1])
    {
        // swap d1 and d2
        fSave = afDiag[1];
        afDiag[1] = afDiag[2];
        afDiag[2] = fSave;

        // swap V1 and V2
        for (i = 0; i < 3; i++)
        {
            fSave = rkRot[i][1];
            rkRot[i][1] = rkRot[i][2];
            rkRot[i][2] = fSave;
        }
        bReflection = !bReflection;
    }

    if (afDiag[1] < afDiag[0])
    {
        // swap d0 and d1
        fSave = afDiag[0];
        afDiag[0] = afDiag[1];
        afDiag[1] = fSave;

        // swap V0 and V1
        for (i = 0; i < 3; i++)
        {
            fSave = rkRot[i][0];
            rkRot[i][0] = rkRot[i][1];
            rkRot[i][1] = fSave;
        }
        bReflection = !bReflection;
    }

    rkDiag.MakeDiagonal(afDiag[0],afDiag[1],afDiag[2]);

    if (bReflection)
    {
        // The orthogonal transformation that diagonalizes M is a reflection.
        // Make the eigenvectors a right--handed system by changing sign on
        // the last column.
        rkRot[0][2] = -rkRot[0][2];
        rkRot[1][2] = -rkRot[1][2];
        rkRot[2][2] = -rkRot[2][2];
    }
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::FromEulerAnglesXYZ (fixed fXAngle, fixed fYAngle,
    fixed fZAngle)
{
    fixed fCos, fSin;

    fCos = Mathx::Cos(fXAngle);
    fSin = Mathx::Sin(fXAngle);
    Matrix3x kXMat(
        fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fCos,-fSin,
        fixed(FIXED_ZERO),fSin,fCos);

    fCos = Mathx::Cos(fYAngle);
    fSin = Mathx::Sin(fYAngle);
    Matrix3x kYMat(
        fCos,fixed(FIXED_ZERO),fSin,
        fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),
        -fSin,fixed(FIXED_ZERO),fCos);

    fCos = Mathx::Cos(fZAngle);
    fSin = Mathx::Sin(fZAngle);
    Matrix3x kZMat(
        fCos,-fSin,fixed(FIXED_ZERO),
        fSin,fCos,fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE));

    *this = kXMat*(kYMat*kZMat);
    return *this;
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::FromEulerAnglesXZY (fixed fXAngle, fixed fZAngle,
    fixed fYAngle)
{
    fixed fCos, fSin;

    fCos = Mathx::Cos(fXAngle);
    fSin = Mathx::Sin(fXAngle);
    Matrix3x kXMat(
        fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fCos,-fSin,
        fixed(FIXED_ZERO),fSin,fCos);

    fCos = Mathx::Cos(fZAngle);
    fSin = Mathx::Sin(fZAngle);
    Matrix3x kZMat(
        fCos,-fSin,fixed(FIXED_ZERO),
        fSin,fCos,fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE));

    fCos = Mathx::Cos(fYAngle);
    fSin = Mathx::Sin(fYAngle);
    Matrix3x kYMat(
        fCos,fixed(FIXED_ZERO),fSin,
        fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),
        -fSin,fixed(FIXED_ZERO),fCos);

    *this = kXMat*(kZMat*kYMat);
    return *this;
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::FromEulerAnglesYXZ (fixed fYAngle, fixed fXAngle,
    fixed fZAngle)
{
    fixed fCos, fSin;

    fCos = Mathx::Cos(fYAngle);
    fSin = Mathx::Sin(fYAngle);
    Matrix3x kYMat(
        fCos,fixed(FIXED_ZERO),fSin,
        fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),
        -fSin,fixed(FIXED_ZERO),fCos);

    fCos = Mathx::Cos(fXAngle);
    fSin = Mathx::Sin(fXAngle);
    Matrix3x kXMat(
        fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fCos,-fSin,
        fixed(FIXED_ZERO),fSin,fCos);

    fCos = Mathx::Cos(fZAngle);
    fSin = Mathx::Sin(fZAngle);
    Matrix3x kZMat(
        fCos,-fSin,fixed(FIXED_ZERO),
        fSin,fCos,fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE));

    *this = kYMat*(kXMat*kZMat);
    return *this;
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::FromEulerAnglesYZX (fixed fYAngle, fixed fZAngle,
    fixed fXAngle)
{
    fixed fCos, fSin;

    fCos = Mathx::Cos(fYAngle);
    fSin = Mathx::Sin(fYAngle);
    Matrix3x kYMat(
        fCos,fixed(FIXED_ZERO),fSin,
        fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),
        -fSin,fixed(FIXED_ZERO),fCos);

    fCos = Mathx::Cos(fZAngle);
    fSin = Mathx::Sin(fZAngle);
    Matrix3x kZMat(
        fCos,-fSin,fixed(FIXED_ZERO),
        fSin,fCos,fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE));

    fCos = Mathx::Cos(fXAngle);
    fSin = Mathx::Sin(fXAngle);
    Matrix3x kXMat(
        fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fCos,-fSin,
        fixed(FIXED_ZERO),fSin,fCos);

    *this = kYMat*(kZMat*kXMat);
    return *this;
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::FromEulerAnglesZXY (fixed fZAngle, fixed fXAngle,
    fixed fYAngle)
{
    fixed fCos, fSin;

    fCos = Mathx::Cos(fZAngle);
    fSin = Mathx::Sin(fZAngle);
    Matrix3x kZMat(
        fCos,-fSin,fixed(FIXED_ZERO),
        fSin,fCos,fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE));

    fCos = Mathx::Cos(fXAngle);
    fSin = Mathx::Sin(fXAngle);
    Matrix3x kXMat(
        fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fCos,-fSin,
        fixed(FIXED_ZERO),fSin,fCos);

    fCos = Mathx::Cos(fYAngle);
    fSin = Mathx::Sin(fYAngle);
    Matrix3x kYMat(
        fCos,fixed(FIXED_ZERO),fSin,
        fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),
        -fSin,fixed(FIXED_ZERO),fCos);

    *this = kZMat*(kXMat*kYMat);
    return *this;
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::FromEulerAnglesZYX (fixed fZAngle, fixed fYAngle,
    fixed fXAngle)
{
    fixed fCos, fSin;

    fCos = Mathx::Cos(fZAngle);
    fSin = Mathx::Sin(fZAngle);
    Matrix3x kZMat(
        fCos,-fSin,fixed(FIXED_ZERO),
        fSin,fCos,fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE));

    fCos = Mathx::Cos(fYAngle);
    fSin = Mathx::Sin(fYAngle);
    Matrix3x kYMat(
        fCos,fixed(FIXED_ZERO),fSin,
        fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),
        -fSin,fixed(FIXED_ZERO),fCos);

    fCos = Mathx::Cos(fXAngle);
    fSin = Mathx::Sin(fXAngle);
    Matrix3x kXMat(
        fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),
        fixed(FIXED_ZERO),fCos,-fSin,
        fixed(FIXED_ZERO),fSin,fCos);

    *this = kZMat*(kYMat*kXMat);
    return *this;
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesXYZ (
    fixed& rfXAngle, fixed& rfYAngle, fixed& rfZAngle) const
{
    // +-           -+   +-                                        -+
    // | r00 r01 r02 |   |  cy*cz           -cy*sz            sy    |
    // | r10 r11 r12 | = |  cz*sx*sy+cx*sz   cx*cz-sx*sy*sz  -cy*sx |
    // | r20 r21 r22 |   | -cx*cz*sy+sx*sz   cz*sx+cx*sy*sz   cx*cy |
    // +-           -+   +-                                        -+

    if (m_afEntry[2] < FIXED_ONE)
    {
        if (m_afEntry[2] > FIXED_NEG_ONE)
        {
            // y_angle = asin(r02)
            // x_angle = atan2(-r12,r22)
            // z_angle = atan2(-r01,r00)
            rfYAngle = FixedFromFloat((float)asin((double)FloatFromFixed(m_afEntry[2])));
            rfXAngle = Mathx::ATan2(-m_afEntry[5],m_afEntry[8]);
            rfZAngle = Mathx::ATan2(-m_afEntry[1],m_afEntry[0]);
            return EA_UNIQUE;
        }
        else
        {
            // y_angle = -pi/2
            // z_angle - x_angle = atan2(r10,r11)
            // WARNING.  The solution is not unique.  Choosing z_angle = 0.
            rfYAngle = -Mathx::HALF_PI;
            rfXAngle = -Mathx::ATan2(m_afEntry[3],m_afEntry[4]);
            rfZAngle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // y_angle = +pi/2
        // z_angle + x_angle = atan2(r10,r11)
        // WARNING.  The solutions is not unique.  Choosing z_angle = 0.
        rfYAngle = Mathx::HALF_PI;
        rfXAngle = Mathx::ATan2(m_afEntry[3],m_afEntry[4]);
        rfZAngle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesXZY (
    fixed& rfXAngle, fixed& rfZAngle, fixed& rfYAngle) const
{
    // +-           -+   +-                                        -+
    // | r00 r01 r02 |   |  cy*cz           -sz      cz*sy          |
    // | r10 r11 r12 | = |  sx*sy+cx*cy*sz   cx*cz  -cy*sx+cx*sy*sz |
    // | r20 r21 r22 |   | -cx*sy+cy*sx*sz   cz*sx   cx*cy+sx*sy*sz |
    // +-           -+   +-                                        -+

    if (m_afEntry[1] < FIXED_ONE)
    {
        if (m_afEntry[1] > FIXED_NEG_ONE)
        {
            // z_angle = asin(-r01)
            // x_angle = atan2(r21,r11)
            // y_angle = atan2(r02,r00)
            rfZAngle = FixedFromFloat((float)asin(-(double)FloatFromFixed(m_afEntry[1])));
            rfXAngle = Mathx::ATan2(m_afEntry[7],m_afEntry[4]);
            rfYAngle = Mathx::ATan2(m_afEntry[2],m_afEntry[0]);
            return EA_UNIQUE;
        }
        else
        {
            // z_angle = +pi/2
            // y_angle - x_angle = atan2(-r20,r22)
            // WARNING.  The solution is not unique.  Choosing y_angle = 0.
            rfZAngle = Mathx::HALF_PI;
            rfXAngle = -Mathx::ATan2(-m_afEntry[6],m_afEntry[8]);
            rfYAngle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // z_angle = -pi/2
        // y_angle + x_angle = atan2(-r20,r22)
        // WARNING.  The solution is not unique.  Choosing y_angle = 0.
        rfZAngle = -Mathx::HALF_PI;
        rfXAngle = Mathx::ATan2(-m_afEntry[6],m_afEntry[8]);
        rfYAngle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesYXZ (
    fixed& rfYAngle, fixed& rfXAngle, fixed& rfZAngle) const
{
    // +-           -+   +-                                       -+
    // | r00 r01 r02 |   |  cy*cz+sx*sy*sz  cz*sx*sy-cy*sz   cx*sy |
    // | r10 r11 r12 | = |  cx*sz           cx*cz           -sx    |
    // | r20 r21 r22 |   | -cz*sy+cy*sx*sz  cy*cz*sx+sy*sz   cx*cy |
    // +-           -+   +-                                       -+

    if (m_afEntry[5] < FIXED_ONE)
    {
        if (m_afEntry[5] > FIXED_NEG_ONE)
        {
            // x_angle = asin(-r12)
            // y_angle = atan2(r02,r22)
            // z_angle = atan2(r10,r11)
            rfXAngle = FixedFromFloat((float)asin(-(double)FloatFromFixed(m_afEntry[5])));
            rfYAngle = Mathx::ATan2(m_afEntry[2],m_afEntry[8]);
            rfZAngle = Mathx::ATan2(m_afEntry[3],m_afEntry[4]);
            return EA_UNIQUE;
        }
        else
        {
            // x_angle = +pi/2
            // z_angle - y_angle = atan2(-r01,r00)
            // WARNING.  The solution is not unique.  Choosing z_angle = 0.
            rfXAngle = Mathx::HALF_PI;
            rfYAngle = -Mathx::ATan2(-m_afEntry[1],m_afEntry[0]);
            rfZAngle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // x_angle = -pi/2
        // z_angle + y_angle = atan2(-r01,r00)
        // WARNING.  The solution is not unique.  Choosing z_angle = 0.
        rfXAngle = -Mathx::HALF_PI;
        rfYAngle = Mathx::ATan2(-m_afEntry[1],m_afEntry[0]);
        rfZAngle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesYZX (
    fixed& rfYAngle, fixed& rfZAngle, fixed& rfXAngle) const
{
    // +-           -+   +-                                       -+
    // | r00 r01 r02 |   |  cy*cz  sx*sy-cx*cy*sz   cx*sy+cy*sx*sz |
    // | r10 r11 r12 | = |  sz     cx*cz           -cz*sx          |
    // | r20 r21 r22 |   | -cz*sy  cy*sx+cx*sy*sz   cx*cy-sx*sy*sz |
    // +-           -+   +-                                       -+

    if (m_afEntry[3] < FIXED_ONE)
    {
        if (m_afEntry[3] > FIXED_NEG_ONE)
        {
            // z_angle = asin(r10)
            // y_angle = atan2(-r20,r00)
            // x_angle = atan2(-r12,r11)
            rfZAngle = FixedFromFloat((float)asin((double)FloatFromFixed(m_afEntry[3])));
            rfYAngle = Mathx::ATan2(-m_afEntry[6],m_afEntry[0]);
            rfXAngle = Mathx::ATan2(-m_afEntry[5],m_afEntry[4]);
            return EA_UNIQUE;
        }
        else
        {
            // z_angle = -pi/2
            // x_angle - y_angle = atan2(r21,r22)
            // WARNING.  The solution is not unique.  Choosing x_angle = 0.
            rfZAngle = -Mathx::HALF_PI;
            rfYAngle = -Mathx::ATan2(m_afEntry[7],m_afEntry[8]);
            rfXAngle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // z_angle = +pi/2
        // x_angle + y_angle = atan2(r21,r22)
        // WARNING.  The solution is not unique.  Choosing x_angle = 0.
        rfZAngle = Mathx::HALF_PI;
        rfYAngle = Mathx::ATan2(m_afEntry[7],m_afEntry[8]);
        rfXAngle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesZXY (
    fixed& rfZAngle, fixed& rfXAngle, fixed& rfYAngle) const
{
    // +-           -+   +-                                        -+
    // | r00 r01 r02 |   |  cy*cz-sx*sy*sz  -cx*sz   cz*sy+cy*sx*sz |
    // | r10 r11 r12 | = |  cz*sx*sy+cy*sz   cx*cz  -cy*cz*sx+sy*sz |
    // | r20 r21 r22 |   | -cx*sy            sx      cx*cy          |
    // +-           -+   +-                                        -+

    if (m_afEntry[7] < FIXED_ONE)
    {
        if (m_afEntry[7] > FIXED_NEG_ONE)
        {
            // x_angle = asin(r21)
            // z_angle = atan2(-r01,r11)
            // y_angle = atan2(-r20,r22)
            rfXAngle = FixedFromFloat((float)asin((double)FloatFromFixed(m_afEntry[7])));
            rfZAngle = Mathx::ATan2(-m_afEntry[1],m_afEntry[4]);
            rfYAngle = Mathx::ATan2(-m_afEntry[6],m_afEntry[8]);
            return EA_UNIQUE;
        }
        else
        {
            // x_angle = -pi/2
            // y_angle - z_angle = atan2(r02,r00)
            // WARNING.  The solution is not unique.  Choosing y_angle = 0.
            rfXAngle = -Mathx::HALF_PI;
            rfZAngle = -Mathx::ATan2(m_afEntry[2],m_afEntry[0]);
            rfYAngle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // x_angle = +pi/2
        // y_angle + z_angle = atan2(r02,r00)
        // WARNING.  The solution is not unique.  Choosing y_angle = 0.
        rfXAngle = Mathx::HALF_PI;
        rfZAngle = Mathx::ATan2(m_afEntry[2],m_afEntry[0]);
        rfYAngle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesZYX (
    fixed& rfZAngle, fixed& rfYAngle, fixed& rfXAngle) const
{
    // +-           -+   +-                                      -+
    // | r00 r01 r02 |   |  cy*cz  cz*sx*sy-cx*sz  cx*cz*sy+sx*sz |
    // | r10 r11 r12 | = |  cy*sz  cx*cz+sx*sy*sz -cz*sx+cx*sy*sz |
    // | r20 r21 r22 |   | -sy     cy*sx           cx*cy          |
    // +-           -+   +-                                      -+

    if (m_afEntry[6] < FIXED_ONE)
    {
        if (m_afEntry[6] > FIXED_NEG_ONE)
        {
            // y_angle = asin(-r20)
            // z_angle = atan2(r10,r00)
            // x_angle = atan2(r21,r22)
            rfYAngle = FixedFromFloat((float)asin(-(double)FloatFromFixed(m_afEntry[6])));
            rfZAngle = Mathx::ATan2(m_afEntry[3],m_afEntry[0]);
            rfXAngle = Mathx::ATan2(m_afEntry[7],m_afEntry[8]);
            return EA_UNIQUE;
        }
        else
        {
            // y_angle = +pi/2
            // x_angle - z_angle = atan2(r01,r02)
            // WARNING.  The solution is not unique.  Choosing x_angle = 0.
            rfYAngle = Mathx::HALF_PI;
            rfZAngle = -Mathx::ATan2(m_afEntry[1],m_afEntry[2]);
            rfXAngle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // y_angle = -pi/2
        // x_angle + z_angle = atan2(-r01,-r02)
        // WARNING.  The solution is not unique.  Choosing x_angle = 0;
        rfYAngle = -Mathx::HALF_PI;
        rfZAngle = Mathx::ATan2(-m_afEntry[1],-m_afEntry[2]);
        rfXAngle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesXYX (
    fixed& rfX0Angle, fixed& rfYAngle, fixed& rfX1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   |  cy      sy*sx1               sy*cx1             |
    // | r10 r11 r12 | = |  sy*sx0  cx0*cx1-cy*sx0*sx1  -cy*cx1*sx0-cx0*sx1 |
    // | r20 r21 r22 |   | -sy*cx0  cx1*sx0+cy*cx0*sx1   cy*cx0*cx1-sx0*sx1 |
    // +-           -+   +-                                                -+

    if (m_afEntry[0] < FIXED_ONE)
    {
        if (m_afEntry[0] > FIXED_NEG_ONE)
        {
            // y_angle  = acos(r00)
            // x0_angle = atan2(r10,-r20)
            // x1_angle = atan2(r01,r02)
            rfYAngle = FixedFromFloat((float)acos((double)FloatFromFixed(m_afEntry[0])));
            rfX0Angle = Mathx::ATan2(m_afEntry[3],-m_afEntry[6]);
            rfX1Angle = Mathx::ATan2(m_afEntry[1],m_afEntry[2]);
            return EA_UNIQUE;
        }
        else
        {
            // Not a unique solution:  x1_angle - x0_angle = atan2(-r12,r11)
            rfYAngle = Mathx::PI;
            rfX0Angle = -Mathx::ATan2(-m_afEntry[5],m_afEntry[4]);
            rfX1Angle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // Not a unique solution:  x1_angle + x0_angle = atan2(-r12,r11)
        rfYAngle = FIXED_ZERO;
        rfX0Angle = Mathx::ATan2(-m_afEntry[5],m_afEntry[4]);
        rfX1Angle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesXZX (
    fixed& rfX0Angle, fixed& rfZAngle, fixed& rfX1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   | cz      -sz*cx1               sz*sx1             |
    // | r10 r11 r12 | = | sz*cx0   cz*cx0*cx1-sx0*sx1  -cx1*sx0-cz*cx0*sx1 |
    // | r20 r21 r22 |   | sz*sx0   cz*cx1*sx0+cx0*sx1   cx0*cx1-cz*sx0*sx1 |
    // +-           -+   +-                                                -+

    if (m_afEntry[0] < FIXED_ONE)
    {
        if (m_afEntry[0] > FIXED_NEG_ONE)
        {
            // z_angle  = acos(r00)
            // x0_angle = atan2(r20,r10)
            // x1_angle = atan2(r02,-r01)
            rfZAngle = FixedFromFloat((float)acos((double)FloatFromFixed(m_afEntry[0])));
            rfX0Angle = Mathx::ATan2(m_afEntry[6],m_afEntry[3]);
            rfX1Angle = Mathx::ATan2(m_afEntry[2],-m_afEntry[1]);
            return EA_UNIQUE;
        }
        else
        {
            // Not a unique solution:  x1_angle - x0_angle = atan2(r21,r22)
            rfZAngle = Mathx::PI;
            rfX0Angle = -Mathx::ATan2(m_afEntry[7],m_afEntry[8]);
            rfX1Angle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // Not a unique solution:  x1_angle + x0_angle = atan2(r21,r22)
        rfZAngle = FIXED_ZERO;
        rfX0Angle = Mathx::ATan2(m_afEntry[7],m_afEntry[8]);
        rfX1Angle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesYXY (
    fixed& rfY0Angle, fixed& rfXAngle, fixed& rfY1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   |  cy0*cy1-cx*sy0*sy1  sx*sy0   cx*cy1*sy0+cy0*sy1 |
    // | r10 r11 r12 | = |  sx*sy1              cx      -sx*cy1             |
    // | r20 r21 r22 |   | -cy1*sy0-cx*cy0*sy1  sx*cy0   cx*cy0*cy1-sy0*sy1 |
    // +-           -+   +-                                                -+

    if (m_afEntry[4] < FIXED_ONE)
    {
        if (m_afEntry[4] > FIXED_NEG_ONE)
        {
            // x_angle  = acos(r11)
            // y0_angle = atan2(r01,r21)
            // y1_angle = atan2(r10,-r12)
            rfXAngle = FixedFromFloat((float)acos((double)FloatFromFixed(m_afEntry[4])));
            rfY0Angle = Mathx::ATan2(m_afEntry[1],m_afEntry[7]);
            rfY1Angle = Mathx::ATan2(m_afEntry[3],-m_afEntry[5]);
            return EA_UNIQUE;
        }
        else
        {
            // Not a unique solution:  y1_angle - y0_angle = atan2(r02,r00)
            rfXAngle = Mathx::PI;
            rfY0Angle = -Mathx::ATan2(m_afEntry[2],m_afEntry[0]);
            rfY1Angle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // Not a unique solution:  y1_angle + y0_angle = atan2(r02,r00)
        rfXAngle = FIXED_ZERO;
        rfY0Angle = Mathx::ATan2(m_afEntry[2],m_afEntry[0]);
        rfY1Angle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesYZY (
    fixed& rfY0Angle, fixed& rfZAngle, fixed& rfY1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   |  cz*cy0*cy1-sy0*sy1  -sz*cy0  cy1*sy0+cz*cy0*sy1 |
    // | r10 r11 r12 | = |  sz*cy1               cz      sz*sy1             |
    // | r20 r21 r22 |   | -cz*cy1*sy0-cy0*sy1   sz*sy0  cy0*cy1-cz*sy0*sy1 |
    // +-           -+   +-                                                -+

    if (m_afEntry[4] < FIXED_ONE)
    {
        if (m_afEntry[4] > FIXED_NEG_ONE)
        {
            // z_angle  = acos(r11)
            // y0_angle = atan2(r21,-r01)
            // y1_angle = atan2(r12,r10)
            rfZAngle = FixedFromFloat((float)acos((double)FloatFromFixed(m_afEntry[4])));
            rfY0Angle = Mathx::ATan2(m_afEntry[7],-m_afEntry[1]);
            rfY1Angle = Mathx::ATan2(m_afEntry[5],m_afEntry[3]);
            return EA_UNIQUE;
        }
        else
        {
            // Not a unique solution:  y1_angle - y0_angle = atan2(-r20,r22)
            rfZAngle = Mathx::PI;
            rfY0Angle = -Mathx::ATan2(-m_afEntry[6],m_afEntry[8]);
            rfY1Angle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // Not a unique solution:  y1_angle + y0_angle = atan2(-r20,r22)
        rfZAngle = FIXED_ZERO;
        rfY0Angle = Mathx::ATan2(-m_afEntry[6],m_afEntry[8]);
        rfY1Angle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesZXZ (
    fixed& rfZ0Angle, fixed& rfXAngle, fixed& rfZ1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   | cz0*cz1-cx*sz0*sz1  -cx*cz1*sz0-cz0*sz1   sx*sz0 |
    // | r10 r11 r12 | = | cz1*sz0+cx*cz0*sz1   cx*cz0*cz1-sz0*sz1  -sz*cz0 |
    // | r20 r21 r22 |   | sx*sz1               sx*cz1               cx     |
    // +-           -+   +-                                                -+

    if (m_afEntry[8] < FIXED_ONE)
    {
        if (m_afEntry[8] > FIXED_NEG_ONE)
        {
            // x_angle  = acos(r22)
            // z0_angle = atan2(r02,-r12)
            // z1_angle = atan2(r20,r21)
            rfXAngle = FixedFromFloat((float)acos((double)FloatFromFixed(m_afEntry[8])));
            rfZ0Angle = Mathx::ATan2(m_afEntry[2],-m_afEntry[5]);
            rfZ1Angle = Mathx::ATan2(m_afEntry[6],m_afEntry[7]);
            return EA_UNIQUE;
        }
        else
        {
            // Not a unique solution:  z1_angle - z0_angle = atan2(-r01,r00)
            rfXAngle = Mathx::PI;
            rfZ0Angle = -Mathx::ATan2(-m_afEntry[1],m_afEntry[0]);
            rfZ1Angle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else
    {
        // Not a unique solution:  z1_angle + z0_angle = atan2(-r01,r00)
        rfXAngle = FIXED_ZERO;
        rfZ0Angle = Mathx::ATan2(-m_afEntry[1],m_afEntry[0]);
        rfZ1Angle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x::EulerResult Matrix3x::ToEulerAnglesZYZ (
    fixed& rfZ0Angle, fixed& rfYAngle, fixed& rfZ1Angle) const
{
    // +-           -+   +-                                                -+
    // | r00 r01 r02 |   |  cy*cz0*cz1-sz0*sz1  -cz1*sz0-cy*cz0*sz1  sy*cz0 |
    // | r10 r11 r12 | = |  cy*cz1*sz0+cz0*sz1   cz0*cz1-cy*sz0*sz1  sy*sz0 |
    // | r20 r21 r22 |   | -sy*cz1               sy*sz1              cy     |
    // +-           -+   +-                                                -+

    if (m_afEntry[8] < FIXED_ONE)
    {
        if (m_afEntry[8] > FIXED_NEG_ONE)
        {
            // y_angle  = acos(r22)
            // z0_angle = atan2(r12,r02)
            // z1_angle = atan2(r21,-r20)
            rfYAngle = FixedFromFloat((float)acos((double)FloatFromFixed(m_afEntry[8])));
            rfZ0Angle = Mathx::ATan2(m_afEntry[5],m_afEntry[2]);
            rfZ1Angle = Mathx::ATan2(m_afEntry[7],-m_afEntry[6]);
            return EA_UNIQUE;
        }
        else // r22 = -1
        {
            // Not a unique solution:  z1_angle - z0_angle = atan2(r10,r11)
            rfYAngle = Mathx::PI;
            rfZ0Angle = -Mathx::ATan2(m_afEntry[3],m_afEntry[4]);
            rfZ1Angle = FIXED_ZERO;
            return EA_NOT_UNIQUE_DIF;
        }
    }
    else // r22 = +1
    {
        // Not a unique solution:  z1_angle + z0_angle = atan2(r10,r11)
        rfYAngle = FIXED_ZERO;
        rfZ0Angle = Mathx::ATan2(m_afEntry[3],m_afEntry[4]);
        rfZ1Angle = FIXED_ZERO;
        return EA_NOT_UNIQUE_SUM;
    }
}
//----------------------------------------------------------------------------

Matrix3x& Matrix3x::Slerp (fixed fT, const Matrix3x& rkR0,
    const Matrix3x& rkR1)
{
    Vector3x kAxis;
    fixed fAngle;
    Matrix3x kProd = rkR0.TransposeTimes(rkR1);
    kProd.ToAxisAngle(kAxis,fAngle);
    FromAxisAngle(kAxis,fT*fAngle);
    *this = rkR0*(*this);
    return *this;
}
//----------------------------------------------------------------------------

bool Matrix3x::Tridiagonalize (fixed afDiag[3], fixed afSubd[2])
{
    // Householder reduction T = Q^t M Q
    //   Input:   
    //     mat, symmetric 3x3 matrix M
    //   Output:  
    //     mat, orthogonal matrix Q (a reflection)
    //     diag, diagonal entries of T
    //     subd, subdiagonal entries of T (T is symmetric)

    fixed fM00 = m_afEntry[0];
    fixed fM01 = m_afEntry[1];
    fixed fM02 = m_afEntry[2];
    fixed fM11 = m_afEntry[4];
    fixed fM12 = m_afEntry[5];
    fixed fM22 = m_afEntry[8];

    afDiag[0] = fM00;
    if (Mathx::FAbs(fM02) >= Mathx::ZERO_TOLERANCE)
    {
        afSubd[0] = Mathx::Sqrt(fM01*fM01+fM02*fM02);
        fixed fInvLength = (FIXED_ONE)/afSubd[0];
        fM01 *= fInvLength;
        fM02 *= fInvLength;
        fixed fTmp = FixedFromFloat((float)2.0)*fM01*fM12+fM02*(fM22-fM11);
        afDiag[1] = fM11+fM02*fTmp;
        afDiag[2] = fM22-fM02*fTmp;
        afSubd[1] = fM12-fM01*fTmp;

        m_afEntry[0] = FIXED_ONE;
        m_afEntry[1] = FIXED_ZERO;
        m_afEntry[2] = FIXED_ZERO;
        m_afEntry[3] = FIXED_ZERO;
        m_afEntry[4] = fM01;
        m_afEntry[5] = fM02;
        m_afEntry[6] = FIXED_ZERO;
        m_afEntry[7] = fM02;
        m_afEntry[8] = -fM01;
        return true;
    }
    else
    {
        afDiag[1] = fM11;
        afDiag[2] = fM22;
        afSubd[0] = fM01;
        afSubd[1] = fM12;

        m_afEntry[0] = FIXED_ONE;
        m_afEntry[1] = FIXED_ZERO;
        m_afEntry[2] = FIXED_ZERO;
        m_afEntry[3] = FIXED_ZERO;
        m_afEntry[4] = FIXED_ONE;
        m_afEntry[5] = FIXED_ZERO;
        m_afEntry[6] = FIXED_ZERO;
        m_afEntry[7] = FIXED_ZERO;
        m_afEntry[8] = FIXED_ONE;
        return false;
    }
}
//----------------------------------------------------------------------------

bool Matrix3x::QLAlgorithm (fixed afDiag[3], fixed afSubd[2])
{
    // This is an implementation of the symmetric QR algorithm from the book
    // "Matrix Computations" by Gene H. Golub and Charles F. Van Loan, second
    // edition.  The algorithm is 8.2.3.  The implementation has a slight
    // variation to actually make it a QL algorithm, and it traps the case
    // when either of the subdiagonal terms s0 or s1 is zero and reduces the
    // 2-by-2 subblock directly.

    const int iMax = 32;
    for (int i = 0; i < iMax; i++)
    {
        fixed fSum, fDiff, fDiscr, fEValue0, fEValue1, fCos, fSin, fTmp;
        int iRow;

        fSum = Mathx::FAbs(afDiag[0]) + Mathx::FAbs(afDiag[1]);
        if (Mathx::FAbs(afSubd[0]) + fSum == fSum)
        {
            // The matrix is effectively
            //       +-        -+
            //   M = | d0  0  0 |
            //       | 0  d1 s1 |
            //       | 0  s1 d2 |
            //       +-        -+

            // Compute the eigenvalues as roots of a quadratic equation.
            fSum = afDiag[1] + afDiag[2];
            fDiff = afDiag[1] - afDiag[2];
            fDiscr = Mathx::Sqrt(fDiff*fDiff +
                FixedFromFloat((float)4.0)*afSubd[1]*afSubd[1]);
            fEValue0 = (FIXED_HALF)*(fSum - fDiscr);
            fEValue1 = (FIXED_HALF)*(fSum + fDiscr);

            // Compute the Givens rotation.
            if (fDiff >= FIXED_ZERO)
            {
                fCos = afSubd[1];
                fSin = afDiag[1] - fEValue0;
            }
            else
            {
                fCos = afDiag[2] - fEValue0;
                fSin = afSubd[1];
            }
            fTmp = Mathx::InvSqrt(fCos*fCos + fSin*fSin);
            fCos *= fTmp;
            fSin *= fTmp;

            // Postmultiply the current orthogonal matrix with the Givens
            // rotation.
            for (iRow = 0; iRow < 3; iRow++)
            {
                fTmp = m_afEntry[2+3*iRow];
                m_afEntry[2+3*iRow] = fSin*m_afEntry[1+3*iRow] + fCos*fTmp;
                m_afEntry[1+3*iRow] = fCos*m_afEntry[1+3*iRow] - fSin*fTmp;
            }

            // Update the tridiagonal matrix.
            afDiag[1] = fEValue0;
            afDiag[2] = fEValue1;
            afSubd[0] = FIXED_ZERO;
            afSubd[1] = FIXED_ZERO;
            return true;
        }

        fSum = Mathx::FAbs(afDiag[1]) + Mathx::FAbs(afDiag[2]);
        if (Mathx::FAbs(afSubd[1]) + fSum == fSum)
        {
            // The matrix is effectively
            //       +-         -+
            //   M = | d0  s0  0 |
            //       | s0  d1  0 |
            //       | 0   0  d2 |
            //       +-         -+

            // Compute the eigenvalues as roots of a quadratic equation.
            fSum = afDiag[0] + afDiag[1];
            fDiff = afDiag[0] - afDiag[1];
            fDiscr = Mathx::Sqrt(fDiff*fDiff +
                FixedFromFloat((float)4.0)*afSubd[0]*afSubd[0]);
            fEValue0 = (FIXED_HALF)*(fSum - fDiscr);
            fEValue1 = (FIXED_HALF)*(fSum + fDiscr);

            // Compute the Givens rotation.
            if (fDiff >= FIXED_ZERO)
            {
                fCos = afSubd[0];
                fSin = afDiag[0] - fEValue0;
            }
            else
            {
                fCos = afDiag[1] - fEValue0;
                fSin = afSubd[0];
            }
            fTmp = Mathx::InvSqrt(fCos*fCos + fSin*fSin);
            fCos *= fTmp;
            fSin *= fTmp;

            // Postmultiply the current orthogonal matrix with the Givens
            // rotation.
            for (iRow = 0; iRow < 3; iRow++)
            {
                fTmp = m_afEntry[1+3*iRow];
                m_afEntry[1+3*iRow] = fSin*m_afEntry[0+3*iRow] + fCos*fTmp;
                m_afEntry[0+3*iRow] = fCos*m_afEntry[0+3*iRow] - fSin*fTmp;
            }

            // Update the tridiagonal matrix.
            afDiag[0] = fEValue0;
            afDiag[1] = fEValue1;
            afSubd[0] = FIXED_ZERO;
            afSubd[1] = FIXED_ZERO;
            return true;
        }

        // The matrix is
        //       +-        -+
        //   M = | d0 s0  0 |
        //       | s0 d1 s1 |
        //       | 0  s1 d2 |
        //       +-        -+

        // Set up the parameters for the first pass of the QL step.  The
        // value for A is the difference between diagonal term D[2] and the
        // implicit shift suggested by Wilkinson.
        fixed fRatio = (afDiag[1]-afDiag[0])/(FixedFromFloat((float)2.0f)*afSubd[0]);
        fixed fRoot = Mathx::Sqrt(FIXED_ONE + fRatio*fRatio);
        fixed fB = afSubd[1];
        fixed fA = afDiag[2] - afDiag[0];
        if (fRatio >= FIXED_ZERO)
        {
            fA += afSubd[0]/(fRatio + fRoot);
        }
        else
        {
            fA += afSubd[0]/(fRatio - fRoot);
        }

        // Compute the Givens rotation for the first pass.
        if (Mathx::FAbs(fB) >= Mathx::FAbs(fA))
        {
            fRatio = fA/fB;
            fSin = Mathx::InvSqrt(FIXED_ONE + fRatio*fRatio);
            fCos = fRatio*fSin;
        }
        else
        {
            fRatio = fB/fA;
            fCos = Mathx::InvSqrt(FIXED_ONE + fRatio*fRatio);
            fSin = fRatio*fCos;
        }

        // Postmultiply the current orthogonal matrix with the Givens
        // rotation.
        for (iRow = 0; iRow < 3; iRow++)
        {
            fTmp = m_afEntry[2+3*iRow];
            m_afEntry[2+3*iRow] = fSin*m_afEntry[1+3*iRow]+fCos*fTmp;
            m_afEntry[1+3*iRow] = fCos*m_afEntry[1+3*iRow]-fSin*fTmp;
        }

        // Set up the parameters for the second pass of the QL step.  The
        // values tmp0 and tmp1 are required to fully update the tridiagonal
        // matrix at the end of the second pass.
        fixed fTmp0 = (afDiag[1] - afDiag[2])*fSin +
            FixedFromFloat((float)2.0)*afSubd[1]*fCos;
        fixed fTmp1 = fCos*afSubd[0];
        fB = fSin*afSubd[0];
        fA = fCos*fTmp0 - afSubd[1];
        fTmp0 *= fSin;

        // Compute the Givens rotation for the second pass.  The subdiagonal
        // term S[1] in the tridiagonal matrix is updated at this time.
        if (Mathx::FAbs(fB) >= Mathx::FAbs(fA))
        {
            fRatio = fA/fB;
            fRoot = Mathx::Sqrt(FIXED_ONE + fRatio*fRatio);
            afSubd[1] = fB*fRoot;
            fSin = (FIXED_ONE)/fRoot;
            fCos = fRatio*fSin;
        }
        else
        {
            fRatio = fB/fA;
            fRoot = Mathx::Sqrt(FIXED_ONE + fRatio*fRatio);
            afSubd[1] = fA*fRoot;
            fCos = (FIXED_ONE)/fRoot;
            fSin = fRatio*fCos;
        }

        // Postmultiply the current orthogonal matrix with the Givens
        // rotation.
        for (iRow = 0; iRow < 3; iRow++)
        {
            fTmp = m_afEntry[1+3*iRow];
            m_afEntry[1+3*iRow] = fSin*m_afEntry[0+3*iRow]+fCos*fTmp;
            m_afEntry[0+3*iRow] = fCos*m_afEntry[0+3*iRow]-fSin*fTmp;
        }

        // Complete the update of the tridiagonal matrix.
        fixed fTmp2 = afDiag[1] - fTmp0;
        afDiag[2] += fTmp0;
        fTmp0 = (afDiag[0] - fTmp2)*fSin + FixedFromFloat((float)2.0)*fTmp1*fCos;
        afSubd[0] = fCos*fTmp0 - fTmp1;
        fTmp0 *= fSin;
        afDiag[1] = fTmp2 + fTmp0;
        afDiag[0] -= fTmp0;
    }
    return false;
}
//----------------------------------------------------------------------------

void Matrix3x::Bidiagonalize (Matrix3x& rkA, Matrix3x& rkL, Matrix3x& rkR)
{
    fixed afV[3], afW[3];
    fixed fLength, fSign, fT1, fInvT1, fT2;
    bool bIdentity;

    // map first column to (*,0,0)
    fLength = Mathx::Sqrt(rkA[0][0]*rkA[0][0] + rkA[1][0]*rkA[1][0] +
        rkA[2][0]*rkA[2][0]);
    if (fLength > FIXED_ZERO)
    {
        fSign = (rkA[0][0] > FIXED_ZERO ? FIXED_ONE : FIXED_NEG_ONE);
        fT1 = rkA[0][0] + fSign*fLength;
        fInvT1 = (FIXED_ONE)/fT1;
        afV[1] = rkA[1][0]*fInvT1;
        afV[2] = rkA[2][0]*fInvT1;

        fT2 = -((fixed)2.0)/((FIXED_ONE)+afV[1]*afV[1]+afV[2]*afV[2]);
        afW[0] = fT2*(rkA[0][0]+rkA[1][0]*afV[1]+rkA[2][0]*afV[2]);
        afW[1] = fT2*(rkA[0][1]+rkA[1][1]*afV[1]+rkA[2][1]*afV[2]);
        afW[2] = fT2*(rkA[0][2]+rkA[1][2]*afV[1]+rkA[2][2]*afV[2]);
        rkA[0][0] += afW[0];
        rkA[0][1] += afW[1];
        rkA[0][2] += afW[2];
        rkA[1][1] += afV[1]*afW[1];
        rkA[1][2] += afV[1]*afW[2];
        rkA[2][1] += afV[2]*afW[1];
        rkA[2][2] += afV[2]*afW[2];

        rkL[0][0] = (FIXED_ONE)+fT2;
        rkL[0][1] = fT2*afV[1];
        rkL[1][0] = rkL[0][1];
        rkL[0][2] = fT2*afV[2];
        rkL[2][0] = rkL[0][2];
        rkL[1][1] = (FIXED_ONE)+fT2*afV[1]*afV[1];
        rkL[1][2] = fT2*afV[1]*afV[2];
        rkL[2][1] = rkL[1][2];
        rkL[2][2] = (FIXED_ONE)+fT2*afV[2]*afV[2];
        bIdentity = false;
    }
    else
    {
        rkL = Matrix3x::IDENTITY;
        bIdentity = true;
    }

    // map first row to (*,*,0)
    fLength = Mathx::Sqrt(rkA[0][1]*rkA[0][1]+rkA[0][2]*rkA[0][2]);
    if (fLength > FIXED_ZERO)
    {
        fSign = (rkA[0][1] > FIXED_ZERO ? FIXED_ONE : FIXED_NEG_ONE);
        fT1 = rkA[0][1] + fSign*fLength;
        afV[2] = rkA[0][2]/fT1;

        fT2 = -FixedFromFloat((float)2.0)/((FIXED_ONE)+afV[2]*afV[2]);
        afW[0] = fT2*(rkA[0][1]+rkA[0][2]*afV[2]);
        afW[1] = fT2*(rkA[1][1]+rkA[1][2]*afV[2]);
        afW[2] = fT2*(rkA[2][1]+rkA[2][2]*afV[2]);
        rkA[0][1] += afW[0];
        rkA[1][1] += afW[1];
        rkA[1][2] += afW[1]*afV[2];
        rkA[2][1] += afW[2];
        rkA[2][2] += afW[2]*afV[2];
        
        rkR[0][0] = FIXED_ONE;
        rkR[0][1] = FIXED_ZERO;
        rkR[1][0] = FIXED_ZERO;
        rkR[0][2] = FIXED_ZERO;
        rkR[2][0] = FIXED_ZERO;
        rkR[1][1] = (FIXED_ONE)+fT2;
        rkR[1][2] = fT2*afV[2];
        rkR[2][1] = rkR[1][2];
        rkR[2][2] = (FIXED_ONE)+fT2*afV[2]*afV[2];
    }
    else
    {
        rkR = Matrix3x::IDENTITY;
    }

    // map second column to (*,*,0)
    fLength = Mathx::Sqrt(rkA[1][1]*rkA[1][1]+rkA[2][1]*rkA[2][1]);
    if (fLength > FIXED_ZERO)
    {
        fSign = (rkA[1][1] > FIXED_ZERO ? FIXED_ONE : FIXED_NEG_ONE);
        fT1 = rkA[1][1] + fSign*fLength;
        afV[2] = rkA[2][1]/fT1;

        fT2 = -FixedFromFloat((float)2.0)/((FIXED_ONE)+afV[2]*afV[2]);
        afW[1] = fT2*(rkA[1][1]+rkA[2][1]*afV[2]);
        afW[2] = fT2*(rkA[1][2]+rkA[2][2]*afV[2]);
        rkA[1][1] += afW[1];
        rkA[1][2] += afW[2];
        rkA[2][2] += afV[2]*afW[2];

        fixed fA = (FIXED_ONE)+fT2;
        fixed fB = fT2*afV[2];
        fixed fC = (FIXED_ONE)+fB*afV[2];

        if (bIdentity)
        {
            rkL[0][0] = FIXED_ONE;
            rkL[0][1] = FIXED_ZERO;
            rkL[1][0] = FIXED_ZERO;
            rkL[0][2] = FIXED_ZERO;
            rkL[2][0] = FIXED_ZERO;
            rkL[1][1] = fA;
            rkL[1][2] = fB;
            rkL[2][1] = fB;
            rkL[2][2] = fC;
        }
        else
        {
            for (int iRow = 0; iRow < 3; iRow++)
            {
                fixed fTmp0 = rkL[iRow][1];
                fixed fTmp1 = rkL[iRow][2];
                rkL[iRow][1] = fA*fTmp0+fB*fTmp1;
                rkL[iRow][2] = fB*fTmp0+fC*fTmp1;
            }
        }
    }
}
//----------------------------------------------------------------------------

void Matrix3x::GolubKahanStep (Matrix3x& rkA, Matrix3x& rkL, Matrix3x& rkR)
{
    fixed fT11 = rkA[0][1]*rkA[0][1]+rkA[1][1]*rkA[1][1];
    fixed fT22 = rkA[1][2]*rkA[1][2]+rkA[2][2]*rkA[2][2];
    fixed fT12 = rkA[1][1]*rkA[1][2];
    fixed fTrace = fT11+fT22;
    fixed fDiff = fT11-fT22;
    fixed fDiscr = Mathx::Sqrt(fDiff*fDiff+FixedFromFloat((float)4.0)*fT12*fT12);
    fixed fRoot1 = (FIXED_HALF)*(fTrace+fDiscr);
    fixed fRoot2 = (FIXED_HALF)*(fTrace-fDiscr);

    // adjust right
    fixed fY = rkA[0][0] - (Mathx::FAbs(fRoot1-fT22) <=
        Mathx::FAbs(fRoot2-fT22) ? fRoot1 : fRoot2);
    fixed fZ = rkA[0][1];
    fixed fInvLength = Mathx::InvSqrt(fY*fY+fZ*fZ);
    fixed fSin = fZ*fInvLength;
    fixed fCos = -fY*fInvLength;

    fixed fTmp0 = rkA[0][0];
    fixed fTmp1 = rkA[0][1];
    rkA[0][0] = fCos*fTmp0-fSin*fTmp1;
    rkA[0][1] = fSin*fTmp0+fCos*fTmp1;
    rkA[1][0] = -fSin*rkA[1][1];
    rkA[1][1] *= fCos;

    int iRow;
    for (iRow = 0; iRow < 3; iRow++)
    {
        fTmp0 = rkR[0][iRow];
        fTmp1 = rkR[1][iRow];
        rkR[0][iRow] = fCos*fTmp0-fSin*fTmp1;
        rkR[1][iRow] = fSin*fTmp0+fCos*fTmp1;
    }

    // adjust left
    fY = rkA[0][0];
    fZ = rkA[1][0];
    fInvLength = Mathx::InvSqrt(fY*fY+fZ*fZ);
    fSin = fZ*fInvLength;
    fCos = -fY*fInvLength;

    rkA[0][0] = fCos*rkA[0][0]-fSin*rkA[1][0];
    fTmp0 = rkA[0][1];
    fTmp1 = rkA[1][1];
    rkA[0][1] = fCos*fTmp0-fSin*fTmp1;
    rkA[1][1] = fSin*fTmp0+fCos*fTmp1;
    rkA[0][2] = -fSin*rkA[1][2];
    rkA[1][2] *= fCos;

    int iCol;
    for (iCol = 0; iCol < 3; iCol++)
    {
        fTmp0 = rkL[iCol][0];
        fTmp1 = rkL[iCol][1];
        rkL[iCol][0] = fCos*fTmp0-fSin*fTmp1;
        rkL[iCol][1] = fSin*fTmp0+fCos*fTmp1;
    }

    // adjust right
    fY = rkA[0][1];
    fZ = rkA[0][2];
    fInvLength = Mathx::InvSqrt(fY*fY+fZ*fZ);
    fSin = fZ*fInvLength;
    fCos = -fY*fInvLength;

    rkA[0][1] = fCos*rkA[0][1]-fSin*rkA[0][2];
    fTmp0 = rkA[1][1];
    fTmp1 = rkA[1][2];
    rkA[1][1] = fCos*fTmp0-fSin*fTmp1;
    rkA[1][2] = fSin*fTmp0+fCos*fTmp1;
    rkA[2][1] = -fSin*rkA[2][2];
    rkA[2][2] *= fCos;

    for (iRow = 0; iRow < 3; iRow++)
    {
        fTmp0 = rkR[1][iRow];
        fTmp1 = rkR[2][iRow];
        rkR[1][iRow] = fCos*fTmp0-fSin*fTmp1;
        rkR[2][iRow] = fSin*fTmp0+fCos*fTmp1;
    }

    // adjust left
    fY = rkA[1][1];
    fZ = rkA[2][1];
    fInvLength = Mathx::InvSqrt(fY*fY+fZ*fZ);
    fSin = fZ*fInvLength;
    fCos = -fY*fInvLength;

    rkA[1][1] = fCos*rkA[1][1]-fSin*rkA[2][1];
    fTmp0 = rkA[1][2];
    fTmp1 = rkA[2][2];
    rkA[1][2] = fCos*fTmp0-fSin*fTmp1;
    rkA[2][2] = fSin*fTmp0+fCos*fTmp1;

    for (iCol = 0; iCol < 3; iCol++)
    {
        fTmp0 = rkL[iCol][1];
        fTmp1 = rkL[iCol][2];
        rkL[iCol][1] = fCos*fTmp0-fSin*fTmp1;
        rkL[iCol][2] = fSin*fTmp0+fCos*fTmp1;
    }
}
//----------------------------------------------------------------------------

void Matrix3x::SingularValueDecomposition (Matrix3x& rkL, Matrix3x& rkD,
    Matrix3x& rkRTranspose) const
{
    int iRow, iCol;

    Matrix3x kA = *this;
    Bidiagonalize(kA,rkL,rkRTranspose);
    rkD.MakeZero();

    const int iMax = 32;
    const fixed fEpsilon = FixedFromFloat((float)1e-04);
    for (int i = 0; i < iMax; i++)
    {
        fixed fTmp, fTmp0, fTmp1;
        fixed fSin0, fCos0, fTan0;
        fixed fSin1, fCos1, fTan1;

        bool bTest1 = (Mathx::FAbs(kA[0][1]) <=
            fEpsilon*(Mathx::FAbs(kA[0][0]) +
            Mathx::FAbs(kA[1][1])));
        bool bTest2 = (Mathx::FAbs(kA[1][2]) <=
            fEpsilon*(Mathx::FAbs(kA[1][1]) +
            Mathx::FAbs(kA[2][2])));
        if (bTest1)
        {
            if (bTest2)
            {
                rkD[0][0] = kA[0][0];
                rkD[1][1] = kA[1][1];
                rkD[2][2] = kA[2][2];
                break;
            }
            else
            {
                // 2x2 closed form factorization
                fTmp = (kA[1][1]*kA[1][1] - kA[2][2]*kA[2][2] +
                    kA[1][2]*kA[1][2])/(kA[1][2]*kA[2][2]);
                fTan0 = (FIXED_HALF)*(fTmp + Mathx::Sqrt(fTmp*fTmp +
                    FixedFromFloat((float)4.0)));
                fCos0 = Mathx::InvSqrt((FIXED_ONE)+fTan0*fTan0);
                fSin0 = fTan0*fCos0;

                for (iCol = 0; iCol < 3; iCol++)
                {
                    fTmp0 = rkL[iCol][1];
                    fTmp1 = rkL[iCol][2];
                    rkL[iCol][1] = fCos0*fTmp0-fSin0*fTmp1;
                    rkL[iCol][2] = fSin0*fTmp0+fCos0*fTmp1;
                }
                
                fTan1 = (kA[1][2]-kA[2][2]*fTan0)/kA[1][1];
                fCos1 = Mathx::InvSqrt((FIXED_ONE)+fTan1*fTan1);
                fSin1 = -fTan1*fCos1;

                for (iRow = 0; iRow < 3; iRow++)
                {
                    fTmp0 = rkRTranspose[1][iRow];
                    fTmp1 = rkRTranspose[2][iRow];
                    rkRTranspose[1][iRow] = fCos1*fTmp0-fSin1*fTmp1;
                    rkRTranspose[2][iRow] = fSin1*fTmp0+fCos1*fTmp1;
                }

                rkD[0][0] = kA[0][0];
                rkD[1][1] = fCos0*fCos1*kA[1][1] -
                    fSin1*(fCos0*kA[1][2]-fSin0*kA[2][2]);
                rkD[2][2] = fSin0*fSin1*kA[1][1] +
                    fCos1*(fSin0*kA[1][2]+fCos0*kA[2][2]);
                break;
            }
        }
        else 
        {
            if (bTest2)
            {
                // 2x2 closed form factorization 
                fTmp = (kA[0][0]*kA[0][0] + kA[1][1]*kA[1][1] -
                    kA[0][1]*kA[0][1])/(kA[0][1]*kA[1][1]);
                fTan0 = (FIXED_HALF)*(-fTmp + Mathx::Sqrt(fTmp*fTmp +
                    FixedFromFloat((float)4.0)));
                fCos0 = Mathx::InvSqrt((FIXED_ONE)+fTan0*fTan0);
                fSin0 = fTan0*fCos0;

                for (iCol = 0; iCol < 3; iCol++)
                {
                    fTmp0 = rkL[iCol][0];
                    fTmp1 = rkL[iCol][1];
                    rkL[iCol][0] = fCos0*fTmp0-fSin0*fTmp1;
                    rkL[iCol][1] = fSin0*fTmp0+fCos0*fTmp1;
                }
                
                fTan1 = (kA[0][1]-kA[1][1]*fTan0)/kA[0][0];
                fCos1 = Mathx::InvSqrt((FIXED_ONE)+fTan1*fTan1);
                fSin1 = -fTan1*fCos1;

                for (iRow = 0; iRow < 3; iRow++)
                {
                    fTmp0 = rkRTranspose[0][iRow];
                    fTmp1 = rkRTranspose[1][iRow];
                    rkRTranspose[0][iRow] = fCos1*fTmp0-fSin1*fTmp1;
                    rkRTranspose[1][iRow] = fSin1*fTmp0+fCos1*fTmp1;
                }

                rkD[0][0] = fCos0*fCos1*kA[0][0] -
                    fSin1*(fCos0*kA[0][1]-fSin0*kA[1][1]);
                rkD[1][1] = fSin0*fSin1*kA[0][0] +
                    fCos1*(fSin0*kA[0][1]+fCos0*kA[1][1]);
                rkD[2][2] = kA[2][2];
                break;
            }
            else
            {
                GolubKahanStep(kA,rkL,rkRTranspose);
            }
        }
    }

    // Make the diagonal entries positive.
    for (iRow = 0; iRow < 3; iRow++)
    {
        if (rkD[iRow][iRow] < FIXED_ZERO)
        {
            rkD[iRow][iRow] = -rkD[iRow][iRow];
            for (iCol = 0; iCol < 3; iCol++)
            {
                rkRTranspose[iRow][iCol] = -rkRTranspose[iRow][iCol];
            }
        }
    }
}
//----------------------------------------------------------------------------

void Matrix3x::SingularValueComposition (const Matrix3x& rkL,
    const Matrix3x& rkD, const Matrix3x& rkRTranspose)
{
    *this = rkL*(rkD*rkRTranspose);
}
//----------------------------------------------------------------------------

void Matrix3x::PolarDecomposition (Matrix3x& rkQ, Matrix3x& rkS)
{
    // Decompose M = L*D*R^T.
    Matrix3x kL, kD, kRTranspose;
    SingularValueDecomposition(kL,kD,kRTranspose);

    // Compute Q = L*R^T.
    rkQ = kL*kRTranspose;

    // Compute S = R*D*R^T.
    rkS = kRTranspose.TransposeTimes(kD*kRTranspose);

    // Numerical round-off errors can cause S not to be symmetric in the
    // sense that S[i][j] and S[j][i] are slightly different for i != j.
    // Correct this by averaging S and Transpose(S).
    rkS[0][1] = (FIXED_HALF)*(rkS[0][1] + rkS[1][0]);
    rkS[1][0] = rkS[0][1];
    rkS[0][2] = (FIXED_HALF)*(rkS[0][2] + rkS[2][0]);
    rkS[2][0] = rkS[0][2];
    rkS[1][2] = (FIXED_HALF)*(rkS[1][2] + rkS[2][1]);
    rkS[2][1] = rkS[1][2];
}
//----------------------------------------------------------------------------

void Matrix3x::QDUDecomposition (Matrix3x& rkQ, Matrix3x& rkD,
    Matrix3x& rkU) const
{
    // Factor M = QR = QDU where Q is orthogonal (rotation), D is diagonal
    // (scaling),  and U is upper triangular with ones on its diagonal
    // (shear).  Algorithm uses Gram-Schmidt orthogonalization (the QR
    // algorithm).
    //
    // If M = [ m0 | m1 | m2 ] and Q = [ q0 | q1 | q2 ], then
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.  The matrix R has entries
    //
    //   r00 = q0*m0  r01 = q0*m1  r02 = q0*m2
    //   r10 = 0      r11 = q1*m1  r12 = q1*m2
    //   r20 = 0      r21 = 0      r22 = q2*m2
    //
    // so D = diag(r00,r11,r22) and U has entries u01 = r01/r00,
    // u02 = r02/r00, and u12 = r12/r11.

    // build orthogonal matrix Q
    fixed fInvLength = Mathx::InvSqrt(m_afEntry[0]*m_afEntry[0] +
        m_afEntry[3]*m_afEntry[3] + m_afEntry[6]*m_afEntry[6]);
    rkQ[0][0] = m_afEntry[0]*fInvLength;
    rkQ[1][0] = m_afEntry[3]*fInvLength;
    rkQ[2][0] = m_afEntry[6]*fInvLength;

    fixed fDot = rkQ[0][0]*m_afEntry[1] + rkQ[1][0]*m_afEntry[4] +
        rkQ[2][0]*m_afEntry[7];
    rkQ[0][1] = m_afEntry[1]-fDot*rkQ[0][0];
    rkQ[1][1] = m_afEntry[4]-fDot*rkQ[1][0];
    rkQ[2][1] = m_afEntry[7]-fDot*rkQ[2][0];
    fInvLength = Mathx::InvSqrt(rkQ[0][1]*rkQ[0][1] +
        rkQ[1][1]*rkQ[1][1] + rkQ[2][1]*rkQ[2][1]);
    rkQ[0][1] *= fInvLength;
    rkQ[1][1] *= fInvLength;
    rkQ[2][1] *= fInvLength;

    fDot = rkQ[0][0]*m_afEntry[2] + rkQ[1][0]*m_afEntry[5] +
        rkQ[2][0]*m_afEntry[8];
    rkQ[0][2] = m_afEntry[2]-fDot*rkQ[0][0];
    rkQ[1][2] = m_afEntry[5]-fDot*rkQ[1][0];
    rkQ[2][2] = m_afEntry[8]-fDot*rkQ[2][0];
    fDot = rkQ[0][1]*m_afEntry[2] + rkQ[1][1]*m_afEntry[5] +
        rkQ[2][1]*m_afEntry[8];
    rkQ[0][2] -= fDot*rkQ[0][1];
    rkQ[1][2] -= fDot*rkQ[1][1];
    rkQ[2][2] -= fDot*rkQ[2][1];
    fInvLength = Mathx::InvSqrt(rkQ[0][2]*rkQ[0][2] +
        rkQ[1][2]*rkQ[1][2] + rkQ[2][2]*rkQ[2][2]);
    rkQ[0][2] *= fInvLength;
    rkQ[1][2] *= fInvLength;
    rkQ[2][2] *= fInvLength;

    // guarantee that orthogonal matrix has determinant 1 (no reflections)
    fixed fDet = rkQ[0][0]*rkQ[1][1]*rkQ[2][2] + rkQ[0][1]*rkQ[1][2]*rkQ[2][0]
        +  rkQ[0][2]*rkQ[1][0]*rkQ[2][1] - rkQ[0][2]*rkQ[1][1]*rkQ[2][0]
        -  rkQ[0][1]*rkQ[1][0]*rkQ[2][2] - rkQ[0][0]*rkQ[1][2]*rkQ[2][1];

    if (fDet < FIXED_ZERO)
    {
        for (int iRow = 0; iRow < 3; iRow++)
        {
            for (int iCol = 0; iCol < 3; iCol++)
            {
                rkQ[iRow][iCol] = -rkQ[iRow][iCol];
            }
        }
    }

    // build "right" matrix R
    Matrix3x kR;
    kR[0][0] = rkQ[0][0]*m_afEntry[0] + rkQ[1][0]*m_afEntry[3] +
        rkQ[2][0]*m_afEntry[6];
    kR[0][1] = rkQ[0][0]*m_afEntry[1] + rkQ[1][0]*m_afEntry[4] +
        rkQ[2][0]*m_afEntry[7];
    kR[1][1] = rkQ[0][1]*m_afEntry[1] + rkQ[1][1]*m_afEntry[4] +
        rkQ[2][1]*m_afEntry[7];
    kR[0][2] = rkQ[0][0]*m_afEntry[2] + rkQ[1][0]*m_afEntry[5] +
        rkQ[2][0]*m_afEntry[8];
    kR[1][2] = rkQ[0][1]*m_afEntry[2] + rkQ[1][1]*m_afEntry[5] +
        rkQ[2][1]*m_afEntry[8];
    kR[2][2] = rkQ[0][2]*m_afEntry[2] + rkQ[1][2]*m_afEntry[5] +
        rkQ[2][2]*m_afEntry[8];

    // the scaling component
    rkD.MakeDiagonal(kR[0][0],kR[1][1],kR[2][2]);

    // the shear component
    fixed fInvD0 = (FIXED_ONE)/rkD[0][0];
    rkU[0][0] = FIXED_ONE;
    rkU[0][1] = kR[0][1]*fInvD0;
    rkU[0][2] = kR[0][2]*fInvD0;
    rkU[1][0] = FIXED_ZERO;
    rkU[1][1] = FIXED_ONE;
    rkU[1][2] = kR[1][2]/rkD[1][1];
    rkU[2][0] = FIXED_ZERO;
    rkU[2][1] = FIXED_ZERO;
    rkU[2][2] = FIXED_ONE;
}
//----------------------------------------------------------------------------

}