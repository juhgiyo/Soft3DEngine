///////////////////////////////////////////////////////////
//                                                       //
//                    WgFrustum3.cpp                     //
//                                                       //
//  - Implementation for Frustum 3 class                 //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgFrustum3.h"

namespace WGSoft3D
{
//----------------------------------------------------------------------------

Frustum3x::Frustum3x ()
	:
Origin(Vector3x::ZERO),
	DVector(-Vector3x::UNIT_Z),
	UVector(Vector3x::UNIT_Y),
	RVector(Vector3x::UNIT_X)
{
	DMin = FIXED_ONE;
	DMax = FixedFromFloat((float)2.0);
	UBound = FIXED_ONE;
	RBound = FIXED_ONE;
	
	Update();
}
//----------------------------------------------------------------------------

Frustum3x::Frustum3x (const Vector3x& rkOrigin,
	const Vector3x& rkDVector, const Vector3x& rkUVector,
	const Vector3x& rkRVector, fixed fDMin, fixed fDMax, fixed fUBound,
	fixed fRBound)
	:
	Origin(rkOrigin),
	DVector(rkDVector),
	UVector(rkUVector),
	RVector(rkRVector)
{
	DMin = fDMin;
	DMax = fDMax;
	UBound = fUBound;
	RBound = fRBound;
	
	Update();
}
//----------------------------------------------------------------------------

void Frustum3x::Update ()
{
	m_fDRatio = DMax/DMin;
	m_fMTwoUF = FixedFromFloat((float)-2.0)*UBound*DMax;
	m_fMTwoRF = FixedFromFloat((float)-2.0)*RBound*DMax;
}
//----------------------------------------------------------------------------

fixed Frustum3x::GetDRatio () const
{
	return m_fDRatio;
}
//----------------------------------------------------------------------------

fixed Frustum3x::GetMTwoUF () const
{
	return m_fMTwoUF;
}
//----------------------------------------------------------------------------

fixed Frustum3x::GetMTwoRF () const
{
	return m_fMTwoRF;
}
//----------------------------------------------------------------------------

void Frustum3x::ComputeVertices (Vector3x akVertex[8]) const
{
	Vector3x kDScaled = DMin*DVector;
	Vector3x kUScaled = UBound*UVector;
	Vector3x kRScaled = RBound*RVector;
	
	akVertex[0] = kDScaled - kUScaled - kRScaled;
	akVertex[1] = kDScaled - kUScaled + kRScaled;
	akVertex[2] = kDScaled + kUScaled + kRScaled;
	akVertex[3] = kDScaled + kUScaled - kRScaled;
	
	for (int i = 0, ip = 4; i < 4; i++, ip++)
	{
		akVertex[ip] = Origin + m_fDRatio*akVertex[i];
		akVertex[i] += Origin;
	}
}
//----------------------------------------------------------------------------

}