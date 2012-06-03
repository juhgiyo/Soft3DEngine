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
#include "WgOmapGLRendererPCH.h"
#include "WgOmapGLRenderer.h"
using namespace WGSoft3D;

GLenum OmapGLRenderer::ms_aeZBufferCompare[ZBufferState::CF_QUANTITY] =
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
void OmapGLRenderer::SetZBufferState (ZBufferState* pkState)
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

