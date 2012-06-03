///////////////////////////////////////////////////////////
//                                                       //
//                    WgBindInfo.h                       //
//                                                       //
//  - Interface for Bind Information class               //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_BINDINFO_H__
#define __WG_BINDINFO_H__

#include "WgFoundationLIB.h"
#include "WgSystem.h"
#include "WgTArray.h"

namespace WGSoft3D
{

class Renderer;

class WG3D_FOUNDATION_ITEM BindInfo
{
public:
    BindInfo ();

    // The renderer to which the resource is bound.
    Renderer* User;

    // The identifier of the resource for the renderer's use.  The number
    // of bytes used is up to 8, but only the renderer knows the true
    // size.
    char ID[8];
};

class WG3D_FOUNDATION_ITEM BindInfoArray
{
public:
    BindInfoArray (int iQuantity, int iGrowBy);

    const TArray<BindInfo>& GetArray () const;

    void Bind (Renderer* pkUser, int iSize, const void* pvID);
    void Unbind (Renderer* pkUser);
    void GetID (Renderer* pkUser, int iSize, void* pvID);

private:
    TArray<BindInfo> m_kBind;
};

};

#endif

