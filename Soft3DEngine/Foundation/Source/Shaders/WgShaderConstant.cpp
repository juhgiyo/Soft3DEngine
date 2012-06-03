///////////////////////////////////////////////////////////
//                                                       //
//                    WgShaderConstant.cpp               //
//                                                       //
//  - Implementation for Shader Constant class           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgShaderConstant.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,ShaderConstant,Object);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(ShaderConstant,Object);

//----------------------------------------------------------------------------
ShaderConstant::ShaderConstant ()
{
    m_iSCType = SC_QUANTITY;
    m_iSCOption = SCO_NONE;
    m_iRegister = 0;
    m_iRegisterQuantity = 0;
    m_afData = 0;
}
//----------------------------------------------------------------------------
ShaderConstant::ShaderConstant (int iSCType, int iSCOption, int iRegister,
    int iRegisterQuantity)
{
    m_iSCType = iSCType;
    m_iSCOption = iSCOption;
    m_iRegister = iRegister;
    m_iRegisterQuantity = iRegisterQuantity;
    m_afData = WG_NEW fixed[4*m_iRegisterQuantity];
    memset(m_afData,0,4*m_iRegisterQuantity*sizeof(fixed));
}
//----------------------------------------------------------------------------
ShaderConstant::~ShaderConstant ()
{
    WG_DELETE[] m_afData;
}
//----------------------------------------------------------------------------
void ShaderConstant::SetRegisterData (int i, fixed fData0, fixed fData1,
    fixed fData2, fixed fData3)
{
    assert(0 <= i && i < m_iRegisterQuantity);
    fixed* pfData = &m_afData[4*i];
    *pfData++ = fData0;
    *pfData++ = fData1;
    *pfData++ = fData2;
    *pfData   = fData3;
}
//----------------------------------------------------------------------------
