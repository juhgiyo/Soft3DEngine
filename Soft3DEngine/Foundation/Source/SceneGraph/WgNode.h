///////////////////////////////////////////////////////////
//                                                       //
//                    WgNode.h                           //
//                                                       //
//  - Interface for Node class                           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#ifndef __WG_NODE_H__
#define __WG_NODE_H__

#include "WgFoundationLIB.h"
#include "WgSpatial.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM Node : public Spatial
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;
    

public:
    // construction and destruction
    Node (int iQuantity = 1, int iGrowBy = 1);
    virtual ~Node ();

    // children
    int GetQuantity () const;
    int GetUsed () const;
    int AttachChild (Spatial* pkChild);
    int DetachChild (Spatial* pkChild);
    SpatialPtr DetachChildAt (int i);
    SpatialPtr SetChild (int i, Spatial* pkChild);
    SpatialPtr GetChild (int i);

    // Picking support.  The origin and direction of the ray must be in world
    // coordinates.  The application is responsible for deleting the pick
    // records in the array.
    virtual void DoPick (const Ray3x& rkRay, PickArray& rkResults);

protected:
    // geometric updates
    virtual void UpdateWorldData (double dAppTime);
    virtual void UpdateWorldBound ();

    // render state updates
    virtual void UpdateState (TStack<GlobalState*>* akGStack,
        TStack<Light*>* pkLStack);

    // children
    TArray<SpatialPtr> m_kChild;
    int m_iUsed;

// internal use
public:
    // Drawing.  The Renderer needs to call this when the Node has a global
    // effect attached to it.
    virtual void Draw (Renderer& rkRenderer, bool bNoCull = false);
};

typedef Pointer<Node> NodePtr;
#include "WgNode.inl"

}

#endif

