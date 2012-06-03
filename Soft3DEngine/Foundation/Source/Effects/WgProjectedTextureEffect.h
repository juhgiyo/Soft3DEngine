///////////////////////////////////////////////////////////
//                                                       //
//               WgProjectedTextureEffect.h              //
//                                                       //
//  - Interface for Projected Texture Effect Class       //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_PROJECTEDTEXTUREEFFECT_H__
#define __WG_PROJECTEDTEXTUREEFFECT_H__

#include "WgFoundationLIB.h"
#include "WgEffect.h"
#include "WgCamera.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM ProjectedTextureEffect : public Effect
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    ProjectedTextureEffect (Image* pkImage, Camera* pkCamera,
		Texture::ApplyMode iApplyMode);
    virtual ~ProjectedTextureEffect ();

    // Create a clone of the effect.  The camera is shared.
    virtual Effect* Clone ();

    // member access
    Camera* GetCamera () const;

protected:
    ProjectedTextureEffect ();
    virtual void DoCloning (Effect* pkClone);

    CameraPtr m_spkCamera;
};

typedef Pointer<ProjectedTextureEffect> ProjectedTextureEffectPtr;
#include "WgProjectedTextureEffect.inl"

}

#endif

