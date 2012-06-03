///////////////////////////////////////////////////////////
//                                                       //
//                    WgZBufferState.cpp                 //
//                                                       //
//  - Implementation for ZBuffer State class             //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgFoundationPCH.h"
#include "WgZBufferState.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,ZBufferState,GlobalState);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(ZBufferState,GlobalState);

//----------------------------------------------------------------------------
ZBufferState::ZBufferState ()
{
    Enabled = true;
    Writable = true;
    Compare = ZBufferState::CF_LEQUAL;
	

}
//----------------------------------------------------------------------------
ZBufferState::~ZBufferState ()
{
}
//----------------------------------------------------------------------------

