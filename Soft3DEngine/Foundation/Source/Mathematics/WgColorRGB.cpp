///////////////////////////////////////////////////////////
//                                                       //
//                    WgColorRGB.cpp                     //
//                                                       //
//  - Implementation for Color RGB class                 //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgColorRGB.h"

namespace WGSoft3D
{

const ColorRGB ColorRGB::BLACK(fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO));
const ColorRGB ColorRGB::WHITE(fixed(FIXED_ONE),fixed(FIXED_ONE),fixed(FIXED_ONE));
const ColorRGB ColorRGB::INVALID(fixed(FIXED_NEG_ONE),fixed(FIXED_NEG_ONE),fixed(FIXED_NEG_ONE));

//----------------------------------------------------------------------------
ColorRGB::ColorRGB ()
{
    m_afTuple[0] = 0;
    m_afTuple[1] = 0;
    m_afTuple[2] = 0;
}
//----------------------------------------------------------------------------
ColorRGB::ColorRGB (fixed fR, fixed fG, fixed fB)
{
    m_afTuple[0] = fR;
    m_afTuple[1] = fG;
    m_afTuple[2] = fB;
}
//----------------------------------------------------------------------------
ColorRGB::ColorRGB (const fixed* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
    m_afTuple[2] = afTuple[2];
}
//----------------------------------------------------------------------------
ColorRGB::ColorRGB (const ColorRGB& rkC)
{
    m_afTuple[0] = rkC.m_afTuple[0];
    m_afTuple[1] = rkC.m_afTuple[1];
    m_afTuple[2] = rkC.m_afTuple[2];
}
//----------------------------------------------------------------------------
ColorRGB& ColorRGB::operator= (const ColorRGB& rkC)
{
    m_afTuple[0] = rkC.m_afTuple[0];
    m_afTuple[1] = rkC.m_afTuple[1];
    m_afTuple[2] = rkC.m_afTuple[2];
    return *this;
}
//----------------------------------------------------------------------------
bool ColorRGB::operator== (const ColorRGB& rkC) const
{
    return
        m_afTuple[0] == rkC.m_afTuple[0] &&
        m_afTuple[1] == rkC.m_afTuple[1] &&
        m_afTuple[2] == rkC.m_afTuple[2];
}
//----------------------------------------------------------------------------
bool ColorRGB::operator!= (const ColorRGB& rkC) const
{
    return
        m_afTuple[0] != rkC.m_afTuple[0] ||
        m_afTuple[1] != rkC.m_afTuple[1] ||
        m_afTuple[2] != rkC.m_afTuple[2];
}
//----------------------------------------------------------------------------
int ColorRGB::CompareArrays (const ColorRGB& rkC) const
{
    return memcmp(m_afTuple,rkC.m_afTuple,3*sizeof(fixed));
}
//----------------------------------------------------------------------------
bool ColorRGB::operator< (const ColorRGB& rkC) const
{
    return CompareArrays(rkC) < 0;
}
//----------------------------------------------------------------------------
bool ColorRGB::operator<= (const ColorRGB& rkC) const
{
    return CompareArrays(rkC) <= 0;
}
//----------------------------------------------------------------------------
bool ColorRGB::operator> (const ColorRGB& rkC) const
{
    return CompareArrays(rkC) > 0;
}
//----------------------------------------------------------------------------
bool ColorRGB::operator>= (const ColorRGB& rkC) const
{
    return CompareArrays(rkC) >= 0;
}
//----------------------------------------------------------------------------
ColorRGB ColorRGB::operator+ (const ColorRGB& rkC) const
{
    return ColorRGB(
        m_afTuple[0] + rkC.m_afTuple[0],
        m_afTuple[1] + rkC.m_afTuple[1],
        m_afTuple[2] + rkC.m_afTuple[2]);
}
//----------------------------------------------------------------------------
ColorRGB ColorRGB::operator- (const ColorRGB& rkC) const
{
    return ColorRGB(
        m_afTuple[0] - rkC.m_afTuple[0],
        m_afTuple[1] - rkC.m_afTuple[1],
        m_afTuple[2] - rkC.m_afTuple[2]);
}
//----------------------------------------------------------------------------
ColorRGB ColorRGB::operator* (const ColorRGB& rkC) const
{
    return ColorRGB(
        m_afTuple[0]*rkC.m_afTuple[0],
        m_afTuple[1]*rkC.m_afTuple[1],
        m_afTuple[2]*rkC.m_afTuple[2]);
}
//----------------------------------------------------------------------------
ColorRGB ColorRGB::operator* (fixed fScalar) const
{
    return ColorRGB(
        fScalar*m_afTuple[0],
        fScalar*m_afTuple[1],
        fScalar*m_afTuple[2]);
}
//----------------------------------------------------------------------------
ColorRGB operator* (fixed fScalar, const ColorRGB& rkC)
{
    return ColorRGB(fScalar*rkC[0],fScalar*rkC[1],fScalar*rkC[2]);
}
//----------------------------------------------------------------------------
ColorRGB& ColorRGB::operator+= (const ColorRGB& rkC)
{
    m_afTuple[0] += rkC.m_afTuple[0];
    m_afTuple[1] += rkC.m_afTuple[1];
    m_afTuple[2] += rkC.m_afTuple[2];
    return *this;
}
//----------------------------------------------------------------------------
ColorRGB& ColorRGB::operator-= (const ColorRGB& rkC)
{
    m_afTuple[0] -= rkC.m_afTuple[0];
    m_afTuple[1] -= rkC.m_afTuple[1];
    m_afTuple[2] -= rkC.m_afTuple[2];
    return *this;
}
//----------------------------------------------------------------------------
ColorRGB& ColorRGB::operator*= (const ColorRGB& rkC)
{
    m_afTuple[0] *= rkC.m_afTuple[0];
    m_afTuple[1] *= rkC.m_afTuple[1];
    m_afTuple[2] *= rkC.m_afTuple[2];
    return *this;
}
//----------------------------------------------------------------------------
ColorRGB& ColorRGB::operator*= (fixed fScalar)
{
	m_afTuple[0] *= fScalar;
    m_afTuple[1] *= fScalar;
    m_afTuple[2] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
void ColorRGB::Clamp ()
{
    for (int i = 0; i < 3; i++)
    {
        if (m_afTuple[i] > FIXED_ONE)
        {
            m_afTuple[i] = FIXED_ONE;
        }
        else if (m_afTuple[i] < FIXED_ZERO)
        {
            m_afTuple[i] = FIXED_ZERO;
        }
    }
}
//----------------------------------------------------------------------------
void ColorRGB::ScaleByMax ()
{
    fixed fMax = m_afTuple[0];
    if (m_afTuple[1] > fMax)
    {
        fMax = m_afTuple[1];
    }
    if (m_afTuple[2] > fMax)
    {
        fMax = m_afTuple[2];
    }

    if (fMax > FIXED_ONE)
    {
        fixed fInvMax = FIXED_ONE/fMax;
        for (int i = 0; i < 3; i++)
        {
            m_afTuple[i] =m_afTuple[i]* fInvMax;
        }
    }
}
//----------------------------------------------------------------------------
}
