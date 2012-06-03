// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved
//
// The Wild Magic Library (WM3) source code is supplied under the terms of
// the license agreement
//     http://www.geometrictools.com/License/WildMagic3License.pdf
// and may not be copied or disclosed except in accordance with the terms
// of that agreement.

#ifndef WM3VECTOR4ARRAY_H
#define WM3VECTOR4ARRAY_H

#include "Wm3FoundationLIB.h"
#include "Wm3TSharedArray.h"
#include "Wm3Vector4.h"

namespace Wm3
{
typedef TSharedArray<Vector4f> Vector4fArray;
typedef Pointer<Vector4fArray> Vector4fArrayPtr;
WM3_REGISTER_STREAM(Vector4fArray);

typedef TSharedArray<Vector4d> Vector4dArray;
typedef Pointer<Vector4dArray> Vector4dArrayPtr;
WM3_REGISTER_STREAM(Vector4dArray);
}

#endif

