///////////////////////////////////////////////////////////
//                                                       //
//                    WgVector4.cpp                      //
//                                                       //
//  - Implementation for Vector4 class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgVector4.h"
namespace WGSoft3D
{
template<> const Vector4<float> Vector4<float>::ZERO(0.0f,0.0f,0.0f,0.0f);
template<> const Vector4<float> Vector4<float>::UNIT_X(1.0f,0.0f,0.0f,0.0f);
template<> const Vector4<float> Vector4<float>::UNIT_Y(0.0f,1.0f,0.0f,0.0f);
template<> const Vector4<float> Vector4<float>::UNIT_Z(0.0f,0.0f,1.0f,0.0f);
template<> const Vector4<float> Vector4<float>::UNIT_W(0.0f,0.0f,0.0f,1.0f);
template<> const Vector4<float> Vector4<float>::ONE(1.0f,1.0f,1.0f,1.0f);

template<> const Vector4<double> Vector4<double>::ZERO(0.0,0.0,0.0,0.0);
template<> const Vector4<double> Vector4<double>::UNIT_X(1.0,0.0,0.0,0.0);
template<> const Vector4<double> Vector4<double>::UNIT_Y(0.0,1.0,0.0,0.0);
template<> const Vector4<double> Vector4<double>::UNIT_Z(0.0,0.0,1.0,0.0);
template<> const Vector4<double> Vector4<double>::UNIT_W(0.0,0.0,0.0,1.0);
template<> const Vector4<double> Vector4<double>::ONE(1.0,1.0,1.0,1.0);

const Vector4x Vector4x::ZERO(fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO));
const Vector4x Vector4x::UNIT_X(fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO));
const Vector4x Vector4x::UNIT_Y(fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO));
const Vector4x Vector4x::UNIT_Z(fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO));
const Vector4x Vector4x::UNIT_W(fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE));
const Vector4x Vector4x::ONE(fixed(FIXED_ONE),fixed(FIXED_ONE),fixed(FIXED_ONE),fixed(FIXED_ONE));


//----------------------------------------------------------------------------
//
// Fixed Vector 4 Implementation
//
//----------------------------------------------------------------------------
Vector4x::Vector4x ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------

Vector4x::Vector4x (fixed fX, fixed fY, fixed fZ, fixed fW)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
    m_afTuple[3] = fW;
}
//----------------------------------------------------------------------------

Vector4x::Vector4x (const fixed* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
    m_afTuple[2] = afTuple[2];
    m_afTuple[3] = afTuple[3];
}
//----------------------------------------------------------------------------

Vector4x::Vector4x (const Vector4x& rkV)
{
    m_afTuple[0] = rkV.m_afTuple[0];
    m_afTuple[1] = rkV.m_afTuple[1];
    m_afTuple[2] = rkV.m_afTuple[2];
    m_afTuple[3] = rkV.m_afTuple[3];
}
//----------------------------------------------------------------------------

int Vector4x::CompareArrays (const Vector4x& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,4*sizeof(fixed));
}
//----------------------------------------------------------------------------

bool Vector4x::operator== (const Vector4x& rkV) const
{
    return CompareArrays(rkV) == 0;
}
//----------------------------------------------------------------------------

bool Vector4x::operator!= (const Vector4x& rkV) const
{
    return CompareArrays(rkV) != 0;
}
//----------------------------------------------------------------------------

bool Vector4x::operator< (const Vector4x& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------

bool Vector4x::operator<= (const Vector4x& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------

bool Vector4x::operator> (const Vector4x& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------

bool Vector4x::operator>= (const Vector4x& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------
#ifndef _WIN32_WCE
std::ostream& operator<< (std::ostream& rkOStr, const Vector4x& rkV)
{
	return rkOStr << FloatFromFixed(rkV.X()) << ' ' << FloatFromFixed(rkV.Y()) << ' ' << FloatFromFixed(rkV.Z())
		<< ' ' << FloatFromFixed(rkV.W());
}
#endif //_WIN32_WCE
}