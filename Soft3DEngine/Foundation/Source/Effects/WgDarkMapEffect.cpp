///////////////////////////////////////////////////////////
//                                                       //
//                    WgDarkMapEffect.cpp                //
//                                                       //
//  - Implementation for Dark Map Effect class           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgDarkMapEffect.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,DarkMapEffect,Effect);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(DarkMapEffect,Effect);

//----------------------------------------------------------------------------
DarkMapEffect::DarkMapEffect (Texture* pkPrimaryTexture,
    Vector2xArray* pkPrimaryUVs, Texture* pkSecondaryTexture,
    Vector2xArray* pkSecondaryUVs)
{
    pkPrimaryTexture->Apply = Texture::AM_REPLACE;
    Textures.Append(pkPrimaryTexture);
    UVs.Append(pkPrimaryUVs);

    pkSecondaryTexture->Apply = Texture::AM_MODULATE;
    Textures.Append(pkSecondaryTexture);
    UVs.Append(pkSecondaryUVs);
}
//----------------------------------------------------------------------------
DarkMapEffect::DarkMapEffect ()
{
}
//----------------------------------------------------------------------------
DarkMapEffect::~DarkMapEffect ()
{
}
//----------------------------------------------------------------------------
Effect* DarkMapEffect::Clone ()
{
    DarkMapEffect* pkClone = WG_NEW DarkMapEffect;
    DoCloning(pkClone);
    return pkClone;
}
//----------------------------------------------------------------------------
void DarkMapEffect::DoCloning (Effect* pkClone)
{
    Effect::DoCloning(pkClone);
}
//----------------------------------------------------------------------------

