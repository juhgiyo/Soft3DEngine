///////////////////////////////////////////////////////////
//                                                       //
//                WgIntrRay3Triangle3.h                  //
//                                                       //
//  - Interface for Intersection Ray3 Triangle3 class    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_INTRRAY3TRIANGLE3_H__
#define __WG_INTRRAY3TRIANGLE3_H__

#include "WgFoundationLIB.h"
#include "WgIntersector.h"
#include "WgRay3.h"
#include "WgTriangle3.h"

namespace WGSoft3D
{

template <class Real>
class WG3D_FOUNDATION_ITEM IntrRay3Triangle3 : public Intersector<Real,Vector3<Real> >
{
public:
    IntrRay3Triangle3 (const Ray3<Real>& rkRay,
        const Triangle3<Real>& rkTriangle);

    // object access
    const Ray3<Real>& GetRay () const;
    const Triangle3<Real>& GetTriangle () const;

    // test-intersection query
    virtual bool Test ();

    // Find-intersection query.  The point of intersection is
    //   P = origin + t*direction = b0*V0 + b1*V1 + b2*V2
    virtual bool Find ();
    Real GetRayT () const;
    Real GetTriB0 () const;
    Real GetTriB1 () const;
    Real GetTriB2 () const;

private:
    // the objects to intersect
    const Ray3<Real>& m_rkRay;
    const Triangle3<Real>& m_rkTriangle;

    // information about the intersection set
    Real m_fRayT, m_fTriB0, m_fTriB1, m_fTriB2;
};

class WG3D_FOUNDATION_ITEM IntrRay3Triangle3x : public Intersector3x
{
public:
    IntrRay3Triangle3x (const Ray3x& rkRay,
        const Triangle3x& rkTriangle);
	
    // object access
    const Ray3x& GetRay () const;
    const Triangle3x& GetTriangle () const;
	
    // test-intersection query
    virtual bool Test ();
	
    // Find-intersection query.  The point of intersection is
    //   P = origin + t*direction = b0*V0 + b1*V1 + b2*V2
    virtual bool Find ();
    fixed GetRayT () const;
    fixed GetTriB0 () const;
    fixed GetTriB1 () const;
    fixed GetTriB2 () const;
	
private:
    // the objects to intersect
    const Ray3x& m_rkRay;
    const Triangle3x& m_rkTriangle;
	
    // information about the intersection set
    fixed m_fRayT, m_fTriB0, m_fTriB1, m_fTriB2;
};

typedef IntrRay3Triangle3<float> IntrRay3Triangle3f;
typedef IntrRay3Triangle3<double> IntrRay3Triangle3d;

#include "WgIntrRay3Triangle3.inl"
}

#endif

