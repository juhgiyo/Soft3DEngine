///////////////////////////////////////////////////////////
//                                                       //
//                    WgVector3Array.h                   //
//                                                       //
//  - Interface for Vector3 Array class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_VECTOR3ARRAY_H__
#define __WG_VECTOR3ARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTSharedArray.h"
#include "WgVector3.h"

namespace WGSoft3D
{
typedef TSharedArray<Vector3x> Vector3xArray;
typedef Pointer<Vector3xArray> Vector3xArrayPtr;


typedef TSharedArray<Vector3f> Vector3fArray;
typedef Pointer<Vector3fArray> Vector3fArrayPtr;

typedef TSharedArray<Vector3d> Vector3dArray;
typedef Pointer<Vector3dArray> Vector3dArrayPtr;

}

#endif

