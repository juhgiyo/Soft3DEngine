// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved
//
// The Wild Magic Library (WM3) source code is supplied under the terms of
// the license agreement
//     http://www.geometrictools.com/License/WildMagic3License.pdf
// and may not be copied or disclosed except in accordance with the terms
// of that agreement.

#include "Wm3FoundationPCH.h"
#include "Wm3CachedIntArray.h"
#include "Wm3CachedVector3fArray.h"
#include "Wm3TriStrip.h"
using namespace Wm3;

WM3_IMPLEMENT_RTTI(Wm3,TriStrip,Triangles);
WM3_IMPLEMENT_STREAM(TriStrip);
WM3_IMPLEMENT_DEFAULT_STREAM(TriStrip,Triangles);
WM3_IMPLEMENT_DEFAULT_NAME_ID(TriStrip,Triangles);

//----------------------------------------------------------------------------
TriStrip::TriStrip ()
{
    GeometryType = GT_TRISTRIP;
}
//----------------------------------------------------------------------------
TriStrip::TriStrip (Vector3fArray* pkVertices, bool bGenerateNormals,
    bool bCachedNormals)
    :
    Triangles(pkVertices,0,false,false)
{
    GeometryType = GT_TRISTRIP;

    int iIQuantity = pkVertices->GetQuantity();
    int* aiIndex = WM3_NEW int[iIQuantity];
    int* piIndex = aiIndex;
    for (int i = 0; i < iIQuantity; i++)
    {
        *piIndex++ = i;
    }

    if (pkVertices->IsExactly(CachedVector3fArray::TYPE))
    {
        Indices = WM3_NEW CachedIntArray(iIQuantity,aiIndex);
    }
    else
    {
        Indices = WM3_NEW IntArray(iIQuantity,aiIndex);
    }

    if (bGenerateNormals)
    {
        GenerateNormals(bCachedNormals);
    }
}
//----------------------------------------------------------------------------
TriStrip::TriStrip (Vector3fArray* pkVertices, IntArray* pkIndices,
    bool bGenerateNormals, bool bCachedNormals)
    :
    Triangles(pkVertices,pkIndices,false,false)
{
    GeometryType = GT_TRISTRIP;

    if (bGenerateNormals)
    {
        GenerateNormals(bCachedNormals);
    }
}
//----------------------------------------------------------------------------
TriStrip::~TriStrip ()
{
}
//----------------------------------------------------------------------------
bool TriStrip::GetTriangle (int i, int& riV0, int& riV1, int& riV2) const
{
    if (0 <= i && i < GetTriangleQuantity())
    {
        const int* aiIndex = Indices->GetData();
        riV0 = aiIndex[i];
        if (i & 1)
        {
            riV1 = aiIndex[i+2];
            riV2 = aiIndex[i+1];
        }
        else
        {
            riV1 = aiIndex[i+1];
            riV2 = aiIndex[i+2];
        }

        // Degenerate triangles are assumed to have been added for swaps and
        // turns in the triangle strip.  They are considered invalid for other
        // purposes in the engine.
        return (riV0 != riV1 && riV0 != riV2 && riV1 != riV2);
    }
    return false;
}
//----------------------------------------------------------------------------
