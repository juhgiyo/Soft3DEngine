///////////////////////////////////////////////////////////
//                                                       //
//                    WgColorRGBA.inl                    //
//                                                       //
//  - Inlines for Color RGBA class                       //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline ColorRGBA::operator const fixed* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline ColorRGBA::operator fixed* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline fixed ColorRGBA::operator[] (int i) const
{
    assert(0 <= i && i <= 3);
    if (i < 0)
    {
        i = 0;
    }
    else if ( i > 3 )
    {
        i = 3;
    }

    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline fixed& ColorRGBA::operator[] (int i)
{
    assert(0 <= i && i <= 3);
    if (i < 0)
    {
        i = 0;
    }
    else if ( i > 3 )
    {
        i = 3;
    }

    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline fixed ColorRGBA::R () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline fixed& ColorRGBA::R ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline fixed ColorRGBA::G () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline fixed& ColorRGBA::G ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline fixed ColorRGBA::B () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline fixed& ColorRGBA::B ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline fixed ColorRGBA::A () const
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------
inline fixed& ColorRGBA::A ()
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------
