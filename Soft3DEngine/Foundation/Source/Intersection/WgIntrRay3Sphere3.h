///////////////////////////////////////////////////////////
//                                                       //
//                WgIntrRay3Sphere3.h                    //
//                                                       //
//  - Interface for Intersection Ray3 Sphere3 class      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_INTRRAY3SPHERE3_H__
#define __WG_INTRRAY3SPHERE3_H__

#include "WgFoundationLIB.h"
#include "WgIntersector.h"
#include "WgRay3.h"
#include "WgSphere3.h"

namespace WGSoft3D
{

template <class Real>
class WG3D_FOUNDATION_ITEM IntrRay3Sphere3 : public Intersector<Real,Vector3<Real> >
{
public:
    IntrRay3Sphere3 (const Ray3<Real>& rkRay, const Sphere3<Real>& rkSphere);

    // object access
    const Ray3<Real>& GetRay () const;
    const Sphere3<Real>& GetSphere () const;

    // test-intersection query
    virtual bool Test ();

    // find-intersection query
    virtual bool Find ();
    int GetQuantity () const;
    const Vector3<Real>& GetPoint (int i) const;
    Real GetRayT (int i) const;

private:
    // the objects to intersect
    const Ray3<Real>& m_rkRay;
    const Sphere3<Real>& m_rkSphere;

    // information about the intersection set
    int m_iQuantity;
    Vector3<Real> m_akPoint[2];
    Real m_afRayT[2];
};

class WG3D_FOUNDATION_ITEM IntrRay3Sphere3x : public Intersector3x
{
public:
    IntrRay3Sphere3x (const Ray3x& rkRay, const Sphere3x& rkSphere);
	
    // object access
    const Ray3x& GetRay () const;
    const Sphere3x& GetSphere () const;
	
    // test-intersection query
    virtual bool Test ();
	
    // find-intersection query
    virtual bool Find ();
    int GetQuantity () const;
    const Vector3x& GetPoint (int i) const;
    fixed GetRayT (int i) const;
	
private:
    // the objects to intersect
    const Ray3x& m_rkRay;
    const Sphere3x& m_rkSphere;
	
    // information about the intersection set
    int m_iQuantity;
    Vector3x m_akPoint[2];
    fixed m_afRayT[2];
};

typedef IntrRay3Sphere3<float> IntrRay3Sphere3f;
typedef IntrRay3Sphere3<double> IntrRay3Sphere3d;

#include "WgIntrRay3Sphere3.inl"
}

#endif

