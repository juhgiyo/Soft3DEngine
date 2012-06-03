///////////////////////////////////////////////////////////
//                                                       //
//                    WgSphereBV.h                       //
//                                                       //
//  - Interface for Sphere Bounding Volume class         //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_SPHEREBV_H__
#define __WG_SPHEREBV_H__

#include "WgFoundationLIB.h"
#include "WgBoundingVolume.h"
#include "WgSphere3.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM SphereBV : public BoundingVolume
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    // construction
    SphereBV ();  // center (0,0,0), radius 0
    SphereBV (const Sphere3x& rkSphere);

    virtual int GetBVType () const;

    // all bounding volumes must define a center and radius
    virtual void SetCenter (const Vector3x& rkCenter);
    virtual void SetRadius (fixed fRadius);
    virtual Vector3x GetCenter () const;
    virtual fixed GetRadius () const;

    Sphere3x& Sphere ();
    const Sphere3x& GetSphere () const;

    // Compute a sphere that contains all the points.
    virtual void ComputeFromData (const Vector3xArray* pkVertices);

    // Transform the sphere (model-to-world conversion).
    virtual void TransformBy (const Transformation& rkTransform,
        BoundingVolume* pkResult);

    // Determine if the bounding volume is one side of the plane, the other
    // side, or straddles the plane.  If it is on the positive side (the
    // side to which the normal points), the return value is +1.  If it is
    // on the negative side, the return value is -1.  If it straddles the
    // plane, the return value is 0.
    virtual int WhichSide (const Plane3x& rkPlane) const;

    // Test for intersection of ray and bound (points of intersection not
    // computed).
    virtual bool TestIntersection (const Ray3x& rkRay) const;

    // Test for intersection of the two bounds.
    virtual bool TestIntersection (const BoundingVolume* pkInput) const;

    // Make a copy of the bounding volume.
    virtual void CopyFrom (const BoundingVolume* pkInput);

    // Change the current sphere so that it is the minimum volume sphere that
    // contains the input sphere as well as its old sphere.
    virtual void GrowToContain (const BoundingVolume* pkInput);

    // test for containment of a point
    virtual bool Contains (const Vector3x& rkPoint) const;

protected:
    Sphere3x m_kSphere;
};

#include "WgSphereBV.inl"

typedef Pointer<SphereBV> SphereBVPtr;

}

#endif

