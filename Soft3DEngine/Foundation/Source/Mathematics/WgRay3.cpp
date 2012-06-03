///////////////////////////////////////////////////////////
//                                                       //
//                    WgRay3.cpp                         //
//                                                       //
//  - Implementation for Ray 3 class                     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgRay3.h"
namespace WGSoft3D
{
//----------------------------------------------------------------------------

Ray3x::Ray3x ()
{
	// uninitialized
}
//----------------------------------------------------------------------------

Ray3x::Ray3x (const Vector3x& rkOrigin,
	const Vector3x& rkDirection)
	:
	Origin(rkOrigin),
	Direction(rkDirection)
{
}
//----------------------------------------------------------------------------
}