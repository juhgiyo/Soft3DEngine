///////////////////////////////////////////////////////////
//                                                       //
//                    WgTextureEffect.cpp                //
//                                                       //
//  - Implementation for Texture Effect class            //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgFoundationPCH.h"
#include "WgTextureEffect.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,TextureEffect,Effect);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(TextureEffect,Effect);

//----------------------------------------------------------------------------
TextureEffect::TextureEffect (Texture* pkTexture, Vector2xArray* pkUVs)
{
    Textures.Append(pkTexture);
    UVs.Append(pkUVs);
}
//----------------------------------------------------------------------------
TextureEffect::TextureEffect ()
{
}
//----------------------------------------------------------------------------
TextureEffect::~TextureEffect ()
{
}
//----------------------------------------------------------------------------
Effect* TextureEffect::Clone ()
{
    TextureEffect* pkClone = WG_NEW TextureEffect;
    DoCloning(pkClone);
    return pkClone;
}
//----------------------------------------------------------------------------
void TextureEffect::DoCloning (Effect* pkClone)
{
    Effect::DoCloning(pkClone);
}
//----------------------------------------------------------------------------

