///////////////////////////////////////////////////////////
//                                                       //
//                    WgOpenGLCullState.cpp              //
//                                                       //
//  - Implementation for OpenGL Cull State class         //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgVincentGLRendererPCH.h"
#include "WgVincentGLRenderer.h"
using namespace WGSoft3D;

GLenum VincentGLRenderer::ms_aeFrontFace[CullState::FT_QUANTITY] =
{
    GL_CCW,
    GL_CW
};

GLenum VincentGLRenderer::ms_aeCullFace[CullState::CT_QUANTITY] =
{
    GL_FRONT,
    GL_BACK
};

//----------------------------------------------------------------------------
void VincentGLRenderer::SetCullState (CullState* pkState)
{
    if (pkState->Enabled)
    {
        glEnable(GL_CULL_FACE);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }

    glFrontFace(ms_aeFrontFace[pkState->FrontFace]);

    if (!m_bReverseCullFace)
    {
        glCullFace(ms_aeCullFace[pkState->CullFace]);
    }
    else
    {
        if (ms_aeCullFace[pkState->CullFace] == GL_BACK)
        {
            glCullFace(GL_FRONT);
        }
        else
        {
            glCullFace(GL_BACK);
        }
    }
}
//----------------------------------------------------------------------------

