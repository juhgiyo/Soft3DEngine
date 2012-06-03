///////////////////////////////////////////////////////////
//                                                       //
//                    WgBumpMapEffect.inl                //
//                                                       //
//  - Inlines for Bump Map Effect class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline Light* BumpMapEffect::GetLight () const
{
    return m_spkLight;
}
//----------------------------------------------------------------------------
inline void BumpMapEffect::NeedsRecalculation ()
{
    m_bNeedsRecalculation = true;
}
//----------------------------------------------------------------------------
inline bool BumpMapEffect::GetNeedsRecalculation () const
{
    return m_bNeedsRecalculation;
}
//----------------------------------------------------------------------------

