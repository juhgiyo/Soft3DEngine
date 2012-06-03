///////////////////////////////////////////////////////////
//                                                       //
//                    WgSpatial.h                        //
//                                                       //
//  - Interface for Spatial class                        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_SPATIAL_H__
#define __WG_SPATIAL_H__

#include "WgFoundationLIB.h"
#include "WgObject.h"
#include "WgBoundingVolume.h"
#include "WgEffect.h"
#include "WgRenderer.h"
#include "WgGlobalState.h"
#include "WgTransformation.h"

namespace WGSoft3D
{

class Light;

class WG3D_FOUNDATION_ITEM Spatial : public Object
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;
  
public:
    // abstract base class
    virtual ~Spatial ();

    // Local and world transforms.  In some situations you might need to set
    // the world transform directly and bypass the Spatial::Update()
    // mechanism.  If World is set directly, the WorldIsCurrent flag should
    // be set to true.  For example, inverse kinematic controllers and skin
    // controllers need this capability.
    Transformation Local;
    Transformation World;
    bool WorldIsCurrent;

    // World bound access and culling.  In some situations you might want to
    // set the world bound directly and bypass the Spatial::Update()
    // mechanism.  If WorldBound is set directly, the WorldBoundIsCurrent
    // flag should be set to true.
    BoundingVolumePtr WorldBound;
    bool WorldBoundIsCurrent;
    bool ForceCull;

    // Update of geometric state and controllers.  The UpdateGS function
    // computes world transformations on the downward pass and world bounding
    // volumes on the upward pass.  The UpdateBS function just computes the
    // world bounding volumes on an upward pass.  This is useful if model
    // data changes, causing the model and world bounds to change, but no
    // transformations need recomputing.
    void UpdateGS (double dAppTime = -Mathd::MAX_REAL, bool bInitiator = true);
    void UpdateBS ();

    // global state
    void SetGlobalState (GlobalState* pkState);
    GlobalState* GetGlobalState (int eType) const;
    void RemoveGlobalState (int eType);
    void RemoveAllGlobalStates ();

    // light state
    void SetLight (Light* pkLight);
    int GetLightQuantity () const;
    Light* GetLight (int i) const;
    void RemoveLight (Light* pkLight);
    void RemoveAllLights ();

    // effect state
    virtual void SetEffect (Effect* pkEffect);
    Effect* GetEffect () const;

    // update of render state
    virtual void UpdateRS (TStack<GlobalState*>* akGStack = 0,
        TStack<Light*>* pkLStack = 0);

    // parent access
    Spatial* GetParent ();

    // The picking system.  Each Spatial-derived class derives its own pick
    // record class from PickRecord and adds whatever information it wants to
    // return from the DoPick call.  The ray parameter can be used to sort
    // the intersection points after a call to DoPick.
    //
    // RTTI for the PickRecord is obtained by using the RTTI for the member
    // IObject.  Once that member's type is known, the PickRecord can be cast
    // to the appropriate PickRecord-derived class.
    class WG3D_FOUNDATION_ITEM PickRecord
    {
    public:
        virtual ~PickRecord ();

        // The intersected object.
        Pointer<Spatial> IObject;

        // The world ray parameter for the point of intersection, a
        // nonnegative number.  That is, if the world ray is P+t*D, the ray
        // parameter is t >= 0.
        fixed T;

    protected:
        PickRecord (Spatial* pkIObject, fixed fT);
    };

    typedef TArray<PickRecord*> PickArray;

    // The origin and direction of the ray must be in world coordinates.  The
    // application is responsible for deleting the pick records in the array.
    virtual void DoPick (const Ray3x& rkRay, PickArray& rkResults);

    static PickRecord* GetClosest (PickArray& rkResults);

protected:
    Spatial ();

    // geometric updates
    virtual void UpdateWorldData (double dAppTime);
    virtual void UpdateWorldBound () = 0;
    void PropagateBoundToRoot ();

    // render state updates
    void PropagateStateFromRoot (TStack<GlobalState*>* akGStack,
        TStack<Light*>* pkLStack);
    void PushState (TStack<GlobalState*>* akGStack, TStack<Light*>* pkLStack);
    void PopState (TStack<GlobalState*>* akGStack, TStack<Light*>* pkLStack);
    virtual void UpdateState (TStack<GlobalState*>* akGStack,
        TStack<Light*>* pkLStack) = 0;

    // support for hierarchical scene graph
    Spatial* m_pkParent;

    // global render state
    TList<GlobalStatePtr>* m_pkGlobalList;

    // light state (Pointer used directly to avoid circular headers)
    TList<Pointer<Light> >* m_pkLightList;

    // Effect state.  If the effect is attached to a Geometry object, it
    // applies to that object alone.  If the effect is attached to a Node
    // object, it applies to all Geometry objects in the subtree rooted at
    // the Node.  However, only one such "global" effect can be active at a
    // time.  The active one is the last one encountered in a depth-first
    // traversal of the scene.
    EffectPtr m_spkEffect;

// internal use
public:
    // parent access (Node calls this during attach/detach of children)
    void SetParent (Spatial* pkParent);

    // renderer needs access to these
    void OnDraw (Renderer& rkRenderer, bool bNoCull = false);
    virtual void Draw (Renderer& rkRenderer, bool bNoCull = false) = 0;
};

typedef Pointer<Spatial> SpatialPtr;
#include "WgSpatial.inl"

}

#endif

