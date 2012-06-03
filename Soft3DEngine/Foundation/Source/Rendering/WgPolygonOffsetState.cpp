///////////////////////////////////////////////////////////
//                                                       //
//                    WgPolygonOffsetState.cpp           //
//                                                       //
//  - Implementation for Polygon Offset State class      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgPolygonOffsetState.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,PolygonOffsetState,GlobalState);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(PolygonOffsetState,GlobalState);

//----------------------------------------------------------------------------
PolygonOffsetState::PolygonOffsetState ()
{
    FillEnabled = false;
    LineEnabled = false;
    PointEnabled = false;
    Scale = FIXED_ZERO;
    Bias = FIXED_ZERO;

}
//----------------------------------------------------------------------------
PolygonOffsetState::~PolygonOffsetState ()
{
}
//----------------------------------------------------------------------------
