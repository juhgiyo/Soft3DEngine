///////////////////////////////////////////////////////////
//                                                       //
//                    WgTriMesh.cpp                      //
//                                                       //
//  - Implementation for Tri Mesh class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgTriMesh.h"
#include "WgIntrRay3Triangle3.h"
#include "WgCachedVector3Array.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,TriMesh,Triangles);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(TriMesh,Triangles);

//----------------------------------------------------------------------------
TriMesh::TriMesh ()
{
    m_GeometryType = GT_TRIMESH;
}
//----------------------------------------------------------------------------
TriMesh::TriMesh (Vector3xArray* pkVertices, ShortArray* pkIndices,
    bool bGenerateNormals, bool bCachedNormals)
    :
    Triangles(pkVertices,pkIndices,bGenerateNormals,bCachedNormals)
{
    m_GeometryType = GT_TRIMESH;
    if (bGenerateNormals)
    {
        GenerateNormals(bCachedNormals);
    }
}
//----------------------------------------------------------------------------
TriMesh::~TriMesh ()
{
}
//----------------------------------------------------------------------------
bool TriMesh::GetTriangle (int i, short& riV0, short& riV1, short& riV2) const
{
    if (0 <= i && i < GetTriangleQuantity())
    {
        const short* piIndex = &Indices->GetData()[3*i];
        riV0 = *piIndex++;
        riV1 = *piIndex++;
        riV2 = *piIndex;
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
