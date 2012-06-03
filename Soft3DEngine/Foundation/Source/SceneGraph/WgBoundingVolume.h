///////////////////////////////////////////////////////////
//                                                       //
//                    WgBoundingVolume.h                 //
//                                                       //
//  - Interface for Bounding Volume class                //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_BOUNDINGVOLUME_H__
#define __WG_BOUNDINGVOLUME_H__

#include "WgFoundationLIB.h"
#include "WgObject.h"
#include "WgPlane3.h"
#include "WgRay3.h"
#include "WgTransformation.h"
#include "WgVector3Array.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM BoundingVolume : public Object
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    // abstract base class
    virtual ~BoundingVolume ();

    // run-time type information
    enum // BVType
    {
        BV_SPHERE,
        BV_BOX,
        BV_QUANTITY
    };
    virtual int GetBVType () const = 0;

    // all bounding volumes must define a center and radius
    virtual void SetCenter (const Vector3x& rkCenter) = 0;
    virtual void SetRadius (fixed fRadius) = 0;
    virtual Vector3x GetCenter () const = 0;
    virtual fixed GetRadius () const = 0;

    // One of the derived classes has the responsibility for implementing
    // this factory function.  Our default is the WmlSphereBV class, but
    // you may change it to another.
    static BoundingVolume* Create ();

    // Compute a bounding volume that contains all the points.
    virtual void ComputeFromData (const Vector3xArray* pkVertices) = 0;

    // Transform the bounding volume (model-to-world conversion).
    virtual void TransformBy (const Transformation& rkTransform,
        BoundingVolume* pkResult) = 0;

    // Determine if the bounding volume is one side of the plane, the other
    // side, or straddles the plane.  If it is on the positive side (the
    // side to which the normal points), the return value is +1.  If it is
    // on the negative side, the return value is -1.  If it straddles the
    // plane, the return value is 0.
    virtual int WhichSide (const Plane3x& rkPlane) const = 0;

    // Test for intersection of ray and bound (points of intersection not
    // computed).  The input direction must be unit length.
    virtual bool TestIntersection (const Ray3x& rkRay) const = 0;

    // Test for intersection of the two bounds.
    virtual bool TestIntersection (const BoundingVolume* pkInput) const = 0;

    // Make a copy of the bounding volume.
    virtual void CopyFrom (const BoundingVolume* pkInput) = 0;

    // Change the current bounding volume so that it contains the input
    // bounding volume as well as its old bounding volume.
    virtual void GrowToContain (const BoundingVolume* pkInput) = 0;

    // test for containment of a point
    virtual bool Contains (const Vector3x& rkPoint) const = 0;

protected:
    BoundingVolume ();
};

typedef Pointer<BoundingVolume> BoundingVolumePtr;

}

#endif

