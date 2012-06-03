///////////////////////////////////////////////////////////
//                                                       //
//              WgCachedColorRGBArray.h                  //
//                                                       //
//  - Interface for Cached Color RGB Array class         //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_CACHEDCOLORRGBARRAY_H__
#define __WG_CACHEDCOLORRGBARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTCachedArray.h"
#include "WgColorRGBArray.h"

namespace WGSoft3D
{
typedef TCachedArray<ColorRGB> CachedColorRGBArray;
typedef Pointer<CachedColorRGBArray> CachedColorRGBArrayPtr;

}

#endif

