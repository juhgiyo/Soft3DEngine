///////////////////////////////////////////////////////////
//                                                       //
//                    WgOpenGLAlphaState.cpp             //
//                                                       //
//  - Implementation for OpenGL Alpha State class        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgOmapGLRendererPCH.h"
#include "WgOmapGLRenderer.h"
using namespace WGSoft3D;

GLenum OmapGLRenderer::ms_aeAlphaSrcBlend[AlphaState::SBF_QUANTITY] =
{
    GL_ZERO,
    GL_ONE,
    GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR,
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_SRC_ALPHA_SATURATE,
//     GL_CONSTANT_COLOR,
//     GL_ONE_MINUS_CONSTANT_COLOR,
//     GL_CONSTANT_ALPHA,
//     GL_ONE_MINUS_CONSTANT_ALPHA
};

GLenum OmapGLRenderer::ms_aeAlphaDstBlend[AlphaState::DBF_QUANTITY] =
{
    GL_ZERO,
    GL_ONE,
    GL_SRC_COLOR,
    GL_ONE_MINUS_SRC_COLOR,
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
//     GL_CONSTANT_COLOR,
//     GL_ONE_MINUS_CONSTANT_COLOR,
//     GL_CONSTANT_ALPHA,
//     GL_ONE_MINUS_CONSTANT_ALPHA
};

GLenum OmapGLRenderer::ms_aeAlphaTest[AlphaState::TF_QUANTITY] =
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
void OmapGLRenderer::SetAlphaState (AlphaState* pkState)
{
    if (pkState->BlendEnabled)
    {
        glEnable(GL_BLEND);
        glBlendFunc(ms_aeAlphaSrcBlend[pkState->SrcBlend],
            ms_aeAlphaDstBlend[pkState->DstBlend]);
    }
    else
    {
        glDisable(GL_BLEND);
    }

    if (pkState->TestEnabled)
    {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(ms_aeAlphaTest[pkState->Test],pkState->Reference.value);
    }
    else
    {
        glDisable(GL_ALPHA_TEST);
    }
}
//----------------------------------------------------------------------------

