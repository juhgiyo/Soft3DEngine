///////////////////////////////////////////////////////////
//                                                       //
//               WgTextureEffect.h                       //
//                                                       //
//  - Interface for Texture Effect Class                 //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_TEXTUREEFFECT_H__
#define __WG_TEXTUREEFFECT_H__

#include "WgFoundationLIB.h"
#include "WgEffect.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM TextureEffect : public Effect
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;


public:
    TextureEffect (Texture* pkTexture, Vector2xArray* pkUVs);
    virtual ~TextureEffect ();

    // create a clone of the effect
    virtual Effect* Clone ();

protected:
    TextureEffect ();
    virtual void DoCloning (Effect* pkClone);
};

typedef Pointer<TextureEffect> TextureEffectPtr;

}

#endif

