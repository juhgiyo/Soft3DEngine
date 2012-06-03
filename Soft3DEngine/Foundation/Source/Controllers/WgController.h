///////////////////////////////////////////////////////////
//                                                       //
//                    WgController.h                     //
//                                                       //
//  - Interface for Controller class                     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_CONTROLLER_H__
#define __WG_CONTROLLER_H__

#include "WgFoundationLIB.h"
#include "WgObject.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM Controller : public Object
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    // destruction (abstract base class)
    virtual ~Controller ();

    // the controlled object
    Object* GetObject () const;

    // animation update
    virtual bool Update (double dAppTime);

    // time management

    enum // RepeatType
    {
        RT_CLAMP,
        RT_WRAP,
        RT_CYCLE,
        RT_QUANTITY
    };

    int RepeatType;    // default = RT_CLAMP
    double MinTime;    // default = 0.0
    double MaxTime;    // default = 0.0
    double Phase;      // default = 0.0
    double Frequency;  // default = 1.0
    bool Active;       // default = true

protected:
    // construction (abstract base class)
    Controller ();

    // the controlled object
    friend class Object;
    virtual void SetObject (Object* pkObject);

    // Conversion from application time units to controller time units.
    // Derived classes may use this in their update routines.
    double GetControlTime (double dAppTime);

    // Regular pointer used for controlled object to avoid circular smart
    // pointers between controller and object.
    Object* m_pkObject;

    double m_dLastAppTime;
};

typedef Pointer<Controller> ControllerPtr;
#include "WgController.inl"

}

#endif

