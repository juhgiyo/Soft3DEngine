///////////////////////////////////////////////////////////
//                                                       //
//                    WgOpenGLShadeState.cpp             //
//                                                       //
//  - Implementation for OpenGL Shade State class        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgOmapGLRendererPCH.h"
#include "WgOmapGLRenderer.h"
using namespace WGSoft3D;

GLenum OmapGLRenderer::ms_aeShade[ShadeState::SM_QUANTITY] =
{
    GL_FLAT,
    GL_SMOOTH
};

//----------------------------------------------------------------------------
void OmapGLRenderer::SetShadeState (ShadeState* pkState)
{
    glShadeModel(ms_aeShade[pkState->Shade]);
}
//----------------------------------------------------------------------------

