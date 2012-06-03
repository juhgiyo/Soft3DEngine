///////////////////////////////////////////////////////////
//                                                       //
//                    WgZBufferState.h                   //
//                                                       //
//  - Interface for ZBuffer State class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_ZBUFFERSTATE_H__
#define __WG_ZBUFFERSTATE_H__

#include "WgFoundationLIB.h"
#include "WgGlobalState.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM ZBufferState : public GlobalState
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    virtual GlobalStateType GetGlobalStateType () const { return ZBUFFER; }

    ZBufferState ();
    virtual ~ZBufferState ();

    typedef enum _compFunc// Compare values
    {
        CF_NEVER,
        CF_LESS,
        CF_EQUAL,
        CF_LEQUAL,
        CF_GREATER,
        CF_NOTEQUAL,
        CF_GEQUAL,
        CF_ALWAYS,
        CF_QUANTITY
    }CompareFunc;

    bool Enabled;    // default: true
    bool Writable;   // default: true
    CompareFunc Compare;     // default: CF_LEQUAL
};

typedef Pointer<ZBufferState> ZBufferStatePtr;

}

#endif

