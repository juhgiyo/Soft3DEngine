///////////////////////////////////////////////////////////
//                                                       //
//                    WgMatrix3.h                        //
//                                                       //
//  - Interface for Matrix3 class                        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_MATRIX_3_H__
#define __WG_MATRIX_3_H__

// Matrix operations are applied on the left.  For example, given a matrix M
// and a vector V, matrix-times-vector is M*V.  That is, V is treated as a
// column vector.  Some graphics APIs use V*M where V is treated as a row
// vector.  In this context the "M" matrix is really a transpose of the M as
// represented in Wild Magic.  Similarly, to apply two matrix operations M0
// and M1, in that order, you compute M1*M0 so that the transform of a vector
// is (M1*M0)*V = M1*(M0*V).  Some graphics APIs use M0*M1, but again these
// matrices are the transpose of those as represented in Wild Magic.  You
// must therefore be careful about how you interface the transformation code
// with graphics APIS.
//
// For memory organization it might seem natural to chose Real[N][N] for the
// matrix storage, but this can be a problem on a platform/console that
// chooses to store the data in column-major rather than row-major format.
// To avoid potential portability problems, the matrix is stored as Real[N*N]
// and organized in row-major order.  That is, the entry of the matrix in row
// r (0 <= r < N) and column c (0 <= c < N) is stored at index i = c+N*r
// (0 <= i < N*N).

// The (x,y,z) coordinate system is assumed to be right-handed.  Coordinate
// axis rotation matrices are of the form
//   RX =    1       0       0
//           0     cos(t) -sin(t)
//           0     sin(t)  cos(t)
// where t > 0 indicates a counterclockwise rotation in the yz-plane
//   RY =  cos(t)    0     sin(t)
//           0       1       0
//        -sin(t)    0     cos(t)
// where t > 0 indicates a counterclockwise rotation in the zx-plane
//   RZ =  cos(t) -sin(t)    0
//         sin(t)  cos(t)    0
//           0       0       1
// where t > 0 indicates a counterclockwise rotation in the xy-plane.

#include "WgFoundationLIB.h"
#include "WgVector3.h"

namespace WGSoft3D
{
template <class Real>
class Quaternion;
class Quaternionx;

template <class Real>
class Matrix3
{
public:
    // If bZero is true, create the zero matrix.  Otherwise, create the
    // identity matrix.
    Matrix3 (bool bZero = true);

    // copy constructor
    Matrix3 (const Matrix3& rkM);

    // input Mrc is in row r, column c.
    Matrix3 (Real fM00, Real fM01, Real fM02,
             Real fM10, Real fM11, Real fM12,
             Real fM20, Real fM21, Real fM22);

    // Create a matrix from an array of numbers.  The input array is
    // interpreted based on the Boolean input as
    //   true:  entry[0..8]={m00,m01,m02,m10,m11,m12,m20,m21,m22} [row major]
    //   false: entry[0..8]={m00,m10,m20,m01,m11,m21,m02,m12,m22} [col major]
    Matrix3 (const Real afEntry[9], bool bRowMajor);

    // Create matrices based on vector input.  The Boolean is interpreted as
    //   true: vectors are columns of the matrix
    //   false: vectors are rows of the matrix
    Matrix3 (const Vector3<Real>& rkU, const Vector3<Real>& rkV,
        const Vector3<Real>& rkW, bool bColumns);
    Matrix3 (const Vector3<Real>* akV, bool bColumns);

    // create a diagonal matrix
    Matrix3 (Real fM00, Real fM11, Real fM22);

    // Create rotation matrices (positive angle - counterclockwise).  The
    // angle must be in radians, not degrees.
    Matrix3 (const Vector3<Real>& rkAxis, Real fAngle);

    // create a tensor product U*V^T
    Matrix3 (const Vector3<Real>& rkU, const Vector3<Real>& rkV);

    // create various matrices
    Matrix3& MakeZero ();
    Matrix3& MakeIdentity ();
    Matrix3& MakeDiagonal (Real fM00, Real fM11, Real fM22);
    Matrix3& FromAxisAngle (const Vector3<Real>& rkAxis, Real fAngle);
    Matrix3& MakeTensorProduct (const Vector3<Real>& rkU,
        const Vector3<Real>& rkV);

    // member access
    inline operator const Real* () const;
    inline operator Real* ();
    inline const Real* operator[] (int iRow) const;
    inline Real* operator[] (int iRow);
    inline Real operator() (int iRow, int iCol) const;
    inline Real& operator() (int iRow, int iCol);
    void SetRow (int iRow, const Vector3<Real>& rkV);
    Vector3<Real> GetRow (int iRow) const;
    void SetColumn (int iCol, const Vector3<Real>& rkV);
    Vector3<Real> GetColumn (int iCol) const;
    void GetColumnMajor (Real* afCMajor) const;

    // assignment
    inline Matrix3& operator= (const Matrix3& rkM);

    // comparison
    bool operator== (const Matrix3& rkM) const;
    bool operator!= (const Matrix3& rkM) const;
    bool operator<  (const Matrix3& rkM) const;
    bool operator<= (const Matrix3& rkM) const;
    bool operator>  (const Matrix3& rkM) const;
    bool operator>= (const Matrix3& rkM) const;

    // arithmetic operations
    inline Matrix3 operator+ (const Matrix3& rkM) const;
    inline Matrix3 operator- (const Matrix3& rkM) const;
    inline Matrix3 operator* (const Matrix3& rkM) const;
    inline Matrix3 operator* (Real fScalar) const;
    inline Matrix3 operator/ (Real fScalar) const;
    inline Matrix3 operator- () const;

    // arithmetic updates
    inline Matrix3& operator+= (const Matrix3& rkM);
    inline Matrix3& operator-= (const Matrix3& rkM);
    inline Matrix3& operator*= (Real fScalar);
    inline Matrix3& operator/= (Real fScalar);

    // matrix times vector
    inline Vector3<Real> operator* (const Vector3<Real>& rkV) const;  // M * v

    // other operations
    Matrix3 Transpose () const;  // M^T
    Matrix3 TransposeTimes (const Matrix3& rkM) const;  // this^T * M
    Matrix3 TimesTranspose (const Matrix3& rkM) const;  // this * M^T
    Matrix3 Inverse () const;
    Matrix3 Adjoint () const;
    Real Determinant () const;
    Real QForm (const Vector3<Real>& rkU,
        const Vector3<Real>& rkV) const;  // u^T*M*v
    Matrix3 TimesDiagonal (const Vector3<Real>& rkDiag) const;  // M*D
    Matrix3 DiagonalTimes (const Vector3<Real>& rkDiag) const;  // D*M


	// Transformation Operation
	static Matrix3 Rotation(Real &xRotAng,Real &yRotAng,Real &zRotAng);
	static Matrix3 RotationX(Real &rkAngle );
	static Matrix3 RotationY(Real &rkAngle );
	static Matrix3 RotationZ(Real &rkAngle );
	static Matrix3 RotationWithQuaternion(Quaternion<Real> &pRotQuat );
	static Matrix3 Scaling(Vector3<Real> &pScale);

	void SetRotation(Real &xRotAng,Real &yRotAng,Real &zRotAng);
	void SetRotationX(Real &rkAngle );
	void SetRotationY(Real &rkAngle );
	void SetRotationZ(Real &rkAngle );
	void SetRotationWithQuaternion(Quaternion<Real> &pRotQuat );
	void SetScaling(Vector3<Real> &pScale);

    // The matrix must be a rotation for these functions to be valid.  The
    // last function uses Gram-Schmidt orthonormalization applied to the
    // columns of the rotation matrix.  The angle must be in radians, not
    // degrees.
    void ToAxisAngle (Vector3<Real>& rkAxis, Real& rfAngle) const;
    void Orthonormalize ();

    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1|u2] is a rotation matrix with columns u0, u1, and u2 and
    // D = diag(d0,d1,d2) is a diagonal matrix whose diagonal entries are d0,
    // d1, and d2.  The eigenvector u[i] corresponds to eigenvector d[i].
    // The eigenvalues are ordered as d0 <= d1 <= d2.
    void EigenDecomposition (Matrix3& rkRot, Matrix3& rkDiag) const;

    // Create rotation matrices from Euler angles.
    Matrix3& FromEulerAnglesXYZ (Real fXAngle, Real fYAngle, Real fZAngle);
    Matrix3& FromEulerAnglesXZY (Real fXAngle, Real fZAngle, Real fYAngle);
    Matrix3& FromEulerAnglesYXZ (Real fYAngle, Real fXAngle, Real fZAngle);
    Matrix3& FromEulerAnglesYZX (Real fYAngle, Real fZAngle, Real fXAngle);
    Matrix3& FromEulerAnglesZXY (Real fZAngle, Real fXAngle, Real fYAngle);
    Matrix3& FromEulerAnglesZYX (Real fZAngle, Real fYAngle, Real fXAngle);

    // TODO.  From EulerAnglesUVU for all combinations of U and V.

    // Extract Euler angles from rotation matrices.
    enum EulerResult
    {
        // The solution is unique.
        EA_UNIQUE,

        // The solution is not unique.  A sum of angles is constant.
        EA_NOT_UNIQUE_SUM,

        // The solution is not unique.  A difference of angles is constant.
        EA_NOT_UNIQUE_DIF
    };

    // The return values are in the specified ranges:
    //   xAngle in [-pi,pi], yAngle in [-pi/2,pi/2], zAngle in [-pi,pi]
    // When the solution is not unique, zAngle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  zAngle + xAngle = c
    //   EA_NOT_UNIQUE_DIF:  zAngle - xAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesXYZ (Real& rfXAngle, Real& rfYAngle,
        Real& rfZAngle) const;

    // The return values are in the specified ranges:
    //   xAngle in [-pi,pi], zAngle in [-pi/2,pi/2], yAngle in [-pi,pi]
    // When the solution is not unique, yAngle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  yAngle + xAngle = c
    //   EA_NOT_UNIQUE_DIF:  yAngle - xAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesXZY (Real& rfXAngle, Real& rfZAngle,
        Real& rfYAngle) const;

    // The return values are in the specified ranges:
    //   yAngle in [-pi,pi], xAngle in [-pi/2,pi/2], zAngle in [-pi,pi]
    // When the solution is not unique, zAngle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  zAngle + yAngle = c
    //   EA_NOT_UNIQUE_DIF:  zAngle - yAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesYXZ (Real& rfYAngle, Real& rfXAngle,
        Real& rfZAngle) const;

    // The return values are in the specified ranges:
    //   yAngle in [-pi,pi], zAngle in [-pi/2,pi/2], xAngle in [-pi,pi]
    // When the solution is not unique, xAngle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  xAngle + yAngle = c
    //   EA_NOT_UNIQUE_DIF:  xAngle - yAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesYZX (Real& rfYAngle, Real& rfZAngle,
        Real& rfXAngle) const;

    // The return values are in the specified ranges:
    //   zAngle in [-pi,pi], xAngle in [-pi/2,pi/2], yAngle in [-pi,pi]
    // When the solution is not unique, yAngle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  yAngle + zAngle = c
    //   EA_NOT_UNIQUE_DIF:  yAngle - zAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesZXY (Real& rfZAngle, Real& rfXAngle,
        Real& rfYAngle) const;

    // The return values are in the specified ranges:
    //   zAngle in [-pi,pi], yAngle in [-pi/2,pi/2], xAngle in [-pi,pi]
    // When the solution is not unique, xAngle = 0 is/ returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  xAngle + zAngle = c
    //   EA_NOT_UNIQUE_DIF:  xAngle - zAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesZYX (Real& rfZAngle, Real& rfYAngle,
        Real& rfXAngle) const;

    // The return values are in the specified ranges:
    //   x0Angle in [-pi,pi], yAngle in [0,pi], x1Angle in [-pi,pi]
    // When the solution is not unique, x1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  x1Angle + x0Angle = c
    //   EA_NOT_UNIQUE_DIF:  x1Angle - x0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesXYX (Real& rfX0Angle, Real& rfYAngle,
        Real& rfX1Angle) const;

    // The return values are in the specified ranges:
    //   x0Angle in [-pi,pi], zAngle in [0,pi], x1Angle in [-pi,pi]
    // When the solution is not unique, x1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  x1Angle + x0Angle = c
    //   EA_NOT_UNIQUE_DIF:  x1Angle - x0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesXZX (Real& rfX0Angle, Real& rfZAngle,
        Real& rfX1Angle) const;

    // The return values are in the specified ranges:
    //   y0Angle in [-pi,pi], xAngle in [0,pi], y1Angle in [-pi,pi]
    // When the solution is not unique, y1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  y1Angle + y0Angle = c
    //   EA_NOT_UNIQUE_DIF:  y1Angle - y0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesYXY (Real& rfY0Angle, Real& rfXAngle,
        Real& rfY1Angle) const;

    // The return values are in the specified ranges:
    //   y0Angle in [-pi,pi], zAngle in [0,pi], y1Angle in [-pi,pi]
    // When the solution is not unique, y1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  y1Angle + y0Angle = c
    //   EA_NOT_UNIQUE_DIF:  y1Angle - y0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesYZY (Real& rfY0Angle, Real& rfZAngle,
        Real& rfY1Angle) const;

    // The return values are in the specified ranges:
    //   z0Angle in [-pi,pi], xAngle in [0,pi], z1Angle in [-pi,pi]
    // When the solution is not unique, z1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  z1Angle + z0Angle = c
    //   EA_NOT_UNIQUE_DIF:  z1Angle - z0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesZXZ (Real& rfZ0Angle, Real& rfXAngle,
        Real& rfZ1Angle) const;

    // The return values are in the specified ranges:
    //   z0Angle in [-pi,pi], yAngle in [0,pi], z1Angle in [-pi,pi]
    // When the solution is not unique, z1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  z1Angle + z0Angle = c
    //   EA_NOT_UNIQUE_DIF:  z1Angle - z0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesZYZ (Real& rfZ0Angle, Real& rfYAngle,
        Real& rfZ1Angle) const;

    // SLERP (spherical linear interpolation) without quaternions.  Computes
    // R(t) = R0*(Transpose(R0)*R1)^t.  If Q is a rotation matrix with
    // unit-length axis U and angle A, then Q^t is a rotation matrix with
    // unit-length axis U and rotation angle t*A.
    Matrix3& Slerp (Real fT, const Matrix3& rkR0, const Matrix3& rkR1);

    // Singular value decomposition, M = L*D*Transpose(R), where L and R are
    // orthogonal and D is a diagonal matrix whose diagonal entries are
    // nonnegative.
    void SingularValueDecomposition (Matrix3& rkL, Matrix3& rkD,
        Matrix3& rkRTranspose) const;

    // For debugging purposes.  Take the output of SingularValueDecomposition
    // and multiply to see if you get M.
    void SingularValueComposition (const Matrix3& rkL, const Matrix3& rkD,
        const Matrix3& rkRTranspose);

    // Polar decomposition, M = Q*S, where Q is orthogonal and S is symmetric.
    // This uses the singular value decomposition:
    //   M = L*D*Transpose(R) = (L*Transpose(R))*(R*D*Transpose(R)) = Q*S
    // where Q = L*Transpose(R) and S = R*D*Transpose(R).
    void PolarDecomposition (Matrix3& rkQ, Matrix3& rkS);

    // Factor M = Q*D*U with orthogonal Q, diagonal D, upper triangular U.
    void QDUDecomposition (Matrix3& rkQ, Matrix3& rkD, Matrix3& rkU) const;

    // special matrices
    WG3D_FOUNDATION_ITEM static const Matrix3 ZERO;
    WG3D_FOUNDATION_ITEM static const Matrix3 IDENTITY;

private:
    // Support for eigendecomposition.  The Tridiagonalize function applies
    // a Householder transformation to the matrix.  If that transformation
    // is the identity (the matrix is already tridiagonal), then the return
    // value is 'false'.  Otherwise, the transformation is a reflection and
    // the return value is 'true'.  The QLAlgorithm returns 'true' iff the
    // QL iteration scheme converged.
    bool Tridiagonalize (Real afDiag[3], Real afSubd[2]);
    bool QLAlgorithm (Real afDiag[3], Real afSubd[2]);

    // support for singular value decomposition
    static void Bidiagonalize (Matrix3& rkA, Matrix3& rkL, Matrix3& rkR);
    static void GolubKahanStep (Matrix3& rkA, Matrix3& rkL, Matrix3& rkR);

    // support for comparisons
    int CompareArrays (const Matrix3& rkM) const;

    Real m_afEntry[9];
};

class WG3D_FOUNDATION_ITEM Matrix3x
{
public:
    // If bZero is true, create the zero matrix.  Otherwise, create the
    // identity matrix.
    Matrix3x (bool bZero = true);

    // copy constructor
    Matrix3x (const Matrix3x& rkM);

    // input Mrc is in row r, column c.
    Matrix3x (fixed fM00, fixed fM01, fixed fM02,
             fixed fM10, fixed fM11, fixed fM12,
             fixed fM20, fixed fM21, fixed fM22);

    // Create a matrix from an array of numbers.  The input array is
    // interpreted based on the Boolean input as
    //   true:  entry[0..8]={m00,m01,m02,m10,m11,m12,m20,m21,m22} [row major]
    //   false: entry[0..8]={m00,m10,m20,m01,m11,m21,m02,m12,m22} [col major]
    Matrix3x (const fixed afEntry[9], bool bRowMajor);

    // Create matrices based on vector input.  The Boolean is interpreted as
    //   true: vectors are columns of the matrix
    //   false: vectors are rows of the matrix
    Matrix3x (const Vector3x& rkU, const Vector3x& rkV,
        const Vector3x& rkW, bool bColumns);
    Matrix3x (const Vector3x* akV, bool bColumns);

    // create a diagonal matrix
    Matrix3x (fixed fM00, fixed fM11, fixed fM22);

    // Create rotation matrices (positive angle - counterclockwise).  The
    // angle must be in radians, not degrees.
    Matrix3x (const Vector3x& rkAxis, fixed fAngle);

    // create a tensor product U*V^T
    Matrix3x (const Vector3x& rkU, const Vector3x& rkV);

    // create various matrices
    Matrix3x& MakeZero ();
    Matrix3x& MakeIdentity ();
    Matrix3x& MakeDiagonal (fixed fM00, fixed fM11, fixed fM22);
    Matrix3x& FromAxisAngle (const Vector3x& rkAxis, fixed fAngle);
    Matrix3x& MakeTensorProduct (const Vector3x& rkU,
        const Vector3x& rkV);

    // member access
    inline operator const fixed* () const;
    inline operator fixed* ();
    inline const fixed* operator[] (int iRow) const;
    inline fixed* operator[] (int iRow);
    inline fixed operator() (int iRow, int iCol) const;
    inline fixed& operator() (int iRow, int iCol);
    void SetRow (int iRow, const Vector3x& rkV);
    Vector3x GetRow (int iRow) const;
    void SetColumn (int iCol, const Vector3x& rkV);
    Vector3x GetColumn (int iCol) const;
    void GetColumnMajor (fixed* afCMajor) const;

    // assignment
    inline Matrix3x& operator= (const Matrix3x& rkM);

    // comparison
    bool operator== (const Matrix3x& rkM) const;
    bool operator!= (const Matrix3x& rkM) const;
    bool operator<  (const Matrix3x& rkM) const;
    bool operator<= (const Matrix3x& rkM) const;
    bool operator>  (const Matrix3x& rkM) const;
    bool operator>= (const Matrix3x& rkM) const;

    // arithmetic operations
    inline Matrix3x operator+ (const Matrix3x& rkM) const;
    inline Matrix3x operator- (const Matrix3x& rkM) const;
    inline Matrix3x operator* (const Matrix3x& rkM) const;
    inline Matrix3x operator* (fixed fScalar) const;
    inline Matrix3x operator/ (fixed fScalar) const;
    inline Matrix3x operator- () const;

    // arithmetic updates
    inline Matrix3x& operator+= (const Matrix3x& rkM);
    inline Matrix3x& operator-= (const Matrix3x& rkM);
    inline Matrix3x& operator*= (fixed fScalar);
    inline Matrix3x& operator/= (fixed fScalar);

    // matrix times vector
    inline Vector3x operator* (const Vector3x& rkV) const;  // M * v

    // other operations
    Matrix3x Transpose () const;  // M^T
    Matrix3x TransposeTimes (const Matrix3x& rkM) const;  // this^T * M
    Matrix3x TimesTranspose (const Matrix3x& rkM) const;  // this * M^T
    Matrix3x Inverse () const;
    Matrix3x Adjoint () const;
    fixed Determinant () const;
    fixed QForm (const Vector3x& rkU,
        const Vector3x& rkV) const;  // u^T*M*v
    Matrix3x TimesDiagonal (const Vector3x& rkDiag) const;  // M*D
    Matrix3x DiagonalTimes (const Vector3x& rkDiag) const;  // D*M

	// Transformation Operation
	static Matrix3x Rotation(fixed &xRotAng,fixed &yRotAng,fixed &zRotAng);
	static Matrix3x RotationX(fixed &rkAngle );
	static Matrix3x RotationY(fixed &rkAngle );
	static Matrix3x RotationZ(fixed &rkAngle );
	static Matrix3x RotationWithQuaternion(Quaternionx &pRotQuat );
	static Matrix3x Scaling(Vector3x &pScale);
	
	void SetRotation(fixed &xRotAng,fixed &yRotAng,fixed &zRotAng);
	void SetRotationX(fixed &rkAngle );
	void SetRotationY(fixed &rkAngle );
	void SetRotationZ(fixed &rkAngle );
	void SetRotationWithQuaternion(Quaternionx &pRotQuat );
	void SetScaling(Vector3x &pScale);


    // The matrix must be a rotation for these functions to be valid.  The
    // last function uses Gram-Schmidt orthonormalization applied to the
    // columns of the rotation matrix.  The angle must be in radians, not
    // degrees.
    void ToAxisAngle (Vector3x& rkAxis, fixed& rfAngle) const;
    void Orthonormalize ();

    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1|u2] is a rotation matrix with columns u0, u1, and u2 and
    // D = diag(d0,d1,d2) is a diagonal matrix whose diagonal entries are d0,
    // d1, and d2.  The eigenvector u[i] corresponds to eigenvector d[i].
    // The eigenvalues are ordered as d0 <= d1 <= d2.
    void EigenDecomposition (Matrix3x& rkRot, Matrix3x& rkDiag) const;

    // Create rotation matrices from Euler angles.
    Matrix3x& FromEulerAnglesXYZ (fixed fXAngle, fixed fYAngle, fixed fZAngle);
    Matrix3x& FromEulerAnglesXZY (fixed fXAngle, fixed fZAngle, fixed fYAngle);
    Matrix3x& FromEulerAnglesYXZ (fixed fYAngle, fixed fXAngle, fixed fZAngle);
    Matrix3x& FromEulerAnglesYZX (fixed fYAngle, fixed fZAngle, fixed fXAngle);
    Matrix3x& FromEulerAnglesZXY (fixed fZAngle, fixed fXAngle, fixed fYAngle);
    Matrix3x& FromEulerAnglesZYX (fixed fZAngle, fixed fYAngle, fixed fXAngle);

    // TODO.  From EulerAnglesUVU for all combinations of U and V.

    // Extract Euler angles from rotation matrices.
    enum EulerResult
    {
        // The solution is unique.
        EA_UNIQUE,

        // The solution is not unique.  A sum of angles is constant.
        EA_NOT_UNIQUE_SUM,

        // The solution is not unique.  A difference of angles is constant.
        EA_NOT_UNIQUE_DIF
    };

    // The return values are in the specified ranges:
    //   xAngle in [-pi,pi], yAngle in [-pi/2,pi/2], zAngle in [-pi,pi]
    // When the solution is not unique, zAngle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  zAngle + xAngle = c
    //   EA_NOT_UNIQUE_DIF:  zAngle - xAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesXYZ (fixed& rfXAngle, fixed& rfYAngle,
        fixed& rfZAngle) const;

    // The return values are in the specified ranges:
    //   xAngle in [-pi,pi], zAngle in [-pi/2,pi/2], yAngle in [-pi,pi]
    // When the solution is not unique, yAngle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  yAngle + xAngle = c
    //   EA_NOT_UNIQUE_DIF:  yAngle - xAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesXZY (fixed& rfXAngle, fixed& rfZAngle,
        fixed& rfYAngle) const;

    // The return values are in the specified ranges:
    //   yAngle in [-pi,pi], xAngle in [-pi/2,pi/2], zAngle in [-pi,pi]
    // When the solution is not unique, zAngle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  zAngle + yAngle = c
    //   EA_NOT_UNIQUE_DIF:  zAngle - yAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesYXZ (fixed& rfYAngle, fixed& rfXAngle,
        fixed& rfZAngle) const;

    // The return values are in the specified ranges:
    //   yAngle in [-pi,pi], zAngle in [-pi/2,pi/2], xAngle in [-pi,pi]
    // When the solution is not unique, xAngle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  xAngle + yAngle = c
    //   EA_NOT_UNIQUE_DIF:  xAngle - yAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesYZX (fixed& rfYAngle, fixed& rfZAngle,
        fixed& rfXAngle) const;

    // The return values are in the specified ranges:
    //   zAngle in [-pi,pi], xAngle in [-pi/2,pi/2], yAngle in [-pi,pi]
    // When the solution is not unique, yAngle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  yAngle + zAngle = c
    //   EA_NOT_UNIQUE_DIF:  yAngle - zAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesZXY (fixed& rfZAngle, fixed& rfXAngle,
        fixed& rfYAngle) const;

    // The return values are in the specified ranges:
    //   zAngle in [-pi,pi], yAngle in [-pi/2,pi/2], xAngle in [-pi,pi]
    // When the solution is not unique, xAngle = 0 is/ returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  xAngle + zAngle = c
    //   EA_NOT_UNIQUE_DIF:  xAngle - zAngle = c
    // for some angle c.
    EulerResult ToEulerAnglesZYX (fixed& rfZAngle, fixed& rfYAngle,
        fixed& rfXAngle) const;

    // The return values are in the specified ranges:
    //   x0Angle in [-pi,pi], yAngle in [0,pi], x1Angle in [-pi,pi]
    // When the solution is not unique, x1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  x1Angle + x0Angle = c
    //   EA_NOT_UNIQUE_DIF:  x1Angle - x0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesXYX (fixed& rfX0Angle, fixed& rfYAngle,
        fixed& rfX1Angle) const;

    // The return values are in the specified ranges:
    //   x0Angle in [-pi,pi], zAngle in [0,pi], x1Angle in [-pi,pi]
    // When the solution is not unique, x1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  x1Angle + x0Angle = c
    //   EA_NOT_UNIQUE_DIF:  x1Angle - x0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesXZX (fixed& rfX0Angle, fixed& rfZAngle,
        fixed& rfX1Angle) const;

    // The return values are in the specified ranges:
    //   y0Angle in [-pi,pi], xAngle in [0,pi], y1Angle in [-pi,pi]
    // When the solution is not unique, y1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  y1Angle + y0Angle = c
    //   EA_NOT_UNIQUE_DIF:  y1Angle - y0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesYXY (fixed& rfY0Angle, fixed& rfXAngle,
        fixed& rfY1Angle) const;

    // The return values are in the specified ranges:
    //   y0Angle in [-pi,pi], zAngle in [0,pi], y1Angle in [-pi,pi]
    // When the solution is not unique, y1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  y1Angle + y0Angle = c
    //   EA_NOT_UNIQUE_DIF:  y1Angle - y0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesYZY (fixed& rfY0Angle, fixed& rfZAngle,
        fixed& rfY1Angle) const;

    // The return values are in the specified ranges:
    //   z0Angle in [-pi,pi], xAngle in [0,pi], z1Angle in [-pi,pi]
    // When the solution is not unique, z1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  z1Angle + z0Angle = c
    //   EA_NOT_UNIQUE_DIF:  z1Angle - z0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesZXZ (fixed& rfZ0Angle, fixed& rfXAngle,
        fixed& rfZ1Angle) const;

    // The return values are in the specified ranges:
    //   z0Angle in [-pi,pi], yAngle in [0,pi], z1Angle in [-pi,pi]
    // When the solution is not unique, z1Angle = 0 is returned.  Generally,
    // the set of solutions is
    //   EA_NOT_UNIQUE_SUM:  z1Angle + z0Angle = c
    //   EA_NOT_UNIQUE_DIF:  z1Angle - z0Angle = c
    // for some angle c.
    EulerResult ToEulerAnglesZYZ (fixed& rfZ0Angle, fixed& rfYAngle,
        fixed& rfZ1Angle) const;

    // SLERP (spherical linear interpolation) without quaternions.  Computes
    // R(t) = R0*(Transpose(R0)*R1)^t.  If Q is a rotation matrix with
    // unit-length axis U and angle A, then Q^t is a rotation matrix with
    // unit-length axis U and rotation angle t*A.
    Matrix3x& Slerp (fixed fT, const Matrix3x& rkR0, const Matrix3x& rkR1);

    // Singular value decomposition, M = L*D*Transpose(R), where L and R are
    // orthogonal and D is a diagonal matrix whose diagonal entries are
    // nonnegative.
    void SingularValueDecomposition (Matrix3x& rkL, Matrix3x& rkD,
        Matrix3x& rkRTranspose) const;

    // For debugging purposes.  Take the output of SingularValueDecomposition
    // and multiply to see if you get M.
    void SingularValueComposition (const Matrix3x& rkL, const Matrix3x& rkD,
        const Matrix3x& rkRTranspose);

    // Polar decomposition, M = Q*S, where Q is orthogonal and S is symmetric.
    // This uses the singular value decomposition:
    //   M = L*D*Transpose(R) = (L*Transpose(R))*(R*D*Transpose(R)) = Q*S
    // where Q = L*Transpose(R) and S = R*D*Transpose(R).
    void PolarDecomposition (Matrix3x& rkQ, Matrix3x& rkS);

    // Factor M = Q*D*U with orthogonal Q, diagonal D, upper triangular U.
    void QDUDecomposition (Matrix3x& rkQ, Matrix3x& rkD, Matrix3x& rkU) const;

    // special matrices
    static const Matrix3x ZERO;
    static const Matrix3x IDENTITY;

private:
    // Support for eigendecomposition.  The Tridiagonalize function applies
    // a Householder transformation to the matrix.  If that transformation
    // is the identity (the matrix is already tridiagonal), then the return
    // value is 'false'.  Otherwise, the transformation is a reflection and
    // the return value is 'true'.  The QLAlgorithm returns 'true' iff the
    // QL iteration scheme converged.
    bool Tridiagonalize (fixed afDiag[3], fixed afSubd[2]);
    bool QLAlgorithm (fixed afDiag[3], fixed afSubd[2]);

    // support for singular value decomposition
    static void Bidiagonalize (Matrix3x& rkA, Matrix3x& rkL, Matrix3x& rkR);
    static void GolubKahanStep (Matrix3x& rkA, Matrix3x& rkL, Matrix3x& rkR);

    // support for comparisons
    int CompareArrays (const Matrix3x& rkM) const;

    fixed m_afEntry[9];
};


// c * M
template <class Real>
inline Matrix3<Real> operator* (Real fScalar, const Matrix3<Real>& rkM);
inline Matrix3x operator* (fixed fScalar, const Matrix3x& rkM);

// v^T * M
template <class Real>
inline Vector3<Real> operator* (const Vector3<Real>& rkV, const Matrix3<Real>& rkM);
inline Vector3x operator* (const Vector3x& rkV, const Matrix3x& rkM);

#include "WgMatrix3.inl"

typedef Matrix3<float> Matrix3f;
typedef Matrix3<double> Matrix3d;

}

#endif
