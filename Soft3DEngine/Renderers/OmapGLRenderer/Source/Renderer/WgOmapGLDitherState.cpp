///////////////////////////////////////////////////////////
//                                                       //
//                    WgOpenGLDitherState.cpp            //
//                                                       //
//  - Implementation for OpenGL Dither State class       //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgOmapGLRendererPCH.h"
#include "WgOmapGLRenderer.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
void OmapGLRenderer::SetDitherState (DitherState* pkState)
{
    if (pkState->Enabled)
    {
        glEnable(GL_DITHER);
    }
    else
    {
        glDisable(GL_DITHER);
    }
}
//----------------------------------------------------------------------------

