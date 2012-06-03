///////////////////////////////////////////////////////////
//                                                       //
//                    WgTexture.h                        //
//                                                       //
//  - Interface for Texture class                        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_TEXTURE_H__
#define __WG_TEXTURE_H__

#include "WgFoundationLIB.h"
#include "WgBindInfo.h"
#include "WgColorRGBA.h"
#include "WgImage.h"
//#include "WgVector2Array.h"

namespace WGSoft3D
{

class Renderer;

class WG3D_FOUNDATION_ITEM Texture : public Object
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    Texture (Image* pkImage = 0);
    virtual ~Texture ();

    enum CorrectionMode
    {
        CM_AFFINE,
        CM_PERSPECTIVE,
        CM_QUANTITY
    };

    enum ApplyMode
    {
        AM_REPLACE,
        AM_DECAL,
        AM_MODULATE,
        AM_BLEND,
        AM_ADD,
        AM_COMBINE,
        AM_QUANTITY
    };

    enum ApplyCombineFunction
    {
        ACF_REPLACE,
        ACF_MODULATE,
        ACF_ADD,
        ACF_ADD_SIGNED,
        ACF_SUBTRACT,
        ACF_INTERPOLATE,
        ACF_DOT3_RGB,
        ACF_DOT3_RGBA,
        ACF_QUANTITY
    };

    enum ApplyCombineSrc
    {
        ACS_TEXTURE,
        ACS_PRIMARY_COLOR,
        ACS_CONSTANT,
        ACS_PREVIOUS,
        ACS_QUANTITY
    };

    enum ApplyCombineOperand
    {
        ACO_SRC_COLOR,
        ACO_ONE_MINUS_SRC_COLOR,
        ACO_SRC_ALPHA,
        ACO_ONE_MINUS_SRC_ALPHA,
        ACO_QUANTITY
    };

    enum ApplyCombineScale
    {
        ACSC_ONE,
        ACSC_TWO,
        ACSC_FOUR,
        ACSC_QUANTITY
    };

    enum WrapMode
    {
        WM_CLAMP,
        WM_REPEAT,
        WM_CLAMP_BORDER,
        WM_CLAMP_EDGE,
        WM_QUANTITY
    };

    enum FilterMode
    {
        FM_NEAREST,
        FM_LINEAR,
        FM_QUANTITY
    };

    enum MipmapMode
    {
        MM_NEAREST,
        MM_LINEAR,
        MM_NEAREST_NEAREST,
        MM_NEAREST_LINEAR,
        MM_LINEAR_NEAREST,
        MM_LINEAR_LINEAR,
        MM_QUANTITY
    };

    enum TexGenMode
    {
        TG_NONE,
        TG_ENVIRONMENT_MAP,
        TG_PROJECTED_TEXTURE,
        TG_QUANTITY
    };

    // texture image
    void SetImage (ImagePtr spkImage);
    ImagePtr GetImage () const;
	void DeleteImageRawData();
	
    // If you change any of the texture state information, call this function
    // to make sure that the texture is unbound from the renderer to release
    // resources, and to allow the modified texture to be rebound to the
    // renderer.  The SetImage(...) function calls this automatically, but
    // you are responsible for calling Changed() when other state information
    // changes.
    void Changed ();

    // texture state information
    CorrectionMode Correction;         // default: CM_PERSPECTIVE
    ApplyMode Apply;              // default: AM_REPLACE
    WrapMode CoordU;             // default: WM_CLAMP_EDGE
    WrapMode CoordV;             // default: WM_CLAMP_EDGE
    FilterMode Filter;             // default: FM_LINEAR
    MipmapMode Mipmap;             // default: MM_LINEAR_LINEAR
    TexGenMode Texgen;             // default: TG_NONE
    ColorRGBA BlendColor;   // default: ColorRGBA(0,0,0,0)
    ColorRGBA BorderColor;  // default: ColorRGBA::INVALID

    // the following are only relevant if the apply mode is AM_COMBINE
    ApplyCombineFunction CombineFuncRGB;     // default: ACF_REPLACE
    ApplyCombineFunction CombineFuncAlpha;   // default: ACF_REPLACE
    ApplyCombineSrc CombineSrc0RGB;     // default: ACS_TEXTURE
    ApplyCombineSrc CombineSrc1RGB;     // default: ACS_TEXTURE
    ApplyCombineSrc CombineSrc2RGB;     // default: ACS_TEXTURE
    ApplyCombineSrc CombineSrc0Alpha;   // default: ACS_TEXTURE
    ApplyCombineSrc CombineSrc1Alpha;   // default: ACS_TEXTURE
    ApplyCombineSrc CombineSrc2Alpha;   // default: ACS_TEXTURE
    ApplyCombineOperand CombineOp0RGB;      // default: ACO_SRC_COLOR
    ApplyCombineOperand CombineOp1RGB;      // default: ACO_SRC_COLOR
    ApplyCombineOperand CombineOp2RGB;      // default: ACO_SRC_COLOR
    ApplyCombineOperand CombineOp0Alpha;    // default: ACO_SRC_COLOR
    ApplyCombineOperand CombineOp1Alpha;    // default: ACO_SRC_COLOR
    ApplyCombineOperand CombineOp2Alpha;    // default: ACO_SRC_COLOR
    ApplyCombineScale CombineScaleRGB;    // default: ACSC_ONE
    ApplyCombineScale CombineScaleAlpha;  // default: ACSC_ONE

protected:
    // texture image
    ImagePtr m_spkImage;

// internal use
public:
    // store renderer-specific information for binding/unbinding textures
    BindInfoArray BIArray;

    // This is used as an index into an array of offscreen buffers that are
    // specific to the renderer's platform.  The default value is -1,
    // indicating that the texture is not associated with an offscreen buffer.
    int m_iOffscreenIndex;
};

typedef Pointer<Texture> TexturePtr;
#include "WgTexture.inl"

}

#endif

