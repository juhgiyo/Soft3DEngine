///////////////////////////////////////////////////////////
//                                                       //
//                    WgPlane3.h                         //
//                                                       //
//  - Interface for Plane 3 class                        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#ifndef __WG_PLANE_3_H__
#define __WG_PLANE_3_H__

#include "WgFoundationLIB.h"
#include "WgVector3.h"

namespace WGSoft3D
{
template <class Real>
class Plane3
{
public:
    // The plane is represented as Dot(N,X) = c where N is a unit-length
    // normal vector, c is the plane constant, and X is any point on the
    // plane.  The user must ensure that the normal vector satisfies this
    // condition.

    Plane3 ();  // uninitialized
    Plane3 (const Plane3& rkPlane);

    // specify N and c directly
    Plane3 (const Vector3<Real>& rkNormal, Real fConstant);

    // N is specified, c = Dot(N,P) where P is on the plane
    Plane3 (const Vector3<Real>& rkNormal, const Vector3<Real>& rkP);

    // N = Cross(P1-P0,P2-P0)/Length(Cross(P1-P0,P2-P0)), c = Dot(N,P0) where
    // P0, P1, P2 are points on the plane.
    Plane3 (const Vector3<Real>& rkP0, const Vector3<Real>& rkP1,
        const Vector3<Real>& rkP2);

    // assignment
    Plane3& operator= (const Plane3& rkPlane);

    // The "positive side" of the plane is the half space to which the plane
    // normal points.  The "negative side" is the other half space.  The
    // function returns +1 for the positive side, -1 for the negative side,
    // and 0 for the point being on the plane.
    int WhichSide (const Vector3<Real>& rkP) const;

    // Compute d = Dot(N,Q)-c where N is the plane normal and c is the plane
    // constant.  This is a signed distance.  The sign of the return value is
    // positive if the point is on the positive side of the plane, negative if
    // the point is on the negative side, and zero if the point is on the
    // plane.
    Real DistanceTo (const Vector3<Real>& rkQ) const;

    Vector3<Real> Normal;
    Real Constant;
};

class WG3D_FOUNDATION_ITEM Plane3x
{
public:
    // The plane is represented as Dot(N,X) = c where N is a unit-length
    // normal vector, c is the plane constant, and X is any point on the
    // plane.  The user must ensure that the normal vector satisfies this
    // condition.
	
    Plane3x ();  // uninitialized
    Plane3x (const Plane3x& rkPlane);
	
    // specify N and c directly
    Plane3x (const Vector3x& rkNormal, fixed fConstant);
	
    // N is specified, c = Dot(N,P) where P is on the plane
    Plane3x (const Vector3x& rkNormal, const Vector3x& rkP);
	
    // N = Cross(P1-P0,P2-P0)/Length(Cross(P1-P0,P2-P0)), c = Dot(N,P0) where
    // P0, P1, P2 are points on the plane.
    Plane3x (const Vector3x& rkP0, const Vector3x& rkP1,
        const Vector3x& rkP2);
	
    // assignment
    Plane3x& operator= (const Plane3x& rkPlane);
	
    // The "positive side" of the plane is the half space to which the plane
    // normal points.  The "negative side" is the other half space.  The
    // function returns +1 for the positive side, -1 for the negative side,
    // and 0 for the point being on the plane.
    int WhichSide (const Vector3x& rkP) const;
	
    // Compute d = Dot(N,Q)-c where N is the plane normal and c is the plane
    // constant.  This is a signed distance.  The sign of the return value is
    // positive if the point is on the positive side of the plane, negative if
    // the point is on the negative side, and zero if the point is on the
    // plane.
    fixed DistanceTo (const Vector3x& rkQ) const;
	
    Vector3x Normal;
    fixed Constant;
};

#include "WgPlane3.inl"

typedef Plane3<float> Plane3f;
typedef Plane3<double> Plane3d;

}

#endif
