///////////////////////////////////////////////////////////
//                                                       //
//              WgCachedVector3Array.h                   //
//                                                       //
//  - Interface for Cached Vector3 Array class           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_CACHEDVECTOR3ARRAY_H__
#define __WG_CACHEDVECTOR3ARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTCachedArray.h"
#include "WgVector3Array.h"

namespace WGSoft3D
{
// typedef TCachedArray<Vector3f> CachedVector3fArray;
// typedef Pointer<CachedVector3fArray> CachedVector3fArrayPtr;

typedef TCachedArray<Vector3x> CachedVector3xArray;
typedef Pointer<CachedVector3xArray> CachedVector3xArrayPtr;


}

#endif

