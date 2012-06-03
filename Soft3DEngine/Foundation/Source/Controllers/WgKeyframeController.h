///////////////////////////////////////////////////////////
//                                                       //
//                    WgKeyframeController.h             //
//                                                       //
//  - Interface for Keyframe Controller class            //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_KEYFRAMECONTROLLER_H__
#define __WG_KEYFRAMECONTROLLER_H__

#include "WgFoundationLIB.h"
#include "WgController.h"
#include "WgFloatArray.h"
#include "WgFixedArray.h"
#include "WgQuaternionArray.h"
#include "WgVector3Array.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM KeyframeController : public Controller
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    KeyframeController ();
    virtual ~KeyframeController ();

    FloatArrayPtr TranslationTimes;
    Vector3xArrayPtr TranslationData;

    FloatArrayPtr RotationTimes;
    QuaternionxArrayPtr RotationData;

    FloatArrayPtr ScaleTimes;
    FixedArrayPtr ScaleData;

    // animation update
    virtual bool Update (double dAppTime);

protected:
    static void GetKeyInfo (float fCtrlTime, int iQuantity, float* afTime,
        int& riLastIndex, float& rfNormTime, int& ri0, int& ri1);

    Vector3x GetTranslate (float fNormTime, int i0, int i1);
    Matrix3x GetRotate (float fNormTime, int i0, int i1);
    fixed GetScale (float fNormTime, int i0, int i1);

    // Cached indices for the last found pair of keys used for interpolation.
    // For a sequence of times, this guarantees an O(1) lookup.
    int m_iTLastIndex;
    int m_iRLastIndex;
    int m_iSLastIndex;
};

typedef Pointer<KeyframeController> KeyframeControllerPtr;

}

#endif

