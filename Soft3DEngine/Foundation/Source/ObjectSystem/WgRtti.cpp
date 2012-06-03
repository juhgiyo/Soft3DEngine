///////////////////////////////////////////////////////////
//                                                       //
//                    WgRtti.cpp                         //
//                                                       //
//  - Implementation for Real Time Type Info class       //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgRtti.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
Rtti::Rtti (const char* acName, const Rtti* pkBaseType)
{
    m_acName = acName;
    m_pkBaseType = pkBaseType;
}
//----------------------------------------------------------------------------
Rtti::~Rtti ()
{
}
//----------------------------------------------------------------------------
bool Rtti::IsDerived (const Rtti& rkType) const
{
    const Rtti* pkSearch = this;
    while (pkSearch)
    {
        if (pkSearch == &rkType)
        {
            return true;
        }
        pkSearch = pkSearch->m_pkBaseType;
    }
    return false;
}
//----------------------------------------------------------------------------

