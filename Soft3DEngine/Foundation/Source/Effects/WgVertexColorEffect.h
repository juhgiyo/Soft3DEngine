///////////////////////////////////////////////////////////
//                                                       //
//               WgVertexColorEffect.h                   //
//                                                       //
//  - Interface for Vertex Color Effect Class            //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////


#ifndef __WG_VERTEXCOLOREFFECT_H__
#define __WG_VERTEXCOLOREFFECT_H__

#include "WgFoundationLIB.h"
#include "WgEffect.h"
#include "WgColorRGBArray.h"
#include "WgColorRGBAArray.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM VertexColorEffect : public Effect
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;
    

public:
    VertexColorEffect (ColorRGBArray* pkColorRGBs);
    VertexColorEffect (ColorRGBAArray* pkColorRGBAs);
    virtual ~VertexColorEffect ();

    // create a clone of the effect
    virtual Effect* Clone ();

protected:
    VertexColorEffect ();
    virtual void DoCloning (Effect* pkClone);
};

typedef Pointer<VertexColorEffect> VertexColorEffectPtr;

}

#endif

