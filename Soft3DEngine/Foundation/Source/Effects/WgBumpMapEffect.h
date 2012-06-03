///////////////////////////////////////////////////////////
//                                                       //
//                    WgBumpMapEffect.h                  //
//                                                       //
//  - Interface for Bump Map Effect Class                //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_BUMPMAPEFFECT_H__
#define __WG_BUMPMAPEFFECT_H__

#include "WgFoundationLIB.h"
#include "WgEffect.h"
#include "WgAlphaState.h"
#include "WgColorRGBArray.h"
#include "WgLight.h"
#include "WgTriangles.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM BumpMapEffect : public Effect
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;


public:
    BumpMapEffect (Image* pkPrimary, Vector2xArray* pkPrimaryUVs,
        Image* pkNormalMap, Vector2xArray* pkNormalUVs, Light* pkLight);

    virtual ~BumpMapEffect ();

    // Create a clone of the effect.  The light is shared.
    virtual Effect* Clone ();

    // member access
    Light* GetLight () const;

    // Call this function if any of the following change:
    // (1) The light's world position (point or spot lights).
    // (2) The light's world direction (directional lights).
    // (3) The mesh world transformation.
    // (4) The mesh vertex positions or normals.
    void NeedsRecalculation ();

protected:
    BumpMapEffect ();
    virtual void DoCloning (Effect* pkClone);

    LightPtr m_spkLight;
    bool m_bNeedsRecalculation;

// internal use
public:
    // Compute the light vectors whenever model space vertices, model space
    // normals, primary uvs, or light location/direction change.
    void ComputeLightVectors (Triangles* pkMesh);
    bool GetNeedsRecalculation () const;
};

typedef Pointer<BumpMapEffect> BumpMapEffectPtr;
#include "WgBumpMapEffect.inl"

}

#endif

