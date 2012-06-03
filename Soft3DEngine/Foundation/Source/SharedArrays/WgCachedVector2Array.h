///////////////////////////////////////////////////////////
//                                                       //
//              WgCachedVector2Array.h                   //
//                                                       //
//  - Interface for Cached Vector2 Array class           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_CACHEDVECTOR2ARRAY_H__
#define __WG_CACHEDVECTOR2ARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTCachedArray.h"
#include "WgVector2Array.h"

namespace WGSoft3D
{
// typedef TCachedArray<Vector2f> CachedVector2fArray;
// typedef Pointer<CachedVector2fArray> CachedVector2fArrayPtr;

typedef TCachedArray<Vector2x> CachedVector2xArray;
typedef Pointer<CachedVector2xArray> CachedVector2xArrayPtr;


}

#endif

