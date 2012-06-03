///////////////////////////////////////////////////////////
//                                                       //
//                    WgGlobalState.h                    //
//                                                       //
//  - Interface for Global State class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_GLOBALSTATE_H__
#define __WG_GLOBALSTATE_H__

#include "WgFoundationLIB.h"
#include "WgObject.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM GlobalState : public Object
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
	
	
    // abstract base class
    virtual ~GlobalState ();

    // supported global states
    enum GlobalStateType
    {
        ALPHA,
        CULL,
        DITHER,
        FOG,
        MATERIAL,
        POLYGONOFFSET,
        SHADE,
 //       WIREFRAME,
        ZBUFFER,
		STENCIL,
        MAX_STATE
    };

    virtual GlobalStateType GetGlobalStateType () const=0;

	static void SetGlobalStates();
    // default states
    static Pointer<GlobalState> Default[MAX_STATE];

protected:
	GlobalState ();
};

typedef Pointer<GlobalState> GlobalStatePtr;

}

#endif

