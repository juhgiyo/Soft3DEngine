///////////////////////////////////////////////////////////
//                                                       //
//                    WgFogState.cpp                     //
//                                                       //
//  - Implementation for Fog State class                 //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#include "WgFoundationPCH.h"
#include "WgFogState.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,FogState,GlobalState);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(FogState,GlobalState);

//----------------------------------------------------------------------------
FogState::FogState ()
    :
    Color(ColorRGBA::BLACK)
{
    Enabled = false;
    Start = FIXED_ZERO;
    End = FIXED_ONE;
    Density = FIXED_ONE;
    DensityFunction = DF_LINEAR;
    ApplyFunction = AF_PER_VERTEX;
	
}
//----------------------------------------------------------------------------
FogState::~FogState ()
{
}
//----------------------------------------------------------------------------

