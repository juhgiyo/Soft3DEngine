///////////////////////////////////////////////////////////
//                                                       //
//                    WgObject.inl                       //
//                                                       //
//  - Inlines for Object class                           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline bool Transformation::IsIdentity () const
{
    return m_bIsIdentity;
}
//----------------------------------------------------------------------------
inline bool Transformation::IsRSMatrix () const
{
    return m_bIsRSMatrix;
}
//----------------------------------------------------------------------------
inline bool Transformation::IsUniformScale () const
{
    return m_bIsRSMatrix && m_bIsUniformScale;
}
//----------------------------------------------------------------------------
inline const Matrix3x& Transformation::GetRotate () const
{
    assert(m_bIsRSMatrix);
    return m_kMatrix;
}
//----------------------------------------------------------------------------
inline const Matrix3x& Transformation::GetMatrix () const
{
    return m_kMatrix;
}
//----------------------------------------------------------------------------
inline const Vector3x& Transformation::GetTranslate () const
{
    return m_kTranslate;
}
//----------------------------------------------------------------------------
inline const Vector3x& Transformation::GetScale () const
{
    assert(m_bIsRSMatrix);
    return m_kScale;
}
//----------------------------------------------------------------------------
inline fixed Transformation::GetUniformScale () const
{
    assert(m_bIsRSMatrix && m_bIsUniformScale);
    return m_kScale.X();
}
//----------------------------------------------------------------------------

