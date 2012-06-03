///////////////////////////////////////////////////////////
//                                                       //
//                    WgEffect.h                         //
//                                                       //
//  - Interface for Effect Class                         //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_EFFECT_H__
#define __WG_EFFECT_H__

#include "WgFoundationLIB.h"
#include "WgObject.h"
#include "WgRenderer.h"
#include "WgColorRGBArray.h"
#include "WgColorRGBAArray.h"
#include "WgTexture.h"
#include "WgVector2Array.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM Effect : public Object
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;


public:
    // The base class is not abstract.  This allows you to create an Effect
    // object and set the colors and textures as desired.  In particular, if
    // you have a special effect that involves fancy use of the "combine"
    // capabilities of textures, you can do this without having to derive
    // a class from Effect to manage the new feature.
    Effect ();
    virtual ~Effect ();

    // Create a clone of the effect.  Colors and textures are shared.  Each
    // derived class can override this behavior and decide what is copied
    // and what is shared.
    virtual Effect* Clone ();

    // data common to many effects
    ColorRGBArrayPtr ColorRGBs;
    ColorRGBAArrayPtr ColorRGBAs;
    TArray<TexturePtr> Textures;
    TArray<Vector2xArrayPtr> UVs;
	
	virtual void RemoveColorRGBData();
	virtual void RemoveColorRGBAData();
	virtual void RemoveTextureRawData(int i);
	virtual void RemoveTextureUVData(int i);
protected:
    virtual void DoCloning (Effect* pkClone);

// internal use
public:
    // function required to draw the effect
    Renderer::DrawFunction Draw;
};

typedef Pointer<Effect> EffectPtr;

}

#endif

