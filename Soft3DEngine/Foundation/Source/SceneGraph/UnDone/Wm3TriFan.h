// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved
//
// The Wild Magic Library (WM3) source code is supplied under the terms of
// the license agreement
//     http://www.geometrictools.com/License/WildMagic3License.pdf
// and may not be copied or disclosed except in accordance with the terms
// of that agreement.

#ifndef WM3TRIFAN_H
#define WM3TRIFAN_H

#include "Wm3FoundationLIB.h"
#include "Wm3Triangles.h"

namespace Wm3
{

class WM3_ITEM TriFan : public Triangles
{
    WM3_DECLARE_RTTI;
    WM3_DECLARE_NAME_ID;
    WM3_DECLARE_STREAM;

public:
    // Construction and destruction.
    TriFan (Vector3fArray* pkVertices, bool bGenerateNormals,
        bool bCachedNormals = false);
    TriFan (Vector3fArray* pkVertices, IntArray* pkIndices,
        bool bGenerateNormals,  bool bCachedNormals = false);
    virtual ~TriFan ();

    // Interpretation of the index buffer data.
    virtual int GetTriangleQuantity () const;
    virtual bool GetTriangle (int i, int& riV0, int& riV1, int& riV2) const;

protected:
    TriFan ();
};

WM3_REGISTER_STREAM(TriFan);
typedef Pointer<TriFan> TriFanPtr;
#include "Wm3TriFan.inl"

}

#endif
