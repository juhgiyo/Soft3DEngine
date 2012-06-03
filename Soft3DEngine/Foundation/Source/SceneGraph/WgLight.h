///////////////////////////////////////////////////////////
//                                                       //
//                    WgLight.h                          //
//                                                       //
//  - Interface for Light class                          //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_LIGHT_H__
#define __WG_LIGHT_H__

#include "WgFoundationLIB.h"
#include "WgSpatial.h"
#include "WgColorRGBA.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM Light : public Spatial
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    enum // Type
    {
        LT_AMBIENT,
        LT_DIRECTIONAL,
        LT_POINT,
        LT_SPOT,
        LT_QUANTITY
    };

    Light (int iType = LT_AMBIENT);
    virtual ~Light ();

    // light frame (local coordinates)
    //   default location  E = (0,0,0)
    //   default direction D = (0,0,-1)
    //   default up        U = (0,1,0)
    //   default right     R = (1,0,0)
    void SetFrame (const Vector3x& rkLocation, const Vector3x& rkDVector,
        const Vector3x& rkUVector, const Vector3x& rkRVector);
    void SetFrame (const Vector3x& rkLocation, const Matrix3x& rkAxes);
    void SetLocation (const Vector3x& rkLocation);
    void SetAxes (const Vector3x& rkDVector, const Vector3x& rkUVector,
        const Vector3x& rkRVector);
    void SetAxes (const Matrix3x& rkAxes);
    Vector3x GetLocation () const;  // Local.Translate
    Vector3x GetDVector () const;   // Local.Rotate column 0
    Vector3x GetUVector () const;   // Local.Rotate column 1
    Vector3x GetRVector () const;   // Local.Rotate column 2

    // For directional lights.  The direction vector must be unit length.
    // The up vector and left vector are generated automatically.
    void SetDirection (const Vector3x& rkDirection);

    // light frame (world coordinates)
    Vector3x GetWorldLocation () const;  // World.Translate
    Vector3x GetWorldDVector () const;   // World.Rotate column 0
    Vector3x GetWorldUVector () const;   // World.Rotate column 1
    Vector3x GetWorldRVector () const;   // World.Rotate column 2

    int Type;            // default: LT_AMBIENT
    ColorRGBA Ambient;   // default: ColorRGBA(0,0,0,1)
    ColorRGBA Diffuse;   // default: ColorRGBA(1,1,1,1)
    ColorRGBA Specular;  // default: ColorRGBA(1,1,1,1)
    fixed Intensity;     // default: 1
    fixed Constant;      // default: 1
    fixed Linear;        // default: 0
    fixed Quadratic;     // default: 0
    bool Attenuate;      // default: false
    bool On;             // default: true

    // spot light parameters (valid only when Type = LT_SPOT)
    fixed Exponent;
    fixed Angle;

private:
    // updates
    virtual void UpdateWorldBound ();
    void OnFrameChange ();

    // base class functions not supported
    virtual void UpdateState (TStack<GlobalState*>*, TStack<Light*>*) { /**/ }
    virtual void Draw (Renderer&, bool) { /**/ }

};

typedef Pointer<Light> LightPtr;
#include "WgLight.inl"

}

#endif

