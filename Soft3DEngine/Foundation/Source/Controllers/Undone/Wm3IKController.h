// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved
//
// The Wild Magic Library (WM3) source code is supplied under the terms of
// the license agreement
//     http://www.geometrictools.com/License/WildMagic3License.pdf
// and may not be copied or disclosed except in accordance with the terms
// of that agreement.

#ifndef WM3IKCONTROLLER_H
#define WM3IKCONTROLLER_H

#include "Wm3FoundationLIB.h"
#include "Wm3Controller.h"
#include "Wm3IKGoal.h"
#include "Wm3IKJoint.h"

namespace Wm3
{

class WM3_ITEM IKController : public Controller
{
    WM3_DECLARE_RTTI;
    WM3_DECLARE_NAME_ID;
    WM3_DECLARE_STREAM;

public:
    // Construction and destruction.  IKController assumes responsibility for
    // the input arrays and will delete them.  They should be dynamically
    // allocated.
    IKController (int iJointQuantity, IKJointPtr* aspkJoint,
        int iGoalQuantity, IKGoalPtr* aspkGoal);
    virtual ~IKController ();

    int Iterations;       // default = 128
    bool OrderEndToRoot;  // default = true

    virtual bool Update (double dAppTime);

protected:
    IKController ();

    int m_iJointQuantity;
    IKJointPtr* m_aspkJoint;

    int m_iGoalQuantity;
    IKGoalPtr* m_aspkGoal;
};

WM3_REGISTER_STREAM(IKController);
typedef Pointer<IKController> IKControllerPtr;

}

#endif

