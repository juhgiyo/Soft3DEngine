///////////////////////////////////////////////////////////
//                                                       //
//                    WgCamera.inl                       //
//                                                       //
//  - Inlines for Camera class                           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline const fixed* Camera::GetFrustum () const
{
    return m_afFrustum;
}
//----------------------------------------------------------------------------
inline fixed Camera::GetDMin () const
{
    return m_afFrustum[VF_DMIN];
}
//----------------------------------------------------------------------------
inline fixed Camera::GetDMax () const
{
    return m_afFrustum[VF_DMAX];
}
//----------------------------------------------------------------------------
inline fixed Camera::GetUMin () const
{
    return m_afFrustum[VF_UMIN];
}
//----------------------------------------------------------------------------
inline fixed Camera::GetUMax () const
{
    return m_afFrustum[VF_UMAX];
}
//----------------------------------------------------------------------------
inline fixed Camera::GetRMin () const
{
    return m_afFrustum[VF_RMIN];
}
//----------------------------------------------------------------------------
inline fixed Camera::GetRMax () const
{
    return m_afFrustum[VF_RMAX];
}
//----------------------------------------------------------------------------
inline Vector3x Camera::GetLocation () const
{
    return Local.GetTranslate();
}
//----------------------------------------------------------------------------
inline Vector3x Camera::GetDVector () const
{
    return Local.GetRotate().GetColumn(0);
}
//----------------------------------------------------------------------------
inline Vector3x Camera::GetUVector () const
{
    return Local.GetRotate().GetColumn(1);
}
//----------------------------------------------------------------------------
inline Vector3x Camera::GetRVector () const
{
    return Local.GetRotate().GetColumn(2);
}
//----------------------------------------------------------------------------
inline Vector3x Camera::GetWorldLocation () const
{
    return World.GetTranslate();
}
//----------------------------------------------------------------------------
inline Vector3x Camera::GetWorldDVector () const
{
    return World.GetRotate().GetColumn(0);
}
//----------------------------------------------------------------------------
inline Vector3x Camera::GetWorldUVector () const
{
    return World.GetRotate().GetColumn(1);
}
//----------------------------------------------------------------------------
inline Vector3x Camera::GetWorldRVector () const
{
    return World.GetRotate().GetColumn(2);
}
//----------------------------------------------------------------------------
inline void Camera::SetPlaneState (unsigned int uiPlaneState)
{
    m_uiPlaneState = uiPlaneState;
}
//----------------------------------------------------------------------------
inline unsigned int Camera::GetPlaneState () const
{
    return m_uiPlaneState;
}
//----------------------------------------------------------------------------
inline int Camera::GetPlaneQuantity () const
{
    return m_iPlaneQuantity;
}
//----------------------------------------------------------------------------
inline const Plane3x* Camera::GetPlanes () const
{
    return m_akWPlane;
}
//----------------------------------------------------------------------------

