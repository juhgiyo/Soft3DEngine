///////////////////////////////////////////////////////////
//                                                       //
//                    WgGlossMapEffect.h                 //
//                                                       //
//  - Interface for GLoss Map Effect Class               //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_GLOSSMAPEFFECT_H__
#define __WG_GLOSSMAPEFFECT_H__

#include "WgFoundationLIB.h"
#include "WgEffect.h"
#include "WgAlphaState.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM GlossMapEffect : public Effect
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    GlossMapEffect (Texture* pkTexture, Vector2xArray* pkUVs);
    virtual ~GlossMapEffect ();

    // Create a clone of the effect.
    virtual Effect* Clone ();

protected:
    GlossMapEffect ();
    virtual void DoCloning (Effect* pkClone);
};

typedef Pointer<GlossMapEffect> GlossMapEffectPtr;

}

#endif

