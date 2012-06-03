///////////////////////////////////////////////////////////
//                                                       //
//                    WgScreePolygon.inl                 //
//                                                       //
//  - Inlines for ScreenPolygon class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline const Vector2x& ScreenPolygon::GetVertex (int i) const
{
    assert(0 <= i && i < Vertices->GetQuantity());
    return m_akVertex[i];
}
//----------------------------------------------------------------------------
inline bool ScreenPolygon::IsForeground () const
{
    return m_bForeground;
}
//----------------------------------------------------------------------------

