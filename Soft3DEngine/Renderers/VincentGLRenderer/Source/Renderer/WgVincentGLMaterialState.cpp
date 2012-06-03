///////////////////////////////////////////////////////////
//                                                       //
//                    WgOpenGLMaterialState.cpp          //
//                                                       //
//  - Implementation for OpenGL Material State class     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgVincentGLRendererPCH.h"
#include "WgVincentGLRenderer.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
void VincentGLRenderer::SetMaterialState (MaterialState* pkState)
{
    glMaterialxv(GL_FRONT,GL_EMISSION,(int*)(fixed*)pkState->Emissive);
    glMaterialxv(GL_FRONT,GL_AMBIENT,(int*)(fixed*)pkState->Ambient);
    glMaterialxv(GL_FRONT,GL_DIFFUSE,(int*)(fixed*)pkState->Diffuse);
    glMaterialxv(GL_FRONT,GL_SPECULAR,(int*)(fixed*)pkState->Specular);
    glMaterialx(GL_FRONT,GL_SHININESS,pkState->Shininess.value);
}
//----------------------------------------------------------------------------

