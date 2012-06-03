///////////////////////////////////////////////////////////
//                                                       //
//                    WgLightMapEffect.cpp               //
//                                                       //
//  - Implementation for Light Map Effect class          //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////


#include "WgFoundationPCH.h"
#include "WgLightMapEffect.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,LightMapEffect,Effect);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(LightMapEffect,Effect);

//----------------------------------------------------------------------------
LightMapEffect::LightMapEffect (Texture* pkPrimaryTexture,
    Vector2xArray* pkPrimaryUVs, Texture* pkSecondaryTexture,
    Vector2xArray* pkSecondaryUVs, bool bHardAdd)
{
    pkPrimaryTexture->Apply = Texture::AM_REPLACE;
    Textures.Append(pkPrimaryTexture);
    UVs.Append(pkPrimaryUVs);

    if (bHardAdd)
    {
        pkSecondaryTexture->Apply = Texture::AM_ADD;
    }
    else
    {
        pkSecondaryTexture->BlendColor = ColorRGBA::WHITE;
        pkSecondaryTexture->Apply = Texture::AM_COMBINE;
        pkSecondaryTexture->CombineFuncRGB = Texture::ACF_INTERPOLATE;
        pkSecondaryTexture->CombineSrc0RGB = Texture::ACS_CONSTANT;
        pkSecondaryTexture->CombineOp0RGB = Texture::ACO_SRC_COLOR;
        pkSecondaryTexture->CombineSrc1RGB = Texture::ACS_PREVIOUS;
        pkSecondaryTexture->CombineOp1RGB = Texture::ACO_SRC_COLOR;
        pkSecondaryTexture->CombineSrc2RGB = Texture::ACS_TEXTURE;
        pkSecondaryTexture->CombineOp2RGB = Texture::ACO_SRC_COLOR;
    }

    Textures.Append(pkSecondaryTexture);
    UVs.Append(pkSecondaryUVs);
}
//----------------------------------------------------------------------------
LightMapEffect::LightMapEffect ()
{
}
//----------------------------------------------------------------------------
LightMapEffect::~LightMapEffect ()
{
}
//----------------------------------------------------------------------------
Effect* LightMapEffect::Clone ()
{
    LightMapEffect* pkClone = WG_NEW LightMapEffect;
    DoCloning(pkClone);
    return pkClone;
}
//----------------------------------------------------------------------------
void LightMapEffect::DoCloning (Effect* pkClone)
{
    Effect::DoCloning(pkClone);
}
//----------------------------------------------------------------------------

