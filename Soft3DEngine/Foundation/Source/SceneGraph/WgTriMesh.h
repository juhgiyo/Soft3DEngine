///////////////////////////////////////////////////////////
//                                                       //
//                    WgTriMesh.h                        //
//                                                       //
//  - Interface for Tri Mesh class                       //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_TRIMESH_H__
#define __WG_TRIMESH_H__

#include "WgFoundationLIB.h"
#include "WgGeometry.h"
#include "WgShortArray.h"
#include "WgTriangle3.h"
#include "WgTriangles.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM TriMesh : public Triangles
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;


public:
    TriMesh (Vector3xArray* pkVertices, ShortArray* pkIndices,
        bool bGenerateNormals, bool bCachedNormals = false);
    virtual ~TriMesh ();

    // Interpretation of the index buffer data.
    virtual int GetTriangleQuantity () const;
    virtual bool GetTriangle (int i, short& riV0, short& riV1, short& riV2) const;

protected:
    TriMesh ();
};

typedef Pointer<TriMesh> TriMeshPtr;
#include "WgTriMesh.inl"

}

#endif

