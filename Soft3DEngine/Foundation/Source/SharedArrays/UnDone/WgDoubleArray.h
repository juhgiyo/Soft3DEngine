// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved
//
// The Wild Magic Library (WM3) source code is supplied under the terms of
// the license agreement
//     http://www.geometrictools.com/License/WildMagic3License.pdf
// and may not be copied or disclosed except in accordance with the terms
// of that agreement.

#ifndef WM3DOUBLEARRAY_H
#define WM3DOUBLEARRAY_H

#include "Wm3FoundationLIB.h"
#include "Wm3TSharedArray.h"

namespace Wm3
{
typedef TSharedArray<double> DoubleArray;
typedef Pointer<DoubleArray> DoubleArrayPtr;
WM3_REGISTER_STREAM(DoubleArray);
}

#endif

