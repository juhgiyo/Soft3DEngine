///////////////////////////////////////////////////////////
//                                                       //
//                    WgFloatArray.h                     //
//                                                       //
//  - Interface for Float Array class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_FLOAT_ARRAY_H__
#define __WG_FLOAT_ARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTSharedArray.h"

namespace WGSoft3D
{
typedef TSharedArray<float> FloatArray;
typedef Pointer<FloatArray> FloatArrayPtr;

}

#endif

