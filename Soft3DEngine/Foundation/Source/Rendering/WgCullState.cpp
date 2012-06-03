///////////////////////////////////////////////////////////
//                                                       //
//                    WgCullState.cpp                    //
//                                                       //
//  - Implementation for Cull State class                //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgFoundationPCH.h"
#include "WgCullState.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,CullState,GlobalState);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(CullState,GlobalState);

//----------------------------------------------------------------------------
CullState::CullState ()
{
    Enabled = true;
    FrontFace = FT_CCW;
    CullFace = CT_BACK;
	
}
//----------------------------------------------------------------------------
CullState::~CullState ()
{
}
//----------------------------------------------------------------------------
