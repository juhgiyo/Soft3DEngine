///////////////////////////////////////////////////////////
//                                                       //
//                    WgQuaternionArray.h                //
//                                                       //
//  - Interface for Quaternion Array class                //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_QUATERNIONARRAY_H__
#define __WG_QUATERNIONARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTSharedArray.h"
#include "WgQuaternion.h"

namespace WGSoft3D
{
typedef TSharedArray<Quaternionf> QuaternionfArray;
typedef Pointer<QuaternionfArray> QuaternionfArrayPtr;

typedef TSharedArray<Quaterniond> QuaterniondArray;
typedef Pointer<QuaterniondArray> QuaterniondArrayPtr;

typedef TSharedArray<Quaternionx> QuaternionxArray;
typedef Pointer<QuaternionxArray> QuaternionxArrayPtr;


}

#endif

