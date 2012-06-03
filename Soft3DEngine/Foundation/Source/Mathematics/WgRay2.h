///////////////////////////////////////////////////////////
//                                                       //
//                    WgRay2.h                           //
//                                                       //
//  - Interface for Ray 2 class                          //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#ifndef __WG_RAY_2_H__
#define __WG_RAY_2_H__

#include "WgFoundationLIB.h"
#include "WgVector2.h"

namespace WGSoft3D
{

template <class Real>
class Ray2
{
public:
    // The ray is represented as P+t*D, where P is the ray origin, D is a
    // unit-length direction vector, and t >= 0.  The user must ensure that
    // the direction vector satisfies this condition.

    // construction
    Ray2 ();  // uninitialized
    Ray2 (const Vector2<Real>& rkOrigin, const Vector2<Real>& rkDirection);

    Vector2<Real> Origin, Direction;
};

class WG3D_FOUNDATION_ITEM Ray2x
{
public:
    // The ray is represented as P+t*D, where P is the ray origin, D is a
    // unit-length direction vector, and t >= 0.  The user must ensure that
    // the direction vector satisfies this condition.
	
    // construction
    Ray2x ();  // uninitialized
    Ray2x (const Vector2x& rkOrigin, const Vector2x& rkDirection);
	
    Vector2x Origin, Direction;
};


#include "WgRay2.inl"

typedef Ray2<float> Ray2f;
typedef Ray2<double> Ray2d;

}

#endif
