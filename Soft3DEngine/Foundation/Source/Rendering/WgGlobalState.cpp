///////////////////////////////////////////////////////////
//                                                       //
//                    WgGlobalState.cpp                  //
//                                                       //
//  - Implementation for Global State class              //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgGlobalState.h"

#include "WgAlphaState.h"
#include "WgCullState.h"
#include "WgDitherState.h"
#include "WgFogState.h"
#include "WgMaterialState.h"
#include "WgPolygonOffsetState.h"
#include "WgShadeState.h"
#include "WgStencilState.h"
//#include "WgWireframeState.h"
#include "WgZBufferState.h"

using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,GlobalState,Object);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(GlobalState,Object);

GlobalStatePtr GlobalState::Default[GlobalState::MAX_STATE];

//----------------------------------------------------------------------------
GlobalState::GlobalState ()
{
}
//----------------------------------------------------------------------------
GlobalState::~GlobalState ()
{
}

void GlobalState::SetGlobalStates()
{
	if(!Default[ALPHA])
		Default[ALPHA]=new AlphaState();
	if(!Default[CULL])
		Default[CULL]=new CullState();
	if(!Default[DITHER])
		Default[DITHER]=new DitherState();
	if(!Default[FOG])
		Default[FOG]=new FogState();
	if(!Default[MATERIAL])
		Default[MATERIAL]=new MaterialState();
	if(!Default[POLYGONOFFSET])
		Default[POLYGONOFFSET]=new PolygonOffsetState();
	if(!Default[SHADE])
		Default[SHADE]=new ShadeState();
	if(!Default[STENCIL])
		Default[STENCIL]=new StencilState();
	if(!Default[ZBUFFER])
		Default[ZBUFFER]=new ZBufferState();
}
//----------------------------------------------------------------------------

