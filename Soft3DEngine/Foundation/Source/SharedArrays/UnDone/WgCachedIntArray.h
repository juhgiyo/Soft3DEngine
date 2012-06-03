///////////////////////////////////////////////////////////
//                                                       //
//              WgCachedIntArray.h                       //
//                                                       //
//  - Interface for Cached Int Array class               //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_CACHEDINTARRAY_H__
#define __WG_CACHEDINTARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTCachedArray.h"
#include "WgIntArray.h"

namespace WGSoft3D
{
typedef TCachedArray<int> CachedIntArray;
typedef Pointer<CachedIntArray> CachedIntArrayPtr;
}

#endif

