// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved
//
// The Wild Magic Library (WM3) source code is supplied under the terms of
// the license agreement
//     http://www.geometrictools.com/License/WildMagic3License.pdf
// and may not be copied or disclosed except in accordance with the terms
// of that agreement.

#ifndef WM3TRISTRIP_H
#define WM3TRISTRIP_H

#include "Wm3FoundationLIB.h"
#include "Wm3Triangles.h"

namespace Wm3
{

class WM3_ITEM TriStrip : public Triangles
{
    WM3_DECLARE_RTTI;
    WM3_DECLARE_NAME_ID;
    WM3_DECLARE_STREAM;

public:
    // Construction and destruction.
    TriStrip (Vector3fArray* pkVertices, bool bGenerateNormals,
        bool bCachedNormals = false);
    TriStrip (Vector3fArray* pkVertices, IntArray* pkIndices,
        bool bGenerateNormals, bool bCachedNormals = false);
    virtual ~TriStrip ();

    // Interpretation of the index buffer data.
    virtual int GetTriangleQuantity () const;
    virtual bool GetTriangle (int i, int& riV0, int& riV1, int& riV2) const;

protected:
    TriStrip ();
};

WM3_REGISTER_STREAM(TriStrip);
typedef Pointer<TriStrip> TriStripPtr;
#include "Wm3TriStrip.inl"

}

#endif
