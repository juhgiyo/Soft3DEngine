///////////////////////////////////////////////////////////
//                                                       //
//                    WgGeometry.h                       //
//                                                       //
//  - Interface for Geometry class                       //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_GEOMETRY_H__
#define __WG_GEOMETRY_H__

#include "WgFoundationLIB.h"
#include "WgSpatial.h"
#include "WgLight.h"
#include "WgEffect.h"
#include "WgShortArray.h"
#include "WgVector3Array.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM Geometry : public Spatial
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    // abstract base class
    virtual ~Geometry ();

    // member access
    Vector3xArrayPtr Vertices;
    Vector3xArrayPtr Normals;
    BoundingVolumePtr ModelBound;
    ShortArrayPtr Indices;

    // geometric updates
    virtual void UpdateMS (bool bUpdateNormals = true);

    // Picking support. This nested class exists only to maintain the
    // class-derivation chain that is parallel to the one whose base is
    // Spatial.
    class WG3D_FOUNDATION_ITEM PickRecord : public Spatial::PickRecord
    {
    protected:
        PickRecord (Geometry* pkIObject, fixed fT);
    };

protected:
    Geometry ();
    Geometry (Vector3xArrayPtr spkVertices);

    // geometric updates
    virtual void UpdateModelBound ();
    virtual void UpdateModelNormals ();
    virtual void UpdateWorldBound ();

    // render state updates
    virtual void UpdateState (TStack<GlobalState*>* akGStack,
        TStack<Light*>* pkLStack);

    // drawing
    virtual void Draw (Renderer& rkRenderer, bool bNoCull = false);

// internal use
public:
    // Render state and lights in path to this object.  An attached effect
    // provides additional render state, lights, and any other information
    // needed to draw the object.
	typedef enum  _geoType// GeometryType
	{
		GT_POLYPOINT,
			GT_POLYLINE_SEGMENTS,
			GT_POLYLINE_OPEN,
			GT_POLYLINE_CLOSED,
			GT_TRIMESH,
			GT_TRISTRIP,
			GT_TRIFAN,
			GT_MAX_QUANTITY
	}GeometryType;


    GeometryType m_GeometryType;
    GlobalStatePtr States[GlobalState::MAX_STATE];
    TArray<LightPtr> Lights;
};

typedef Pointer<Geometry> GeometryPtr;
#include "WgGeometry.inl"

}

#endif

