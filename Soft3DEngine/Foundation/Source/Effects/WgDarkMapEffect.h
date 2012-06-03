///////////////////////////////////////////////////////////
//                                                       //
//                    WgDarkMapEffect.h                  //
//                                                       //
//  - Interface for Dark Map Effect Class                //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_DARKMAPEFFECT_H__
#define __WG_DARKMAPEFFECT_H__

#include "WgFoundationLIB.h"
#include "WgEffect.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM DarkMapEffect : public Effect
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    DarkMapEffect (Texture* pkPrimaryTexture, Vector2xArray* pkPrimaryUVs,
        Texture* pkSecondaryTexture, Vector2xArray* pkSecondaryUVs);
    virtual ~DarkMapEffect ();

    // create a clone of the effect
    virtual Effect* Clone ();

protected:
    DarkMapEffect ();
    virtual void DoCloning (Effect* pkClone);
};

typedef Pointer<DarkMapEffect> DarkMapEffectPtr;

}

#endif

