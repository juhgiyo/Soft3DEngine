///////////////////////////////////////////////////////////
//                                                       //
//                    WgLinComp.cpp                      //
//                                                       //
//  - Implementation for Lin Comp class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgLinComp.h"

namespace WGSoft3D
{
//----------------------------------------------------------------------------

LinCompx::LinCompx ()
{
    m_iType = CT_EMPTY;
    m_fMin = Mathx::MAX_REAL;
    m_fMax = -Mathx::MAX_REAL;
}
//----------------------------------------------------------------------------

LinCompx::~LinCompx ()
{
}
//----------------------------------------------------------------------------

LinCompx& LinCompx::operator= (const LinCompx& rkComponent)
{
    m_iType = rkComponent.m_iType;
    m_fMin = rkComponent.m_fMin;
    m_fMax = rkComponent.m_fMax;
    return *this;
}
//----------------------------------------------------------------------------

int LinCompx::GetType () const
{
    return m_iType;
}
//----------------------------------------------------------------------------

fixed LinCompx::GetMin () const
{
    return m_fMin;
}
//----------------------------------------------------------------------------

fixed LinCompx::GetMax () const
{
    return m_fMax;
}
//----------------------------------------------------------------------------

bool LinCompx::Contains (fixed fParam) const
{
    return m_fMin <= fParam && fParam <= m_fMax;
}
//----------------------------------------------------------------------------

void LinCompx::SetInterval (fixed fMin, fixed fMax)
{
    m_iType = GetTypeFromInterval(fMin,fMax);
    m_fMin = fMin;
    m_fMax = fMax;
}
//----------------------------------------------------------------------------

int LinCompx::GetTypeFromInterval (fixed fMin, fixed fMax)
{
    if (fMin < fMax)
    {
        if (fMax == Mathx::MAX_REAL)
        {
            if (fMin == -Mathx::MAX_REAL)
            {
                return CT_LINE;
            }
            else
            {
                return CT_RAY;
            }
        }
        else
        {
            if (fMin == -Mathx::MAX_REAL)
            {
                return CT_RAY;
            }
            else
            {
                return CT_SEGMENT;
            }
        }
    }
    else if (fMin == fMax)
    {
        if (fMin != -Mathx::MAX_REAL && fMax != Mathx::MAX_REAL)
        {
            return CT_POINT;
        }
    }

    return CT_EMPTY;
}
//----------------------------------------------------------------------------

bool LinCompx::IsCanonical () const
{
    if (m_iType == CT_RAY)
    {
        return m_fMin == FIXED_ZERO && m_fMax == Mathx::MAX_REAL;
    }

    if (m_iType == CT_SEGMENT)
    {
        return m_fMin == -m_fMax;
    }

    if (m_iType == CT_POINT)
    {
        return m_fMin == FIXED_ZERO; 
    }

    if (m_iType == CT_EMPTY)
    {
        return m_fMin == Mathx::MAX_REAL
            && m_fMax == -Mathx::MAX_REAL;
    }

    // m_iType == CT_LINE
    return true;
}
//----------------------------------------------------------------------------

}