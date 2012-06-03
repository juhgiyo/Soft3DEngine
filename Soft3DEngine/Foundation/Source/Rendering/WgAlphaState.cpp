///////////////////////////////////////////////////////////
//                                                       //
//                    WgAlphaState.cpp                   //
//                                                       //
//  - Implementation for Alpha State class               //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgAlphaState.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,AlphaState,GlobalState);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(AlphaState,GlobalState);

//----------------------------------------------------------------------------
AlphaState::AlphaState ()
{
    BlendEnabled = false;
    SrcBlend = SBF_SRC_ALPHA;
    DstBlend = DBF_ONE_MINUS_SRC_ALPHA;
    TestEnabled = false;
    Test = TF_ALWAYS;
    Reference = FIXED_ZERO;

}
//----------------------------------------------------------------------------
AlphaState::~AlphaState ()
{
}
//----------------------------------------------------------------------------

