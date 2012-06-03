///////////////////////////////////////////////////////////
//                                                       //
//                    WgColorRGB.inl                     //
//                                                       //
//  - Inlines for Color RGB class                        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline ColorRGB::operator const fixed* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline ColorRGB::operator fixed* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline fixed ColorRGB::operator[] (int i) const
{
    assert(0 <= i && i <= 2);
    if (i < 0)
    {
        i = 0;
    }
    else if (i > 2)
    {
        i = 2;
    }

    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline fixed& ColorRGB::operator[] (int i)
{
    assert(0 <= i && i <= 2);
    if (i < 0)
    {
        i = 0;
    }
    else if (i > 2)
    {
        i = 2;
    }

    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline fixed ColorRGB::R () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline fixed& ColorRGB::R ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline fixed ColorRGB::G () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline fixed& ColorRGB::G ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline fixed ColorRGB::B () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline fixed& ColorRGB::B ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
