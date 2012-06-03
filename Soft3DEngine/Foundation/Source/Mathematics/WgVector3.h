///////////////////////////////////////////////////////////
//                                                       //
//                    WgVector3.h                        //
//                                                       //
//  - Interface for Vector3 class                        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_VECTOR_3_H__
#define __WG_VECTOR_3_H__

#include "WgFoundationLIB.h"
#include "WgMath.h"

namespace WGSoft3D
{

template <class Real>
class Vector3
{
public:
    // construction
    Vector3 ();  // uninitialized
    Vector3 (Real fX, Real fY, Real fZ);
    Vector3 (const Real* afTuple);
    Vector3 (const Vector3& rkV);

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

    // assignment
    inline Vector3& operator= (const Vector3& rkV);

    // comparison
    bool operator== (const Vector3& rkV) const;
    bool operator!= (const Vector3& rkV) const;
    bool operator<  (const Vector3& rkV) const;
    bool operator<= (const Vector3& rkV) const;
    bool operator>  (const Vector3& rkV) const;
    bool operator>= (const Vector3& rkV) const;

    // arithmetic operations
    inline Vector3 operator+ (const Vector3& rkV) const;
    inline Vector3 operator- (const Vector3& rkV) const;
    inline Vector3 operator* (Real fScalar) const;
    inline Vector3 operator/ (Real fScalar) const;
    inline Vector3 operator- () const;

    // arithmetic updates
    inline Vector3& operator+= (const Vector3& rkV);
    inline Vector3& operator-= (const Vector3& rkV);
    inline Vector3& operator*= (Real fScalar);
    inline Vector3& operator/= (Real fScalar);

    // vector operations
    inline Real Length () const;
    inline Real SquaredLength () const;
    inline Real Dot (const Vector3& rkV) const;
    inline Real Normalize ();

    // The cross products are computed using the right-handed rule.  Be aware
    // that some graphics APIs use a left-handed rule.  If you have to compute
    // a cross product with these functions and send the result to the API
    // that expects left-handed, you will need to change sign on the vector
    // (replace each component value c by -c).
    inline Vector3 Cross (const Vector3& rkV) const;
    inline Vector3 UnitCross (const Vector3& rkV) const;

    // Compute the barycentric coordinates of the point with respect to the
    // tetrahedron <V0,V1,V2,V3>, P = b0*V0 + b1*V1 + b2*V2 + b3*V3, where
    // b0 + b1 + b2 + b3 = 1.
    void GetBarycentrics (const Vector3& rkV0, const Vector3& rkV1,
        const Vector3& rkV2, const Vector3& rkV3, Real afBary[4]) const;

    // Gram-Schmidt orthonormalization.  Take linearly independent vectors
    // U, V, and W and compute an orthonormal set (unit length, mutually
    // perpendicular).
    static void Orthonormalize (Vector3& rkU, Vector3& rkV, Vector3& rkW);
    static void Orthonormalize (Vector3* akV);

    // Input W must be a nonzero vector. The output is an orthonormal basis
    // {U,V,W}.  The input W is normalized by this function.  If you know
    // W is already unit length, use GenerateComplementBasis to compute U
    // and V.
    static void GenerateOrthonormalBasis (Vector3& rkU, Vector3& rkV,
        Vector3& rkW);

    // Input W must be a unit-length vector.  The output vectors {U,V} are
    // unit length and mutually perpendicular, and {U,V,W} is an orthonormal
    // basis.
    static void GenerateComplementBasis (Vector3& rkU, Vector3& rkV,
        const Vector3& rkW);

    // Compute the extreme values.
    static void ComputeExtremes (int iVQuantity, const Vector3* akPoint,
        Vector3& rkMin, Vector3& rkMax);

    // special vectors
    WG3D_FOUNDATION_ITEM static const Vector3 ZERO;    // (0,0,0)
    WG3D_FOUNDATION_ITEM static const Vector3 UNIT_X;  // (1,0,0)
    WG3D_FOUNDATION_ITEM static const Vector3 UNIT_Y;  // (0,1,0)
    WG3D_FOUNDATION_ITEM static const Vector3 UNIT_Z;  // (0,0,1)
    WG3D_FOUNDATION_ITEM static const Vector3 ONE;     // (1,1,1)

private:
    // support for comparisons
    int CompareArrays (const Vector3& rkV) const;

    Real m_afTuple[3];
};

class WG3D_FOUNDATION_ITEM Vector3x
{
public:
    // construction
    Vector3x ();  // uninitialized
    Vector3x (fixed fX, fixed fY, fixed fZ);
    Vector3x (const fixed* afTuple);
    Vector3x (const Vector3x& rkV);

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

    // assignment
    inline Vector3x& operator= (const Vector3x& rkV);

    // comparison
    bool operator== (const Vector3x& rkV) const;
    bool operator!= (const Vector3x& rkV) const;
    bool operator<  (const Vector3x& rkV) const;
    bool operator<= (const Vector3x& rkV) const;
    bool operator>  (const Vector3x& rkV) const;
    bool operator>= (const Vector3x& rkV) const;

    // arithmetic operations
    inline Vector3x operator+ (const Vector3x& rkV) const;
    inline Vector3x operator- (const Vector3x& rkV) const;
    inline Vector3x operator* (fixed fScalar) const;
    inline Vector3x operator/ (fixed fScalar) const;
    inline Vector3x operator- () const;

    // arithmetic updates
    inline Vector3x& operator+= (const Vector3x& rkV);
    inline Vector3x& operator-= (const Vector3x& rkV);
    inline Vector3x& operator*= (fixed fScalar);
    inline Vector3x& operator/= (fixed fScalar);

    // vector operations
    inline fixed Length () const;
    inline fixed SquaredLength () const;
    inline fixed Dot (const Vector3x& rkV) const;
    inline fixed Normalize ();

    // The cross products are computed using the right-handed rule.  Be aware
    // that some graphics APIs use a left-handed rule.  If you have to compute
    // a cross product with these functions and send the result to the API
    // that expects left-handed, you will need to change sign on the vector
    // (replace each component value c by -c).
    inline Vector3x Cross (const Vector3x& rkV) const;
    inline Vector3x UnitCross (const Vector3x& rkV) const;

    // Compute the barycentric coordinates of the point with respect to the
    // tetrahedron <V0,V1,V2,V3>, P = b0*V0 + b1*V1 + b2*V2 + b3*V3, where
    // b0 + b1 + b2 + b3 = 1.
    void GetBarycentrics (const Vector3x& rkV0, const Vector3x& rkV1,
        const Vector3x& rkV2, const Vector3x& rkV3, fixed afBary[4]) const;

    // Gram-Schmidt orthonormalization.  Take linearly independent vectors
    // U, V, and W and compute an orthonormal set (unit length, mutually
    // perpendicular).
    static void Orthonormalize (Vector3x& rkU, Vector3x& rkV, Vector3x& rkW);
    static void Orthonormalize (Vector3x* akV);

    // Input W must be a nonzero vector. The output is an orthonormal basis
    // {U,V,W}.  The input W is normalized by this function.  If you know
    // W is already unit length, use GenerateComplementBasis to compute U
    // and V.
    static void GenerateOrthonormalBasis (Vector3x& rkU, Vector3x& rkV,Vector3x& rkW);

    // Input W must be a unit-length vector.  The output vectors {U,V} are
    // unit length and mutually perpendicular, and {U,V,W} is an orthonormal
    // basis.
    static void GenerateComplementBasis (Vector3x& rkU, Vector3x& rkV, const Vector3x& rkW);

    // Compute the extreme values.
    static void ComputeExtremes (int iVQuantity, const Vector3x* akPoint,Vector3x& rkMin, Vector3x& rkMax);

    // special vectors
    static const Vector3x ZERO;    // (0,0,0)
    static const Vector3x UNIT_X;  // (1,0,0)
    static const Vector3x UNIT_Y;  // (0,1,0)
    static const Vector3x UNIT_Z;  // (0,0,1)
    static const Vector3x ONE;     // (1,1,1)

private:
    // support for comparisons
    int CompareArrays (const Vector3x& rkV) const;

    fixed m_afTuple[3];
};


// arithmetic operations

template <class Real>
Vector3<Real> operator* (Real fScalar, const Vector3<Real>& rkV);
Vector3x operator* (fixed fScalar, const Vector3x& rkV);


// debugging output
#ifndef _WIN32_WCE
template <class Real>
std::ostream& operator<< (std::ostream& rkOStr, const Vector3<Real>& rkV);
std::ostream& operator<< (std::ostream& rkOStr, const Vector3x& rkV);
#endif //_WIN32_WCE

#include "WgVector3.inl"
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

}

#endif
