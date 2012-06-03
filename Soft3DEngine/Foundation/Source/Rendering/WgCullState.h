///////////////////////////////////////////////////////////
//                                                       //
//                    WgCullState.h                      //
//                                                       //
//  - Interface for Cull State class                     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_CULLSTATE_H__
#define __WG_CULLSTATE_H__

#include "WgFoundationLIB.h"
#include "WgGlobalState.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM CullState : public GlobalState
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;
    
public:
    virtual GlobalStateType GetGlobalStateType () const { return CULL; }

    CullState ();
    virtual ~CullState ();

    enum FrontType
    {
        FT_CCW,  // front faces are counterclockwise ordered
        FT_CW,   // front faces are clockwise ordered
        FT_QUANTITY
    };

    enum CullType
    {
        CT_FRONT,  // cull front-facing triangles
        CT_BACK,   // cull back-facing triangles
        CT_QUANTITY
    };

    bool Enabled;   // default: true
    FrontType FrontFace;  // default: FT_CCW
    CullType CullFace;   // default: CT_BACK
};
typedef Pointer<CullState> CullStatePtr;

}

#endif

