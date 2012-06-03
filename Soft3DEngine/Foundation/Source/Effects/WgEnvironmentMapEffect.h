///////////////////////////////////////////////////////////
//                                                       //
//                    WgEnvironmentMapEffect.h           //
//                                                       //
//  - Interface for Environment Map Effect Class         //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_ENVIRONMENTMAPEFFECT_H__
#define __WG_ENVIRONMENTMAPEFFECT_H__

#include "WgFoundationLIB.h"
#include "WgEffect.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM EnvironmentMapEffect : public Effect
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    EnvironmentMapEffect (Image* pkImage, Texture::ApplyMode iApplyMode);
    virtual ~EnvironmentMapEffect ();

    // create a clone of the effect
    virtual Effect* Clone ();

protected:
    EnvironmentMapEffect ();
    virtual void DoCloning (Effect* pkClone);
};


typedef Pointer<EnvironmentMapEffect> EnvironmentMapEffectPtr;

}

#endif

