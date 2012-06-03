///////////////////////////////////////////////////////////
//                                                       //
//                    WgLight.cpp                        //
//                                                       //
//  - Implementation for Light class                     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgLight.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,Light,Spatial);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(Light,Spatial);

//----------------------------------------------------------------------------
Light::Light (int iType)
    :
    Ambient(ColorRGBA::BLACK),
    Diffuse(ColorRGBA::WHITE),
    Specular(ColorRGBA::WHITE)
{
    SetFrame(Vector3x::ZERO,-Vector3x::UNIT_Z,Vector3x::UNIT_Y,
        Vector3x::UNIT_X);

    Type = iType;
    Intensity = FIXED_ONE;
    Constant = FIXED_ONE;
    Linear = FIXED_ZERO;
    Quadratic = FIXED_ZERO;
    Attenuate = false;
    On = true;

    // spot light parameters
    Exponent = FIXED_ZERO;
    Angle = Mathx::PI;
}
//----------------------------------------------------------------------------
Light::~Light ()
{
}
//----------------------------------------------------------------------------
void Light::SetFrame (const Vector3x& rkLocation, const Vector3x& rkDVector,
    const Vector3x& rkUVector, const Vector3x& rkRVector)
{
    Local.SetTranslate(rkLocation);
    Local.SetRotate(Matrix3x(rkDVector,rkUVector,rkRVector,true));
    OnFrameChange();
}
//----------------------------------------------------------------------------
void Light::SetFrame (const Vector3x& rkLocation, const Matrix3x& rkAxes)
{
    Local.SetTranslate(rkLocation);
    Local.SetRotate(rkAxes);
    OnFrameChange();
}
//----------------------------------------------------------------------------
void Light::SetLocation (const Vector3x& rkLocation)
{
    Local.SetTranslate(rkLocation);
    OnFrameChange();
}
//----------------------------------------------------------------------------
void Light::SetAxes (const Vector3x& rkDVector, const Vector3x& rkUVector,
    const Vector3x& rkRVector)
{
    Local.SetRotate(Matrix3x(rkDVector,rkUVector,rkRVector,true));
    OnFrameChange();
}
//----------------------------------------------------------------------------
void Light::SetAxes (const Matrix3x& rkAxes)
{
    Local.SetRotate(rkAxes);
    OnFrameChange();
}
//----------------------------------------------------------------------------
void Light::SetDirection (const Vector3x& rkDirection)
{
    Vector3x kDVector = rkDirection, kUVector, kRVector;
    Vector3x::GenerateComplementBasis(kUVector,kRVector,kDVector);
    SetAxes(kDVector,kUVector,kRVector);
    OnFrameChange();
}
//----------------------------------------------------------------------------
void Light::OnFrameChange ()
{
    // Get the world coordinate direction vectors for the light.  The input
    // application time of MAX_REAL is based on knowing that OnFrameChange
    // was called via Light interface functions, not through controllers.
    // If the light frame is modified by controllers, the local transforms
    // are modified directly through the Spatial interface, so that interface
    // itself will update the world transforms.  The application time passed
    // through the Spatial interface will be different than MAX_REAL, so
    // the Update call in this function will not prevent a controller update.
    UpdateGS(-Mathd::MAX_REAL);
}
//----------------------------------------------------------------------------
void Light::UpdateWorldBound ()
{
    // The light has an implicit model bound whose center is the light's
    // position and whose radius is zero.  If you attach a light as a Spatial
    // object, set the position even if the light does not formally have one.
    // For example, if you attach a directional light to headlight geometry in
    // an automobile, set the position of the light to somewhere inside the
    // headlight.  By doing so, you will help the culling system by
    // generating a properly sized world bound for the parent node of the
    // headlight.
    WorldBound->SetCenter(World.ApplyForward(Local.GetTranslate()));
    WorldBound->SetRadius(fixed(FIXED_ZERO));
}
//----------------------------------------------------------------------------
