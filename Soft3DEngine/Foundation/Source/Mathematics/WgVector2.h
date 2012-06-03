///////////////////////////////////////////////////////////
//                                                       //
//                    WgVector2.h                        //
//                                                       //
//  - Interface for Vector2 class                        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_VECTOR_2_H__
#define __WG_VECTOR_2_H__

#include "WgFoundationLIB.h"
#include "WgMath.h"

namespace WGSoft3D
{

template <class Real>
class Vector2
{
public:
    // construction
    Vector2 ();  // uninitialized
    Vector2 (Real fX, Real fY);
    Vector2 (const Real* afTuple);
    Vector2 (const Vector2& rkV);

    // coordinate access
    inline operator const Real* () const;
    inline operator Real* ();
    inline Real operator[] (int i) const;
    inline Real& operator[] (int i);
    inline Real X () const;
    inline Real& X ();
    inline Real Y () const;
    inline Real& Y ();

    // assignment
    inline Vector2& operator= (const Vector2& rkV);

    // comparison
    bool operator== (const Vector2& rkV) const;
    bool operator!= (const Vector2& rkV) const;
    bool operator<  (const Vector2& rkV) const;
    bool operator<= (const Vector2& rkV) const;
    bool operator>  (const Vector2& rkV) const;
    bool operator>= (const Vector2& rkV) const;

    // arithmetic operations
    inline Vector2 operator+ (const Vector2& rkV) const;
    inline Vector2 operator- (const Vector2& rkV) const;
    inline Vector2 operator* (Real fScalar) const;
    inline Vector2 operator/ (Real fScalar) const;
    inline Vector2 operator- () const;

    // arithmetic updates
    inline Vector2& operator+= (const Vector2& rkV);
    inline Vector2& operator-= (const Vector2& rkV);
    inline Vector2& operator*= (Real fScalar);
    inline Vector2& operator/= (Real fScalar);

    // vector operations
    inline Real Length () const;
    inline Real SquaredLength () const;
    inline Real Dot (const Vector2& rkV) const;
    inline Real Normalize ();

    // returns (y,-x)
    inline Vector2 Perp () const;

    // returns (y,-x)/sqrt(x*x+y*y)
    inline Vector2 UnitPerp () const;

    // returns DotPerp((x,y),(V.x,V.y)) = x*V.y - y*V.x
    inline Real DotPerp (const Vector2& rkV) const;

    // Compute the barycentric coordinates of the point with respect to the
    // triangle <V0,V1,V2>, P = b0*V0 + b1*V1 + b2*V2, where b0 + b1 + b2 = 1.
    void GetBarycentrics (const Vector2& rkV0, const Vector2& rkV1,
        const Vector2& rkV2, Real afBary[3]) const;

    // Gram-Schmidt orthonormalization.  Take linearly independent vectors U
    // and V and compute an orthonormal set (unit length, mutually
    // perpendicular).
    static void Orthonormalize (Vector2& rkU, Vector2& rkV);

    // Input V must be a nonzero vector.  The output is an orthonormal basis
    // {U,V}.  The input V is normalized by this function.  If you know V is
    // already unit length, use U = V.Perp().
    static void GenerateOrthonormalBasis (Vector2& rkU, Vector2& rkV);

    // Compute the extreme values.
    static void ComputeExtremes (int iVQuantity, const Vector2* akPoint,
        Vector2& rkMin, Vector2& rkMax);

    // special vectors
    WG3D_FOUNDATION_ITEM static const Vector2 ZERO;    // (0,0)
    WG3D_FOUNDATION_ITEM static const Vector2 UNIT_X;  // (1,0)
    WG3D_FOUNDATION_ITEM static const Vector2 UNIT_Y;  // (0,1)
    WG3D_FOUNDATION_ITEM static const Vector2 ONE;     // (1,1)

private:
    // support for comparisons
    int CompareArrays (const Vector2& rkV) const;

    Real m_afTuple[2];
};

class WG3D_FOUNDATION_ITEM Vector2x
{
public:
    // construction
    Vector2x ();  // uninitialized
    Vector2x (fixed fX, fixed fY);
    Vector2x (const fixed* afTuple);
    Vector2x (const Vector2x& rkV);
	
    // coordinate access
    inline operator const fixed* () const;
    inline operator fixed* ();
    inline fixed operator[] (int i) const;
    inline fixed& operator[] (int i);
    inline fixed X () const;
    inline fixed& X ();
    inline fixed Y () const;
    inline fixed& Y ();
	
    // assignment
    inline Vector2x& operator= (const Vector2x& rkV);
	
    // comparison
    bool operator== (const Vector2x& rkV) const;
    bool operator!= (const Vector2x& rkV) const;
    bool operator<  (const Vector2x& rkV) const;
    bool operator<= (const Vector2x& rkV) const;
    bool operator>  (const Vector2x& rkV) const;
    bool operator>= (const Vector2x& rkV) const;
	
    // arithmetic operations
    inline Vector2x operator+ (const Vector2x& rkV) const;
    inline Vector2x operator- (const Vector2x& rkV) const;
    inline Vector2x operator* (fixed fScalar) const;
    inline Vector2x operator/ (fixed fScalar) const;
    inline Vector2x operator- () const;
	
    // arithmetic updates
    inline Vector2x& operator+= (const Vector2x& rkV);
    inline Vector2x& operator-= (const Vector2x& rkV);
    inline Vector2x& operator*= (fixed fScalar);
    inline Vector2x& operator/= (fixed fScalar);
	
    // vector operations
    inline fixed Length () const;
    inline fixed SquaredLength () const;
    inline fixed Dot (const Vector2x& rkV) const;
    inline fixed Normalize ();
	
    // returns (y,-x)
    inline Vector2x Perp () const;
	
    // returns (y,-x)/sqrt(x*x+y*y)
    inline Vector2x UnitPerp () const;
	
    // returns DotPerp((x,y),(V.x,V.y)) = x*V.y - y*V.x
    inline fixed DotPerp (const Vector2x& rkV) const;
	
    // Compute the barycentric coordinates of the point with respect to the
    // triangle <V0,V1,V2>, P = b0*V0 + b1*V1 + b2*V2, where b0 + b1 + b2 = 1.
    void GetBarycentrics (const Vector2x& rkV0, const Vector2x& rkV1,
        const Vector2x& rkV2, fixed afBary[3]) const;
	
    // Gram-Schmidt orthonormalization.  Take linearly independent vectors U
    // and V and compute an orthonormal set (unit length, mutually
    // perpendicular).
    static void Orthonormalize (Vector2x& rkU, Vector2x& rkV);
	
    // Input V must be a nonzero vector.  The output is an orthonormal basis
    // {U,V}.  The input V is normalized by this function.  If you know V is
    // already unit length, use U = V.Perp().
    static void GenerateOrthonormalBasis (Vector2x& rkU, Vector2x& rkV);
	
    // Compute the extreme values.
    static void ComputeExtremes (int iVQuantity, const Vector2x* akPoint,
        Vector2x& rkMin, Vector2x& rkMax);
	
    // special vectors
    static const Vector2x ZERO;    // (0,0)
    static const Vector2x UNIT_X;  // (1,0)
    static const Vector2x UNIT_Y;  // (0,1)
    static const Vector2x ONE;     // (1,1)
	
private:
    // support for comparisons
    int CompareArrays (const Vector2x& rkV) const;
	
    fixed m_afTuple[2];
};

// arithmetic operations
template <class Real>
Vector2<Real> operator* (Real fScalar, const Vector2<Real>& rkV);
Vector2x operator* (fixed fScalar, const Vector2x& rkV);

// debugging output
#ifndef _WIN32_WCE
template <class Real>
std::ostream& operator<< (std::ostream& rkOStr, const Vector2<Real>& rkV);
std::ostream& operator<< (std::ostream& rkOStr, const Vector2x& rkV);
#endif //_WIN32_WCE

#include "WgVector2.inl"

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

}

#endif
