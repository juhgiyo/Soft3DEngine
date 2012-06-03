///////////////////////////////////////////////////////////
//                                                       //
//              WgColorRGBAArray.h                       //
//                                                       //
//  - Interface for Color RGBA Array class               //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_COLORRGBAARRAY_H__
#define __WG_COLORRGBAARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTSharedArray.h"
#include "WgColorRGBA.h"

namespace WGSoft3D
{
typedef TSharedArray<ColorRGBA> ColorRGBAArray;
typedef Pointer<ColorRGBAArray> ColorRGBAArrayPtr;

}

#endif

