///////////////////////////////////////////////////////////
//                                                       //
//                    WgVector2Array.h                   //
//                                                       //
//  - Interface for Vector2 Array class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_VECTOR2ARRAY_H__
#define __WG_VECTOR2ARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTSharedArray.h"
#include "WgVector2.h"

namespace WGSoft3D
{
typedef TSharedArray<Vector2x> Vector2xArray;
typedef Pointer<Vector2xArray> Vector2xArrayPtr;

typedef TSharedArray<Vector2f> Vector2fArray;
typedef Pointer<Vector2fArray> Vector2fArrayPtr;

typedef TSharedArray<Vector2d> Vector2dArray;
typedef Pointer<Vector2dArray> Vector2dArrayPtr;

}

#endif

