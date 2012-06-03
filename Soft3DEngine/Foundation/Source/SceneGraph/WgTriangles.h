///////////////////////////////////////////////////////////
//                                                       //
//                    WgTriangles.h                      //
//                                                       //
//  - Interface for Triangles class                      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_TRIANGLES_H__
#define __WG_TRIANGLES_H__

#include "WgFoundationLIB.h"
#include "WgGeometry.h"
#include "WgTriangle3.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM Triangles : public Geometry
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;
    

public:
    // abstract base class
    virtual ~Triangles ();

    // These functions depend on the interpretation of the index buffer of
    // the triangle primitive.  The triangle <V0,V1,V2> is counterclockwise
    // order.
    virtual int GetTriangleQuantity () const = 0;
    virtual bool GetTriangle (int i, short& riV0, short& riV1, short& riV2)
        const = 0;

    bool GetModelTriangle (int i, Triangle3x& rkMTri) const;
    bool GetWorldTriangle (int i, Triangle3x& rkWTri) const;
    void GenerateNormals (bool bCached = false);

    // Picking support.  The pick record stores the index of any triangle
    // intersected by the ray.  It stores the barycentric coordinates of
    // the intersection point.  This allows the application to compute
    // interpolated vertex attributes as well as the actual point of
    // intersection.
    class WG3D_FOUNDATION_ITEM PickRecord : public Geometry::PickRecord
    {
    public:
        PickRecord (Triangles* pkIObject, fixed fT, short iTriangle,
            fixed fBary0, fixed fBary1, fixed fBary2);

        // Index of the triangle that is intersected by the ray.
        short Triangle;

        // Barycentric coordinates of the point of intersection.  If b0, b1,
        // and b2 are the values, then all are in [0,1] and b0+b1+b2=1.
        fixed Bary0, Bary1, Bary2;
    };

    // The origin and direction of the ray must be in world coordinates.  The
    // application is responsible for deleting the pick records in the array.
    virtual void DoPick (const Ray3x& rkRay, PickArray& rkResults);

protected:
    Triangles ();
    Triangles (Vector3xArray* pkVertices, ShortArray* pkIndices,
        bool bGenerateNormals, bool bCachedNormals);

    // geometric updates
    virtual void UpdateModelNormals ();
};

typedef Pointer<Triangles> TrianglesPtr;

}

#endif
