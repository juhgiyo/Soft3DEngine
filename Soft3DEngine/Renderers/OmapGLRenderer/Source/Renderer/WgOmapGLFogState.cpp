///////////////////////////////////////////////////////////
//                                                       //
//                    WgOpenGLFogState.cpp               //
//                                                       //
//  - Implementation for OpenGL Fog State class          //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgOmapGLRendererPCH.h"
#include "WgOmapGLRenderer.h"
using namespace WGSoft3D;

GLenum OmapGLRenderer::ms_aeFogDensity[FogState::DF_QUANTITY] =
{
    GL_LINEAR,
    GL_EXP,
    GL_EXP2
};

GLenum OmapGLRenderer::ms_aeFogApply[FogState::AF_QUANTITY] =
{
    GL_FASTEST,
    GL_NICEST
};

//----------------------------------------------------------------------------
void OmapGLRenderer::SetFogState (FogState* pkState)
{
    if (pkState->Enabled)
    {
        glEnable(GL_FOG);
        glFogx(GL_FOG_START,pkState->Start.value);
        glFogx(GL_FOG_END,pkState->End.value);
        glFogxv(GL_FOG_COLOR,(GLfixed*)(fixed*)pkState->Color);
        glFogx(GL_FOG_DENSITY,pkState->Density.value);
        glFogx(GL_FOG_MODE,ms_aeFogDensity[pkState->DensityFunction]);
        glHint(GL_FOG_HINT,ms_aeFogApply[pkState->ApplyFunction]);
    }
    else
    {
        glDisable(GL_FOG);
    }
}
//----------------------------------------------------------------------------

