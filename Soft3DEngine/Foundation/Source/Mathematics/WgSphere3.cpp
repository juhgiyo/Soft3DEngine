///////////////////////////////////////////////////////////
//                                                       //
//                    WgSphere3.cpp                      //
//                                                       //
//  - Implementation for Sphere 3 class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgSphere3.h"
namespace WGSoft3D
{
//----------------------------------------------------------------------------

Sphere3x::Sphere3x ()
{
	// uninitialized
}
//----------------------------------------------------------------------------

Sphere3x::Sphere3x (const Vector3x& rkCenter, fixed fRadius)
	:
	Center(rkCenter),
	Radius(fRadius)
{
}
//----------------------------------------------------------------------------

Sphere3x::Sphere3x (const Sphere3x& rkSphere)
	:
	Center(rkSphere.Center),
	Radius(rkSphere.Radius)
{
}
//----------------------------------------------------------------------------

Sphere3x& Sphere3x::operator= (const Sphere3x& rkSphere)
{
	Center = rkSphere.Center;
	Radius = rkSphere.Radius;
	return *this;
}
//----------------------------------------------------------------------------
}