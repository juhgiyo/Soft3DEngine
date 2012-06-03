///////////////////////////////////////////////////////////
//                                                       //
//                    WgTriangle3.h                      //
//                                                       //
//  - Interface for Triangle 3 class                     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_TRIANGLE3_H__
#define __WG_TRIANGLE3_H__

#include "WgFoundationLIB.h"
#include "WgVector3.h"

namespace WGSoft3D
{

template <class Real>
class Triangle3
{
public:
    // The triangle is represented as an array of three vertices, V0, V1,
    // and V2.

    // construction
    Triangle3 ();  // uninitialized
    Triangle3 (const Vector3<Real>& rkV0, const Vector3<Real>& rkV1,
        const Vector3<Real>& rkV2);
    Triangle3 (const Vector3<Real> akV[3]);

    // distance from the point Q to the triangle
    Real DistanceTo (const Vector3<Real>& rkQ) const;

    Vector3<Real> V[3];
};

class WG3D_FOUNDATION_ITEM Triangle3x
{
public:
    // The triangle is represented as an array of three vertices, V0, V1,
    // and V2.
	
    // construction
    Triangle3x ();  // uninitialized
    Triangle3x (const Vector3x& rkV0, const Vector3x& rkV1,
        const Vector3x& rkV2);
    Triangle3x (const Vector3x akV[3]);
	
    // distance from the point Q to the triangle
    fixed DistanceTo (const Vector3x& rkQ) const;
	
    Vector3x V[3];
};


#include "WgTriangle3.inl"

typedef Triangle3<float> Triangle3f;
typedef Triangle3<double> Triangle3d;

}

#endif
