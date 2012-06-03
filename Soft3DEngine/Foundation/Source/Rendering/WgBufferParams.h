///////////////////////////////////////////////////////////
//                                                       //
//                    WgBufferParams.h                   //
//                                                       //
//  - Interface for Buffer Pamrameter class              //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_BUFFERPARAMS_H__
#define __WG_BUFFERPARAMS_H__

#include "WgFoundationLIB.h"
#include "WgSystem.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM BufferParams
{
public:
    enum WG3D_FOUNDATION_ITEM FormatType
    {
        BP_FORMAT_RGBA
    };

    enum WG3D_FOUNDATION_ITEM DepthType
    {
        BP_DEPTH_NONE,
        BP_DEPTH_16,
        BP_DEPTH_24,
        BP_DEPTH_32
    };

    enum WG3D_FOUNDATION_ITEM StencilType
    {
        BP_STENCIL_NONE,
        BP_STENCIL_8
    };

    enum WG3D_FOUNDATION_ITEM BufferedType
    {
        BP_BUFFERED_SINGLE,
        BP_BUFFERED_DOUBLE
    };

    enum WG3D_FOUNDATION_ITEM SamplingType
    {
        BP_SAMPLING_NONE,
        BP_SAMPLING_2,
        BP_SAMPLING_4
    };

    enum WG3D_FOUNDATION_ITEM TextureTargetType
    {
        BP_TEXTURE_TARGET_NONE,
        BP_TEXTURE_TARGET_2D,
        BP_TEXTURE_TARGET_2D_MIPMAP,
        BP_TEXTURE_TARGET_CUBE,
        BP_TEXTURE_TARGET_CUBE_MIPMAP
    };

    FormatType Format;
    DepthType Depth;
    StencilType Stencil;
    BufferedType Buffering;
    SamplingType Sampling;
    TextureTargetType TextureTarget;

    BufferParams ()
    {
        Format = BP_FORMAT_RGBA;
        Depth = BP_DEPTH_16;
        Stencil = BP_STENCIL_8;
        Buffering = BP_BUFFERED_DOUBLE;
        Sampling = BP_SAMPLING_NONE;
        TextureTarget = BP_TEXTURE_TARGET_NONE;
    }
};

}

#endif

