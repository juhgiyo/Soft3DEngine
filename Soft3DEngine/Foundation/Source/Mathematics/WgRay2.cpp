///////////////////////////////////////////////////////////
//                                                       //
//                    WgRay2.cpp                         //
//                                                       //
//  - Implementation for Ray 2 class                     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgRay2.h"
namespace WGSoft3D
{
//----------------------------------------------------------------------------

Ray2x::Ray2x ()
{
	// uninitialized
}
//----------------------------------------------------------------------------

Ray2x::Ray2x (const Vector2x& rkOrigin,
	const Vector2x& rkDirection)
	:
	Origin(rkOrigin),
	Direction(rkDirection)
{
}
//----------------------------------------------------------------------------

}