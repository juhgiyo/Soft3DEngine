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
#include "Wm3TriFan.h"
using namespace Wm3;

WM3_IMPLEMENT_RTTI(Wm3,TriFan,Triangles);
WM3_IMPLEMENT_STREAM(TriFan);
WM3_IMPLEMENT_DEFAULT_STREAM(TriFan,Triangles);
WM3_IMPLEMENT_DEFAULT_NAME_ID(TriFan,Triangles);

//----------------------------------------------------------------------------
TriFan::TriFan ()
{
    GeometryType = GT_TRIFAN;
}
//----------------------------------------------------------------------------
TriFan::TriFan (Vector3fArray* pkVertices, bool bGenerateNormals,
    bool bCachedNormals)
    :
    Triangles(pkVertices,0,false,false)
{
    GeometryType = GT_TRIFAN;

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
TriFan::TriFan (Vector3fArray* pkVertices, IntArray* pkIndices,
    bool bGenerateNormals, bool bCachedNormals)
    :
    Triangles(pkVertices,pkIndices,false,false)
{
    GeometryType = GT_TRIFAN;

    if (bGenerateNormals)
    {
        GenerateNormals(bCachedNormals);
    }
}
//----------------------------------------------------------------------------
TriFan::~TriFan ()
{
}
//----------------------------------------------------------------------------
bool TriFan::GetTriangle (int i, int& riV0, int& riV1, int& riV2) const
{
    if (0 <= i && i < GetTriangleQuantity())
    {
        const int* aiIndex = Indices->GetData();
        riV0 = aiIndex[0];
        riV1 = aiIndex[i+1];
        riV2 = aiIndex[i+2];
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
