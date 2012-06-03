///////////////////////////////////////////////////////////
//                                                       //
//                    WgMaterialState.h                  //
//                                                       //
//  - Interface for Material State class                 //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_MATERIALSTATE_H__
#define __WG_MATERIALSTATE_H__

#include "WgFoundationLIB.h"
#include "WgGlobalState.h"
#include "WgColorRGBA.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM MaterialState : public GlobalState
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;
    
public:
    virtual GlobalStateType GetGlobalStateType () const { return MATERIAL; }

    MaterialState ();
    virtual ~MaterialState ();

    ColorRGBA Emissive;  // default:  ColorRGBA(0,0,0,1)
    ColorRGBA Ambient;   // default:  ColorRGBA(0.2,0.2,0.2,1)
    ColorRGBA Diffuse;   // default:  ColorRGBA(0.8,0.8,0.8,1)
    ColorRGBA Specular;  // default:  ColorRGBA(0,0,0,1)
    fixed Shininess;     // default:  1
};

typedef Pointer<MaterialState> MaterialStatePtr;

}

#endif

