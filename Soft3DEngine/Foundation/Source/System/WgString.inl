///////////////////////////////////////////////////////////
//                                                       //
//                    WgString.inl                       //
//                                                       //
//  - Inlines for String class                           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline int String::GetLength () const
{
    return m_iLength;
}
//----------------------------------------------------------------------------
inline String::operator const char* () const
{
    return m_acText;
}
//----------------------------------------------------------------------------
inline int String::GetMemoryUsed () const
{
    return sizeof(m_iLength) + (m_iLength+1)*sizeof(char);
}
//----------------------------------------------------------------------------
inline int String::GetDiskUsed () const
{
    return sizeof(m_iLength) + m_iLength*sizeof(char);
}
//----------------------------------------------------------------------------

