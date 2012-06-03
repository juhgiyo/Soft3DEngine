///////////////////////////////////////////////////////////
//                                                       //
//                    WgLightMapEffect.h                 //
//                                                       //
//  - Interface for Light Map Effect Class               //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////


#ifndef __WG_LIGHTMAPEFFECT_H__
#define __WG_LIGHTMAPEFFECT_H__

#include "WgFoundationLIB.h"
#include "WgEffect.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM LightMapEffect : public Effect
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    LightMapEffect (Texture* pkPrimaryTexture, Vector2xArray* pkPrimaryUVs,
        Texture* pkSecondaryTexture, Vector2xArray* pkSecondaryUVs,
        bool bHardAdd = true);
    virtual ~LightMapEffect ();

    // create a clone of the effect
    virtual Effect* Clone ();

protected:
    LightMapEffect ();
    virtual void DoCloning (Effect* pkClone);
};

typedef Pointer<LightMapEffect> LightMapEffectPtr;

}

#endif

