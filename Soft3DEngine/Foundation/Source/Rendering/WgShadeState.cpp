///////////////////////////////////////////////////////////
//                                                       //
//                    WgShadeState.cpp                   //
//                                                       //
//  - Implementation for Shade State class               //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgShadeState.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,ShadeState,GlobalState);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(ShadeState,GlobalState);


//----------------------------------------------------------------------------
ShadeState::ShadeState ()
{
    Shade = SM_SMOOTH;

}
//----------------------------------------------------------------------------
ShadeState::~ShadeState ()
{
}
//----------------------------------------------------------------------------
