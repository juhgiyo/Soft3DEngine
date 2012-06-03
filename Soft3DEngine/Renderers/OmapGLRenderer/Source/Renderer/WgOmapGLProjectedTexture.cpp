///////////////////////////////////////////////////////////
//                                                       //
//                    WgOpenGLProjectedTexture.cpp       //
//                                                       //
//  - Implementation for OpenGL Projected Texture class  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgOmapGLRendererPCH.h"
#include "WgOmapGLRenderer.h"
#include "WgNode.h"
#include "WgProjectedTextureEffect.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
void OmapGLRenderer::DrawProjectedTexture ()
{
    // Access the special effect.  Detach it from the node to allow the
    // effectless node drawing.
    assert(DynamicCast<ProjectedTextureEffect>(m_pkGlobalEffect));
    ProjectedTextureEffectPtr spkPTEffect =
        (ProjectedTextureEffect*)m_pkGlobalEffect;
    m_pkNode->SetEffect(0);

    // Draw the Node tree.  Any Geometry objects with textures will have the
    // projected texture as an additional one, drawn after the others
    // according to the apply mode stored by the projected texture.
    m_pkNode->Draw(*this);

    // reattach the effect
    m_pkNode->SetEffect(spkPTEffect);
}
//----------------------------------------------------------------------------

