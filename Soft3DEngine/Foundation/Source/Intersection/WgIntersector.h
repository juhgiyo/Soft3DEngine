///////////////////////////////////////////////////////////
//                                                       //
//                WgIntersector.h                        //
//                                                       //
//  - Interface for Intersector class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_INTERSECTOR_H__
#define __WG_INTERSECTOR_H__

#include "WgFoundationLIB.h"
#include "WgLinComp.h"
#include "WgVector2.h"
#include "WgVector3.h"

namespace WGSoft3D
{

template <class Real, class TVector>
class WG3D_FOUNDATION_ITEM Intersector
{
public:
    // abstract base class
    virtual ~Intersector ();

    // Static intersection queries.  The default implementations return
    // 'false'.  The Find query produces a set of intersection.  The derived
    // class is responsible for providing access to that set, since the nature
    // of the set is dependent on the object types.
    virtual bool Test ();
    virtual bool Find ();

    // Dynamic intersection queries.  The default implementations return
    // 'false'.  The Find query produces a set of first contact.  The derived
    // class is responsible for providing access to that set, since the nature
    // of the set is dependent on the object types.
    virtual bool Test (Real fTMax, const TVector& rkVelocity0,
        const TVector& rkVelocity1);
    virtual bool Find (Real fTMax, const TVector& rkVelocity0,
        const TVector& rkVelocity1);

    // The time at which two objects are in first contact for the dynamic
    // intersection queries.
    Real GetContactTime () const;

    // information about the intersection set
    enum
    {
        IT_EMPTY = LinComp<Real>::CT_EMPTY,
        IT_POINT = LinComp<Real>::CT_POINT,
        IT_SEGMENT = LinComp<Real>::CT_SEGMENT,
        IT_RAY = LinComp<Real>::CT_RAY,
        IT_LINE = LinComp<Real>::CT_LINE,
        IT_POLYGON,
        IT_PLANE,
        IT_POLYHEDRON,
        IT_OTHER
    };
    int GetIntersectionType () const;

protected:
    Intersector ();

    Real m_fContactTime;
    int m_iIntersectionType;
};

class WG3D_FOUNDATION_ITEM Intersector3x
{
public:
    // abstract base class
    virtual ~Intersector3x ();
	
    // Static intersection queries.  The default implementations return
    // 'false'.  The Find query produces a set of intersection.  The derived
    // class is responsible for providing access to that set, since the nature
    // of the set is dependent on the object types.
    virtual bool Test ();
    virtual bool Find ();
	
    // Dynamic intersection queries.  The default implementations return
    // 'false'.  The Find query produces a set of first contact.  The derived
    // class is responsible for providing access to that set, since the nature
    // of the set is dependent on the object types.
    virtual bool Test (fixed fTMax, const Vector3x& rkVelocity0,
        const Vector3x& rkVelocity1);
    virtual bool Find (fixed fTMax, const Vector3x& rkVelocity0,
        const Vector3x& rkVelocity1);
	
    // The time at which two objects are in first contact for the dynamic
    // intersection queries.
    fixed GetContactTime () const;
	
    // information about the intersection set
    enum
    {
        IT_EMPTY = LinCompx::CT_EMPTY,
			IT_POINT = LinCompx::CT_POINT,
			IT_SEGMENT = LinCompx::CT_SEGMENT,
			IT_RAY = LinCompx::CT_RAY,
			IT_LINE = LinCompx::CT_LINE,
			IT_POLYGON,
			IT_PLANE,
			IT_POLYHEDRON,
			IT_OTHER
    };
    int GetIntersectionType () const;
	
protected:
    Intersector3x ();
	
    fixed m_fContactTime;
    int m_iIntersectionType;
};
class WG3D_FOUNDATION_ITEM Intersector2x
{
public:
    // abstract base class
    virtual ~Intersector2x ();
	
    // Static intersection queries.  The default implementations return
    // 'false'.  The Find query produces a set of intersection.  The derived
    // class is responsible for providing access to that set, since the nature
    // of the set is dependent on the object types.
    virtual bool Test ();
    virtual bool Find ();
	
    // Dynamic intersection queries.  The default implementations return
    // 'false'.  The Find query produces a set of first contact.  The derived
    // class is responsible for providing access to that set, since the nature
    // of the set is dependent on the object types.
    virtual bool Test (fixed fTMax, const Vector2x& rkVelocity0,
        const Vector2x& rkVelocity1);
    virtual bool Find (fixed fTMax, const Vector2x& rkVelocity0,
        const Vector2x& rkVelocity1);
	
    // The time at which two objects are in first contact for the dynamic
    // intersection queries.
    fixed GetContactTime () const;
	
    // information about the intersection set
    enum
    {
        IT_EMPTY = LinCompx::CT_EMPTY,
			IT_POINT = LinCompx::CT_POINT,
			IT_SEGMENT = LinCompx::CT_SEGMENT,
			IT_RAY = LinCompx::CT_RAY,
			IT_LINE = LinCompx::CT_LINE,
			IT_POLYGON,
			IT_PLANE,
			IT_POLYHEDRON,
			IT_OTHER
    };
    int GetIntersectionType () const;
	
protected:
    Intersector2x ();
	
    fixed m_fContactTime;
    int m_iIntersectionType;
};


typedef Intersector<float, Vector2<float> > Intersector2f;
typedef Intersector<float, Vector3<float> > Intersector3f;
typedef Intersector<double, Vector2<double> > Intersector2d;
typedef Intersector<double, Vector3<double> > Intersector3d;

#include "WgIntersector.inl"

}

#endif

