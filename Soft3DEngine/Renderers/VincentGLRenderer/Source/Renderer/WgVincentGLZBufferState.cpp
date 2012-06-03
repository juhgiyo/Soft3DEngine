///////////////////////////////////////////////////////////
//                                                       //
//                    WgOpenGLZBufferState.cpp           //
//                                                       //
//  - Implementation for OpenGL Z Buffer State class     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgVincentGLRendererPCH.h"
#include "WgVincentGLRenderer.h"
using namespace WGSoft3D;

GLenum VincentGLRenderer::ms_aeZBufferCompare[ZBufferState::CF_QUANTITY] =
{
    GL_NEVER,
    GL_LESS,
    GL_EQUAL,
    GL_LEQUAL,
    GL_GREATER,
    GL_NOTEQUAL,
    GL_GEQUAL,
    GL_ALWAYS
};

//----------------------------------------------------------------------------
void VincentGLRenderer::SetZBufferState (ZBufferState* pkState)
{
    if (pkState->Enabled)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(ms_aeZBufferCompare[pkState->Compare]);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
    }

    if (pkState->Writable)
    {
        glDepthMask(GL_TRUE);
    }
    else
    {
        glDepthMask(GL_FALSE);
    }
}
//----------------------------------------------------------------------------

