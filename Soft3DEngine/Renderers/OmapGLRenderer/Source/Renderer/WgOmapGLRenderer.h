///////////////////////////////////////////////////////////
//                                                       //
//                    WgOmapGLRenderer.h                 //
//                                                       //
//  - Interface for OmapGLRenderer class                 //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#ifndef __WG_OMAPGLRENDERER_H__
#define __WG_OMAPGLRENDERER_H__

#include "WgOmapGLRendererLIB.h"
#include "WgRenderer.h"

#include "gles/egl.h"
#include "gles/gl.h"

#include "WgLight.h"
#include "WgTexture.h"
#include "WgGeometry.h"

namespace WGSoft3D
{

class WG3D_RENDERER_ITEM OmapGLRenderer : public Renderer
{
public:
    // driver information
    static const char* GetVendor ();
    static const char* GetRenderer ();
    static const char* GetVersion ();
    static const char* GetGluVersion ();
    static const char* GetExtensions ();

    // Test if a specified extension is supported.  If you need to test for
    // multiple extensions, the function must be called for each extension.
    // The extensions could vary per rendering context, so check for
    // extensions immediately after setting the context.
    static bool ExtensionSupported (const char* acExt);

    // Abstract base class.  The InitializeState call is made by derived
    // class constructors after an OpenGL context is created.
    virtual ~OmapGLRenderer();
    void InitializeState ();

    virtual void Activate ();

    virtual void SetBackgroundColor (const ColorRGBA& rkColor);

    // full window buffer operations
    virtual void ClearBackBuffer ();
    virtual void ClearZBuffer ();
    virtual void ClearStencilBuffer ();
    virtual void ClearBuffers ();
	virtual void DisplayBackBuffer () = 0;

    // clear the buffer in the specified subwindow
    virtual void ClearBackBuffer (int iXPos, int iYPos, int iWidth,
        int iHeight);
    virtual void ClearZBuffer (int iXPos, int iYPos, int iWidth,
        int iHeight);
    virtual void ClearStencilBuffer (int iXPos, int iYPos, int iWidth,
        int iHeight);
    virtual void ClearBuffers (int iXPos, int iYPos, int iWidth,
        int iHeight);


    // point size, line width, and line stipple
    virtual void SetPointSize (fixed fSize);
    virtual void SetLineWidth (fixed fWidth);
    virtual void SetLineStipple (int iRepeat, unsigned short usPattern);

    // management of texture resources
    virtual void ReleaseTexture (Texture* pkTexture);

    // management of array resources
    virtual void ReleaseArray (CachedColorRGBAArray* pkArray);
    virtual void ReleaseArray (CachedColorRGBArray* pkArray);
    virtual void ReleaseArray (CachedShortArray* pkArray);
    virtual void ReleaseArray (CachedVector2xArray* pkArray);
    virtual void ReleaseArray (CachedVector3xArray* pkArray);


protected:
    // construction
    OmapGLRenderer (const BufferParams& rkBufferParams, int iWidth,
        int iHeight);

    // camera updates
    virtual void OnFrustumChange ();
    virtual void OnViewPortChange ();
    virtual void OnFrameChange ();

    // context handling
    virtual void SaveContext () = 0;
    virtual void RestoreContext () = 0;

    // model-to-world transformation handling
    void SetWorldMatrix ();
    fixed m_afWorldMatrix[16];

    // global render state management
    virtual void SetAlphaState (AlphaState* pkState);
    virtual void SetCullState (CullState* pkState);
    virtual void SetDitherState (DitherState* pkState);
    virtual void SetFogState (FogState* pkState);
    virtual void SetMaterialState (MaterialState* pkState);
    virtual void SetPolygonOffsetState (PolygonOffsetState* pkState);
    virtual void SetShadeState (ShadeState* pkState);
    virtual void SetZBufferState (ZBufferState* pkState);

    // light management
    virtual void EnableLighting (int eEnable = EL_ALL);
    virtual void DisableLighting ();
    virtual void EnableLight (int eEnable, int i, const Light* pkLight);
    virtual void DisableLight (int i, const Light* pkLight);

    // texture management
    virtual void EnableTexture (int iUnit, int i, Effect* pkEffect);
    virtual void DisableTexture (int iUnit, int i, Effect* pkEffect);
    virtual void SetActiveTextureUnit (int iUnit);

    // transformations
    virtual void SetWorldTransformation ();
    virtual void RestoreWorldTransformation ();
    virtual void SetScreenTransformation ();
    virtual void RestoreScreenTransformation ();

    // array management
    virtual void EnableVertices ();
    virtual void DisableVertices ();
    virtual void EnableNormals ();
    virtual void DisableNormals ();
    virtual void EnableColorRGBAs ();
    virtual void DisableColorRGBAs ();
    virtual void EnableColorRGBs ();
    virtual void DisableColorRGBs ();
    virtual void EnableUVs (int i, Effect* pkEffect);
    virtual void DisableUVs (Vector2xArray* pkUVs);
    virtual void DrawElements ();

    // shader management
    virtual void SetConstantTransformM (int iOption, fixed* afData);
    virtual void SetConstantTransformP (int iOption, fixed* afData);
    virtual void SetConstantTransformMV (int iOption, fixed* afData);
    virtual void SetConstantTransformMVP (int iOption, fixed* afData);
    void GetTransform (Matrix4x& rkMat, int iOption, fixed* afData);

    // effects
    virtual void DrawBumpMap ();
    virtual void DrawEnvironmentMap ();
    virtual void DrawGlossMap ();
    virtual void DrawPlanarShadow ();
    virtual void DrawProjectedTexture ();

    // display list base indices for fonts/characters
    class DisplayListInfo
    {
    public:
        int Quantity;  // number of display lists, input to glGenLists
        int Start;     // start index, output from glGenLists
        int Base;      // base index for glListBase
    };
    TArray<DisplayListInfo> m_kDLInfo;

    // *** maps from Soft3D enums to OpenGL enums ***

    // object types
    static GLenum ms_aeObjectType[Geometry::GT_MAX_QUANTITY];
    
    // global render state
    static GLenum ms_aeAlphaSrcBlend[AlphaState::SBF_QUANTITY];
    static GLenum ms_aeAlphaDstBlend[AlphaState::DBF_QUANTITY];
    static GLenum ms_aeAlphaTest[AlphaState::TF_QUANTITY];
    static GLenum ms_aeFrontFace[CullState::FT_QUANTITY];
    static GLenum ms_aeCullFace[CullState::CT_QUANTITY];
    static GLenum ms_aeFogDensity[FogState::DF_QUANTITY];
    static GLenum ms_aeFogApply[FogState::AF_QUANTITY];
    static GLenum ms_aeShade[ShadeState::SM_QUANTITY];
    static GLenum ms_aeZBufferCompare[ZBufferState::CF_QUANTITY];

    // texture effects
    static GLenum ms_aeTextureCorrection[Texture::CM_QUANTITY];
    static GLenum ms_aeTextureApply[Texture::AM_QUANTITY];
    static GLenum ms_aeTextureFilter[Texture::FM_QUANTITY];
    static GLenum ms_aeTextureCombineFunc[Texture::ACF_QUANTITY];
    static GLenum ms_aeTextureCombineSrc[Texture::ACS_QUANTITY];
    static GLenum ms_aeTextureCombineOperand[Texture::ACO_QUANTITY];
    static GLint  ms_aiTextureCombineScale[Texture::ACSC_QUANTITY];
    static GLenum ms_aeTextureMipmap[Texture::MM_QUANTITY];

    // images
    static GLenum ms_aeImageComponents[Image::IT_QUANTITY];
    static GLenum ms_aeImageFormats[Image::IT_QUANTITY];
};
#include "WgOmapGLRenderer.inl"
}

#endif
