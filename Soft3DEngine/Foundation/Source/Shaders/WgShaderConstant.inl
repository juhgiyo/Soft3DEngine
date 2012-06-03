///////////////////////////////////////////////////////////
//                                                       //
//                    WgShaderConstant.inl               //
//                                                       //
//  - Inlines for Shader Constant class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline int ShaderConstant::GetSCType () const
{
    return m_iSCType;
}
//----------------------------------------------------------------------------
inline int ShaderConstant::GetSCOption () const
{
    return m_iSCOption;
}
//----------------------------------------------------------------------------
inline int ShaderConstant::GetRegister () const
{
    return m_iRegister;
}
//----------------------------------------------------------------------------
inline int ShaderConstant::GetRegisterQuantity () const
{
    return m_iRegisterQuantity;
}
//----------------------------------------------------------------------------
inline fixed* ShaderConstant::Data ()
{
    return m_afData;
}
//----------------------------------------------------------------------------
inline fixed ShaderConstant::Data (int i) const
{
    return m_afData[i];
}
//----------------------------------------------------------------------------

