///////////////////////////////////////////////////////////
//                                                       //
//                    WgRenderer.inl                     //
//                                                       //
//  - Inlines for Renderer class                         //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline int Renderer::GetType ()
{
    return ms_eType;
}
//----------------------------------------------------------------------------
// inline void Renderer::Activate ()
// {
//     // stub for derived classes
// }
// //----------------------------------------------------------------------------
// inline bool Renderer::IsActive () const
// {
//     // stub for derived classes
//     return true;
// }
//----------------------------------------------------------------------------
inline Camera* Renderer::GetCamera () const
{
    return m_pkCamera;
}
//----------------------------------------------------------------------------
inline const BufferParams& Renderer::GetBufferParams () const
{
    return m_kBufferParams;
}
//----------------------------------------------------------------------------
inline int Renderer::GetWidth () const
{
    return m_iWidth;
}
//----------------------------------------------------------------------------
inline int Renderer::GetHeight () const
{
    return m_iHeight;
}
//----------------------------------------------------------------------------
inline void Renderer::SetBackgroundColor (const ColorRGBA& rkColor)
{
    m_kBackgroundColor = rkColor;
}
//----------------------------------------------------------------------------
inline const ColorRGBA& Renderer::GetBackgroundColor () const
{
    return m_kBackgroundColor;
}
//----------------------------------------------------------------------------
// inline bool Renderer::BeginScene ()
// {
//     // stub for derived classes
//     return true;
// }
// //----------------------------------------------------------------------------
// inline void Renderer::EndScene ()
// {
//     // stub for derived classes
// }
//----------------------------------------------------------------------------
inline void Renderer::SetPointSize (fixed fSize)
{
    if (fSize > FIXED_ZERO)
    {
        m_fPointSize = fSize;
    }
}
//----------------------------------------------------------------------------
inline fixed Renderer::GetPointSize () const
{
    return m_fPointSize;
}
//----------------------------------------------------------------------------
inline void Renderer::SetLineWidth (fixed fWidth)
{
    if (fWidth > FIXED_ZERO)
    {
        m_fLineWidth = fWidth;
    }
}
//----------------------------------------------------------------------------
inline fixed Renderer::GetLineWidth () const
{
    return m_fLineWidth;
}
//----------------------------------------------------------------------------
inline void Renderer::SetLineStipple (int iRepeat, unsigned short usPattern)
{
    if (iRepeat < 0)
    {
        iRepeat = 0;
    }
    m_iLineStippleRepeat = iRepeat;
    m_usLineStipplePattern = usPattern;
}
//----------------------------------------------------------------------------
inline int Renderer::GetLineStippleRepeat () const
{
    return m_iLineStippleRepeat;
}
//----------------------------------------------------------------------------
inline unsigned short Renderer::GetLineStipplePattern () const
{
    return m_usLineStipplePattern;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxLights () const
{
    return m_iMaxLights;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxTextures () const
{
    return m_iMaxTextures;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxStencilIndices () const
{
    return m_iMaxStencilIndices;
}
//----------------------------------------------------------------------------
inline Texture* Renderer::GetTarget ()
{
    return m_pkTarget;
}
//----------------------------------------------------------------------------
