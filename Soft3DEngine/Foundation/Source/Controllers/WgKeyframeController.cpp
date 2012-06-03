///////////////////////////////////////////////////////////
//                                                       //
//                    WgKeyframeController.cpp           //
//                                                       //
//  - Implementation for Keyframe Controller class       //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgKeyframeController.h"
#include "WgSpatial.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,KeyframeController,Controller);

//----------------------------------------------------------------------------
KeyframeController::KeyframeController ()
{
    m_iTLastIndex = 0;
    m_iRLastIndex = 0;
    m_iSLastIndex = 0;
}
//----------------------------------------------------------------------------
KeyframeController::~KeyframeController ()
{
}
//----------------------------------------------------------------------------
void KeyframeController::GetKeyInfo (float fCtrlTime, int iQuantity,
    float* afTime, int& riLastIndex, float& rfTime, int& ri0, int& ri1)
{
    if (fCtrlTime <= afTime[0])
    {
        rfTime = 0.0f;
        riLastIndex = 0;
        ri0 = 0;
        ri1 = 0;
        return;
    }

    if (fCtrlTime >= afTime[iQuantity-1])
    {
        rfTime = 0.0f;
        riLastIndex = iQuantity - 1;
        ri0 = riLastIndex;
        ri1 = riLastIndex;
        return;
    }

    int iNextIndex;
    if (fCtrlTime > afTime[riLastIndex])
    {
        iNextIndex = riLastIndex + 1;
        while (fCtrlTime >= afTime[iNextIndex])
        {
            riLastIndex = iNextIndex;
            iNextIndex++;
        }

        ri0 = riLastIndex;
        ri1 = iNextIndex;
        rfTime = (fCtrlTime - afTime[ri0])/(afTime[ri1] - afTime[ri0]);
    }
    else if (fCtrlTime < afTime[riLastIndex])
    {
        iNextIndex = riLastIndex - 1;
        while (fCtrlTime <= afTime[iNextIndex])
        {
            riLastIndex = iNextIndex;
            iNextIndex--;
        }

        ri0 = iNextIndex;
        ri1 = riLastIndex;
        rfTime = (fCtrlTime - afTime[ri0])/(afTime[ri1] - afTime[ri0]);
    }
    else
    {
        rfTime = 0.0f;
        ri0 = riLastIndex;
        ri1 = riLastIndex;
    }
}
//----------------------------------------------------------------------------
Vector3x KeyframeController::GetTranslate (float fNormTime, int i0, int i1)
{
    Vector3x* akTData = TranslationData->GetData();
    return akTData[i0] + fNormTime*(akTData[i1] - akTData[i0]);
}
//----------------------------------------------------------------------------
Matrix3x KeyframeController::GetRotate (float fNormTime, int i0, int i1)
{
    Quaternionx* akRData = RotationData->GetData();
    Quaternionx kQ;
    kQ.Slerp(fNormTime,akRData[i0],akRData[i1]);

    Matrix3x kRot;
    kQ.ToRotationMatrix(kRot);
    return kRot;
}
//----------------------------------------------------------------------------
fixed KeyframeController::GetScale (float fNormTime, int i0, int i1)
{
    fixed* afSData = ScaleData->GetData();
    return afSData[i0] + fNormTime*(afSData[i1] - afSData[i0]);
}
//----------------------------------------------------------------------------
bool KeyframeController::Update (double dAppTime)
{
    if (!Controller::Update(dAppTime))
    {
        return false;
    }

    Spatial* pkSpatial = StaticCast<Spatial>(m_pkObject);
    float fCtrlTime = (float)GetControlTime(dAppTime);
    float fNormTime;
    int i0, i1;

    // The logic here checks for equal time arrays to minimize the number of
    // times GetKeyInfo is called.
    if (TranslationTimes == RotationTimes)
    {
        if (TranslationTimes)
        {
            GetKeyInfo(fCtrlTime,TranslationTimes->GetQuantity(),
                TranslationTimes->GetData(),m_iTLastIndex,fNormTime,
                i0,i1);
        }

        if (TranslationData)
        {
            pkSpatial->Local.SetTranslate(GetTranslate(fNormTime,i0,i1));
        }

        if (RotationData)
        {
            pkSpatial->Local.SetRotate(GetRotate(fNormTime,i0,i1));
        }

        if (TranslationTimes == ScaleTimes)
        {
            // T == R == S
            if (ScaleData)
            {
                pkSpatial->Local.SetUniformScale(GetScale(fNormTime,i0,i1));
            }
        }
        else
        {
            // T == R != S
            if (ScaleTimes && ScaleData)
            {
                GetKeyInfo(fCtrlTime,ScaleTimes->GetQuantity(),
                    ScaleTimes->GetData(),m_iSLastIndex,fNormTime,i0,i1);
                pkSpatial->Local.SetUniformScale(GetScale(fNormTime,i0,i1));
            }
        }
    }
    else if (TranslationTimes == ScaleTimes)
    {
        // R != T == S
        if (TranslationTimes)
        {
            GetKeyInfo(fCtrlTime,TranslationTimes->GetQuantity(),
                TranslationTimes->GetData(),m_iTLastIndex,fNormTime,
                i0,i1);
        }

        if (TranslationData)
        {
            pkSpatial->Local.SetTranslate(GetTranslate(fNormTime,i0,i1));
        }

        if (ScaleData)
        {
            pkSpatial->Local.SetUniformScale(GetScale(fNormTime,i0,i1));
        }

        if (RotationTimes && RotationData)
        {
            GetKeyInfo(fCtrlTime,RotationTimes->GetQuantity(),
                RotationTimes->GetData(),m_iRLastIndex,fNormTime,i0,i1);
            pkSpatial->Local.SetRotate(GetRotate(fNormTime,i0,i1));
        }
    }
    else if (RotationTimes == ScaleTimes)
    {
        // S == R != T
        if (RotationTimes)
        {
            GetKeyInfo(fCtrlTime,RotationTimes->GetQuantity(),
                RotationTimes->GetData(),m_iRLastIndex,fNormTime,i0,i1);
        }

        if (RotationData)
        {
            pkSpatial->Local.SetRotate(GetRotate(fNormTime,i0,i1));
        }

        if (ScaleData)
        {
            pkSpatial->Local.SetUniformScale(GetScale(fNormTime,i0,i1));
        }

        if (TranslationTimes && TranslationData)
        {
            GetKeyInfo(fCtrlTime,TranslationTimes->GetQuantity(),
                TranslationTimes->GetData(),m_iTLastIndex,fNormTime,i0,i1);
            pkSpatial->Local.SetTranslate(GetTranslate(fNormTime,i0,i1));
        }
    }
    else
    {
        // S != R, T != R (and R != T, something caught earlier in the logic)
        if (TranslationTimes && TranslationData)
        {
            GetKeyInfo(fCtrlTime,TranslationTimes->GetQuantity(),
                TranslationTimes->GetData(),m_iTLastIndex,fNormTime,i0,i1);
            pkSpatial->Local.SetTranslate(GetTranslate(fNormTime,i0,i1));
        }

        if (RotationTimes && RotationData)
        {
            GetKeyInfo(fCtrlTime,RotationTimes->GetQuantity(),
                RotationTimes->GetData(),m_iRLastIndex,fNormTime,i0,i1);
            pkSpatial->Local.SetRotate(GetRotate(fNormTime,i0,i1));
        }

        if (ScaleTimes && ScaleData)
        {
            GetKeyInfo(fCtrlTime,ScaleTimes->GetQuantity(),
                ScaleTimes->GetData(),m_iSLastIndex,fNormTime,i0,i1);
            pkSpatial->Local.SetUniformScale(GetScale(fNormTime,i0,i1));
        }
    }

    return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* KeyframeController::GetObjectByName (const String& rkName)
{
    Object* pkFound = Controller::GetObjectByName(rkName);
    if (pkFound)
    {
        return pkFound;
    }

    if (TranslationTimes)
    {
        pkFound = TranslationTimes->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (TranslationData)
    {
        pkFound = TranslationData->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (RotationTimes)
    {
        pkFound = RotationTimes->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (RotationData)
    {
        pkFound = RotationData->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (ScaleTimes)
    {
        pkFound = ScaleTimes->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (ScaleData)
    {
        pkFound = ScaleData->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void KeyframeController::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    Controller::GetAllObjectsByName(rkName,rkObjects);

    if (TranslationTimes)
    {
        TranslationTimes->GetAllObjectsByName(rkName,rkObjects);
    }

    if (TranslationData)
    {
        TranslationData->GetAllObjectsByName(rkName,rkObjects);
    }

    if (RotationTimes)
    {
        RotationTimes->GetAllObjectsByName(rkName,rkObjects);
    }

    if (RotationData)
    {
        RotationData->GetAllObjectsByName(rkName,rkObjects);
    }

    if (ScaleTimes)
    {
        ScaleTimes->GetAllObjectsByName(rkName,rkObjects);
    }

    if (ScaleData)
    {
        ScaleData->GetAllObjectsByName(rkName,rkObjects);
    }
}
//----------------------------------------------------------------------------
Object* KeyframeController::GetObjectByID (unsigned int uiID)
{
    Object* pkFound = Controller::GetObjectByID(uiID);
    if (pkFound)
    {
        return pkFound;
    }

    if (TranslationTimes)
    {
        pkFound = TranslationTimes->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (TranslationData)
    {
        pkFound = TranslationData->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (RotationTimes)
    {
        pkFound = RotationTimes->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (RotationData)
    {
        pkFound = RotationData->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (ScaleTimes)
    {
        pkFound = ScaleTimes->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (ScaleData)
    {
        pkFound = ScaleData->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------

