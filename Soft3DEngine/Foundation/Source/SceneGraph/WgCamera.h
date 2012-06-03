///////////////////////////////////////////////////////////
//                                                       //
//                    WgCamera.h                         //
//                                                       //
//  - Interface for Camera class                         //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_CAMERA_H__
#define __WG_CAMERA_H__

#include "WgFoundationLIB.h"
#include "WgSpatial.h"
#include "WgPlane3.h"
#include "WgRay3.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM Camera : public Spatial
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    // construction and destruction
    Camera ();
    virtual ~Camera ();

    // Camera frame (local coordinates)
    //   default location  E = (0,0,0)
    //   default direction D = (0,0,-1)
    //   default up        U = (0,1,0)
    //   default right     R = (1,0,0)
    // If a rotation matrix is used for the axis directions, the columns of
    // the matrix are [D U R].  That is, the view direction is in column 0,
    // the up direction is in column 1, and the right direction is in
    // column 2.
    void SetFrame (const Vector3x& rkLocation, const Vector3x& rkDVector,
        const Vector3x& rkUVector, const Vector3x& rkRVector);
    void SetFrame (const Vector3x& rkLocation, const Matrix3x& rkAxes);
    void SetLocation (const Vector3x& rkLocation);
    void SetAxes (const Vector3x& rkDVector, const Vector3x& rkUVector,
        const Vector3x& rkRVector);
    void SetAxes (const Matrix3x& rkAxes);
    Vector3x GetLocation () const;  // Local.Translate
    Vector3x GetDVector () const;   // Local.Rotate column 0
    Vector3x GetUVector () const;   // Local.Rotate column 1
    Vector3x GetRVector () const;   // Local.Rotate column 2

    // camera frame (world coordinates)
    Vector3x GetWorldLocation () const;  // World.Translate
    Vector3x GetWorldDVector () const;   // World.Rotate column 0
    Vector3x GetWorldUVector () const;   // World.Rotate column 1
    Vector3x GetWorldRVector () const;   // World.Rotate column 2

    // The view frustum has parameters [rmin,rmax], [umin,umax], and
    // [dmin,dmax].  The interval [rmin,rmax] is measured in the right
    // direction R.  These are the "left" and "right" frustum values.  The
    // interval [umin,umax] is measured in the up direction U.  These are
    // the "bottom" and "top" values.  The interval [dmin,dmax] is measured
    // in the view direction D.  These are the "near" and "far" values.
    // The frustum values are stored in an array with the following mappings:
    enum
    {
        VF_DMIN     = 0,  // near
        VF_DMAX     = 1,  // far
        VF_UMIN     = 2,  // bottom
        VF_UMAX     = 3,  // top
        VF_RMIN     = 4,  // left
        VF_RMAX     = 5,  // right
        VF_QUANTITY = 6
    };

    // Set the view frustum.  The interval [rmin,rmax] is measured in the
    // right direction R.  These are the "left" and "right" frustum values.
    // The interval [umin,umax] is measured in the up direction U.  These are
    // the "bottom" and "top" values.  The interval [dmin,dmax] is measured
    // in the view direction D.  These are the "near" and "far" values.
    void SetFrustum (fixed fRMin, fixed fRMax, fixed fUMin, fixed fUMax,
        fixed fDMin, fixed fDMax);

    // Set all the view frustum values simultaneously.
    void SetFrustum (const fixed* afFrustum);

    // Set a symmetric view frustum (umin = -umax, rmin = -rmax) using a field
    // of view in the "up" direction and an aspect ratio "width/height".  This
    // call is the equivalent of gluPerspective in OpenGL.  As such, the field
    // of view in this function must be specified in degrees and be in the
    // interval (0,180).
    void SetFrustum (fixed fUpFovDegrees, fixed fAspectRatio, fixed fDMin,
        fixed fDMax);

    // Get the view frustum.
    void GetFrustum (fixed& rfRMin, fixed& rfRMax, fixed& rfUMin,
        fixed& rfUMax, fixed& rfDMin, fixed& rfDMax) const;

    // Get all the view frustum values simultaneously.
    const fixed* GetFrustum () const;

    // Get the parameters for a symmetric view frustum.  The return value is
    // 'true' iff the current frustum is symmetric, in which case the output
    // parameters are valid.
    bool GetFrustum (fixed& rfUpFovDegrees, fixed& rfAspectRatio,
        fixed& rfDMin, fixed& rfDMax) const;

    // Get the individual frustum values.
    fixed GetDMin () const;
    fixed GetDMax () const;
    fixed GetUMin () const;
    fixed GetUMax () const;
    fixed GetRMin () const;
    fixed GetRMax () const;

    // Allow for orthogonal cameras as well as perspective cameras.  The
    // default is perspective (value is 'true').  Set to 'false' for an
    // orthogonal camera.  TO DO: This member needs to be streamed.
    bool Perspective;

    // viewport (contained in [0,1]^2)
    void SetViewPort (fixed fLeft, fixed fRight, fixed fTop, fixed fBottom);
    void GetViewPort (fixed& rfLeft, fixed& rfRight, fixed& rfTop,
        fixed& rfBottom);

    // access to stack of world culling planes
    int GetPlaneQuantity () const;
    const Plane3x* GetPlanes () const;
    void PushPlane (const Plane3x& rkPlane);
    void PopPlane ();

    // Support for determining if the view frustum is fully on one side of a
    // plane.  The "positive side" of the plane is the half space to which the
    // plane normal points.  The "negative side" is the other half space.  The
    // flag "no side" indicates the plane itself.  The function returns +1 if
    // the view frustum is fully on the positive side of the plane, -1 if the
    // view frustum is fully on the negative side of the plane, or 0 if the
    // view frustum straddles the plane.  The input plane is in world
    // coordinates and the world camera coordinate system is used for the
    // test.
    int WhichSide (const Plane3x& rkPlane) const;

    // Mouse picking support.  The (x,y) input point is in left-handed screen
    // coordinates (what you usually read from the windowing system).  The
    // function returns 'true' if and only if the input point is located in
    // the current viewport.  When 'true', the origin and direction values
    // are valid and are in world coordinates.  The direction vector is unit
    // length.
    bool GetPickRay (int iX, int iY, int iWidth, int iHeight, Ray3x& rkRay)
        const;

protected:
    // update callbacks
    virtual void UpdateWorldBound ();
    void OnFrustumChange ();
    void OnViewPortChange ();
    void OnFrameChange ();

    // view frustum (near, far, bottom, top, left, right)
    fixed m_afFrustum[VF_QUANTITY];

    // viewport
    fixed m_fPortL, m_fPortR, m_fPortT, m_fPortB;

    // Bit flag to store whether or not a plane is active in the culling
    // system.  A bit of 1 means the plane is active, otherwise the plane is
    // inactive.  The first 6 planes are the view frustum planes.  Indices
    // are:  left = 0, right = 1, bottom = 2, top = 3, near = 4, far = 5.
    // The system currently supports at most 32 culling planes.
    unsigned int m_uiPlaneState;

    // world planes: left = 0, right = 1, bottom = 2, top = 3, near = 4,
    // far = 5, extra culling planes >= 6
    enum 
    {
        CAM_FRUSTUM_PLANES = 6,
        CAM_MAX_WORLD_PLANES = 32
    };
    int m_iPlaneQuantity;
    Plane3x m_akWPlane[CAM_MAX_WORLD_PLANES];

    // values computed in OnFrustumChange that are needed in OnFrameChange
    fixed m_afCoeffL[2], m_afCoeffR[2], m_afCoeffB[2], m_afCoeffT[2];

// internal use
public:
    // culling support in Spatial::OnDraw
    void SetPlaneState (unsigned int uiPlaneState);
    unsigned int GetPlaneState () const;
    bool Culled (const BoundingVolume* pkWBound);

    // culling support in Portal::Draw
    bool Culled (int iVertexQuantity, const Vector3x* akVertex,
        bool bIgnoreNearPlane);

    // The renderer to which this camera has been attached.  The camera is
    // considered to be active if this pointer is not null.  By necessity, a
    // camera cannot be attached to multiple renderers, but a camera may be
    // shared by renderers as long as only one renderer at a time uses the
    // camera.  The renderer is responsible for setting this Camera member.
    Renderer* m_pkRenderer;

private:
    // base class functions not supported
    virtual void UpdateState (TStack<GlobalState*>*, TStack<Light*>*) { /**/ }
    virtual void Draw (Renderer&, bool) { /**/ }
};

typedef Pointer<Camera> CameraPtr;
#include "WgCamera.inl"

}

#endif

