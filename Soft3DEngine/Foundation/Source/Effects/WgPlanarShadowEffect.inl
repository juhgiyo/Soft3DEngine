///////////////////////////////////////////////////////////
//                                                       //
//                    WgPlanarShadowEffect.inl           //
//                                                       //
//  - Inlines for Planar Shadow Effect class             //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline int PlanarShadowEffect::GetQuantity () const
{
    return m_iQuantity;
}
//----------------------------------------------------------------------------
inline void PlanarShadowEffect::SetPlane (int i, TriMeshPtr spkPlane)
{
    assert(0 <= i && i < m_iQuantity);
    m_aspkPlane[i] = spkPlane;
    m_aspkPlane[i]->ForceCull = true;
}
//----------------------------------------------------------------------------
inline TriMeshPtr PlanarShadowEffect::GetPlane (int i) const
{
    assert(0 <= i && i < m_iQuantity);
    return m_aspkPlane[i];
}
//----------------------------------------------------------------------------
inline void PlanarShadowEffect::SetProjector (int i, LightPtr spkProjector)
{
    assert(0 <= i && i < m_iQuantity);
    m_aspkProjector[i] = spkProjector;
}
//----------------------------------------------------------------------------
inline LightPtr PlanarShadowEffect::GetProjector (int i) const
{
    assert(0 <= i && i < m_iQuantity);
    return m_aspkProjector[i];
}
//----------------------------------------------------------------------------
inline void PlanarShadowEffect::SetShadowColor (int i,
    const ColorRGBA& rkShadowColor)
{
    assert(0 <= i && i < m_iQuantity);
    m_akShadowColor[i] = rkShadowColor;
}
//----------------------------------------------------------------------------
inline const ColorRGBA& PlanarShadowEffect::GetShadowColor (int i) const
{
    assert(0 <= i && i < m_iQuantity);
    return m_akShadowColor[i];
}
//----------------------------------------------------------------------------

