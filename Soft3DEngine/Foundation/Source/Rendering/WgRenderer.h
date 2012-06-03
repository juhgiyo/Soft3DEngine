///////////////////////////////////////////////////////////
//                                                       //
//                    WgRenderer.h                       //
//                                                       //
//  - Interface for Renderer class                       //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_RENDERER_H__
#define __WG_RENDERER_H__

#include "WgFoundationLIB.h"
#include "WgBufferParams.h"
#include "WgColorRGB.h"
#include "WgColorRGBA.h"
#include "WgAlphaState.h"
#include "WgCullState.h"
#include "WgDitherState.h"
#include "WgFogState.h"
#include "WgMaterialState.h"
#include "WgPolygonOffsetState.h"
#include "WgShadeState.h"
//#include "WgWireframeState.h"
#include "WgZBufferState.h"
#include "WgStencilState.h"
#include "WgShaderConstant.h"

namespace WGSoft3D
{

template <class T> class TSharedArray;
typedef TSharedArray<Vector2x> Vector2xArray;

template <class T> class TCachedArray;
typedef TCachedArray<ColorRGBA> CachedColorRGBAArray;
typedef TCachedArray<ColorRGB> CachedColorRGBArray;
typedef TCachedArray<short> CachedShortArray;
typedef TCachedArray<Vector2x> CachedVector2xArray;
typedef TCachedArray<Vector3x> CachedVector3xArray;

class Camera;
class Effect;
class Geometry;
class Light;
class Node;
class PBuffer;
class PixelShader;
class ScreenPolygon;
class Shader;
class Spatial;
class Texture;
class VertexShader;

class WG3D_FOUNDATION_ITEM Renderer
{
public:
    // Abstract API for renderers.  Each graphics API must implement this
    // layer.
    virtual ~Renderer ();

    // Only one type of renderer can exist in an application.  The active
    // renderer sets the ms_eType data member to the appropriate enumeration.
    enum
    {
        RT_OPENGL,
        RT_DIRECT3D,
        RT_QUANTITY
    };
    static int GetType ();

    // Make this renderer context the active one.
    //virtual void Activate ();
    //virtual bool IsActive () const;

    // camera access and support
    void SetCamera (Camera* pkCamera);
    Camera* GetCamera () const;

    // framebuffer parameters
    const BufferParams& GetBufferParams () const;

    // window parameters
    int GetWidth () const;
    int GetHeight () const;
    virtual void Resize (int iWidth, int iHeight);

    // background color access
    virtual void SetBackgroundColor (const ColorRGBA& rkColor);
    const ColorRGBA& GetBackgroundColor () const;

    // pre- and postdraw semantics
    //virtual bool BeginScene ();
    //virtual void EndScene ();

    // full window buffer operations
    virtual void ClearBackBuffer () = 0;
    virtual void ClearZBuffer () = 0;
    virtual void ClearStencilBuffer () = 0;
    virtual void ClearBuffers () = 0;
    //virtual void DisplayBackBuffer () = 0;

    // clear the buffer in the specified subwindow
    virtual void ClearBackBuffer (int iXPos, int iYPos, int iWidth,
        int iHeight) = 0;
    virtual void ClearZBuffer (int iXPos, int iYPos, int iWidth,
        int iHeight) = 0;
    virtual void ClearStencilBuffer (int iXPos, int iYPos, int iWidth,
        int iHeight) = 0;
    virtual void ClearBuffers (int iXPos, int iYPos, int iWidth,
        int iHeight) = 0;

    // object drawing
    void DrawScene (Node* pkScene, bool bNoCull=false);
    virtual void Draw (ScreenPolygon* pkPolygon);

    // 2D drawing
    //virtual void Draw (const unsigned char* aucBuffer) = 0;

    // Point size, line width, and line stipple.  These translate nicely to
    // OpenGL calls.  The point size is supported by Direct3D.  However, to
    // draw thicker lines or stippled lines, a separate interface in Direct3D
    // (ID3DXLine) must be used.  Until code is added to use this interface,
    // the Direct3D renderer ignores the SetLineWidth and SetLineStipple
    // function calls.  Line stippling is disabled when either of "repeat" or
    // "pattern" is zero.
    virtual void SetPointSize (fixed fSize);
    fixed GetPointSize () const;
    virtual void SetLineWidth (fixed fWidth);
    fixed GetLineWidth () const;
    virtual void SetLineStipple (int iRepeat, unsigned short usPattern);
    int GetLineStippleRepeat () const;
    unsigned short GetLineStipplePattern () const;

    // Support for rendering to an offscreen texture.  If any offscreen
    // buffers are created, the application is responsible for calling
    // DeleteOffscreen or DeleteAllOffscreen to delete the buffers and any
    // associated renderer resources.
    bool BeginOffscreen (Texture* pkTarget);
    void EndOffscreen ();
    bool SaveOffscreen ();
    bool DeleteOffscreen (Texture* pkTarget);
    void DeleteAllOffscreen ();

    int GetMaxLights () const;
    int GetMaxTextures () const;
    int GetMaxStencilIndices () const;

    // management of texture resources
    virtual void ReleaseTexture (Texture* pkTexture) = 0;
    void ReleaseTextures (Spatial* pkScene);

    // management of array resources
    virtual void ReleaseArray (CachedColorRGBAArray* pkArray) = 0;
    virtual void ReleaseArray (CachedColorRGBArray* pkArray) = 0;
    virtual void ReleaseArray (CachedShortArray* pkArray) = 0;
    virtual void ReleaseArray (CachedVector2xArray* pkArray) = 0;
    virtual void ReleaseArray (CachedVector3xArray* pkArray) = 0;
    
	void ReleaseArrays (Spatial* pkScene);

    // release textures, arrays, and shaders
    void ReleaseResources (Spatial* pkScene);

    // deferred drawing (for render state sorting)
    typedef void (Renderer::*DrawFunction)();
    DrawFunction DrawDeferred;

    // no drawing (useful for profiling scene graph overhead)
    void DrawDeferredNoDraw ();

    // draw all objects without sorting
    void DrawDeferredNoSort ();

protected:
    // abstract base class
    Renderer (const BufferParams& rkBufferParams, int iWidth, int iHeight);

    // global render state management
    void SetGlobalState (GlobalStatePtr aspkState[GlobalState::MAX_STATE]);
    virtual void SetAlphaState (AlphaState* pkState) = 0;
    virtual void SetCullState (CullState* pkState) = 0;
    virtual void SetDitherState (DitherState* pkState) = 0;
    virtual void SetFogState (FogState* pkState) = 0;
    virtual void SetMaterialState (MaterialState* pkState) = 0;
    virtual void SetPolygonOffsetState (PolygonOffsetState* pkState) = 0;
    virtual void SetShadeState (ShadeState* pkState) = 0;
//    virtual void SetWireframeState (WireframeState* pkState) = 0;
    virtual void SetZBufferState (ZBufferState* pkState) = 0;

    // light management
    enum
    {
        EL_AMBIENT = 1,
        EL_DIFFUSE = 2,
        EL_SPECULAR = 4,
        EL_ALL = 7
    };

    virtual void EnableLighting (int eEnable = EL_ALL) = 0;
    virtual void DisableLighting () = 0;
    virtual void EnableLight (int eEnable, int i, const Light* pkLight) = 0;
    virtual void DisableLight (int i, const Light* pkLight) = 0;

    // texture management
    void EnableTextures ();
    void DisableTextures ();
    virtual void EnableTexture (int iUnit, int i, Effect* pkEffect) = 0;
    virtual void DisableTexture (int iUnit, int i, Effect* pkEffect) = 0;
    virtual void SetActiveTextureUnit (int iUnit) = 0;

    // offscreen buffer management
    virtual bool CreateOffscreenBuffer ();
    virtual void DestroyOffscreenBuffer ();

    // transformations
    virtual void SetWorldTransformation () = 0;
    virtual void RestoreWorldTransformation () = 0;
    virtual void SetScreenTransformation () = 0;
    virtual void RestoreScreenTransformation () = 0;

    // array management
    virtual void EnableVertices () = 0;
    virtual void DisableVertices () = 0;
    virtual void EnableNormals () = 0;
    virtual void DisableNormals () = 0;
    virtual void EnableColorRGBAs () = 0;
    virtual void DisableColorRGBAs () = 0;
    virtual void EnableColorRGBs () = 0;
    virtual void DisableColorRGBs () = 0;
    virtual void EnableUVs (int i, Effect* pkEffect) = 0;
    virtual void DisableUVs (Vector2xArray* pkUVs) = 0;
    virtual void DrawElements () = 0;

    virtual void SetConstantTransformM (int iOption, fixed* afData) = 0;
    virtual void SetConstantTransformP (int iOption, fixed* afData) = 0;
    virtual void SetConstantTransformMV (int iOption, fixed* afData) = 0;
    virtual void SetConstantTransformMVP (int iOption, fixed* afData) = 0;
    void SetConstantCameraPosition (int iOption, fixed* afData);
    void SetConstantCameraDirection (int iOption, fixed* afData);
    void SetConstantCameraUp (int iOption, fixed* afData);
    void SetConstantCameraRight (int iOption, fixed* afData);
    void SetConstantFogColor (int iOption, fixed* afData);
    void SetConstantFogParams (int iOption, fixed* afData);
    void SetConstantMaterialEmissive (int iOption, fixed* afData);
    void SetConstantMaterialAmbient (int iOption, fixed* afData);
    void SetConstantMaterialDiffuse (int iOption, fixed* afData);
    void SetConstantMaterialSpecular (int iOption, fixed* afData);
    void SetConstantMaterialShininess (int iOption, fixed* afData);
    void SetConstantLightPosition (int iOption, fixed* afData);
    void SetConstantLightDirection (int iOption, fixed* afData);
    void SetConstantLightAmbient (int iOption, fixed* afData);
    void SetConstantLightDiffuse (int iOption, fixed* afData);
    void SetConstantLightSpecular (int iOption, fixed* afData);
    void SetConstantLightSpotCutoff (int iOption, fixed* afData);
    void SetConstantLightAttenParams (int iOption, fixed* afData);

    typedef void (Renderer::*SetConstantFunction)(int,fixed*);
    static SetConstantFunction ms_aoSCFunction[ShaderConstant::SC_QUANTITY];

    // frame buffer parameters
    BufferParams m_kBufferParams;

    // window parameters
    int m_iWidth, m_iHeight;
    ColorRGBA m_kBackgroundColor;

    // camera for establishing view frustum
    Camera* m_pkCamera;

    // values set by derived renderer
    int m_iMaxLights;
    int m_iMaxTextures;
    int m_iMaxStencilIndices;

    // current object and special effects for drawing
    Node* m_pkNode;
    Geometry* m_pkGeometry;
    Effect* m_pkLocalEffect;
    Effect* m_pkGlobalEffect;

    // Fine-tuned control of drawing.  Default 'true' for all flags.
    bool m_bAllowGlobalState;
    bool m_bAllowAlphaState;
    bool m_bAllowCullState;
    bool m_bAllowDitherState;
    bool m_bAllowFogState;
    bool m_bAllowMaterialState;
    bool m_bAllowPolygonOffsetState;
    bool m_bAllowShadeState;
    //bool m_bAllowWireframeState;
    bool m_bAllowZBufferState;
    bool m_bAllowLighting;
    bool m_bAllowNormals;
    bool m_bAllowColors;
    bool m_bAllowTextures;
    bool m_bAllowWorldTransform;

    // support for mirror effects (default 'false')
    bool m_bReverseCullFace;

    // toggle for fullscreen/window mode
    bool m_bFullscreen;

    // current font for text drawing
    int m_iFontID;

    // deferred drawing
    int m_iDeferredQuantity;
    TArray<Spatial*> m_kDeferredObject;
    TArray<bool> m_kDeferredIsGeometry;

    // point size, line width, and line stipple
    fixed m_fPointSize;  // default = 1
    fixed m_fLineWidth;  // default = 1
    int m_iLineStippleRepeat;  // default = 0 (disabled)
    unsigned short m_usLineStipplePattern;  // default = 0 (disabled)

// internal use
public:
    // camera access and support
    virtual void OnFrustumChange () = 0;
    virtual void OnViewPortChange () = 0;
    virtual void OnFrameChange () = 0;

    // object drawing
    void Draw (Node* pkNode);
    void Draw (Geometry* pkGeometry);

    // drawing functions
    void DrawPrimitive ();
    virtual void DrawBumpMap () = 0;
    virtual void DrawEnvironmentMap () = 0;
    virtual void DrawGlossMap () = 0;
    virtual void DrawPlanarShadow () = 0;
    virtual void DrawProjectedTexture () = 0;

    // offscreen buffers
    Texture* GetTarget ();

protected:
    // Support for rendering to an offscreen texture.
    Texture* m_pkTarget;
    TArray<PBuffer*> m_kPBuffer;

    // One of the enumerations RT_OPENGL, RT_DIRECT3D, etc.  Only one type
    // of renderer may exist in an application.  The derived-class renderer
    // sets this value on creation.
    static int ms_eType;
};

#include "WgRenderer.inl"

}

#endif
