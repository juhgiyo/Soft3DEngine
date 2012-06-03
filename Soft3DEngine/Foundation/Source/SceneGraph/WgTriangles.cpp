///////////////////////////////////////////////////////////
//                                                       //
//                    WgTriangles.cpp                    //
//                                                       //
//  - Implementation for Triangles class                 //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgTriangles.h"
#include "WgCachedVector3Array.h"
#include "WgIntrRay3Triangle3.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,Triangles,Geometry);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(Triangles,Geometry);

//----------------------------------------------------------------------------
Triangles::Triangles ()
{
    // The Type value will be assigned by the derived class.
}
//----------------------------------------------------------------------------
Triangles::Triangles (Vector3xArray* pkVertices, ShortArray* pkIndices,
    bool bGenerateNormals, bool bCachedNormals)
    :
    Geometry(pkVertices)
{
    // The Type value will be assigned by the derived class.
    Indices = pkIndices;
}
//----------------------------------------------------------------------------
Triangles::~Triangles ()
{
}
//----------------------------------------------------------------------------
bool Triangles::GetModelTriangle (int i, Triangle3x& rkMTri) const
{
    short iV0, iV1, iV2;
    if (GetTriangle(i,iV0,iV1,iV2))
    {
        Vector3x* akVertex = Vertices->GetData();
        rkMTri.V[0] = akVertex[iV0];
        rkMTri.V[1] = akVertex[iV1];
        rkMTri.V[2] = akVertex[iV2];
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
bool Triangles::GetWorldTriangle (int i, Triangle3x& rkWTri) const
{
    short iV0, iV1, iV2;
    if (GetTriangle(i,iV0,iV1,iV2))
    {
        Vector3x* akVertex = Vertices->GetData();
        rkWTri.V[0] = World.ApplyForward(akVertex[iV0]);
        rkWTri.V[1] = World.ApplyForward(akVertex[iV1]);
        rkWTri.V[2] = World.ApplyForward(akVertex[iV2]);
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
void Triangles::GenerateNormals (bool bCached)
{
    int iVQuantity;
    Vector3x* akNormal;

    if (!Normals)
    {
        iVQuantity = Vertices->GetQuantity();
        akNormal = WG_NEW Vector3x[iVQuantity];
        if (bCached)
        {
            Normals = WG_NEW CachedVector3xArray(iVQuantity,akNormal);
        }
        else
        {
            Normals = WG_NEW Vector3xArray(iVQuantity,akNormal);
        }
        UpdateModelNormals();
    }
    else
    {
        if (bCached && !Normals->IsExactly(CachedVector3xArray::TYPE))
        {
            iVQuantity = Normals->GetQuantity();
            akNormal = WG_NEW Vector3x[iVQuantity];
            Normals = WG_NEW CachedVector3xArray(iVQuantity,akNormal);
            UpdateModelNormals();
        }
        else if (!bCached && Normals->IsExactly(CachedVector3xArray::TYPE))
        {
            iVQuantity = Normals->GetQuantity();
            akNormal = WG_NEW Vector3x[iVQuantity];
            Normals = WG_NEW Vector3xArray(iVQuantity,akNormal);
            UpdateModelNormals();
        }
    }
}
//----------------------------------------------------------------------------
void Triangles::UpdateModelNormals ()
{
    if (!Normals)
    {
        return;
    }

    // Calculate normals from vertices by weighted averages of facet planes
    // that contain the vertices.

    int iVQuantity = Vertices->GetQuantity();
    Vector3x* akVertex = Vertices->GetData();
    Vector3x* akNormal = Normals->GetData();
    memset(Normals->GetData(),0,iVQuantity*sizeof(Vector3x));

    int iTQuantity = GetTriangleQuantity();
    int i;
    for (i = 0; i < iTQuantity; i++)
    {
        // get vertex indices
        short iV0, iV1, iV2;
        if (!GetTriangle(i,iV0,iV1,iV2))
        {
            continue;
        }

        // get vertices
        Vector3x& rkV0 = akVertex[iV0];
        Vector3x& rkV1 = akVertex[iV1];
        Vector3x& rkV2 = akVertex[iV2];

        // compute the normal (length provides the weighted sum)
        Vector3x kEdge1 = rkV1 - rkV0;
        Vector3x kEdge2 = rkV2 - rkV0;
        Vector3x kNormal = kEdge1.Cross(kEdge2);

        akNormal[iV0] += kNormal;
        akNormal[iV1] += kNormal;
        akNormal[iV2] += kNormal;
    }

    for (i = 0; i < iVQuantity; i++)
    {
        akNormal[i].Normalize();
    }
}
//----------------------------------------------------------------------------
Triangles::PickRecord::PickRecord (Triangles* pkIObject, fixed fT,
    short iTriangle, fixed fBary0, fixed fBary1, fixed fBary2)
    :
    Geometry::PickRecord(pkIObject,fT)
{
    Triangle = iTriangle;
    Bary0 = fBary0;
    Bary1 = fBary1;
    Bary2 = fBary2;
}
//----------------------------------------------------------------------------
void Triangles::DoPick (const Ray3x& rkRay, PickArray& rkResults)
{
    if (WorldBound->TestIntersection(rkRay))
    {
        // convert the ray to model-space coordinates
        Ray3x kRay(World.ApplyInverse(rkRay.Origin),
            World.InvertVector(rkRay.Direction));

        // compute intersections with the model-space triangles
        const Vector3x* akVertex = Vertices->GetData();
        int iTQuantity = GetTriangleQuantity();
        for (int i = 0; i < iTQuantity; i++)
        {
            short iV0, iV1, iV2;
            if (!GetTriangle(i,iV0,iV1,iV2))
            {
                continue;
            }

            Triangle3x kTriangle(akVertex[iV0],akVertex[iV1],akVertex[iV2]);
            IntrRay3Triangle3x kIntr(kRay,kTriangle);
            if (kIntr.Find())
            {
                rkResults.Append(WG_NEW PickRecord(this,kIntr.GetRayT(),i,
                    kIntr.GetTriB0(),kIntr.GetTriB1(),kIntr.GetTriB2()));
            }
        }
    }
}
//----------------------------------------------------------------------------
