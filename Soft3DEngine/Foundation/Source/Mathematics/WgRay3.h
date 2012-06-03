///////////////////////////////////////////////////////////
//                                                       //
//                    WgRay3.h                           //
//                                                       //
//  - Interface for Ray 3 class                          //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#ifndef __WG_RAY_3_H__
#define __WG_RAY_3_H__

#include "WgFoundationLIB.h"
#include "WgVector3.h"

namespace WGSoft3D
{

template <class Real>
class Ray3
{
public:
    // The ray is represented as P+t*D, where P is the ray origin, D is a
    // unit-length direction vector, and t >= 0.  The user must ensure that
    // the direction vector satisfies this condition.

    // construction
    Ray3 ();  // uninitialized
    Ray3 (const Vector3<Real>& rkOrigin, const Vector3<Real>& rkDirection);

    Vector3<Real> Origin, Direction;
};

class WG3D_FOUNDATION_ITEM Ray3x
{
public:
    // The ray is represented as P+t*D, where P is the ray origin, D is a
    // unit-length direction vector, and t >= 0.  The user must ensure that
    // the direction vector satisfies this condition.
	
    // construction
    Ray3x ();  // uninitialized
    Ray3x (const Vector3x& rkOrigin, const Vector3x& rkDirection);
	
    Vector3x Origin, Direction;
};

#include "WgRay3.inl"

typedef Ray3<float> Ray3f;
typedef Ray3<double> Ray3d;

}

#endif
