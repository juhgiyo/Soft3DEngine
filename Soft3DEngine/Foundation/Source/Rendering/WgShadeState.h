///////////////////////////////////////////////////////////
//                                                       //
//                    WgShadeState.h                     //
//                                                       //
//  - Interface for Shade State class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_SHADESTATE_H__
#define __WG_SHADESTATE_H__

#include "WgFoundationLIB.h"
#include "WgGlobalState.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM ShadeState : public GlobalState
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    virtual GlobalStateType GetGlobalStateType () const { return SHADE; }

    ShadeState ();
    virtual ~ShadeState ();

    enum // ShadeMode
    {
        SM_FLAT,
        SM_SMOOTH,
        SM_QUANTITY
    };

    int Shade;  // default: SM_SMOOTH
};

typedef Pointer<ShadeState> ShadeStatePtr;

}

#endif

