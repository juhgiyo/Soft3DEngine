///////////////////////////////////////////////////////////
//                                                       //
//                    WgRenderer.cpp                     //
//                                                       //
//  - Implementation for Renderer class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgRenderer.h"
#include "WgCamera.h"
#include "WgEffect.h"
#include "WgGeometry.h"
#include "WgLight.h"
#include "WgNode.h"
#include "WgPBuffer.h"
#include "WgScreenPolygon.h"
#include "WgTexture.h"
#include "WgCachedColorRGBAArray.h"
#include "WgCachedColorRGBArray.h"
#include "WgCachedShortArray.h"
#include "WgCachedVector2Array.h"
#include "WgCachedVector3Array.h"
using namespace WGSoft3D;

Renderer::SetConstantFunction
Renderer::ms_aoSCFunction[ShaderConstant::SC_QUANTITY] =
{
    &Renderer::SetConstantTransformM,
    &Renderer::SetConstantTransformP,
    &Renderer::SetConstantTransformMV,
    &Renderer::SetConstantTransformMVP,
    &Renderer::SetConstantCameraPosition,
    &Renderer::SetConstantCameraDirection,
    &Renderer::SetConstantCameraUp,
    &Renderer::SetConstantCameraRight,
    &Renderer::SetConstantFogColor,
    &Renderer::SetConstantFogParams,
    &Renderer::SetConstantMaterialEmissive,
    &Renderer::SetConstantMaterialAmbient,
    &Renderer::SetConstantMaterialDiffuse,
    &Renderer::SetConstantMaterialSpecular,
    &Renderer::SetConstantMaterialShininess,
    &Renderer::SetConstantLightPosition,
    &Renderer::SetConstantLightDirection,
    &Renderer::SetConstantLightAmbient,
    &Renderer::SetConstantLightDiffuse,
    &Renderer::SetConstantLightSpecular,
    &Renderer::SetConstantLightSpotCutoff,
    &Renderer::SetConstantLightAttenParams,
};

int Renderer::ms_eType = Renderer::RT_QUANTITY;

//----------------------------------------------------------------------------
Renderer::Renderer (const BufferParams& rkBufferParams, int iWidth,
    int iHeight)
    :
    m_kBufferParams(rkBufferParams),
    m_kBackgroundColor(ColorRGBA::WHITE),
    m_kDeferredObject(1024,128),
    m_kDeferredIsGeometry(1024,128)
{
    m_iDeferredQuantity = 0;
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_pkCamera = 0;

    // Derived classes should set the maximum values, then resize the
    // m_kLight and m_kTexture arrays accordingly.  This will guarantee that
    // these arrays never reallocate their internal data in the SetState
    // call that is made on each drawing pass.
    m_iMaxLights = 0;
    m_iMaxTextures = 0;
    m_iMaxStencilIndices = 0;

    // current object and effect
    m_pkNode = 0;
    m_pkGeometry = 0;
    m_pkLocalEffect = 0;
    m_pkGlobalEffect = 0;

    m_bAllowGlobalState = true;
    m_bAllowAlphaState = true;
    m_bAllowCullState = true;
    m_bAllowDitherState = true;
    m_bAllowFogState = true;
    m_bAllowMaterialState = true;
    m_bAllowShadeState = true;
   // m_bAllowWireframeState = true;
    m_bAllowZBufferState = true;
    m_bAllowLighting = true;
    m_bAllowNormals = true;
    m_bAllowColors = true;
    m_bAllowTextures = true;
    m_bAllowWorldTransform = true;
    m_bReverseCullFace = false;

    // windowed mode by default
    m_bFullscreen = false;

    // current font (id = 0 is the default font)
    m_iFontID = 0;

    // deferred drawing disabled
    DrawDeferred = 0;

    // Temporary pointer to the offscreen buffer passed to BeginOffscreen.
    m_pkTarget = 0;

    m_fPointSize = FIXED_ONE;
    m_fLineWidth = FIXED_ONE;
    m_iLineStippleRepeat = 0;
    m_usLineStipplePattern = 0;
}
//----------------------------------------------------------------------------
Renderer::~Renderer ()
{
    SetCamera(0);
}
//----------------------------------------------------------------------------
void Renderer::SetCamera (Camera* pkCamera)
{
    if (m_pkCamera)
    {
        m_pkCamera->m_pkRenderer = 0;
    }

    if (pkCamera)
    {
        pkCamera->m_pkRenderer = this;
    }

    m_pkCamera = pkCamera;
}
//----------------------------------------------------------------------------
void Renderer::Resize (int iWidth, int iHeight)
{
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    OnViewPortChange();
}
//----------------------------------------------------------------------------
void Renderer::DrawScene (Node* pkScene, bool bNoCull)
{
    if (pkScene)
    {
        pkScene->OnDraw(*this,bNoCull);

        if (DrawDeferred)
        {
            (this->*DrawDeferred)();
            m_iDeferredQuantity = 0;
        }
    }
}
//----------------------------------------------------------------------------
void Renderer::Draw (Node* pkNode)
{
    if (!DrawDeferred)
    {
        m_pkNode = pkNode;
        m_pkGlobalEffect = pkNode->GetEffect();

        // If you reach this assert, make sure you call DrawScene rather than
        // Draw on the root node of your scene graph.
        assert(m_pkGlobalEffect);
        (this->*m_pkGlobalEffect->Draw)();

        m_pkNode = 0;
        m_pkGlobalEffect = 0;
    }
    else
    {
        m_kDeferredObject.SetElement(m_iDeferredQuantity,pkNode);
        m_kDeferredIsGeometry.SetElement(m_iDeferredQuantity,false);
        m_iDeferredQuantity++;
    }
}
//----------------------------------------------------------------------------
void Renderer::Draw (Geometry* pkGeometry)
{
    if (!DrawDeferred)
    {
        m_pkGeometry = pkGeometry;
        m_pkLocalEffect = pkGeometry->GetEffect();

        if (m_pkLocalEffect)
        {
            (this->*m_pkLocalEffect->Draw)();
        }
        else
        {
            DrawPrimitive();
        }

        m_pkLocalEffect = 0;
        m_pkGeometry = 0;
    }
    else
    {
        m_kDeferredObject.SetElement(m_iDeferredQuantity,pkGeometry);
        m_kDeferredIsGeometry.SetElement(m_iDeferredQuantity,true);
        m_iDeferredQuantity++;
    }
}
//----------------------------------------------------------------------------
void Renderer::Draw (ScreenPolygon* pkPolygon)
{
    m_bAllowWorldTransform = false;
    Draw((Geometry*)pkPolygon);
    m_bAllowWorldTransform = true;
}
//----------------------------------------------------------------------------
void Renderer::SetGlobalState (
    GlobalStatePtr aspkState[GlobalState::MAX_STATE])
{
    GlobalState* pkState;

    if (m_bAllowAlphaState)
    {
        pkState = aspkState[GlobalState::ALPHA];
        SetAlphaState((AlphaState*)pkState);
    }

    if (m_bAllowCullState)
    {
        pkState = aspkState[GlobalState::CULL];
        SetCullState((CullState*)pkState);
    }

    if (m_bAllowDitherState)
    {
        pkState = aspkState[GlobalState::DITHER];
        SetDitherState((DitherState*)pkState);
    }

    if (m_bAllowFogState)
    {
        pkState = aspkState[GlobalState::FOG];
        SetFogState((FogState*)pkState);
    }

    if (m_bAllowMaterialState)
    {
        pkState = aspkState[GlobalState::MATERIAL];
        SetMaterialState((MaterialState*)pkState);
    }

    if (m_bAllowPolygonOffsetState)
    {
        pkState = aspkState[GlobalState::POLYGONOFFSET];
        SetPolygonOffsetState((PolygonOffsetState*)pkState);
    }

    if (m_bAllowShadeState)
    {
        pkState = aspkState[GlobalState::SHADE];
        SetShadeState((ShadeState*)pkState);
    }

//     if (m_bAllowWireframeState)
//     {
//         pkState = aspkState[GlobalState::WIREFRAME];
//         SetWireframeState((WireframeState*)pkState);
//     }

    if (m_bAllowZBufferState)
    {
        pkState = aspkState[GlobalState::ZBUFFER];
        SetZBufferState((ZBufferState*)pkState);
    }
}
//----------------------------------------------------------------------------
void Renderer::EnableTextures ()
{
    int iTMax, i;
    int iUnit = 0;

    // set the local-effect texture units
    if (m_pkLocalEffect)
    {
        iTMax = m_pkLocalEffect->Textures.GetQuantity();
        if (iTMax > m_iMaxTextures)
        {
            iTMax = m_iMaxTextures;
        }

        for (i = 0; i < iTMax; i++)
        {
            EnableTexture(iUnit++,i,m_pkLocalEffect);
        }
    }

    // set the global-effect texture units
    if (m_pkGlobalEffect)
    {
        iTMax = m_pkGlobalEffect->Textures.GetQuantity();
        if (iTMax > m_iMaxTextures)
        {
            iTMax = m_iMaxTextures;
        }

        for (i = 0; i < iTMax; i++)
        {
            EnableTexture(iUnit++,i,m_pkGlobalEffect);
        }
    }
}
//----------------------------------------------------------------------------
void Renderer::DisableTextures ()
{
    int iTMax, i;
    int iUnit = 0;

    // disable the local-effect texture units
    if (m_pkLocalEffect)
    {
        iTMax = m_pkLocalEffect->Textures.GetQuantity();
        if (iTMax > m_iMaxTextures)
        {
            iTMax = m_iMaxTextures;
        }

        for (i = 0; i < iTMax; i++)
        {
            DisableTexture(iUnit++,i,m_pkLocalEffect);
        }
    }

    // disable the global-effect texture units
    if (m_pkGlobalEffect)
    {
        iTMax = m_pkGlobalEffect->Textures.GetQuantity();
        if (iTMax > m_iMaxTextures)
        {
            iTMax = m_iMaxTextures;
        }

        for (i = 0; i < iTMax; i++)
        {
            DisableTexture(iUnit++,i,m_pkGlobalEffect);
        }
    }
}
//----------------------------------------------------------------------------
void Renderer::ReleaseTextures (Spatial* pkScene)
{
    int i;

    // release all textures attached to this object
    Effect* pkEffect = pkScene->GetEffect();
    if (pkEffect)
    {
        for (i = 0; i < pkEffect->Textures.GetQuantity(); i++)
        {
            Texture* pkTexture = pkEffect->Textures[i];
            if (pkTexture)
            {
                ReleaseTexture(pkTexture);
            }
        }
    }

    // recurse the subtree of this object and release other textures
    Node* pkNode = DynamicCast<Node>(pkScene);
    if (pkNode)
    {
        for (i = 0; i < pkNode->GetQuantity(); i++)
        {
            Spatial* pkChild = pkNode->GetChild(i);
            if (pkChild)
            {
                ReleaseTextures(pkChild);
            }
        }
    }
}
//----------------------------------------------------------------------------
void Renderer::ReleaseArrays (Spatial* pkScene)
{
    Geometry* pkGeometry = DynamicCast<Geometry>(pkScene);
    if (pkGeometry)
    {
        CachedVector3xArray* pkCVertices =
            DynamicCast<CachedVector3xArray>(pkGeometry->Vertices);
        if (pkCVertices)
        {
            ReleaseArray(pkCVertices);
        }

        CachedShortArray* pkCIndices =
            DynamicCast<CachedShortArray>(pkGeometry->Indices);
        if (pkCIndices)
        {
            ReleaseArray(pkCIndices);
        }

        CachedVector3xArray* pkCNormals =
            DynamicCast<CachedVector3xArray>(pkGeometry->Normals);
        if (pkCNormals)
        {
            ReleaseArray(pkCNormals);
        }
    }

    int i;

    // release all colors and uv's attached to this object
    Effect* pkEffect = pkScene->GetEffect();
    if (pkEffect)
    {
        CachedColorRGBAArray* pkCColorRGBAs =
            DynamicCast<CachedColorRGBAArray>(pkEffect->ColorRGBAs);
        if (pkCColorRGBAs)
        {
            ReleaseArray(pkCColorRGBAs);
        }

        CachedColorRGBArray* pkCColorRGBs =
            DynamicCast<CachedColorRGBArray>(pkEffect->ColorRGBs);
        if (pkCColorRGBs)
        {
            ReleaseArray(pkCColorRGBs);
        }

        for (i = 0; i < pkEffect->UVs.GetQuantity(); i++)
        {
            CachedVector2xArray* pkCUVs =
                DynamicCast<CachedVector2xArray>(pkEffect->UVs[i]);
            if (pkCUVs)
            {
                ReleaseArray(pkCUVs);
            }
        }
    }

    // recurse the subtree of this object and release other arrays
    Node* pkNode = DynamicCast<Node>(pkScene);
    if (pkNode)
    {
        for (i = 0; i < pkNode->GetQuantity(); i++)
        {
            Spatial* pkChild = pkNode->GetChild(i);
            if (pkChild)
            {
                ReleaseArrays(pkChild);
            }
        }
    }
}
//----------------------------------------------------------------------------
void Renderer::DrawPrimitive ()
{
    if (m_bAllowGlobalState)
    {
        SetGlobalState(m_pkGeometry->States);
    }

    if (m_bAllowLighting)
    {
        EnableLighting();
    }

    EnableVertices();

    if (m_bAllowNormals && m_pkGeometry->Normals)
    {
        EnableNormals();
    }

    if (m_bAllowColors && m_pkLocalEffect)
    {
        if (m_pkLocalEffect->ColorRGBAs)
        {
            EnableColorRGBAs();
        }
        else if (m_pkLocalEffect->ColorRGBs)
        {
            EnableColorRGBs();
        }
    }

    if (m_bAllowTextures)
    {
        EnableTextures();
    }

    if (m_bAllowWorldTransform)
    {
        SetWorldTransformation();
    }
    else
    {
        SetScreenTransformation();
    }

    DrawElements();

    if (m_bAllowWorldTransform)
    {
        RestoreWorldTransformation();
    }
    else
    {
        RestoreScreenTransformation();
    }

    if (m_bAllowTextures)
    {
        DisableTextures();
    }

    if (m_bAllowColors && m_pkLocalEffect)
    {
        if (m_pkLocalEffect->ColorRGBAs)
        {
            DisableColorRGBAs();
        }
        else if (m_pkLocalEffect->ColorRGBs)
        {
            DisableColorRGBs();
        }
    }

    if (m_bAllowNormals && m_pkGeometry->Normals)
    {
        DisableNormals();
    }

    DisableVertices();

    if (m_bAllowLighting)
    {
        DisableLighting();
    }
}
//----------------------------------------------------------------------------
void Renderer::DrawDeferredNoDraw ()
{
    // This function is supposed to do nothing.  Really!
}
//----------------------------------------------------------------------------
void Renderer::DrawDeferredNoSort ()
{
    // disable deferred drawing
    DrawFunction oSave = DrawDeferred;
    DrawDeferred = 0;

    for (int i = 0; i < m_iDeferredQuantity; i++)
    {
        if (m_kDeferredIsGeometry[i])
        {
            Draw((Geometry*)m_kDeferredObject[i]);
        }
        else
        {
            Draw((Node*)m_kDeferredObject[i]);
        }
    }

    // enable deferred drawing
    DrawDeferred = oSave;
}
//----------------------------------------------------------------------------
void Renderer::ReleaseResources (Spatial* pkScene)
{
    ReleaseTextures(pkScene);
    ReleaseArrays(pkScene);
}
//----------------------------------------------------------------------------
void Renderer::SetConstantCameraPosition (int, fixed* afData)
{
    Vector3x kWLocation = m_pkCamera->GetWorldLocation();
    afData[0] = kWLocation.X();
    afData[1] = kWLocation.Y();
    afData[2] = kWLocation.Z();
    afData[3] = FIXED_ONE;
}
//----------------------------------------------------------------------------
void Renderer::SetConstantCameraDirection (int, fixed* afData)
{
    Vector3x kWDVector = m_pkCamera->GetWorldDVector();
    afData[0] = kWDVector.X();
    afData[1] = kWDVector.Y();
    afData[2] = kWDVector.Z();
    afData[3] = FIXED_ZERO;
}
//----------------------------------------------------------------------------
void Renderer::SetConstantCameraUp (int, fixed* afData)
{
    Vector3x kWUVector = m_pkCamera->GetWorldUVector();
    afData[0] = kWUVector.X();
    afData[1] = kWUVector.Y();
    afData[2] = kWUVector.Z();
    afData[3] = FIXED_ZERO;
}
//----------------------------------------------------------------------------
void Renderer::SetConstantCameraRight (int, fixed* afData)
{
    Vector3x kWRVector = m_pkCamera->GetWorldRVector();
    afData[0] = kWRVector.X();
    afData[1] = kWRVector.Y();
    afData[2] = kWRVector.Z();
    afData[3] = FIXED_ZERO;
}
//----------------------------------------------------------------------------
void Renderer::SetConstantFogColor (int, fixed* afData)
{
    FogState* pkFog = StaticCast<FogState>(
        m_pkGeometry->States[GlobalState::FOG]);
    afData[0] = pkFog->Color.R();
    afData[1] = pkFog->Color.G();
    afData[2] = pkFog->Color.B();
    afData[3] = pkFog->Color.A();
}
//----------------------------------------------------------------------------
void Renderer::SetConstantFogParams (int, fixed* afData)
{
    FogState* pkFog = StaticCast<FogState>(
        m_pkGeometry->States[GlobalState::FOG]);
    afData[0] = pkFog->Start;
    afData[1] = pkFog->End;
    afData[2] = pkFog->Density;
    afData[3] = (pkFog->Enabled ? FIXED_ONE : FIXED_ZERO);
}
//----------------------------------------------------------------------------
void Renderer::SetConstantMaterialEmissive (int, fixed* afData)
{
    MaterialState* pkMaterial = StaticCast<MaterialState>(
        m_pkGeometry->States[GlobalState::MATERIAL]);
    afData[0] = pkMaterial->Emissive.R();
    afData[1] = pkMaterial->Emissive.G();
    afData[2] = pkMaterial->Emissive.B();
    afData[3] = pkMaterial->Emissive.A();
}
//----------------------------------------------------------------------------
void Renderer::SetConstantMaterialAmbient (int, fixed* afData)
{
    MaterialState* pkMaterial = StaticCast<MaterialState>(
        m_pkGeometry->States[GlobalState::MATERIAL]);
    afData[0] = pkMaterial->Ambient.R();
    afData[1] = pkMaterial->Ambient.G();
    afData[2] = pkMaterial->Ambient.B();
    afData[3] = pkMaterial->Ambient.A();
}
//----------------------------------------------------------------------------
void Renderer::SetConstantMaterialDiffuse (int, fixed* afData)
{
    MaterialState* pkMaterial = StaticCast<MaterialState>(
        m_pkGeometry->States[GlobalState::MATERIAL]);
    afData[0] = pkMaterial->Diffuse.R();
    afData[1] = pkMaterial->Diffuse.G();
    afData[2] = pkMaterial->Diffuse.B();
    afData[3] = pkMaterial->Diffuse.A();
}
//----------------------------------------------------------------------------
void Renderer::SetConstantMaterialSpecular (int, fixed* afData)
{
    MaterialState* pkMaterial = StaticCast<MaterialState>(
        m_pkGeometry->States[GlobalState::MATERIAL]);
    afData[0] = pkMaterial->Specular.R();
    afData[1] = pkMaterial->Specular.G();
    afData[2] = pkMaterial->Specular.B();
    afData[3] = pkMaterial->Specular.A();
}
//----------------------------------------------------------------------------
void Renderer::SetConstantMaterialShininess (int, fixed* afData)
{
    MaterialState* pkMaterial = StaticCast<MaterialState>(
        m_pkGeometry->States[GlobalState::MATERIAL]);
    afData[0] = pkMaterial->Shininess;
    afData[1] = FIXED_ZERO;
    afData[2] = FIXED_ZERO;
    afData[3] = FIXED_ZERO;
}
//----------------------------------------------------------------------------
void Renderer::SetConstantLightPosition (int iOption, fixed* afData)
{
    Light* pkLight = m_pkGeometry->Lights[iOption];
    assert(pkLight && (pkLight->Type == Light::LT_POINT ||
        pkLight->Type == Light::LT_SPOT));

    if (pkLight)
    {
        Vector3x kWLocation = pkLight->GetWorldLocation();
        afData[0] = kWLocation.X();
        afData[1] = kWLocation.Y();
        afData[2] = kWLocation.Z();
        afData[3] = FIXED_ONE;
    }
    else
    {
        afData[0] = FIXED_ZERO;
        afData[1] = FIXED_ZERO;
        afData[2] = FIXED_ZERO;
        afData[3] = FIXED_ONE;
    }
}
//----------------------------------------------------------------------------
void Renderer::SetConstantLightDirection (int iOption, fixed* afData)
{
    Light* pkLight = m_pkGeometry->Lights[iOption];
    assert(pkLight && (pkLight->Type == Light::LT_DIRECTIONAL ||
        pkLight->Type == Light::LT_SPOT));

    if (pkLight)
    {
        Vector3x kWDVector = pkLight->GetWorldDVector();
        afData[0] = kWDVector.X();
        afData[1] = kWDVector.Y();
        afData[2] = kWDVector.Z();
        afData[3] = FIXED_ZERO;
    }
    else
    {
        afData[0] = FIXED_ZERO;
        afData[1] = FIXED_ZERO;
        afData[2] = FIXED_ZERO;
        afData[3] = FIXED_ONE;
    }
}
//----------------------------------------------------------------------------
void Renderer::SetConstantLightAmbient (int iOption, fixed* afData)
{
    Light* pkLight = m_pkGeometry->Lights[iOption];
    assert(pkLight);

    if (pkLight && pkLight->On)
    {
        afData[0] = pkLight->Ambient.R();
        afData[1] = pkLight->Ambient.G();
        afData[2] = pkLight->Ambient.B();
        afData[3] = pkLight->Ambient.A();
    }
    else
    {
        afData[0] = FIXED_ZERO;
        afData[1] = FIXED_ZERO;
        afData[2] = FIXED_ZERO;
        afData[3] = FIXED_ONE;
    }
 }
//----------------------------------------------------------------------------
void Renderer::SetConstantLightDiffuse (int iOption, fixed* afData)
{
    Light* pkLight = m_pkGeometry->Lights[iOption];
    assert(pkLight);

    if (pkLight && pkLight->On)
    {
        afData[0] = pkLight->Diffuse.R();
        afData[1] = pkLight->Diffuse.G();
        afData[2] = pkLight->Diffuse.B();
        afData[3] = pkLight->Diffuse.A();
    }
    else
    {
        afData[0] = FIXED_ZERO;
        afData[1] = FIXED_ZERO;
        afData[2] = FIXED_ZERO;
        afData[3] = FIXED_ONE;
    }
}
//----------------------------------------------------------------------------
void Renderer::SetConstantLightSpecular (int iOption, fixed* afData)
{
    Light* pkLight = m_pkGeometry->Lights[iOption];
    assert(pkLight);

    if (pkLight && pkLight->On)
    {
        afData[0] = pkLight->Specular.R();
        afData[1] = pkLight->Specular.G();
        afData[2] = pkLight->Specular.B();
        afData[3] = pkLight->Specular.A();
    }
    else
    {
        afData[0] = FIXED_ZERO;
        afData[1] = FIXED_ZERO;
        afData[2] = FIXED_ZERO;
        afData[3] = FIXED_ONE;
    }
}
//----------------------------------------------------------------------------
void Renderer::SetConstantLightSpotCutoff (int iOption, fixed* afData)
{
    Light* pkLight = m_pkGeometry->Lights[iOption];
    assert(pkLight && pkLight->Type == Light::LT_SPOT);

    if (pkLight)
    {
        afData[0] = pkLight->Angle;
        afData[1] = Mathx::Cos(afData[0]);
        afData[2] = Mathx::Sin(afData[0]);
        afData[3] = pkLight->Exponent;
    }
    else
    {
        afData[0] = FIXED_ZERO;
        afData[1] = FIXED_ONE;
        afData[2] = FIXED_ZERO;
        afData[3] = FIXED_ONE;
    }
}
//----------------------------------------------------------------------------
void Renderer::SetConstantLightAttenParams (int iOption, fixed* afData)
{
    Light* pkLight = m_pkGeometry->Lights[iOption];
    assert(pkLight);

    if (pkLight)
    {
        afData[0] = pkLight->Constant;
        afData[1] = pkLight->Linear;
        afData[2] = pkLight->Quadratic;
        afData[3] = pkLight->Intensity;
    }
    else
    {
        afData[0] = FIXED_ONE;
        afData[1] = FIXED_ZERO;
        afData[2] = FIXED_ZERO;
        afData[3] = FIXED_ZERO;
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// offscreen buffer support
//----------------------------------------------------------------------------
bool Renderer::BeginOffscreen (Texture* pkTarget)
{
    if (m_pkTarget || !pkTarget)
    {
        return false;
    }

    m_pkTarget = pkTarget;
    if (m_pkTarget->m_iOffscreenIndex == -1)
    {
        if (!CreateOffscreenBuffer())
        {
            m_pkTarget = 0;
            return false;
        }
    }

    PBuffer* pkBuffer = m_kPBuffer[m_pkTarget->m_iOffscreenIndex];
    assert(pkBuffer);
    pkBuffer->Release();
    pkBuffer->Enable();
    return true;
}
//----------------------------------------------------------------------------
void Renderer::EndOffscreen ()
{
    if (m_pkTarget)
    {
        PBuffer* pkBuffer = m_kPBuffer[m_pkTarget->m_iOffscreenIndex];
        assert(pkBuffer);

        if (pkBuffer->GetBufferParams().TextureTarget ==
            BufferParams::BP_TEXTURE_TARGET_NONE)
        {
            // The derived-class renderer does not support render-to-texture,
            // so a copy from pbuffer to system memory must be used.
            pkBuffer->CopyToTarget(true);
        }

        pkBuffer->Disable();
        pkBuffer->Bind();
        m_pkTarget = 0;
    }
}
//----------------------------------------------------------------------------
bool Renderer::SaveOffscreen ()
{
    if (m_pkTarget && m_pkTarget->m_iOffscreenIndex >= 0)
    {
        PBuffer* pkBuffer = m_kPBuffer[m_pkTarget->m_iOffscreenIndex];
        assert(pkBuffer);
        pkBuffer->CopyToTarget(false);
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
bool Renderer::DeleteOffscreen (Texture* pkTarget)
{
    if (pkTarget && pkTarget->m_iOffscreenIndex >= 0)
    {
        Texture* pkSaveTarget = m_pkTarget;
        m_pkTarget = pkTarget;
        DestroyOffscreenBuffer();
        m_pkTarget = pkSaveTarget;
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
void Renderer::DeleteAllOffscreen ()
{
    for (int i = 0; i < m_kPBuffer.GetQuantity(); i++)
    {
        PBuffer* pkBuffer = m_kPBuffer[i];
        if (pkBuffer)
        {
            Texture* pkSaveTarget = m_pkTarget;
            m_pkTarget = pkBuffer->GetTarget();
            assert( m_pkTarget->m_iOffscreenIndex == i );
            DestroyOffscreenBuffer();
            m_pkTarget = pkSaveTarget;
        }
    }
}
//----------------------------------------------------------------------------
bool Renderer::CreateOffscreenBuffer ()
{
    // The texture must have an image associated with it so that the pbuffer
    // sizes are set from this image.  This image will also be used to copy
    // to from the pbuffer.
    Image* pkImage = m_pkTarget->GetImage();
    if (!pkImage)
    {
        return false;
    }

    // The image must be RGBA8888 for now.  TO DO:  Consider changing
    // this constraint later.
    if (pkImage->GetFormat() != Image::IT_RGBA8888)
    {
        return false;
    }

    int iIndex;
    for (iIndex = 0; iIndex < m_kPBuffer.GetQuantity(); iIndex++)
    {
        if (m_kPBuffer[iIndex] == 0)
        {
            break;
        }
    }

    if (iIndex == m_kPBuffer.GetQuantity())
    {
        BufferParams kBufferParams;
        kBufferParams.Buffering = BufferParams::BP_BUFFERED_DOUBLE;

        if (m_pkTarget->Mipmap == Texture::MM_NEAREST
        ||  m_pkTarget->Mipmap == Texture::MM_LINEAR)
        {
            kBufferParams.TextureTarget =
                BufferParams::BP_TEXTURE_TARGET_2D_MIPMAP;
        }
        else
        {
            kBufferParams.TextureTarget =
                BufferParams::BP_TEXTURE_TARGET_2D;
        }

        PBuffer* pkBuffer = PBuffer::Create(kBufferParams,pkImage->GetWidth(),
            pkImage->GetHeight(),this);
        if (!pkBuffer)
        {
            return false;
        }

        m_kPBuffer.Append(pkBuffer);
    }

    m_pkTarget->m_iOffscreenIndex = iIndex;
    return true;
}
//----------------------------------------------------------------------------
void Renderer::DestroyOffscreenBuffer ()
{
    PBuffer* pkBuffer = m_kPBuffer[m_pkTarget->m_iOffscreenIndex];
    assert(pkBuffer);
    PBuffer::Destroy(pkBuffer);

    m_kPBuffer[m_pkTarget->m_iOffscreenIndex] = 0;
    m_pkTarget->m_iOffscreenIndex = -1;
}
//----------------------------------------------------------------------------
