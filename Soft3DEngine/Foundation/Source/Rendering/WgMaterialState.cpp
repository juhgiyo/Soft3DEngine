///////////////////////////////////////////////////////////
//                                                       //
//                    WgMaterialState.cpp                //
//                                                       //
//  - Implementation for Material State class            //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgMaterialState.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,MaterialState,GlobalState);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(MaterialState,GlobalState);

//----------------------------------------------------------------------------
MaterialState::MaterialState ()
    :
    Emissive(ColorRGBA::BLACK),
    Ambient(fixed(FixedFromFloat((float)0.2f)),fixed(FixedFromFloat((float)0.2f)),fixed(FixedFromFloat((float)0.2f)),fixed(FixedFromFloat((float)1.0f))),
    Diffuse(fixed(FixedFromFloat((float)0.8f)),fixed(FixedFromFloat((float)0.8f)),fixed(FixedFromFloat((float)0.8f)),fixed(FixedFromFloat((float)1.0f))),
    Specular(ColorRGBA::BLACK)
{
    Shininess = FIXED_ONE;


}
//----------------------------------------------------------------------------
MaterialState::~MaterialState ()
{
}
//----------------------------------------------------------------------------
