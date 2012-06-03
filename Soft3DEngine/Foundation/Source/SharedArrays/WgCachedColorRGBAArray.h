///////////////////////////////////////////////////////////
//                                                       //
//              WgCachedColorRGBAArray.h                 //
//                                                       //
//  - Interface for Cached Color RGBA Array class        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_CACHEDCOLORRGBAARRAY_H__
#define __WG_CACHEDCOLORRGBAARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTCachedArray.h"
#include "WgColorRGBAArray.h"

namespace WGSoft3D
{
typedef TCachedArray<ColorRGBA> CachedColorRGBAArray;
typedef Pointer<CachedColorRGBAArray> CachedColorRGBAArrayPtr;
}

#endif

