///////////////////////////////////////////////////////////
//                                                       //
//                    WgDitherState.cpp                  //
//                                                       //
//  - Implementation for Dither State class              //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgDitherState.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,DitherState,GlobalState);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(DitherState,GlobalState);

//----------------------------------------------------------------------------
DitherState::DitherState ()
{
    Enabled = false;
	
}
//----------------------------------------------------------------------------
DitherState::~DitherState ()
{
}
//----------------------------------------------------------------------------