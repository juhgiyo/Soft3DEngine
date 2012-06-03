///////////////////////////////////////////////////////////
//                                                       //
//                    WgSphereBV.inl                     //
//                                                       //
//  - Inlines for Sphere Bounding Volume class           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline int SphereBV::GetBVType () const
{
    return BoundingVolume::BV_SPHERE;
}
//----------------------------------------------------------------------------
inline void SphereBV::SetCenter (const Vector3x& rkCenter)
{
    m_kSphere.Center = rkCenter;
}
//----------------------------------------------------------------------------
inline void SphereBV::SetRadius (fixed fRadius)
{
    m_kSphere.Radius = fRadius;
}
//----------------------------------------------------------------------------
inline Vector3x SphereBV::GetCenter () const
{
    return m_kSphere.Center;
}
//----------------------------------------------------------------------------
inline fixed SphereBV::GetRadius () const
{
    return m_kSphere.Radius;
}
//----------------------------------------------------------------------------
inline Sphere3x& SphereBV::Sphere ()
{
    return m_kSphere;
}
//----------------------------------------------------------------------------
inline const Sphere3x& SphereBV::GetSphere () const
{
    return m_kSphere;
}
//----------------------------------------------------------------------------

