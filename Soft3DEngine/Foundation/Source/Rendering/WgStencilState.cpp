///////////////////////////////////////////////////////////
//                                                       //
//                    WgStencilState.cpp                 //
//                                                       //
//  - Implementation for Stencil State class             //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgStencilState.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,StencilState,GlobalState);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(StencilState,GlobalState);

const char* StencilState::ms_aacCompare[StencilState::CF_QUANTITY] =
{
    "CF_NEVER",
    "CF_LESS",
    "CF_EQUAL",
    "CF_LEQUAL",
    "CF_GREATER",
    "CF_NOTEQUAL",
    "CF_GEQUAL",
    "CF_ALWAYS"
};

const char* StencilState::ms_aacOperation[StencilState::OT_QUANTITY] =
{
    "OT_KEEP",
    "OT_ZERO",
    "OT_REPLACE",
    "OT_INCREMENT",
    "OT_DECREMENT",
    "OT_INVERT"
};

//----------------------------------------------------------------------------
StencilState::StencilState ()
{
    Enabled = false;
    Compare = CF_NEVER;
    Reference = 0;
    Mask = (unsigned int)~0;
    WriteMask = (unsigned int)~0;
    OnFail = OT_KEEP;
    OnZFail = OT_KEEP;
    OnZPass = OT_KEEP;

}
//----------------------------------------------------------------------------
StencilState::~StencilState ()
{
}
//----------------------------------------------------------------------------