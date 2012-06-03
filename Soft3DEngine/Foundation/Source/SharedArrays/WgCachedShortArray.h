///////////////////////////////////////////////////////////
//                                                       //
//              WgCachedShortArray.h                     //
//                                                       //
//  - Interface for Cached Short Array class             //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_CACHEDSHORTARRAY_H__
#define __WG_CACHEDSHORTARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTCachedArray.h"
#include "WgShortArray.h"

namespace WGSoft3D
{
typedef TCachedArray<short> CachedShortArray;
typedef Pointer<CachedShortArray> CachedShortArrayPtr;
}

#endif

