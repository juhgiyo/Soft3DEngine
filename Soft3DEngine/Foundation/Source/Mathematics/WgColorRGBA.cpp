///////////////////////////////////////////////////////////
//                                                       //
//                    WgColorRGBA.cpp                    //
//                                                       //
//  - Implementation for Color RGBA class                //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgColorRGBA.h"

namespace WGSoft3D
{

const ColorRGBA ColorRGBA::BLACK(fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE));
const ColorRGBA ColorRGBA::WHITE(fixed(FIXED_ONE),fixed(FIXED_ONE),fixed(FIXED_ONE),fixed(FIXED_ONE));
const ColorRGBA ColorRGBA::INVALID(fixed(FIXED_NEG_ONE),fixed(FIXED_NEG_ONE),fixed(FIXED_NEG_ONE),fixed(FIXED_NEG_ONE));

//----------------------------------------------------------------------------
ColorRGBA::ColorRGBA ()
{
    m_afTuple[0] = FIXED_ZERO;
    m_afTuple[1] = FIXED_ZERO;
    m_afTuple[2] = FIXED_ZERO;
    m_afTuple[3] = FIXED_ZERO;
}
//----------------------------------------------------------------------------
ColorRGBA::ColorRGBA (fixed fR, fixed fG, fixed fB, fixed fA)
{
    m_afTuple[0] = fR;
    m_afTuple[1] = fG;
    m_afTuple[2] = fB;
    m_afTuple[3] = fA;
}
//----------------------------------------------------------------------------
ColorRGBA::ColorRGBA (const fixed* afTuple)
{
    m_afTuple[0] = afTuple[0];
    m_afTuple[1] = afTuple[1];
    m_afTuple[2] = afTuple[2];
    m_afTuple[3] = afTuple[3];
}
//----------------------------------------------------------------------------
ColorRGBA::ColorRGBA (const ColorRGBA& rkC)
{
    m_afTuple[0] = rkC.m_afTuple[0];
    m_afTuple[1] = rkC.m_afTuple[1];
    m_afTuple[2] = rkC.m_afTuple[2];
    m_afTuple[3] = rkC.m_afTuple[3];
}
//----------------------------------------------------------------------------
ColorRGBA& ColorRGBA::operator= (const ColorRGBA& rkC)
{
    m_afTuple[0] = rkC.m_afTuple[0];
    m_afTuple[1] = rkC.m_afTuple[1];
    m_afTuple[2] = rkC.m_afTuple[2];
    m_afTuple[3] = rkC.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator== (const ColorRGBA& rkC) const
{
    return
        m_afTuple[0] == rkC.m_afTuple[0] &&
        m_afTuple[1] == rkC.m_afTuple[1] &&
        m_afTuple[2] == rkC.m_afTuple[2] &&
        m_afTuple[3] == rkC.m_afTuple[3];
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator!= (const ColorRGBA& rkC) const
{
    return
        m_afTuple[0] != rkC.m_afTuple[0] ||
        m_afTuple[1] != rkC.m_afTuple[1] ||
        m_afTuple[2] != rkC.m_afTuple[2] ||
        m_afTuple[3] != rkC.m_afTuple[3];
}
//----------------------------------------------------------------------------
int ColorRGBA::CompareArrays (const ColorRGBA& rkC) const
{
    return memcmp(m_afTuple,rkC.m_afTuple,4*sizeof(fixed));
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator< (const ColorRGBA& rkC) const
{
    return CompareArrays(rkC) < 0;
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator<= (const ColorRGBA& rkC) const
{
    return CompareArrays(rkC) <= 0;
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator> (const ColorRGBA& rkC) const
{
    return CompareArrays(rkC) > 0;
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator>= (const ColorRGBA& rkC) const
{
    return CompareArrays(rkC) >= 0;
}
//----------------------------------------------------------------------------
ColorRGBA ColorRGBA::operator+ (const ColorRGBA& rkC) const
{
    return ColorRGBA(
        m_afTuple[0] + rkC.m_afTuple[0],
        m_afTuple[1] + rkC.m_afTuple[1],
        m_afTuple[2] + rkC.m_afTuple[2],
        m_afTuple[3] + rkC.m_afTuple[3]);
}
//----------------------------------------------------------------------------
ColorRGBA ColorRGBA::operator- (const ColorRGBA& rkC) const
{
    return ColorRGBA(
        m_afTuple[0] - rkC.m_afTuple[0],
        m_afTuple[1] - rkC.m_afTuple[1],
        m_afTuple[2] - rkC.m_afTuple[2],
        m_afTuple[3] - rkC.m_afTuple[3]);
}
//----------------------------------------------------------------------------
ColorRGBA ColorRGBA::operator* (const ColorRGBA& rkC) const
{
    return ColorRGBA(
        m_afTuple[0]*rkC.m_afTuple[0],
        m_afTuple[1]*rkC.m_afTuple[1],
        m_afTuple[2]*rkC.m_afTuple[2],
        m_afTuple[3]*rkC.m_afTuple[3]);
}
//----------------------------------------------------------------------------
ColorRGBA ColorRGBA::operator* (fixed fScalar) const
{
    return ColorRGBA(
        fScalar*m_afTuple[0],
        fScalar*m_afTuple[1],
        fScalar*m_afTuple[2],
        fScalar*m_afTuple[3]);
}
//----------------------------------------------------------------------------
ColorRGBA operator* (fixed fScalar, const ColorRGBA& rkC)
{
    return ColorRGBA(
        fScalar*rkC[0],
        fScalar*rkC[1],
        fScalar*rkC[2],
        fScalar*rkC[3]);
}
//----------------------------------------------------------------------------
ColorRGBA& ColorRGBA::operator+= (const ColorRGBA& rkC)
{
    m_afTuple[0] += rkC.m_afTuple[0];
    m_afTuple[1] += rkC.m_afTuple[1];
    m_afTuple[2] += rkC.m_afTuple[2];
    m_afTuple[3] += rkC.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
ColorRGBA& ColorRGBA::operator-= (const ColorRGBA& rkC)
{
    m_afTuple[0] -= rkC.m_afTuple[0];
    m_afTuple[1] -= rkC.m_afTuple[1];
    m_afTuple[2] -= rkC.m_afTuple[2];
    m_afTuple[3] -= rkC.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
ColorRGBA& ColorRGBA::operator*= (const ColorRGBA& rkC)
{
    m_afTuple[0] *= rkC.m_afTuple[0];
    m_afTuple[1] *= rkC.m_afTuple[1];
    m_afTuple[2] *= rkC.m_afTuple[2];
    m_afTuple[3] *= rkC.m_afTuple[3];
    return *this;
}
//----------------------------------------------------------------------------
ColorRGBA& ColorRGBA::operator*= (fixed fScalar)
{
    m_afTuple[0] *= fScalar;
    m_afTuple[1] *= fScalar;
    m_afTuple[2] *= fScalar;
    m_afTuple[3] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
void ColorRGBA::Clamp ()
{
    for (int i = 0; i < 4; i++)
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
void ColorRGBA::ScaleByMax ()
{
    // Use max of color channels, not alpha channel.
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
            m_afTuple[i]  *= fInvMax;
        }
    }

    // clamp alpha to [0,1]
    if (m_afTuple[3] > FIXED_ONE)
    {
        m_afTuple[3] = FIXED_ONE;
    }
    else if (m_afTuple[3] < FIXED_ZERO)
    {
        m_afTuple[3] = FIXED_ZERO;
    }
}
//----------------------------------------------------------------------------
}
