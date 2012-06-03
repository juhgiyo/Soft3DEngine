///////////////////////////////////////////////////////////
//                                                       //
//                    WgImage.inl                        //
//                                                       //
//  - Inlines for Image class                            //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Image::TextureFormat Image::GetFormat () const
{
    return m_eFormat;
}
//----------------------------------------------------------------------------
inline int Image::GetBytesPerPixel () const
{
    return ms_aiBytesPerPixel[m_eFormat];
}
//----------------------------------------------------------------------------
inline int Image::GetWidth () const
{
    return m_iWidth;
}
//----------------------------------------------------------------------------
inline int Image::GetHeight () const
{
    return m_iHeight;
}
//----------------------------------------------------------------------------
inline int Image::GetQuantity () const
{
    return m_iQuantity;
}
//----------------------------------------------------------------------------
inline unsigned char* Image::GetData () const
{
    return m_aucData;
}
//----------------------------------------------------------------------------
inline unsigned char* Image::operator() (int i)
{
    return m_aucData + i*ms_aiBytesPerPixel[m_eFormat];
}
//----------------------------------------------------------------------------

