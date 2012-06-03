///////////////////////////////////////////////////////////
//                                                       //
//               WgPlanarShadowEffect.h                  //
//                                                       //
//  - Interface for Planar Shadow Effect Class           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_PLANARSHADOWEFFECT_H__
#define __WG_PLANARSHADOWEFFECT_H__

#include "WgFoundationLIB.h"
#include "WgEffect.h"
#include "WgLight.h"
#include "WgTriMesh.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM PlanarShadowEffect : public Effect
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    PlanarShadowEffect (int iQuantity);
    virtual ~PlanarShadowEffect ();

    // Create a clone of the effect.  The planes and projectors are shared.
    // The shadow colors are copied.  The stencil values are uniquely
    // generated in the cloned object.
    virtual Effect* Clone ();

    // member access
    int GetQuantity () const;
    void SetPlane (int i, TriMeshPtr spkPlane);
    TriMeshPtr GetPlane (int i) const;
    void SetProjector (int i, LightPtr spkProjector);
    LightPtr GetProjector (int i) const;
    void SetShadowColor (int i, const ColorRGBA& rkShadowColor);
    const ColorRGBA& GetShadowColor (int i) const;

protected:
    PlanarShadowEffect ();
    virtual void DoCloning (Effect* pkClone);

    int m_iQuantity;
    TriMeshPtr* m_aspkPlane;
    LightPtr* m_aspkProjector;
    ColorRGBA* m_akShadowColor;
};

typedef Pointer<PlanarShadowEffect> PlanarShadowEffectPtr;
#include "WgPlanarShadowEffect.inl"

}

#endif

