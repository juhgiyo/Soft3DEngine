///////////////////////////////////////////////////////////
//                                                       //
//              WgColorRGBArray.h                        //
//                                                       //
//  - Interface for Color RGB Array class                //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_COLORRGBARRAY_H__
#define __WG_COLORRGBARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTSharedArray.h"
#include "WgColorRGB.h"

namespace WGSoft3D
{
typedef TSharedArray<ColorRGB> ColorRGBArray;
typedef Pointer<ColorRGBArray> ColorRGBArrayPtr;
}

#endif

