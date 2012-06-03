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
#include "WgOmapGLRendererPCH.h"
#include "WgOmapGLRenderer.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
void OmapGLRenderer::SetMaterialState (MaterialState* pkState)
{
    glMaterialxv(GL_FRONT,GL_EMISSION,(GLfixed*)(fixed*)pkState->Emissive);
    glMaterialxv(GL_FRONT,GL_AMBIENT,(GLfixed*)(fixed*)pkState->Ambient);
    glMaterialxv(GL_FRONT,GL_DIFFUSE,(GLfixed*)(fixed*)pkState->Diffuse);
    glMaterialxv(GL_FRONT,GL_SPECULAR,(GLfixed*)(fixed*)pkState->Specular);
    glMaterialx(GL_FRONT,GL_SHININESS,pkState->Shininess.value);
}
//----------------------------------------------------------------------------

