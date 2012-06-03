/////////////////////////////////////////////////////////////////
//                                                             //
//                    WgOpenGLPolygonOffsetState.cpp           //
//                                                             //
//  - Implementation for OpenGL Polygon Offset State class     //
//                                                             //
//  - Written By Woong Gyu La a.k.a. Chris                     //
//       on 2009.10.07                                         //
//                                                             //
/////////////////////////////////////////////////////////////////
#include "WgVincentGLRendererPCH.h"
#include "WgVincentGLRenderer.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
void VincentGLRenderer::SetPolygonOffsetState (PolygonOffsetState* pkState)
{
    if (pkState->FillEnabled)
    {
        glEnable(GL_POLYGON_OFFSET_FILL);
    }
    else
    {
        glDisable(GL_POLYGON_OFFSET_FILL);
    }

//     if (pkState->LineEnabled)
//     {
//         glEnable(GL_POLYGON_OFFSET_LINE);
//     }
//     else
//     {
//         glDisable(GL_POLYGON_OFFSET_LINE);
//     }
// 
//     if (pkState->PointEnabled)
//     {
//         glEnable(GL_POLYGON_OFFSET_POINT);
//     }
//     else
//     {
//         glDisable(GL_POLYGON_OFFSET_POINT);
//     }

    glPolygonOffsetx(pkState->Scale.value,pkState->Bias.value);
}
//----------------------------------------------------------------------------
