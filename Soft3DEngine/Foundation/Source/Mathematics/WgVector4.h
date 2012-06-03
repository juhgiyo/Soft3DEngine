///////////////////////////////////////////////////////////
//                                                       //
//                    WgVector4.h                        //
//                                                       //
//  - Interface for Vector4 class                        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_VECTOR_4_H__
#define __WG_VECTOR_4_H__

#include "WgFoundationLIB.h"
#include "WgMath.h"

namespace WGSoft3D
{

template <class Real>
class Vector4
{
public:
    // construction
    Vector4 ();  // uninitialized
    Vector4 (Real fX, Real fY, Real fZ, Real fW);
    Vector4 (const Real* afTuple);
    Vector4 (const Vector4& rkV);

    // coordinate access
    inline operator const Real* () const;
    inline operator Real* ();
    inline Real operator[] (int i) const;
    inline Real& operator[] (int i);
    inline Real X () const;
    inline Real& X ();
    inline Real Y () const;
    inline Real& Y ();
    inline Real Z () const;
    inline Real& Z ();
    inline Real W () const;
    inline Real& W ();

    // assignment
    inline Vector4& operator= (const Vector4& rkV);

    // comparison
    bool operator== (const Vector4& rkV) const;
    bool operator!= (const Vector4& rkV) const;
    bool operator<  (const Vector4& rkV) const;
    bool operator<= (const Vector4& rkV) const;
    bool operator>  (const Vector4& rkV) const;
    bool operator>= (const Vector4& rkV) const;

    // arithmetic operations
    inline Vector4 operator+ (const Vector4& rkV) const;
    inline Vector4 operator- (const Vector4& rkV) const;
    inline Vector4 operator* (Real fScalar) const;
    inline Vector4 operator/ (Real fScalar) const;
    inline Vector4 operator- () const;

    // arithmetic updates
    inline Vector4& operator+= (const Vector4& rkV);
    inline Vector4& operator-= (const Vector4& rkV);
    inline Vector4& operator*= (Real fScalar);
    inline Vector4& operator/= (Real fScalar);

    // vector operations
    inline Real Length () const;
    inline Real SquaredLength () const;
    inline Real Dot (const Vector4& rkV) const;
    inline Real Normalize ();

    // special vectors
    WG3D_FOUNDATION_ITEM static const Vector4 ZERO;
    WG3D_FOUNDATION_ITEM static const Vector4 UNIT_X;  // (1,0,0,0)
    WG3D_FOUNDATION_ITEM static const Vector4 UNIT_Y;  // (0,1,0,0)
    WG3D_FOUNDATION_ITEM static const Vector4 UNIT_Z;  // (0,0,1,0)
    WG3D_FOUNDATION_ITEM static const Vector4 UNIT_W;  // (0,0,0,1)
    WG3D_FOUNDATION_ITEM static const Vector4 ONE;     // (1,1,1,1)

private:
    // support for comparisons
    int CompareArrays (const Vector4& rkV) const;

    Real m_afTuple[4];
};

class WG3D_FOUNDATION_ITEM Vector4x
{
public:
    // construction
    Vector4x ();  // uninitialized
    Vector4x (fixed fX, fixed fY, fixed fZ, fixed fW);
    Vector4x (const fixed* afTuple);
    Vector4x (const Vector4x& rkV);
	
    // coordinate access
    inline operator const fixed* () const;
    inline operator fixed* ();
    inline fixed operator[] (int i) const;
    inline fixed& operator[] (int i);
    inline fixed X () const;
    inline fixed& X ();
    inline fixed Y () const;
    inline fixed& Y ();
    inline fixed Z () const;
    inline fixed& Z ();
    inline fixed W () const;
    inline fixed& W ();
	
    // assignment
    inline Vector4x& operator= (const Vector4x& rkV);
	
    // comparison
    bool operator== (const Vector4x& rkV) const;
    bool operator!= (const Vector4x& rkV) const;
    bool operator<  (const Vector4x& rkV) const;
    bool operator<= (const Vector4x& rkV) const;
    bool operator>  (const Vector4x& rkV) const;
    bool operator>= (const Vector4x& rkV) const;
	
    // arithmetic operations
    inline Vector4x operator+ (const Vector4x& rkV) const;
    inline Vector4x operator- (const Vector4x& rkV) const;
    inline Vector4x operator* (fixed fScalar) const;
    inline Vector4x operator/ (fixed fScalar) const;
    inline Vector4x operator- () const;
	
    // arithmetic updates
    inline Vector4x& operator+= (const Vector4x& rkV);
    inline Vector4x& operator-= (const Vector4x& rkV);
    inline Vector4x& operator*= (fixed fScalar);
    inline Vector4x& operator/= (fixed fScalar);
	
    // vector operations
    inline fixed Length () const;
    inline fixed SquaredLength () const;
    inline fixed Dot (const Vector4x& rkV) const;
    inline fixed Normalize ();
	
    // special vectors
    static const Vector4x ZERO;
    static const Vector4x UNIT_X;  // (1,0,0,0)
    static const Vector4x UNIT_Y;  // (0,1,0,0)
    static const Vector4x UNIT_Z;  // (0,0,1,0)
    static const Vector4x UNIT_W;  // (0,0,0,1)
    static const Vector4x ONE;     // (1,1,1,1)
	
private:
    // support for comparisons
    int CompareArrays (const Vector4x& rkV) const;
	
    fixed m_afTuple[4];
};

// arithmetic operations
template <class Real>
Vector4<Real> operator* (Real fScalar, const Vector4<Real>& rkV);
Vector4x operator* (fixed fScalar, const Vector4x& rkV);

// debugging output
#ifndef _WIN32_WCE
template <class Real>
std::ostream& operator<< (std::ostream& rkOStr, const Vector4<Real>& rkV);
std::ostream& operator<< (std::ostream& rkOStr, const Vector4x& rkV);
#endif
#include "WgVector4.inl"

typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;

}

#endif
