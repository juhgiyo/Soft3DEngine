///////////////////////////////////////////////////////////
//                                                       //
//                    WgAlphaState.h                     //
//                                                       //
//  - Interface for Alpha State class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_ALPHASTATE_H__
#define __WG_ALPHASTATE_H__

#include "WgFoundationLIB.h"
#include "WgGlobalState.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM AlphaState : public GlobalState
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    virtual GlobalStateType GetGlobalStateType () const { return ALPHA; }

    AlphaState ();
    virtual ~AlphaState ();

    enum SrcBlendFunc //values
    {
        SBF_ZERO,
        SBF_ONE,
        SBF_DST_COLOR,
        SBF_ONE_MINUS_DST_COLOR,
        SBF_SRC_ALPHA,
        SBF_ONE_MINUS_SRC_ALPHA,
        SBF_DST_ALPHA,
        SBF_ONE_MINUS_DST_ALPHA,
        SBF_SRC_ALPHA_SATURATE,
        SBF_CONSTANT_COLOR,
        SBF_ONE_MINUS_CONSTANT_COLOR,
        SBF_CONSTANT_ALPHA,
        SBF_ONE_MINUS_CONSTANT_ALPHA,
        SBF_QUANTITY
    };

    enum DstBlendFunc // values
    {
        DBF_ZERO,
        DBF_ONE,
        DBF_SRC_COLOR,
        DBF_ONE_MINUS_SRC_COLOR,
        DBF_SRC_ALPHA,
        DBF_ONE_MINUS_SRC_ALPHA,
        DBF_DST_ALPHA,
        DBF_ONE_MINUS_DST_ALPHA,
        DBF_CONSTANT_COLOR,
        DBF_ONE_MINUS_CONSTANT_COLOR,
        DBF_CONSTANT_ALPHA,
        DBF_ONE_MINUS_CONSTANT_ALPHA,
        DBF_QUANTITY
    };

    enum TestFunc// Test values
    {
        TF_NEVER,
        TF_LESS,
        TF_EQUAL,
        TF_LEQUAL,
        TF_GREATER,
        TF_NOTEQUAL,
        TF_GEQUAL,
        TF_ALWAYS,
        TF_QUANTITY
    };

    bool BlendEnabled;  // default: false
    SrcBlendFunc SrcBlend;       // default: SBF_SRC_ALPHA
    DstBlendFunc DstBlend;       // default: DBF_ONE_MINUS_SRC_ALPHA
    bool TestEnabled;   // default: false;
    TestFunc Test;           // default: TF_ALWAYS
    fixed Reference;    // default: 0, always in [0,1]
};

typedef Pointer<AlphaState> AlphaStatePtr;

}

#endif

