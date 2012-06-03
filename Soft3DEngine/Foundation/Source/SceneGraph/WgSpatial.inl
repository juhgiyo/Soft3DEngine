///////////////////////////////////////////////////////////
//                                                       //
//                    WgSpatial.inl                      //
//                                                       //
//  - Inlines for Spatial class                          //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline void Spatial::SetParent (Spatial* pkParent)
{
    m_pkParent = pkParent;
}
//----------------------------------------------------------------------------
inline Spatial* Spatial::GetParent ()
{
    return m_pkParent;
}
//----------------------------------------------------------------------------
inline void Spatial::SetEffect (Effect* pkEffect)
{
    m_spkEffect = pkEffect;
}
//----------------------------------------------------------------------------
inline Effect* Spatial::GetEffect () const
{
    return m_spkEffect;
}
//----------------------------------------------------------------------------

