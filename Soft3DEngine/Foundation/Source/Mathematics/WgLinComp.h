///////////////////////////////////////////////////////////
//                                                       //
//                    WgLinComp.h                        //
//                                                       //
//  - Interface for Lin Comp class                       //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#ifndef __WG_LINCOMP_H__
#define __WG_LINCOMP_H__

#include "WgFoundationLIB.h"
#include "WgMath.h"

namespace WGSoft3D
{

template <class Real>
class LinComp
{
public:
    // abstract base class
    virtual ~LinComp ();

    // The linear component is represented as P+t*D where P is the component
    // origin and D is a unit-length direction vector.  The user must ensure
    // that the direction vector satisfies this condition.  The t-intervals
    // for lines, rays, segments, points, or the empty set are described
    // later.

    // component type
    enum
    {
        CT_EMPTY,
        CT_POINT,
        CT_SEGMENT,
        CT_RAY,
        CT_LINE
    };

    int GetType () const;

    // The interval of restriction for t, as defined above.  The function
    // SetInterval(min,max) sets the t-interval; it handles all possible
    // inputs according to the following scheme:
    //   CT_LINE:
    //     [-MAX_REAL,MAX_REAL]
    //   CT_RAY:
    //     [min,MAX_REAL], where min is finite
    //     [-MAX_REAL,max], where max is finite
    //   CT_SEGMENT:
    //     [min,max], where min and max are finite with min < max
    //   CT_POINT:
    //     [min,max], where min and max are finite with min = max
    //   CT_EMPTY:
    //     [min,max], where min > max or min = max = MAX_REAL or
    //                min = max = -MAX_REAL
    void SetInterval (Real fMin, Real fMax);

    // Determine the type of an interval without having to create an instance
    // of a LinComp object.
    static int GetTypeFromInterval (Real fMin, Real fMax);

    // The canonical intervals are [-MAX_REAL,MAX_REAL] for a line;
    // [0,MAX_REAL] for a ray; [-e,e] for a segment, where e > 0; [0,0] for
    // a point, and [MAX_REAL,-MAX_REAL] for the empty set.  If the interval
    // is [min,max], the adjustments are as follows.
    // 
    // CT_RAY:  If max is MAX_REAL and if min is not zero, then P is modified
    // to P' = P+min*D so that the ray is represented by P'+t*D for t >= 0.
    // If min is -MAX_REAL and max is finite, then the origin and direction
    // are modified to P' = P+max*D and D' = -D.
    //
    // CT_SEGMENT:  If min is not -max, then P is modified to
    // P' = P + ((min+max)/2)*D and the extent is e' = (max-min)/2.
    //
    // CT_POINT:  If min is not zero, the P is modified to P' = P+min*D.
    //
    // CT_EMPTY:  Set max to -MAX_REAL and min to MAX_REAL.
    //
    // The first function is virtual since the updates are dependent on the
    // dimension of the vector space.
    virtual void MakeCanonical () = 0;
    bool IsCanonical () const;

    // access the interval [min,max]
    Real GetMin () const;
    Real GetMax () const;

    // Determine if the specified parameter is in the interval.
    bool Contains (Real fParam) const;

protected:
    LinComp ();  // default is CT_NONE

    // assignment
    LinComp& operator= (const LinComp& rkComponent);

    // component type
    int m_iType;

    // the interval of restriction for t
    Real m_fMin, m_fMax;
};


class WG3D_FOUNDATION_ITEM LinCompx
{
public:
    // abstract base class
    virtual ~LinCompx ();
	
    // The linear component is represented as P+t*D where P is the component
    // origin and D is a unit-length direction vector.  The user must ensure
    // that the direction vector satisfies this condition.  The t-intervals
    // for lines, rays, segments, points, or the empty set are described
    // later.
	
    // component type
    enum
    {
        CT_EMPTY,
			CT_POINT,
			CT_SEGMENT,
			CT_RAY,
			CT_LINE
    };
	
    int GetType () const;
	
    // The interval of restriction for t, as defined above.  The function
    // SetInterval(min,max) sets the t-interval; it handles all possible
    // inputs according to the following scheme:
    //   CT_LINE:
    //     [-MAX_REAL,MAX_REAL]
    //   CT_RAY:
    //     [min,MAX_REAL], where min is finite
    //     [-MAX_REAL,max], where max is finite
    //   CT_SEGMENT:
    //     [min,max], where min and max are finite with min < max
    //   CT_POINT:
    //     [min,max], where min and max are finite with min = max
    //   CT_EMPTY:
    //     [min,max], where min > max or min = max = MAX_REAL or
    //                min = max = -MAX_REAL
    void SetInterval (fixed fMin, fixed fMax);
	
    // Determine the type of an interval without having to create an instance
    // of a LinComp object.
    static int GetTypeFromInterval (fixed fMin, fixed fMax);
	
    // The canonical intervals are [-MAX_REAL,MAX_REAL] for a line;
    // [0,MAX_REAL] for a ray; [-e,e] for a segment, where e > 0; [0,0] for
    // a point, and [MAX_REAL,-MAX_REAL] for the empty set.  If the interval
    // is [min,max], the adjustments are as follows.
    // 
    // CT_RAY:  If max is MAX_REAL and if min is not zero, then P is modified
    // to P' = P+min*D so that the ray is represented by P'+t*D for t >= 0.
    // If min is -MAX_REAL and max is finite, then the origin and direction
    // are modified to P' = P+max*D and D' = -D.
    //
    // CT_SEGMENT:  If min is not -max, then P is modified to
    // P' = P + ((min+max)/2)*D and the extent is e' = (max-min)/2.
    //
    // CT_POINT:  If min is not zero, the P is modified to P' = P+min*D.
    //
    // CT_EMPTY:  Set max to -MAX_REAL and min to MAX_REAL.
    //
    // The first function is virtual since the updates are dependent on the
    // dimension of the vector space.
    virtual void MakeCanonical () = 0;
    bool IsCanonical () const;
	
    // access the interval [min,max]
    fixed GetMin () const;
    fixed GetMax () const;
	
    // Determine if the specified parameter is in the interval.
    bool Contains (fixed fParam) const;
	
protected:
    LinCompx ();  // default is CT_NONE
	
    // assignment
    LinCompx& operator= (const LinCompx& rkComponent);
	
    // component type
    int m_iType;
	
    // the interval of restriction for t
    fixed m_fMin, m_fMax;
};


#include "WgLinComp.inl"

typedef LinComp<float> LinCompf;
typedef LinComp<double> LinCompd;

}

#endif
