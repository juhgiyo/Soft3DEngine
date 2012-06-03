///////////////////////////////////////////////////////////
//                                                       //
//                    WgFixedArray.h                     //
//                                                       //
//  - Interface for Fixed Array class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_FIXEDARRAY_H__
#define __WG_FIXEDARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTSharedArray.h"

namespace WGSoft3D
{
typedef TSharedArray<fixed> FixedArray;
typedef Pointer<FixedArray> FixedArrayPtr;
}

#endif

