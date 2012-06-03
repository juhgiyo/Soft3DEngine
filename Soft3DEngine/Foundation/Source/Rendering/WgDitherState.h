///////////////////////////////////////////////////////////
//                                                       //
//                    WgDitherState.h                    //
//                                                       //
//  - Interface for Dither State class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_DITHERSTATE_H__
#define __WG_DITHERSTATE_H__

#include "WgFoundationLIB.h"
#include "WgGlobalState.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM DitherState : public GlobalState
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;
    

public:
    virtual GlobalStateType GetGlobalStateType () const { return DITHER; }

    DitherState ();
    virtual ~DitherState ();

    bool Enabled;  // default: false
};

typedef Pointer<DitherState> DitherStatePtr;

}

#endif

