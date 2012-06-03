///////////////////////////////////////////////////////////
//                                                       //
//                    WgOpenGLBumpMap.cpp                //
//                                                       //
//  - Implementation for OpenGL Bump Map class           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgOmapGLRendererPCH.h"
#include "WgOmapGLRenderer.h"
#include "WgBumpMapEffect.h"
#include "WgCachedColorRGBArray.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
void OmapGLRenderer::DrawBumpMap ()
{
    Triangles* pkMesh = DynamicCast<Triangles>(m_pkGeometry);
    assert(pkMesh);
    BumpMapEffect* pkBMEffect = DynamicCast<BumpMapEffect>(
        m_pkGeometry->GetEffect());
    assert(pkBMEffect);

    // set up the model-to-world transformation
    SetWorldTransformation();

    // set the vertex array
    EnableVertices();

    // *** FIRST PASS
    SetGlobalState(m_pkGeometry->States);

    if (pkBMEffect->GetNeedsRecalculation())
    {
        // no lighting, the color array stores the light vectors
        pkBMEffect->ComputeLightVectors(pkMesh);

        // If the colors were cached in VRAM, they must be refreshed by the
        // newly calculated values.
        CachedColorRGBArray* akColors =
            DynamicCast<CachedColorRGBArray>(m_pkLocalEffect->ColorRGBs);
        if (akColors)
        {
            ReleaseArray(akColors);
        }
    }

    EnableColorRGBs();

    // texture unit 0 handles the normal map
    EnableTexture(0,1,pkBMEffect);

    // draw the object
    DrawElements();

    // *** SECOND PASS
    EnableLighting();
    glEnable(GL_BLEND);
    glBlendFunc(GL_DST_COLOR,GL_ZERO);

    // set the normal array
    EnableNormals();

    // texture unit 0 handles the primary texture
    EnableTexture(0,0,pkBMEffect);

    // other textures handled by the remaining texture units
    int iTMax = pkBMEffect->Textures.GetQuantity();
    if (iTMax > m_iMaxTextures)
    {
        iTMax = m_iMaxTextures;
    }

    int i, iUnit;
    for (i = 2, iUnit = 1; i < iTMax; i++)
    {
        EnableTexture(iUnit++,i,pkBMEffect);
    }

    // draw the object
    DrawElements();

    // disable texture states
    DisableTexture(0,0,pkBMEffect);
    for (i = 2, iUnit = 1; i < iTMax; i++)
    {
        DisableTexture(iUnit++,i,pkBMEffect);
    }

    // disable normal state
    DisableNormals();

    // disable color state
    DisableColorRGBs();

    DisableLighting();

    // restore the default alpha state
    GlobalState* pkAState = GlobalState::Default[GlobalState::ALPHA];
    SetAlphaState((AlphaState*)pkAState);

    // disable vertices
    DisableVertices();

    // restore the model-to-world transformation
    RestoreWorldTransformation();
}
//----------------------------------------------------------------------------

