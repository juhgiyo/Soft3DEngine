///////////////////////////////////////////////////////////
//                                                       //
//                    WgOpenGLEnvironmentMap.cpp         //
//                                                       //
//  - Implementation for OpenGL Environment Map class    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgOmapGLRendererPCH.h"
#include "WgOmapGLRenderer.h"
#include "WgNode.h"
#include "WgEnvironmentMapEffect.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
void OmapGLRenderer::DrawEnvironmentMap ()
{
    // Access the special effect.  Detach it from the node to allow the
    // effectless node drawing.
    assert(DynamicCast<EnvironmentMapEffect>(m_pkGlobalEffect));
    EnvironmentMapEffectPtr spkEMEffect =
        (EnvironmentMapEffect*)m_pkGlobalEffect;
    m_pkNode->SetEffect(0);

    // Draw the Node tree.  Any Geometry objects with textures will have the
    // environment map as an additional one, drawn after the others
    // according to the apply mode stored by the environment map.
    m_pkNode->Draw(*this);

    // reattach the effect
    m_pkNode->SetEffect(spkEMEffect);
}
//----------------------------------------------------------------------------

