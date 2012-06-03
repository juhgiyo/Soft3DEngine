///////////////////////////////////////////////////////////
//                                                       //
//                    WgScreenPolygon.h                  //
//                                                       //
//  - Interface for Screen Polygon class                 //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_SCREENPOLYGON_H__
#define __WG_SCREENPOLYGON_H__

#include "WgFoundationLIB.h"
#include "WgTriMesh.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM ScreenPolygon : public TriMesh
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    // Construction and destruction.  The polygon must be convex and vertices
    // stored in counterclockwise order.  ScreenPolygon assumes responsibility
    // for deleting the input array.  Consequently, the array cannot be a
    // shared object.
    ScreenPolygon (int iVQuantity, Vector2x* akVertex, bool bForeground);
    virtual ~ScreenPolygon ();

    void SetVertex (int i, const Vector2x& rkV);
    const Vector2x& GetVertex (int i) const;
    bool IsForeground () const;

protected:
    ScreenPolygon ();

    Vector2x* m_akVertex;
    bool m_bForeground;
};

typedef Pointer<ScreenPolygon> ScreenPolygonPtr;
#include "WgScreenPolygon.inl"

}

#endif

