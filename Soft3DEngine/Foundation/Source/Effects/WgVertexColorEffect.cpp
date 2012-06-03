///////////////////////////////////////////////////////////
//                                                       //
//                    WgVertexColorEffect.cpp            //
//                                                       //
//  - Implementation for Vertex Color Effect class       //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgVertexColorEffect.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,VertexColorEffect,Effect);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(VertexColorEffect,Effect);

//----------------------------------------------------------------------------
VertexColorEffect::VertexColorEffect (ColorRGBArray* pkColorRGBs)
{
    ColorRGBs = pkColorRGBs;
}
//----------------------------------------------------------------------------
VertexColorEffect::VertexColorEffect (ColorRGBAArray* pkColorRGBAs)
{
    ColorRGBAs = pkColorRGBAs;
}
//----------------------------------------------------------------------------
VertexColorEffect::VertexColorEffect ()
{
}
//----------------------------------------------------------------------------
VertexColorEffect::~VertexColorEffect ()
{
}
//----------------------------------------------------------------------------
Effect* VertexColorEffect::Clone ()
{
    VertexColorEffect* pkClone = WG_NEW VertexColorEffect;
    DoCloning(pkClone);
    return pkClone;
}
//----------------------------------------------------------------------------
void VertexColorEffect::DoCloning (Effect* pkClone)
{
    Effect::DoCloning(pkClone);
}
//----------------------------------------------------------------------------

