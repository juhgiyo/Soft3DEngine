///////////////////////////////////////////////////////////
//                                                       //
//                    WgSphere3.h                        //
//                                                       //
//  - Interface for Sphere 3 class                       //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_SPHERE_3_H__
#define __WG_SPHERE_3_H__

#include "WgFoundationLIB.h"
#include "WgVector3.h"

namespace WGSoft3D
{
template <class Real>
class Sphere3
{
public:
    // The sphere is represented as |X-C| = R where C is the center and R is
    // the radius.

    Sphere3 ();  // uninitialized
    Sphere3 (const Vector3<Real>& rkCenter, Real fRadius);
    Sphere3 (const Sphere3& rkSphere);

    // assignment
    Sphere3& operator= (const Sphere3& rkSphere);

    Vector3<Real> Center;
    Real Radius;
};

class WG3D_FOUNDATION_ITEM Sphere3x
{
public:
    // The sphere is represented as |X-C| = R where C is the center and R is
    // the radius.
	
    Sphere3x ();  // uninitialized
    Sphere3x (const Vector3x& rkCenter, fixed fRadius);
    Sphere3x (const Sphere3x& rkSphere);
	
    // assignment
    Sphere3x& operator= (const Sphere3x& rkSphere);
	
    Vector3x Center;
    fixed Radius;
};

#include "WgSphere3.inl"

typedef Sphere3<float> Sphere3f;
typedef Sphere3<double> Sphere3d;

}

#endif
