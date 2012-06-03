///////////////////////////////////////////////////////////
//                                                       //
//                    WgPolarCamera.cpp                  //
//                                                       //
//  - Implementation for Polar Camera class              //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgPolarCamera.h"
#include "WgRenderer.h"
#include "WgMath.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,PolarCamera,Camera);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(PolarCamera,Camera);


PolarCamera::PolarCamera() : Camera()
{
	
	Vector3x kCLoc, kCDir, kCUp, kCRight;						
	kCLoc=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);		
	kCDir=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
	kCUp=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
	kCRight=kCDir.Cross(kCUp);
	
	SetFrame(kCLoc ,kCDir ,kCUp ,kCRight);
}

PolarCamera::~PolarCamera()
{

}


//////////////////////////////////
//
// Polar Camera Routines
//
/////////////////////////////////
void PolarCamera::polarToCartesianDeg(fixed azimuthDegAngle ,fixed altitudeDegAngle ,fixed dist ,Vector3x &pKVecOut)
{	
	float x,y,z;
	float altitudeDegAnglef=FloatFromFixed(altitudeDegAngle);
	float azimuthDegAnglef=FloatFromFixed(azimuthDegAngle);
	float theta=(90.0f - azimuthDegAnglef)*Mathf::DEG_TO_RAD;
	float tantheta =(float)tan(theta);//Mathf::Tan(theta);
	float radian_alt=altitudeDegAnglef*Mathf::DEG_TO_RAD;
	float cospsi =Mathf::Cos(radian_alt);
	float distf=FloatFromFixed(dist);
	x= Mathf::Sqrt((distf*distf)/(tantheta * tantheta + 1.0f));
	z= tantheta * x;

	x=-x;
	if(((altitudeDegAnglef>=180.0f) && (altitudeDegAnglef <=360.0f)) || (altitudeDegAnglef==0.0f))
	{
		x=-x;
		z=-z;
	}
	y=Mathf::Sqrt((x * x + z * z))*Mathf::Sin(radian_alt);
	
	if(distf<0.0f)
	{
		x = -x;
		y = -y;
		z = -z;
	}
	
	x= x*cospsi;
	z= z*cospsi;
	
	pKVecOut.X()=FixedFromFloat(x);
	pKVecOut.Y()=FixedFromFloat(z);
	pKVecOut.Z()=FixedFromFloat(y);
	
}
void PolarCamera::polarToCartesianRad(fixed azimuthDegAngle ,fixed altitudeDegAngle ,fixed dist ,Vector3x &pKVecOut)
{
	float x,y,z;
	float azimuthDegAnglef= FloatFromFixed(azimuthDegAngle);
	float theta=Mathf::HALF_PI - FloatFromFixed(azimuthDegAngle);
	float tantheta =(float)tan(theta);//Mathf::Tan(theta);
	float radian_alt=FloatFromFixed(altitudeDegAngle);
	float cospsi =Mathf::Cos(radian_alt);
	float distf=FloatFromFixed(dist);
	x= Mathf::Sqrt(((distf*distf)/(tantheta * tantheta + 1.0f)));
	z= tantheta * x;
	
	x=-x;
	if(((azimuthDegAnglef>=Mathf::PI) && (azimuthDegAnglef <=(2.0f*Mathf::PI))) || (azimuthDegAnglef==0.0f))
	{
		x=-x;
		z=-z;
	}
	y=Mathf::Sqrt((z * z + x * x))*Mathf::Sin(radian_alt);
	
	if(distf<0.0f)
	{
		x = -x;
		y = -y;
		z = -z;
	}
	
	x= x*cospsi;
	z= z*cospsi;
	
	pKVecOut.X()=FixedFromFloat(x);
	pKVecOut.Y()=FixedFromFloat(z);
	pKVecOut.Z()=FixedFromFloat(y);
	
}

void PolarCamera::LookAt(Vector3x pkLocation,Vector3x pkAtVector)
{
	
	Vector3x kCLoc, kCDir, kCUp, kCRight;						
	kCLoc=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);		
	kCDir=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
	kCUp=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
	kCRight=kCDir.Cross(kCUp);	
	SetFrame(kCLoc ,kCDir ,kCUp ,kCRight);
	
	
	Vector3x kOrigLoc,kOrigAt;
	kOrigLoc=pkLocation;
	kOrigAt=pkAtVector;
	
	pkLocation=kOrigLoc;
	pkAtVector=kOrigAt;

	Vector3x kCMag;
	kCMag=pkLocation-pkAtVector;
	
	fixed dist=kCMag.Length();
	if(kCMag.X()==FIXED_ZERO && kCMag.Z()==FIXED_ZERO)
	{
		// error
		return;
	}
	
	fixed altitudeAngle=FIXED_ZERO;
	fixed azimuthAngle=FIXED_ZERO;
	
	Vector3x kCMagFlat;
	kCMagFlat.X()=kCMag.X();
	kCMagFlat.Y()=FIXED_ZERO;
	kCMagFlat.Z()=kCMag.Z();
	kCMagFlat.Normalize();
	
	azimuthAngle=Mathx::ACos(kCMagFlat.Z());
	if(kCMagFlat.X()>FIXED_ZERO)
		azimuthAngle*=FIXED_NEG_ONE;
	if(azimuthAngle<FIXED_ZERO)
		azimuthAngle+=Mathx::TWO_PI;

	kCMag.Normalize();
	
	altitudeAngle=Mathx::ACos(FIXED_NEG_ONE*kCMag.Y());
	if(altitudeAngle<FIXED_ZERO)
		altitudeAngle+=Mathx::TWO_PI;

			
	polarToCartesianRad(azimuthAngle ,altitudeAngle ,dist ,kCUp);
	kOrigAt=kOrigAt-kOrigLoc;
	
	m_locVec=kOrigLoc;
	m_atVec=kOrigAt;
	m_upVec=kCUp;
	
    if (m_pkRenderer)
    {
		m_atVec.Normalize();
		m_upVec.Normalize();
		kCRight=m_atVec.Cross(m_upVec);
		SetFrame(m_locVec,m_atVec,m_upVec,kCRight);
    }
}

void PolarCamera::LookAtDeg(Vector3x pkAtVector  ,fixed fAziDegAngle ,fixed fAltDegAngle ,fixed fDist)
{
	Vector3x kCLoc, kCDir, kCUp, kCRight;						
	kCLoc=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);		
	kCDir=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
	kCUp=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
	kCRight=kCDir.Cross(kCUp);		
	SetFrame(kCLoc ,kCDir ,kCUp ,kCRight);
	
	while(fAziDegAngle<FIXED_ZERO)
	{
		fAziDegAngle+=FixedFromFloat(360.0f);
	}
	while(fAziDegAngle>=FixedFromFloat(360.0f))
	{
		fAziDegAngle-=FixedFromFloat(360.0f);
	}
	
	while(fAltDegAngle<FIXED_ZERO)
	{
		fAltDegAngle+=FixedFromFloat(360.0f);
	}
	while(fAltDegAngle>=FixedFromFloat(360.0f))
	{
		fAltDegAngle-=FixedFromFloat(360.0f);
	}
	
	polarToCartesianDeg(fAziDegAngle ,fAltDegAngle ,fDist ,kCLoc);
	polarToCartesianDeg(fAziDegAngle ,fAltDegAngle+FixedFromFloat(90.0f) ,fDist ,kCUp);
	//kCLoc+= pkAtVector;
	pkAtVector-=kCLoc;
	
	m_locVec=kCLoc;
	m_atVec=pkAtVector;
	m_upVec=kCUp;
	
	if (m_pkRenderer)
    {
		m_atVec.Normalize();
		m_upVec.Normalize();
		kCRight=pkAtVector.Cross(kCUp);
		kCRight.Normalize();
		SetFrame(m_locVec ,m_atVec ,m_upVec ,kCRight);
    }
}

void PolarCamera::LookAtRad(Vector3x pkAtVector  ,fixed fAziRadAngle ,fixed fAltRadAngle ,fixed fDist)
{
	
	Vector3x kCLoc, kCDir, kCUp, kCRight;						
	kCLoc=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);		
	kCDir=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
	kCUp=Vector3x(FIXED_ZERO, FIXED_ZERO, FIXED_ZERO);
	kCRight=kCDir.Cross(kCUp);	
	SetFrame(kCLoc ,kCDir ,kCUp ,kCRight);
	
	while(fAziRadAngle<FIXED_ZERO)
	{
		fAziRadAngle+=Mathx::TWO_PI;
	}
	while(fAziRadAngle>=Mathx::TWO_PI)
	{
		fAziRadAngle-=Mathx::TWO_PI;
	}
	
	while(fAltRadAngle<FIXED_ZERO)
	{
		fAltRadAngle+=Mathx::TWO_PI;
	}
	while(fAltRadAngle>=Mathx::TWO_PI)
	{
		fAltRadAngle-=Mathx::TWO_PI;
	}
	
	polarToCartesianRad(fAziRadAngle ,fAltRadAngle ,fDist ,kCLoc);
	polarToCartesianRad(fAziRadAngle ,fAltRadAngle+Mathx::HALF_PI ,fDist ,kCUp);

	//kCLoc+= pkAtVector;
	pkAtVector-=kCLoc;
	
	m_locVec=kCLoc;
	m_atVec=pkAtVector;
	m_upVec=kCUp;
	
	if (m_pkRenderer)
    {
		m_atVec.Normalize();
		m_upVec.Normalize();
		kCRight=pkAtVector.Cross(kCUp);
		kCRight.Normalize();
		SetFrame(m_locVec ,m_atVec ,m_upVec ,kCRight);
    }
}

