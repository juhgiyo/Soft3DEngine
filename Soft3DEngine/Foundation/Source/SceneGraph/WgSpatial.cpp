///////////////////////////////////////////////////////////
//                                                       //
//                    WgSpatial.cpp                      //
//                                                       //
//  - Implementation for Spatial class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgSpatial.h"
#include "WgCamera.h"
#include "WgLight.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,Spatial,Object);


//----------------------------------------------------------------------------
Spatial::Spatial ()
    :
    WorldBound(BoundingVolume::Create())
{
    ForceCull = false;
    WorldIsCurrent = false;
    WorldBoundIsCurrent = false;
    m_pkParent = 0;
    m_pkGlobalList = 0;
    m_pkLightList = 0;
}
//----------------------------------------------------------------------------
Spatial::~Spatial ()
{
    RemoveAllGlobalStates();
    RemoveAllLights();
}
//----------------------------------------------------------------------------
void Spatial::UpdateGS (double dAppTime, bool bInitiator)
{
    UpdateWorldData(dAppTime);
    UpdateWorldBound();
    if (bInitiator)
    {
        PropagateBoundToRoot();
    }
}
//----------------------------------------------------------------------------
void Spatial::UpdateBS ()
{
    UpdateWorldBound();
    PropagateBoundToRoot();
}
//----------------------------------------------------------------------------
void Spatial::UpdateWorldData (double dAppTime)
{
    // update any controllers associated with this object
    UpdateControllers(dAppTime);

    TList<GlobalStatePtr>* pkGList;
    for (pkGList = m_pkGlobalList; pkGList!=NULL; pkGList = pkGList->Next())
    {
        pkGList->Item()->UpdateControllers(dAppTime);
    }

    TList<LightPtr>* pkLList;
    for (pkLList = m_pkLightList; pkLList!=NULL; pkLList = pkLList->Next())
    {
        pkLList->Item()->UpdateControllers(dAppTime);
    }

    // update world transforms
    if (!WorldIsCurrent)
    {
        if (m_pkParent)
        {
            World.Product(m_pkParent->World,Local);
        }
        else
        {
            World = Local;
        }
    }
}
//----------------------------------------------------------------------------
void Spatial::PropagateBoundToRoot ()
{
    if (m_pkParent)
    {
        m_pkParent->UpdateWorldBound();
        m_pkParent->PropagateBoundToRoot();
    }
}
//----------------------------------------------------------------------------
void Spatial::SetGlobalState (GlobalState* pkState)
{
    assert(pkState);

    // check if type of state already exists
    TList<GlobalStatePtr>* pkList;
    for (pkList = m_pkGlobalList; pkList!=NULL; pkList = pkList->Next())
    {
        if (pkList->Item()->GetGlobalStateType() ==
            pkState->GetGlobalStateType())
        {
            // type of state exists, replace it
            pkList->Item() = pkState;
            return;
        }
    }

    // type of state not in current list, add state
    pkList = WG_NEW TList<GlobalStatePtr>;
    pkList->Item() = pkState;
    pkList->Next() = m_pkGlobalList;
    m_pkGlobalList = pkList;
}
//----------------------------------------------------------------------------
GlobalState* Spatial::GetGlobalState (int eType) const
{
    // check if type of state already exists
    TList<GlobalStatePtr>* pkList;
    for (pkList = m_pkGlobalList; pkList!=NULL; pkList = pkList->Next())
    {
        if (pkList->Item()->GetGlobalStateType() == eType)
        {
            // type of state exists, return it
            return pkList->Item();
        }
    }
    return 0;
}
//----------------------------------------------------------------------------
void Spatial::RemoveGlobalState (int eType)
{
    // check if type of state already exists
    TList<GlobalStatePtr>* pkList = m_pkGlobalList;
    TList<GlobalStatePtr>* pkPrev = 0;
    for (/**/; pkList!=NULL; pkPrev = pkList, pkList = pkList->Next())
    {
        if (pkList->Item()->GetGlobalStateType() == eType)
        {
            // type of state exists, remove it
            if (pkPrev)
            {
                // render state not at front of list
                pkPrev->Next() = pkList->Next();
            }
            else
            {
                // render state at front of list
                assert(pkList == m_pkGlobalList);
                m_pkGlobalList = pkList->Next();
            }
            pkList->Next() = 0;
            WG_DELETE pkList;
            return;
        }
    }
}
//----------------------------------------------------------------------------
void Spatial::RemoveAllGlobalStates ()
{
    while (m_pkGlobalList)
    {
        m_pkGlobalList->Item() = 0;
        TList<GlobalStatePtr>* pkSave = m_pkGlobalList->Next();
        WG_DELETE m_pkGlobalList;
        m_pkGlobalList = pkSave;
    }
}
//----------------------------------------------------------------------------
void Spatial::SetLight (Light* pkLight)
{
    assert(pkLight);

    // check if light is already in the list
    TList<LightPtr>* pkList;
    for (pkList = m_pkLightList; pkList; pkList = pkList->Next())
    {
        if (pkList->Item() == pkLight)
        {
            // light already exists, nothing to do
            return;
        }
    }

    // light not in current list, add it
    pkList = WG_NEW TList<LightPtr>;
    pkList->Item() = pkLight;
    pkList->Next() = m_pkLightList;
    m_pkLightList = pkList;
}
//----------------------------------------------------------------------------
int Spatial::GetLightQuantity () const
{
    int iLightQuantity = 0;

    TList<LightPtr>* pkList;
    for (pkList = m_pkLightList; pkList; pkList = pkList->Next())
    {
        iLightQuantity++;
    }

    return iLightQuantity;
}
//----------------------------------------------------------------------------
Light* Spatial::GetLight (int i) const
{
    assert(i >= 0);

    TList<LightPtr>* pkList = m_pkLightList;
    for (int j = 0; j < i; j++, pkList = pkList->Next())
    {
        if (!pkList)
        {
            // i >= iLightQuantity
            return 0;
        }
    }
    return (pkList ? pkList->Item() : 0);
}
//----------------------------------------------------------------------------
void Spatial::RemoveLight (Light* pkLight)
{
    // check if light is in list
    TList<LightPtr>* pkList = m_pkLightList;
    TList<LightPtr>* pkPrev = 0;
    for (/**/; pkList; pkPrev = pkList, pkList = pkList->Next())
    {
        if (pkList->Item() == pkLight)
        {
            // light exists, remove it
            if (pkPrev)
            {
                // light not at front of list
                pkPrev->Next() = pkList->Next();
            }
            else
            {
                // light at front of list
                assert(pkList == m_pkLightList);
                m_pkLightList = pkList->Next();
            }
            pkList->Next() = 0;
            WG_DELETE pkList;
            return;
        }
    }
}
//----------------------------------------------------------------------------
void Spatial::RemoveAllLights ()
{
    while (m_pkLightList)
    {
        m_pkLightList->Item() = 0;
        TList<LightPtr>* pkSave = m_pkLightList->Next();
        WG_DELETE m_pkLightList;
        m_pkLightList = pkSave;
    }
}
//----------------------------------------------------------------------------
void Spatial::UpdateRS (TStack<GlobalState*>* akGStack,
    TStack<Light*>* pkLStack)
{
    bool bInitiator = (akGStack == 0);

    if (bInitiator)
    {
        // stack initialized to contain the default global states
        akGStack = WG_NEW TStack<GlobalState*>[GlobalState::MAX_STATE];
        for (int i = 0; i < GlobalState::MAX_STATE; i++)
        {
            akGStack[i].Push(GlobalState::Default[i]);
        }

        // stack has no lights initially
        pkLStack = WG_NEW TStack<Light*>;

        // traverse to root and push states from root to this node
        PropagateStateFromRoot(akGStack,pkLStack);
    }
    else
    {
        // push states at this node
        PushState(akGStack,pkLStack);
    }

    // propagate the new state to the subtree rooted here
    UpdateState(akGStack,pkLStack);

    if (bInitiator)
    {
        WG_DELETE[] akGStack;
        WG_DELETE pkLStack;
    }
    else
    {
        // pop states at this node
        PopState(akGStack,pkLStack);
    }
}
//----------------------------------------------------------------------------
void Spatial::PropagateStateFromRoot (TStack<GlobalState*>* akGStack,
    TStack<Light*>* pkLStack)
{
    // traverse to root to allow downward state propagation
    if (m_pkParent)
    {
        m_pkParent->PropagateStateFromRoot(akGStack,pkLStack);
    }

    // push states onto current render state stack
    PushState(akGStack,pkLStack);
}
//----------------------------------------------------------------------------
void Spatial::PushState (TStack<GlobalState*>* akGStack,
    TStack<Light*>* pkLStack)
{
    TList<GlobalStatePtr>* pkGList;
    for (pkGList = m_pkGlobalList; pkGList; pkGList = pkGList->Next())
    {
        int eType = pkGList->Item()->GetGlobalStateType();
        akGStack[eType].Push(pkGList->Item());
    }

    TList<LightPtr>* pkLList;
    for (pkLList = m_pkLightList; pkLList; pkLList = pkLList->Next())
    {
        pkLStack->Push(pkLList->Item());
    }
}
//----------------------------------------------------------------------------
void Spatial::PopState (TStack<GlobalState*>* akGStack,
    TStack<Light*>* pkLStack)
{
    TList<GlobalStatePtr>* pkGList;
    for (pkGList = m_pkGlobalList; pkGList; pkGList = pkGList->Next())
    {
        int eType = pkGList->Item()->GetGlobalStateType();
        GlobalState* pkDummy;
        akGStack[eType].Pop(pkDummy);
    }

    TList<LightPtr>* pkLList;
    for (pkLList = m_pkLightList; pkLList; pkLList = pkLList->Next())
    {
        Light* pkDummy;
        pkLStack->Pop(pkDummy);
    }
}
//----------------------------------------------------------------------------
void Spatial::OnDraw (Renderer& rkRenderer, bool bNoCull)
{
    if (ForceCull)
    {
        return;
    }

    CameraPtr spkCamera = rkRenderer.GetCamera();
    unsigned int uiState = spkCamera->GetPlaneState();

    if (bNoCull || !spkCamera->Culled(WorldBound))
    {
        Draw(rkRenderer,bNoCull);
    }

    spkCamera->SetPlaneState(uiState);
}
//----------------------------------------------------------------------------
Spatial::PickRecord::PickRecord (Spatial* pkIObject, fixed fT)
    :
    IObject(pkIObject)
{
    T = fT;
}
//----------------------------------------------------------------------------
Spatial::PickRecord::~PickRecord ()
{
    // stub for derived classes
}
//----------------------------------------------------------------------------
void Spatial::DoPick (const Ray3x&, PickArray&)
{
    // stub for derived classes
}
//----------------------------------------------------------------------------
Spatial::PickRecord* Spatial::GetClosest (PickArray& rkResults)
{
    if (rkResults.GetQuantity() == 0)
    {
        return 0;
    }

    fixed fTMin = rkResults[0]->T;
    int iMin = 0;
    for (int i = 1; i < rkResults.GetQuantity(); i++)
    {
        fixed fT = rkResults[i]->T;
        if (fT < fTMin)
        {
            fTMin = fT;
            iMin = i;
        }
    }
    return rkResults[iMin];
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* Spatial::GetObjectByName (const String& rkName)
{
    Object* pkFound = Object::GetObjectByName(rkName);
    if (pkFound)
    {
        return pkFound;
    }

    if (WorldBound)
    {
        pkFound = WorldBound->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    TList<GlobalStatePtr>* pkGList;
    for (pkGList = m_pkGlobalList; pkGList; pkGList = pkGList->Next())
    {
        GlobalState* pkGState = pkGList->Item();
        if (pkGState)
        {
            pkFound = pkGState->GetObjectByName(rkName);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    TList<LightPtr>* pkLList;
    for (pkLList = m_pkLightList; pkLList; pkLList = pkLList->Next())
    {
        Light* pkLight = pkLList->Item();
        if (pkLight)
        {
            pkFound = pkLight->GetObjectByName(rkName);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    if (m_spkEffect)
    {
        pkFound = m_spkEffect->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    // To avoid cycles in a recursive search of a scene graph for an object
    // with the specified name, the member m_pkParent is not checked.
    return 0;
}
//----------------------------------------------------------------------------
void Spatial::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    Object::GetAllObjectsByName(rkName,rkObjects);

    if (WorldBound)
    {
        WorldBound->GetAllObjectsByName(rkName,rkObjects);
    }

    TList<GlobalStatePtr>* pkGList;
    for (pkGList = m_pkGlobalList; pkGList; pkGList = pkGList->Next())
    {
        GlobalState* pkGState = pkGList->Item();
        if (pkGState)
        {
            pkGState->GetAllObjectsByName(rkName,rkObjects);
        }
    }

    TList<LightPtr>* pkLList;
    for (pkLList = m_pkLightList; pkLList; pkLList = pkLList->Next())
    {
        Light* pkLight = pkLList->Item();
        if (pkLight)
        {
            pkLight->GetAllObjectsByName(rkName,rkObjects);
        }
    }

    if (m_spkEffect)
    {
        m_spkEffect->GetAllObjectsByName(rkName,rkObjects);
    }

    // To avoid cycles in a recursive search of a scene graph for an object
    // with the specified name, the member m_pkParent is not checked.
}
//----------------------------------------------------------------------------
Object* Spatial::GetObjectByID (unsigned int uiID)
{
    Object* pkFound = Object::GetObjectByID(uiID);
    if (pkFound)
    {
        return pkFound;
    }

    if (WorldBound)
    {
        pkFound = WorldBound->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    TList<GlobalStatePtr>* pkGList;
    for (pkGList = m_pkGlobalList; pkGList; pkGList = pkGList->Next())
    {
        GlobalState* pkGState = pkGList->Item();
        if (pkGState)
        {
            pkFound = pkGState->GetObjectByID(uiID);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    TList<LightPtr>* pkLList;
    for (pkLList = m_pkLightList; pkLList; pkLList = pkLList->Next())
    {
        Light* pkLight = pkLList->Item();
        if (pkLight)
        {
            pkFound = pkLight->GetObjectByID(uiID);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    if (m_spkEffect)
    {
        pkFound = m_spkEffect->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    // To avoid cycles in a recursive search of a scene graph for an object
    // with the specified id, the member m_pkParent is not checked.
    return 0;
}
//----------------------------------------------------------------------------
