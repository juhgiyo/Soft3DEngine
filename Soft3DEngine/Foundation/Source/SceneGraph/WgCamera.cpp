///////////////////////////////////////////////////////////
//                                                       //
//                    WgCamera.cpp                       //
//                                                       //
//  - Implementation for Camera class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#include "WgFoundationPCH.h"
#include "WgCamera.h"
#include "WgRenderer.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,Camera,Spatial);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(Camera,Spatial);

//----------------------------------------------------------------------------
Camera::Camera ()
{
    m_pkRenderer = 0;

    SetFrustum(fixed(FixedFromFloat(-0.5f)),fixed(FIXED_HALF),fixed(FixedFromFloat(-0.5f)),fixed(FIXED_HALF),fixed(FIXED_ONE),fixed(FixedFromFloat(2.0f)));
    SetViewPort(fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ONE),fixed(FIXED_ZERO));
    SetFrame(Vector3x::ZERO,-Vector3x::UNIT_Z,Vector3x::UNIT_Y,
        Vector3x::UNIT_X);

    Perspective = true;

    m_uiPlaneState = (unsigned int)(~0);  // all planes initially active
    m_iPlaneQuantity = 6;  // frustum planes always processed for culling
}
//----------------------------------------------------------------------------
Camera::~Camera ()
{
}
//----------------------------------------------------------------------------
void Camera::SetFrame (const Vector3x& rkLocation, const Vector3x& rkDVector,
    const Vector3x& rkUVector, const Vector3x& rkRVector)
{
    Local.SetTranslate(rkLocation);
    Local.SetRotate(Matrix3x(rkDVector,rkUVector,rkRVector,true));
    OnFrameChange();
}
//----------------------------------------------------------------------------
void Camera::SetFrame (const Vector3x& rkLocation, const Matrix3x& rkAxes)
{
    Local.SetTranslate(rkLocation);
    Local.SetRotate(rkAxes);
    OnFrameChange();
}
//----------------------------------------------------------------------------
void Camera::SetLocation (const Vector3x& rkLocation)
{
    Local.SetTranslate(rkLocation);
    OnFrameChange();
}
//----------------------------------------------------------------------------
void Camera::SetAxes (const Vector3x& rkDVector, const Vector3x& rkUVector,
    const Vector3x& rkRVector)
{
    Local.SetRotate(Matrix3x(rkDVector,rkUVector,rkRVector,true));
    OnFrameChange();
}
//----------------------------------------------------------------------------
void Camera::SetAxes (const Matrix3x& rkAxes)
{
    Local.SetRotate(rkAxes);
    OnFrameChange();
}
//----------------------------------------------------------------------------
void Camera::UpdateWorldBound ()
{
    // The camera has an implicit model bound whose center is the camera's
    // position and whose radius is zero.
    WorldBound->SetCenter(World.ApplyForward(Local.GetTranslate()));
    WorldBound->SetRadius(fixed(FIXED_ZERO));
}
//----------------------------------------------------------------------------
void Camera::SetFrustum (fixed fRMin, fixed fRMax, fixed fUMin, fixed fUMax,
    fixed fDMin, fixed fDMax)
{
    m_afFrustum[VF_DMIN] = fDMin;
    m_afFrustum[VF_DMAX] = fDMax;
    m_afFrustum[VF_UMIN] = fUMin;
    m_afFrustum[VF_UMAX] = fUMax;
    m_afFrustum[VF_RMIN] = fRMin;
    m_afFrustum[VF_RMAX] = fRMax;
    OnFrustumChange();
}
//----------------------------------------------------------------------------
void Camera::SetFrustum (const fixed* afFrustum)
{
    size_t uiSize = VF_QUANTITY*sizeof(fixed);
    System::Memcpy(m_afFrustum,uiSize,afFrustum,uiSize);
    OnFrustumChange();
}
//----------------------------------------------------------------------------
void Camera::SetFrustum (fixed fUpFovDegrees, fixed fAspectRatio, fixed fDMin,
    fixed fDMax)
{
    fixed fHalfAngleRadians = FixedFromFloat(0.5f*FloatFromFixed(fUpFovDegrees)*Mathf::DEG_TO_RAD);
    m_afFrustum[VF_UMAX] = FixedFromFloat(FloatFromFixed(fDMin)*Mathf::Tan(FloatFromFixed(fHalfAngleRadians)));
    m_afFrustum[VF_RMAX] = fAspectRatio*m_afFrustum[VF_UMAX];
    m_afFrustum[VF_UMIN] = -m_afFrustum[VF_UMAX];
    m_afFrustum[VF_RMIN] = -m_afFrustum[VF_RMAX];
    m_afFrustum[VF_DMIN] = fDMin;
    m_afFrustum[VF_DMAX] = fDMax;
    OnFrustumChange();
}
//----------------------------------------------------------------------------
void Camera::GetFrustum (fixed& rfRMin, fixed& rfRMax, fixed& rfUMin,
    fixed& rfUMax, fixed& rfDMin, fixed& rfDMax) const
{
    rfDMin = m_afFrustum[VF_DMIN];
    rfDMax = m_afFrustum[VF_DMAX];
    rfUMin = m_afFrustum[VF_UMIN];
    rfUMax = m_afFrustum[VF_UMAX];
    rfRMin = m_afFrustum[VF_RMIN];
    rfRMax = m_afFrustum[VF_RMAX];
}
//----------------------------------------------------------------------------
bool Camera::GetFrustum (fixed& rfUpFovDegrees, fixed& rfAspectRatio,
    fixed& rfDMin, fixed& rfDMax) const
{
    if (m_afFrustum[VF_RMIN] == -m_afFrustum[VF_RMAX]
    &&  m_afFrustum[VF_UMIN] == -m_afFrustum[VF_UMAX])
    {
        fixed fAngle = m_afFrustum[VF_UMAX]/m_afFrustum[VF_DMIN];
        rfUpFovDegrees = FixedFromFloat(2.0f)*FixedFromFloat(Mathf::ATan(FloatFromFixed(fAngle))*Mathf::RAD_TO_DEG);
        rfAspectRatio = m_afFrustum[VF_RMAX]/m_afFrustum[VF_UMAX];
        rfDMin = m_afFrustum[VF_DMIN];
        rfDMax = m_afFrustum[VF_DMAX];
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
void Camera::SetViewPort (fixed fLeft, fixed fRight, fixed fTop,
    fixed fBottom)
{
    m_fPortL = fLeft;
    m_fPortR = fRight;
    m_fPortT = fTop;
    m_fPortB = fBottom;
    OnViewPortChange();
}
//----------------------------------------------------------------------------
void Camera::GetViewPort (fixed& rfLeft, fixed& rfRight, fixed& rfTop,
    fixed& rfBottom)
{
    rfLeft = m_fPortL;
    rfRight = m_fPortR;
    rfTop = m_fPortT;
    rfBottom = m_fPortB;
}
//----------------------------------------------------------------------------
void Camera::OnFrustumChange ()
{
    fixed fDMinSqr = m_afFrustum[VF_DMIN]*m_afFrustum[VF_DMIN];
    fixed fInvLength;

    // left plane normal vector coefficients
    fixed fRMinSqr = m_afFrustum[VF_RMIN]*m_afFrustum[VF_RMIN];
    fInvLength = FixedFromFloat(1.0f/Mathf::Sqrt(FloatFromFixed(fDMinSqr + fRMinSqr)));
    m_afCoeffL[0] = -m_afFrustum[VF_RMIN]*fInvLength;  // D component
    m_afCoeffL[1] = +m_afFrustum[VF_DMIN]*fInvLength;  // R component

    // right plane normal vector coefficients
    fixed fRMaxSqr = m_afFrustum[VF_RMAX]*m_afFrustum[VF_RMAX];
    fInvLength = FixedFromFloat(1.0f/Mathf::Sqrt(FloatFromFixed(fDMinSqr + fRMaxSqr)));
    m_afCoeffR[0] = +m_afFrustum[VF_RMAX]*fInvLength;  // D component
    m_afCoeffR[1] = -m_afFrustum[VF_DMIN]*fInvLength;  // R component

    // bottom plane normal vector coefficients
    fixed fUMinSqr = m_afFrustum[VF_UMIN]*m_afFrustum[VF_UMIN];
    fInvLength = FixedFromFloat(1.0f/Mathf::Sqrt(FloatFromFixed(fDMinSqr + fUMinSqr)));
    m_afCoeffB[0] = -m_afFrustum[VF_UMIN]*fInvLength;  // D component
    m_afCoeffB[1] = +m_afFrustum[VF_DMIN]*fInvLength;  // U component

    // top plane normal vector coefficients
    fixed fUMaxSqr = m_afFrustum[VF_UMAX]*m_afFrustum[VF_UMAX];
    fInvLength = FixedFromFloat(1.0f/Mathf::Sqrt(FloatFromFixed(fDMinSqr + fUMaxSqr)));
    m_afCoeffT[0] = +m_afFrustum[VF_UMAX]*fInvLength;  // D component
    m_afCoeffT[1] = -m_afFrustum[VF_DMIN]*fInvLength;  // U component

    if (m_pkRenderer)
    {
        m_pkRenderer->OnFrustumChange();
    }
}
//----------------------------------------------------------------------------
void Camera::OnViewPortChange ()
{
    if (m_pkRenderer)
    {
        m_pkRenderer->OnViewPortChange();
    }
}
//----------------------------------------------------------------------------
void Camera::OnFrameChange ()
{
    // Get the world coordinate direction vectors for the camera.  The input
    // application time of MAX_REAL is based on knowing that OnFrameChange
    // was called via Camera interface functions, not through controllers.
    // If the camera frame is modified by controllers, the local transforms
    // are modified directly through the Spatial interface, so that interface
    // itself will update the world transforms.  The application time passed
    // through the Spatial interface will be different than MAX_REAL, so
    // the Update call in this function will not prevent a controller update.
    UpdateGS(-Mathd::MAX_REAL);
    Vector3x kLoc = World.GetTranslate();
    Vector3x kDVec = World.GetRotate().GetColumn(0);
    Vector3x kUVec = World.GetRotate().GetColumn(1);
    Vector3x kRVec = World.GetRotate().GetColumn(2);

    fixed fDdE = kDVec.Dot(kLoc);

    // left plane
    m_akWPlane[0].Normal = m_afCoeffL[0]*kDVec + m_afCoeffL[1]*kRVec;
    m_akWPlane[0].Constant = kLoc.Dot(m_akWPlane[0].Normal);

    // right plane
    m_akWPlane[1].Normal = m_afCoeffR[0]*kDVec + m_afCoeffR[1]*kRVec;
    m_akWPlane[1].Constant = kLoc.Dot(m_akWPlane[1].Normal);

    // bottom plane
    m_akWPlane[2].Normal = m_afCoeffB[0]*kDVec + m_afCoeffB[1]*kUVec;
    m_akWPlane[2].Constant = kLoc.Dot(m_akWPlane[2].Normal);

    // top plane
    m_akWPlane[3].Normal = m_afCoeffT[0]*kDVec + m_afCoeffT[1]*kUVec;
    m_akWPlane[3].Constant = kLoc.Dot(m_akWPlane[3].Normal);

    // near plane
    m_akWPlane[4].Normal = kDVec;
    m_akWPlane[4].Constant = fDdE + m_afFrustum[VF_DMIN];

    // far plane
    m_akWPlane[5].Normal = -kDVec;
    m_akWPlane[5].Constant = -(fDdE + m_afFrustum[VF_DMAX]);

    if (m_pkRenderer)
    {
        m_pkRenderer->OnFrameChange();
    }
}
//----------------------------------------------------------------------------
void Camera::PushPlane (const Plane3x& rkPlane)
{
    if (m_iPlaneQuantity < CAM_MAX_WORLD_PLANES)
    {
        m_akWPlane[m_iPlaneQuantity++] = rkPlane;
    }
}
//----------------------------------------------------------------------------
void Camera::PopPlane ()
{
    if (m_iPlaneQuantity > CAM_FRUSTUM_PLANES)
    {
        // frustum planes may not be removed from the stack
        m_iPlaneQuantity--;
    }
}
//----------------------------------------------------------------------------
bool Camera::Culled (const BoundingVolume* pkWBound)
{
    // start with last pushed plane (potentially the most restrictive plane)
    int iP = m_iPlaneQuantity - 1;
    unsigned int uiMask = 1 << iP;

    for (int i = 0; i < m_iPlaneQuantity; i++, iP--, uiMask >>= 1)
    {
        if (m_uiPlaneState & uiMask)
        {
            int iSide = pkWBound->WhichSide(m_akWPlane[iP]);

            if (iSide < 0)
            {
                // Object is on negative side.  Cull it.
                return true;
            }

            if (iSide > 0)
            {
                // Object is on positive side of plane.  There is no need to
                // compare subobjects against this plane, so mark it as
                // inactive.
                m_uiPlaneState &= ~uiMask;
            }
        }
    }

    return false;
}
//----------------------------------------------------------------------------
bool Camera::Culled (int iVertexQuantity, const Vector3x* akVertex,
    bool bIgnoreNearPlane)
{
    // The Boolean variable bIgnoreNearPlane should be set to 'true' when
    // the test polygon is a portal.  This avoids the situation when the
    // portal is in the view pyramid (eye+left/right/top/bottom), but is
    // between the eye and near plane.  In such a situation you do not want
    // the portal system to cull the portal.  This situation typically occurs
    // when the camera moves through the portal from current region to
    // adjacent region.

    // start with last pushed plane (potentially the most restrictive plane)
    int iP = m_iPlaneQuantity - 1;
    for (int i = 0; i < m_iPlaneQuantity; i++, iP--)
    {
        Plane3x& rkPlane = m_akWPlane[iP];
        if (bIgnoreNearPlane && iP == 4 /* camera near plane */)
        {
            continue;
        }

        int iV;
        for (iV = 0; iV < iVertexQuantity; iV++)
        {
            int iSide = rkPlane.WhichSide(akVertex[iV]);
            if (iSide >= 0)
            {
                // polygon is not totally outside this plane
                break;
            }
        }

        if (iV == iVertexQuantity)
        {
            // polygon is totally outside this plane
            return true;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
int Camera::WhichSide (const Plane3x& rkPlane) const
{
    // The plane is N*(X-C) = 0 where the * indicates dot product.  The signed
    // distance from the camera location E to the plane is N*(E-C).
    fixed fNdEmC = rkPlane.DistanceTo(GetWorldLocation());

    fixed fNdD = rkPlane.Normal.Dot(GetWorldDVector());
    fixed fNdU = rkPlane.Normal.Dot(GetWorldUVector());
    fixed fNdR = rkPlane.Normal.Dot(GetWorldRVector());
    fixed fFdN = m_afFrustum[VF_DMAX]/m_afFrustum[VF_DMIN];

    int iPositive = 0, iNegative = 0;
    fixed fSgnDist;

    // check near-plane vertices
    fixed fPDMin = m_afFrustum[VF_DMIN]*fNdD;
    fixed fNUMin = m_afFrustum[VF_UMIN]*fNdU;
    fixed fNUMax = m_afFrustum[VF_UMAX]*fNdU;
    fixed fNRMin = m_afFrustum[VF_RMIN]*fNdR;
    fixed fNRMax = m_afFrustum[VF_RMAX]*fNdR;

    // V = E + dmin*D + umin*U + rmin*R
    // N*(V-C) = N*(E-C) + dmin*(N*D) + umin*(N*U) + rmin*(N*R)
    fSgnDist = fNdEmC + fPDMin + fNUMin + fNRMin;
    if (fSgnDist > FIXED_ZERO)
    {
        iPositive++;
    }
    else if (fSgnDist < FIXED_ZERO)
    {
        iNegative++;
    }

    // V = E + dmin*D + umin*U + rmax*R
    // N*(V-C) = N*(E-C) + dmin*(N*D) + umin*(N*U) + rmax*(N*R)
    fSgnDist = fNdEmC + fPDMin + fNUMin + fNRMax;
    if (fSgnDist > FIXED_ZERO)
    {
        iPositive++;
    }
    else if (fSgnDist < FIXED_ZERO)
    {
        iNegative++;
    }

    // V = E + dmin*D + umax*U + rmin*R
    // N*(V-C) = N*(E-C) + dmin*(N*D) + umax*(N*U) + rmin*(N*R)
    fSgnDist = fNdEmC + fPDMin + fNUMax + fNRMin;
    if (fSgnDist > FIXED_ZERO)
    {
        iPositive++;
    }
    else if (fSgnDist < FIXED_ZERO)
    {
        iNegative++;
    }

    // V = E + dmin*D + umax*U + rmax*R
    // N*(V-C) = N*(E-C) + dmin*(N*D) + umax*(N*U) + rmax*(N*R)
    fSgnDist = fNdEmC + fPDMin + fNUMax + fNRMax;
    if (fSgnDist > FIXED_ZERO)
    {
        iPositive++;
    }
    else if (fSgnDist < FIXED_ZERO)
    {
        iNegative++;
    }

    // check far-plane vertices (s = dmax/dmin)
    fixed fPDMax = m_afFrustum[VF_DMAX]*fNdD;
    fixed fFUMin = fFdN*fNUMin;
    fixed fFUMax = fFdN*fNUMax;
    fixed fFRMin = fFdN*fNRMin;
    fixed fFRMax = fFdN*fNRMax;

    // V = E + dmax*D + umin*U + rmin*R
    // N*(V-C) = N*(E-C) + dmax*(N*D) + s*umin*(N*U) + s*rmin*(N*R)
    fSgnDist = fNdEmC + fPDMax + fFUMin + fFRMin;
    if (fSgnDist > FIXED_ZERO)
    {
        iPositive++;
    }
    else if (fSgnDist < FIXED_ZERO)
    {
        iNegative++;
    }

    // V = E + dmax*D + umin*U + rmax*R
    // N*(V-C) = N*(E-C) + dmax*(N*D) + s*umin*(N*U) + s*rmax*(N*R)
    fSgnDist = fNdEmC + fPDMax + fFUMin + fFRMax;
    if (fSgnDist > FIXED_ZERO)
    {
        iPositive++;
    }
    else if (fSgnDist < FIXED_ZERO)
    {
        iNegative++;
    }

    // V = E + dmax*D + umax*U + rmin*R
    // N*(V-C) = N*(E-C) + dmax*(N*D) + s*umax*(N*U) + s*rmin*(N*R)
    fSgnDist = fNdEmC + fPDMax + fFUMax + fFRMin;
    if (fSgnDist > FIXED_ZERO)
    {
        iPositive++;
    }
    else if (fSgnDist < FIXED_ZERO)
    {
        iNegative++;
    }

    // V = E + dmax*D + umax*U + rmax*R
    // N*(V-C) = N*(E-C) + dmax*(N*D) + s*umax*(N*U) + s*rmax*(N*R)
    fSgnDist = fNdEmC + fPDMax + fFUMax + fFRMax;
    if (fSgnDist > FIXED_ZERO)
    {
        iPositive++;
    }
    else if (fSgnDist < FIXED_ZERO)
    {
        iNegative++;
    }

    if (iPositive > 0)
    {
        if (iNegative > 0)
        {
            // frustum straddles the plane
            return 0;
        }

        // frustum is fully on the positive side
        return +1;
    }

    // frustum is fully on the negative side
    return -1;
}
//----------------------------------------------------------------------------
bool Camera::GetPickRay (int iX, int iY, int iWidth, int iHeight,
    Ray3x& rkRay) const
{
    fixed fPortX = ((fixed)iX)/(fixed)(iWidth-1);
    if (fPortX < m_fPortL || fPortX > m_fPortR)
    {
        return false;
    }

    fixed fPortY = ((fixed)(iHeight-1-iY))/(fixed)(iHeight-1);
    if (fPortY < m_fPortB || fPortY > m_fPortT)
    {
        return false;
    }

    fixed fXWeight = (fPortX - m_fPortL)/(m_fPortR - m_fPortL);
    fixed fViewX = (FIXED_ONE-fXWeight)*m_afFrustum[VF_RMIN] +
        fXWeight*m_afFrustum[VF_RMAX];
    fixed fYWeight = (fPortY - m_fPortB)/(m_fPortT - m_fPortB);
    fixed fViewY = (FIXED_ONE-fYWeight)*m_afFrustum[VF_UMIN] +
        fYWeight*m_afFrustum[VF_UMAX];

    rkRay.Origin = GetWorldLocation();
    rkRay.Direction = m_afFrustum[VF_DMIN]*GetWorldDVector() +
        fViewX*GetWorldRVector() + fViewY*GetWorldUVector();
    rkRay.Direction.Normalize();
    return true;
}
//----------------------------------------------------------------------------
