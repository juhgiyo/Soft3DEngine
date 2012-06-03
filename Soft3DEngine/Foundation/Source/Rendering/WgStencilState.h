///////////////////////////////////////////////////////////
//                                                       //
//                    WgStencilState.h                   //
//                                                       //
//  - Interface for Stencil State class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef _WG_STENCILSTATE_H_
#define _WG_STENCILSTATE_H_

#include "WgFoundationLIB.h"
#include "WgGlobalState.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM StencilState : public GlobalState
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    virtual GlobalStateType GetGlobalStateType () const { return STENCIL; }

    StencilState ();
    virtual ~StencilState ();

    enum CompareFunction
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
    };

    enum OperationType
    {
        OT_KEEP,
        OT_ZERO,
        OT_REPLACE,
        OT_INCREMENT,
        OT_DECREMENT,
        OT_INVERT,
        OT_QUANTITY
    };

    bool Enabled;             // default: false
    CompareFunction Compare;  // default: CF_NEVER
    unsigned int Reference;   // default: 0
    unsigned int Mask;        // default: ~0
    unsigned int WriteMask;   // default: ~0
    OperationType OnFail;     // default: OT_KEEP
    OperationType OnZFail;    // default: OT_KEEP
    OperationType OnZPass;    // default: OT_KEEP

private:
    static const char* ms_aacCompare[CF_QUANTITY];
    static const char* ms_aacOperation[OT_QUANTITY];
};

typedef Pointer<StencilState> StencilStatePtr;

}

#endif
