///////////////////////////////////////////////////////////
//                                                       //
//                WgIntrSphere3Sphere3.h                 //
//                                                       //
//  - Interface for Intersection Sphere3 Sphere3 class   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_INTRSPHERE3SPHERE3_H__
#define __WG_INTRSPHERE3SPHERE3_H__

#include "WgFoundationLIB.h"
#include "WgIntersector.h"
#include "WgSphere3.h"

namespace WGSoft3D
{

template <class Real>
class WG3D_FOUNDATION_ITEM IntrSphere3Sphere3 : public Intersector<Real,Vector3<Real> >
{
public:
    IntrSphere3Sphere3 (const Sphere3<Real>& rkSphere0,
        const Sphere3<Real>& rkSphere1);

    // object access
    const Sphere3<Real>& GetSphere0 () const;
    const Sphere3<Real>& GetSphere1 () const;

    // static test-intersection query
    virtual bool Test ();

    // static find-intersection query
    virtual bool Find ();

    // intersection set for static find-intersection query
    const Vector3<Real>& GetCenter () const;
    const Vector3<Real>& GetUAxis () const;
    const Vector3<Real>& GetVAxis () const;
    const Vector3<Real>& GetNormal () const;
    Real GetRadius () const;

    // dynamic test-intersection query
    virtual bool Test (Real fTMax, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);

    // dynamic find-intersection query
    virtual bool Find (Real fTMax, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);

    // intersection set for dynamic find-intersection query
    const Vector3<Real>& GetContactPoint () const;

private:
    using Intersector<Real,Vector3<Real> >::m_fContactTime;

    // the objects to intersect
    const Sphere3<Real>& m_rkSphere0;
    const Sphere3<Real>& m_rkSphere1;

    // Circle of intersection for static spheres.  The center is C and lies
    // on a plane spanned by the unit-length, orthogonal vectors U and V.
    // The plane normal is a unit-length vector N.  The radius of the circle
    // in that plane is R.
    Vector3<Real> m_kCenter, m_kUAxis, m_kVAxis, m_kNormal;
    Real m_fRadius;

    // Point of intersection for dynamic spheres.
    Vector3<Real> m_kContactPoint;
};

class WG3D_FOUNDATION_ITEM IntrSphere3Sphere3x : public Intersector3x
{
public:
    IntrSphere3Sphere3x (const Sphere3x& rkSphere0,
        const Sphere3x& rkSphere1);
	
    // object access
    const Sphere3x& GetSphere0 () const;
    const Sphere3x& GetSphere1 () const;
	
    // static test-intersection query
    virtual bool Test ();
	
    // static find-intersection query
    virtual bool Find ();
	
    // intersection set for static find-intersection query
    const Vector3x& GetCenter () const;
    const Vector3x& GetUAxis () const;
    const Vector3x& GetVAxis () const;
    const Vector3x& GetNormal () const;
    fixed GetRadius () const;
	
    // dynamic test-intersection query
    virtual bool Test (fixed fTMax, const Vector3x& rkVelocity0,
        const Vector3x& rkVelocity1);
	
    // dynamic find-intersection query
    virtual bool Find (fixed fTMax, const Vector3x& rkVelocity0,
        const Vector3x& rkVelocity1);
	
    // intersection set for dynamic find-intersection query
    const Vector3x& GetContactPoint () const;
	
private:
    using Intersector3x::m_fContactTime;
	
    // the objects to intersect
    const Sphere3x& m_rkSphere0;
    const Sphere3x& m_rkSphere1;
	
    // Circle of intersection for static spheres.  The center is C and lies
    // on a plane spanned by the unit-length, orthogonal vectors U and V.
    // The plane normal is a unit-length vector N.  The radius of the circle
    // in that plane is R.
    Vector3x m_kCenter, m_kUAxis, m_kVAxis, m_kNormal;
    fixed m_fRadius;
	
    // Point of intersection for dynamic spheres.
    Vector3x m_kContactPoint;
};

typedef IntrSphere3Sphere3<float> IntrSphere3Sphere3f;
typedef IntrSphere3Sphere3<double> IntrSphere3Sphere3d;

#include "WgIntrSphere3Sphere3.inl"
}

#endif

