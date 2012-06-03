///////////////////////////////////////////////////////////
//                                                       //
//                    WgOpenGLPlanarShadow.cpp           //
//                                                       //
//  - Implementation for OpenGL Planar Shadow class      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgOmapGLRendererPCH.h"
#include "WgOmapGLRenderer.h"
#include "WgMatrix4.h"
#include "WgNode.h"
#include "WgPlanarShadowEffect.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
void OmapGLRenderer::DrawPlanarShadow ()
{
    // Access the special effect.  Detach it from the node to allow the
    // effectless node drawing.
    assert(DynamicCast<PlanarShadowEffect>(m_pkNode->GetEffect()));
    PlanarShadowEffectPtr spkPSEffect =
        (PlanarShadowEffect*)m_pkNode->GetEffect();
    m_pkNode->SetEffect(0);

    // draw the caster
    m_pkNode->Draw(*this);

    // number of planes limited by stencil buffer size
    int iQuantity = spkPSEffect->GetQuantity();
    if (iQuantity >= m_iMaxStencilIndices-1)
    {
        iQuantity = m_iMaxStencilIndices-1;
    }

    for (int i = 0; i < iQuantity; i++)
    {
        TriMeshPtr spkPlane = spkPSEffect->GetPlane(i);
        LightPtr spkProjector = spkPSEffect->GetProjector(i);
        ColorRGBA kShadowColor = spkPSEffect->GetShadowColor(i);

        // enable depth buffering
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);
        m_bAllowZBufferState = false;

        // Enable the stencil buffer so that the shadow can be clipped by the
        // plane.
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS,i+1,~0);
        glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
        glStencilMask(~0);

        // draw the plane
        Renderer::Draw(spkPlane);

        // disable the stencil buffer and depth buffer
        glDisable(GL_STENCIL_TEST);
        glDisable(GL_DEPTH_TEST);
        m_bAllowZBufferState = true;

        // compute the equation for the shadow plane in world coordinates
        Triangle3x kTri;
        spkPlane->GetWorldTriangle(0,kTri);
        Plane3x kPlane(kTri.V[0],kTri.V[1],kTri.V[2]);

        // Conservative test to see if a shadow should be cast.  This can
        // cause incorrect results if the caster is large and intersects the
        // plane, but ordinarily we are not trying to cast shadows in such
        // situations.
        if (m_pkNode->WorldBound->WhichSide(kPlane) < 0)
        {
            // shadow caster is on far side of plane
            continue;
        }

        // Compute the projection matrix for the light source.
        Matrix4x kProjectionTranspose;
        if (spkProjector->Type == Light::LT_DIRECTIONAL)
        {
            fixed fNdD =
                kPlane.Normal.Dot(spkProjector->GetWorldDVector());
            if (fNdD >= FIXED_ZERO)
            {
                // Projection must be onto the "positive side" of the plane.
                continue;
            }

            kProjectionTranspose.MakeObliqueProjection(kPlane.Normal,
                kTri.V[0],spkProjector->GetWorldDVector());
        }
        else if (spkProjector->Type == Light::LT_POINT
        ||  spkProjector->Type == Light::LT_SPOT)
        {
            fixed fNdE =
                kPlane.Normal.Dot(spkProjector->GetWorldLocation());
            if (fNdE <= FIXED_ZERO)
            {
                // Projection must be onto the "positive side" of the plane.
                continue;
            }

            kProjectionTranspose.MakePerspectiveProjection(kPlane.Normal,
                kTri.V[0],spkProjector->GetWorldLocation());
        }
        else
        {
            assert(false);
            kProjectionTranspose = Matrix4x::IDENTITY;
        }

        Matrix4x kProjection = kProjectionTranspose.Transpose();

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMultMatrixx((const GLfixed*)(const fixed*)kProjection);

        // Alpha blending used to blend the shadow color with the appropriate
        // pixels drawn for the projection plane.
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        ColorRGBA kSaveColor;
        glGetFixedv(GL_CURRENT_COLOR,(GLfixed*)(fixed*)kSaveColor);
        glColor4x(kShadowColor.R().value,kShadowColor.G().value,kShadowColor.B().value,kShadowColor.A().value);
		
        // Only draw where the plane has been drawn.
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_EQUAL,i+1,~0);
        glStencilOp(GL_KEEP,GL_KEEP,GL_ZERO);

        // Draw the caster again, but using only vertices and triangles
        // indices.  Disable culling to allow out-of-view objects to cast
        // shadows.
        m_bAllowGlobalState = false;
        m_bAllowLighting = false;
        m_bAllowNormals = false;
        m_bAllowColors = false;
        m_bAllowTextures = false;

        m_pkNode->Draw(*this,true);

        m_bAllowGlobalState = true;
        m_bAllowLighting = true;
        m_bAllowNormals = true;
        m_bAllowColors = true;
        m_bAllowTextures = true;

        // disable the stencil buffer
        glDisable(GL_STENCIL_TEST);

        // restore current color
		glColor4x(kSaveColor.R().value,kSaveColor.G().value,kSaveColor.B().value,kSaveColor.A().value);

        // disable alpha blending
        glDisable(GL_BLEND);

        // restore the model-to-world transformation
        glPopMatrix();
    }

    // reattach the effect
    m_pkNode->SetEffect(spkPSEffect);
}
//----------------------------------------------------------------------------

