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
#include "WgVincentGLRendererPCH.h"
#include "WgVincentGLRenderer.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
void VincentGLRenderer::SetDitherState (DitherState* pkState)
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

