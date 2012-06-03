///////////////////////////////////////////////////////////
//                                                       //
//                    WgTransformation.h                 //
//                                                       //
//  - Interface for Transformation class                 //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_TRANSFORMATION_H__
#define __WG_TRANSFORMATION_H__

#include "WgFoundationLIB.h"
#include "WgMatrix3.h"
#include "WgPlane3.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM Transformation
{
public:
    // The transformation is Y = M*X+T, where M is a 3-by-3 matrix and T is
    // a translation vector.  In most cases, M = R, a rotation matrix, or
    // M = R*S, where R is a rotation matrix and S is a diagonal matrix
    // whose diagonal entries are positive scales.  To support modeling
    // packages that allow reflections and nonuniform scales, I now allow
    // the general transformation Y = M*X+T.  The vector X is transformed in
    // the "forward" direction to Y.  The "inverse" direction transforms Y
    // to X, namely X = M^{-1}*(Y-T) in the general case.  In the special
    // case of M = R*S, the inverse direction is X = S^{-1}*R^t*(Y-T).

    // Construction and destruction.  The default constructor produces the
    // identity transformation.  The default copy constructor is created by
    // the compiler, as is the default assignment operator.  The defaults are
    // consistent with the design of this class.
    Transformation ();
    ~Transformation ();

    // set the transformation to the identity
    void MakeIdentity ();

    // set the scales to 1
    void MakeUnitScale ();

    // Hints about the structure of the transformation.  In the common case
    // of M = R*S, IsRSMatrix() returns true.
    bool IsIdentity () const;
    bool IsRSMatrix () const;
    bool IsUniformScale () const;

    // Member access.
    // (1) The Set* functions set the is-identity hint to false.
    // (2) The SetRotate function sets the is-rsmatrix hint to true.  If this
    //     hint is false,  GetRotate fires an "assert" in debug mode.
    // (3) The SetMatrix function sets the is-rsmatrix and is-uniform-scale
    //     hints to false.
    // (4) The SetScale function sets the is-uniform-scale hint to false.
    //     The SetUniformScale function sets the is-uniform-scale hint to
    //     true.  If this hint is false, GetUniformScale fires an "assert" in
    //     debug mode.
    void SetRotate (const Matrix3x& rkRotate);
    const Matrix3x& GetRotate () const;
    void SetMatrix (const Matrix3x& rkMatrix);
    const Matrix3x& GetMatrix () const;
    void SetTranslate (const Vector3x& rkTranslate);
    const Vector3x& GetTranslate () const;
    void SetScale (const Vector3x& rkScale);
    const Vector3x& GetScale () const;
    void SetUniformScale (fixed fScale);
    fixed GetUniformScale () const;

    // For M = R*S, the largest value of S in absolute value is returned.
    // For general M, the max-column-sum norm is returned and is guaranteed
    // to be larger than or equal to the largest eigenvalue of S in absolute
    // value.
    fixed GetNorm () const;

    // Compute Y = M*X+T where X is the input and Y is the output.
    Vector3x ApplyForward (const Vector3x& rkInput) const;
    void ApplyForward (int iQuantity, const Vector3x* akInput,
        Vector3x* akOutput) const;

    // Compute X = M^{-1}*(Y-T) where Y is the input and X is the output.
    Vector3x ApplyInverse (const Vector3x& rkInput) const;
    void ApplyInverse (int iQuantity, const Vector3x* akInput,
        Vector3x* akOutput) const;

    // Inverse-transform the input vector V0.  The output vector is
    // V1 = M^{-1}*V0.
    Vector3x InvertVector (const Vector3x& rkInput) const;

    // Transform the plane Dot(N0,X) = c0 to Dot(N1,Y) = c1 where both N0 and
    // N1 must be unit-length normals.
    Plane3x ApplyForward (const Plane3x& rkInput) const;

    // Compute C = A*B.
    void Product (const Transformation& rkA, const Transformation& rkB);

    // Compute the inverse transformation.  If <M,T> is the matrix-translation
    // pair, the inverse is <M^{-1},-M^{-1}*T>.
    void Inverse (Transformation& rkInverse) const;

    // The identity transformation.
    static const Transformation IDENTITY;

private:
    friend class Spatial;

    Matrix3x m_kMatrix;
    Vector3x m_kTranslate;
    Vector3x m_kScale;
    bool m_bIsIdentity, m_bIsRSMatrix, m_bIsUniformScale;
};

#include "WgTransformation.inl"

}

#endif

