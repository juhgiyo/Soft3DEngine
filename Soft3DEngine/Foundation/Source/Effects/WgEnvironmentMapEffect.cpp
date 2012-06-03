///////////////////////////////////////////////////////////
//                                                       //
//                    WgEnvironmentMapEffect.cpp         //
//                                                       //
//  - Implementation for Environment Map Effect class    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgEnvironmentMapEffect.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,EnvironmentMapEffect,Effect);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(EnvironmentMapEffect,Effect);

//----------------------------------------------------------------------------
EnvironmentMapEffect::EnvironmentMapEffect (Image* pkImage, Texture::ApplyMode iApplyMode)
{
    Draw = &Renderer::DrawEnvironmentMap;

    Texture* pkTexture = WG_NEW Texture;
    pkTexture->SetImage(pkImage);
    pkTexture->Apply = iApplyMode;
    pkTexture->Filter = Texture::FM_LINEAR;
    pkTexture->Mipmap = Texture::MM_NEAREST;
    pkTexture->Texgen = Texture::TG_ENVIRONMENT_MAP;
    Textures.Append(pkTexture);
    UVs.Append(0);
}
//----------------------------------------------------------------------------
EnvironmentMapEffect::EnvironmentMapEffect ()
{
    Draw = &Renderer::DrawEnvironmentMap;
}
//----------------------------------------------------------------------------
EnvironmentMapEffect::~EnvironmentMapEffect ()
{
}
//----------------------------------------------------------------------------
Effect* EnvironmentMapEffect::Clone ()
{
    EnvironmentMapEffect* pkClone = WG_NEW EnvironmentMapEffect;
    DoCloning(pkClone);
    return pkClone;
}
//----------------------------------------------------------------------------
void EnvironmentMapEffect::DoCloning (Effect* pkClone)
{
    Effect::DoCloning(pkClone);
}
//----------------------------------------------------------------------------

