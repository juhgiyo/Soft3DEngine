///////////////////////////////////////////////////////////
//                                                       //
//                    WgShortArray.h                     //
//                                                       //
//  - Interface for Short Array class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_SHORTARRAY_H__
#define __WG_SHORTARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTSharedArray.h"

namespace WGSoft3D
{
typedef TSharedArray<short> ShortArray;
typedef Pointer<ShortArray> ShortArrayPtr;
}

#endif

