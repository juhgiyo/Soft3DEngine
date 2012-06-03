///////////////////////////////////////////////////////////
//                                                       //
//                    WgPolarCamera.h                    //
//                                                       //
//  - Interface for Polar Camera class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_POLARCAMERA_H__
#define __WG_POLARCAMERA_H__

#include "WgCamera.h"

namespace WGSoft3D
{
	class WG3D_FOUNDATION_ITEM PolarCamera :public Camera
	{
		WG3D_DECLARE_RTTI;
		WG3D_DECLARE_NAME_ID;
	public:
		
		PolarCamera();
		virtual ~PolarCamera();

		// ==================================================
		// Camera Frame
		// ==================================================
		void LookAt(Vector3x pkLocation,Vector3x pkAtVector);
		void LookAtDeg(Vector3x pkAtVector  ,fixed fAziDegAngle ,fixed fAltDegAngle ,fixed fDist);
		void LookAtRad(Vector3x pkAtVector  ,fixed fAziRadAngle ,fixed fAltRadAngle ,fixed fDist);
	
	private:

		void polarToCartesianDeg(fixed azimuthDegAngle ,fixed altitudeDegAngle ,fixed dist ,Vector3x &pKVecOut);
		void polarToCartesianRad(fixed azimuthDegAngle ,fixed altitudeDegAngle ,fixed dist ,Vector3x &pKVecOut);
		Vector3x m_locVec;  // location
		Vector3x m_atVec;   // direction
		Vector3x m_upVec;   // up
	
	};
	typedef Pointer<PolarCamera> PolarCameraPtr;


}
#endif