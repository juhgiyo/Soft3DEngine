///////////////////////////////////////////////////////////
//                                                       //
//                    WgController.cpp                   //
//                                                       //
//  - Implementation for Controller class                //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgController.h"
#include "WgMath.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,Controller,Object);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(Controller,Object);

//----------------------------------------------------------------------------
Controller::Controller ()
{
    m_pkObject = 0;
    RepeatType = RT_CLAMP;
    MinTime = 0.0;
    MaxTime = 0.0;
    Phase = 0.0;
    Frequency = 1.0;
    Active = true;
    m_dLastAppTime = -Mathd::MAX_REAL;
}
//----------------------------------------------------------------------------
Controller::~Controller ()
{
}
//----------------------------------------------------------------------------
double Controller::GetControlTime (double dAppTime)
{
    double dCtrlTime = Frequency*dAppTime + Phase;

    if (RepeatType == RT_CLAMP)
    {
        if (dCtrlTime < MinTime)
        {
            return MinTime;
        }
        if (dCtrlTime > MaxTime)
        {
            return MaxTime;
        }
        return dCtrlTime;
    }

    double dRange = MaxTime - MinTime;
    if (dRange > 0.0)
    {
        double dMultiples = (dCtrlTime - MinTime)/dRange;
        double dIntTime = Mathd::Floor(dMultiples);
        double dFrcTime = dMultiples - dIntTime;
        if (RepeatType == RT_WRAP)
        {
            return MinTime + dFrcTime*dRange;
        }

        // Repeat == RT_CYCLE
        if (int(dIntTime) & 1)
        {
            // backward time
            return MaxTime - dFrcTime*dRange;
        }
        else
        {
            // forward time
            return MinTime + dFrcTime*dRange;
        }
    }
    else
    {
        return MinTime;
    }
}
//----------------------------------------------------------------------------
bool Controller::Update (double dAppTime)
{
    if (Active
    &&  (dAppTime == -Mathd::MAX_REAL || dAppTime != m_dLastAppTime) )
    {
        m_dLastAppTime = dAppTime;
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------

