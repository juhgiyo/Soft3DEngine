///////////////////////////////////////////////////////////
//                                                       //
//                    WgPolygonOffsetState.h             //
//                                                       //
//  - Interface for Polygon Offset State class           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#ifndef __WG_POLYGONOFFSETSTATE_H__
#define __WG_POLYGONOFFSETSTATE_H__

#include "WgFoundationLIB.h"
#include "WgGlobalState.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM PolygonOffsetState : public GlobalState
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;
    
public:
    virtual GlobalStateType GetGlobalStateType () const { return POLYGONOFFSET; }

    PolygonOffsetState ();
    virtual ~PolygonOffsetState ();

    // Set whether offset should be enabled for the various polygon drawing
    // modes (fill, line, point).
    bool FillEnabled;   // default: false
    bool LineEnabled;   // default: false
    bool PointEnabled;  // default: false

    // The offset is Scale()*dZ + Bias()*r where dZ is the change in depth
    // relative to the screen space area of the poly, and r is the smallest
    // resolvable depth difference.  Negative values move polygons closer to
    // the eye.
    fixed Scale;  // default: 0
    fixed Bias;   // default: 0
};

typedef Pointer<PolygonOffsetState> PolygonOffsetStatePtr;

}

#endif
