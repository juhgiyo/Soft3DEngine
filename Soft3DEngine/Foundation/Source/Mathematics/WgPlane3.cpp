///////////////////////////////////////////////////////////
//                                                       //
//                    WgPlane3.cpp                       //
//                                                       //
//  - Implementation for Plane 3 class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgPlane3.h"
namespace WGSoft3D
{
//----------------------------------------------------------------------------

Plane3x::Plane3x ()
{
	// uninitialized
}
//----------------------------------------------------------------------------

Plane3x::Plane3x (const Plane3x& rkPlane)
	:
Normal(rkPlane.Normal)
{
	Constant = rkPlane.Constant;
}
//----------------------------------------------------------------------------

Plane3x::Plane3x (const Vector3x& rkNormal, fixed fConstant)
{
	Vector3x iVec=rkNormal;
	if(iVec.Length()!=FIXED_ONE)
	{
		iVec=rkNormal;
		iVec.Normalize();
	}
	Normal=iVec;
	Constant = fConstant;
}
//----------------------------------------------------------------------------

Plane3x::Plane3x (const Vector3x& rkNormal, const Vector3x& rkP)
{
	Vector3x iVec=rkNormal;
	if(iVec.Length()!=FIXED_ONE)
	{
		iVec=rkNormal;
		iVec.Normalize();
	}
	Normal=iVec;
	Constant = rkNormal.Dot(rkP);
}
//----------------------------------------------------------------------------

Plane3x::Plane3x (const Vector3x& rkP0, const Vector3x& rkP1,
	const Vector3x& rkP2)
{
	Vector3x kEdge1 = rkP1 - rkP0;
	Vector3x kEdge2 = rkP2 - rkP0;
	Normal = kEdge1.UnitCross(kEdge2);
	Constant = Normal.Dot(rkP0);
}
//----------------------------------------------------------------------------

Plane3x& Plane3x::operator= (const Plane3x& rkPlane)
{
	Normal = rkPlane.Normal;
	Constant = rkPlane.Constant;
	return *this;
}
//----------------------------------------------------------------------------

fixed Plane3x::DistanceTo (const Vector3x& rkP) const
{
	return Normal.Dot(rkP) - Constant;
}
//----------------------------------------------------------------------------

int Plane3x::WhichSide (const Vector3x& rkQ) const
{
	fixed fDistance = DistanceTo(rkQ);
	
	if (fDistance < FIXED_ZERO)
	{
		return -1;
	}
	
	if (fDistance > FIXED_ZERO)
	{
		return +1;
	}
	
	return 0;
}
//----------------------------------------------------------------------------
}