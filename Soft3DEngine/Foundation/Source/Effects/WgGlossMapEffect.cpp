///////////////////////////////////////////////////////////
//                                                       //
//                    WgGlossMapEffect.cpp               //
//                                                       //
//  - Implementation for Gloss Map Effect class          //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgGlossMapEffect.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,GlossMapEffect,Effect);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(GlossMapEffect,Effect);

//----------------------------------------------------------------------------
GlossMapEffect::GlossMapEffect (Texture* pkTexture, Vector2xArray* pkUVs)
{
    Draw = &Renderer::DrawGlossMap;
    pkTexture->Apply = Texture::AM_MODULATE;
    Textures.Append(pkTexture);
    UVs.Append(pkUVs);
}
//----------------------------------------------------------------------------
GlossMapEffect::GlossMapEffect ()
{
    Draw = &Renderer::DrawGlossMap;
}
//----------------------------------------------------------------------------
GlossMapEffect::~GlossMapEffect ()
{
}
//----------------------------------------------------------------------------
Effect* GlossMapEffect::Clone ()
{
    GlossMapEffect* pkClone = WG_NEW GlossMapEffect;
    DoCloning(pkClone);
    return pkClone;
}
//----------------------------------------------------------------------------
void GlossMapEffect::DoCloning (Effect* pkClone)
{
    Effect::DoCloning(pkClone);
}
//----------------------------------------------------------------------------

