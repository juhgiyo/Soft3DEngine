///////////////////////////////////////////////////////////
//                                                       //
//                    WgFogState.h                       //
//                                                       //
//  - Interface for Fog State class                      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_FOGSTATE_H__
#define __WG_FOGSTATE_H__

#include "WgFoundationLIB.h"
#include "WgGlobalState.h"
#include "WgColorRGBA.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM FogState : public GlobalState
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    virtual GlobalStateType GetGlobalStateType () const { return FOG; }

    FogState ();
    virtual ~FogState ();

    enum DensityFunction
    {
        DF_LINEAR,
        DF_EXP,
        DF_EXPSQR,
        DF_QUANTITY
    };

    enum ApplyFunction
    {
        AF_PER_VERTEX,
        AF_PER_PIXEL,
        AF_QUANTITY
    };

    bool Enabled;         // default: false
    fixed Start;          // default: 0
    fixed End;            // default: 1
    fixed Density;        // default: 1
    ColorRGBA Color;      // default: ColorRGB(0,0,0)
    DensityFunction DensityFunction;  // default: DF_LINEAR
    ApplyFunction ApplyFunction;    // default: AF_PER_VERTEX
};

typedef Pointer<FogState> FogStatePtr;

}

#endif

