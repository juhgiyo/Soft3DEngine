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
#include "Wm3Polypoint.h"
using namespace Wm3;

WM3_IMPLEMENT_RTTI(Wm3,Polypoint,Geometry);
WM3_IMPLEMENT_STREAM(Polypoint);
WM3_IMPLEMENT_DEFAULT_NAME_ID(Polypoint,Geometry);

//----------------------------------------------------------------------------
Polypoint::Polypoint (Vector3fArrayPtr spkVertices)
    :
    Geometry(spkVertices)
{
    GeometryType = GT_POLYPOINT;

    int iVQuantity = Vertices->GetQuantity();
    m_iActiveQuantity = iVQuantity;

    // support for drawing vertex arrays
    int* aiIndex = WM3_NEW int[iVQuantity];
    for (int i = 0; i < iVQuantity; i++)
    {
        aiIndex[i] = i;
    }
    Indices = WM3_NEW IntArray(iVQuantity,aiIndex);
}
//----------------------------------------------------------------------------
Polypoint::Polypoint ()
{
    GeometryType = GT_POLYPOINT;
    m_iActiveQuantity = 0;
}
//----------------------------------------------------------------------------
Polypoint::~Polypoint ()
{
}
//----------------------------------------------------------------------------
void Polypoint::SetActiveQuantity (int iActiveQuantity)
{
    int iVQuantity = Vertices->GetQuantity();
    if (0 <= iActiveQuantity && iActiveQuantity <= iVQuantity)
    {
        m_iActiveQuantity = iActiveQuantity;
    }
    else
    {
        m_iActiveQuantity = iVQuantity;
    }

    Indices->SetActiveQuantity(m_iActiveQuantity);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void Polypoint::Load (Stream& rkStream, Stream::Link* pkLink)
{
    WM3_BEGIN_DEBUG_STREAM_LOAD;

    Geometry::Load(rkStream,pkLink);

    // native data
    rkStream.Read(m_iActiveQuantity);

    WM3_END_DEBUG_STREAM_LOAD(Polypoint);
}
//----------------------------------------------------------------------------
void Polypoint::Link (Stream& rkStream, Stream::Link* pkLink)
{
    Geometry::Link(rkStream,pkLink);
}
//----------------------------------------------------------------------------
bool Polypoint::Register (Stream& rkStream) const
{
    return Geometry::Register(rkStream);
}
//----------------------------------------------------------------------------
void Polypoint::Save (Stream& rkStream) const
{
    WM3_BEGIN_DEBUG_STREAM_SAVE;

    Geometry::Save(rkStream);

    // native data
    rkStream.Write(m_iActiveQuantity);

    WM3_END_DEBUG_STREAM_SAVE(Polypoint);
}
//----------------------------------------------------------------------------
StringTree* Polypoint::SaveStrings (const char*)
{
    StringTree* pkTree = WM3_NEW StringTree(2,1);

    // strings
    pkTree->SetString(0,Format(&TYPE,GetName()));
    pkTree->SetString(1,Format("active = ",m_iActiveQuantity));

    // children
    pkTree->SetChild(0,Geometry::SaveStrings());

    return pkTree;
}
//----------------------------------------------------------------------------
int Polypoint::GetMemoryUsed () const
{
    return sizeof(Polypoint) - sizeof(Geometry) + Geometry::GetMemoryUsed();
}
//----------------------------------------------------------------------------
int Polypoint::GetDiskUsed (const StreamVersion& rkVersion) const
{
    return Geometry::GetDiskUsed(rkVersion) +
        sizeof(m_iActiveQuantity);
}
//----------------------------------------------------------------------------

