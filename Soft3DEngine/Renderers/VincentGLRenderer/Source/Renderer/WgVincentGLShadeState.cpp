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
#include "WgVincentGLRendererPCH.h"
#include "WgVincentGLRenderer.h"
using namespace WGSoft3D;

GLenum VincentGLRenderer::ms_aeShade[ShadeState::SM_QUANTITY] =
{
    GL_FLAT,
    GL_SMOOTH
};

//----------------------------------------------------------------------------
void VincentGLRenderer::SetShadeState (ShadeState* pkState)
{
    glShadeModel(ms_aeShade[pkState->Shade]);
}
//----------------------------------------------------------------------------

