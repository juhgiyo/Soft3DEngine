///////////////////////////////////////////////////////////
//                                                       //
//                    WgRtti.h                           //
//                                                       //
//  - Interface for Real Time Type Information class     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_RTTI_H__
#define __WG_RTTI_H__

#include "WgFoundationLIB.h"
#include "WgSystem.h"
#include "WgRtti.mcr"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM Rtti
{
public:
    // The name must be unique among all objects in the system.  In the WGSoft3D
    // namespace, a class Foo should use "WGSoft3D.Foo".  If an application has
    // another namespace, SomeName, then the name should be "SomeName.Foo".
    Rtti (const char* acName, const Rtti* pkBaseType);
    ~Rtti ();

    const char* GetName () const;
    int GetDiskUsed () const;

    bool IsExactly (const Rtti& rkType) const;
    bool IsDerived (const Rtti& rkType) const;

private:
    const char* m_acName;
    const Rtti* m_pkBaseType;
};

#include "WgRtti.inl"

}

#endif

