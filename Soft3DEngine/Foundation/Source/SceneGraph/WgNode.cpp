///////////////////////////////////////////////////////////
//                                                       //
//                    WgNode.cpp                         //
//                                                       //
//  - Implementation for Node class                      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgNode.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,Node,Spatial);

//----------------------------------------------------------------------------
Node::Node (int iQuantity, int iGrowBy)
    :
    m_kChild(iQuantity,iGrowBy)
{
    m_iUsed = 0;
}
//----------------------------------------------------------------------------
Node::~Node ()
{
    for (int i = 0; i < m_kChild.GetQuantity(); i++)
    {
        SpatialPtr spkChild = DetachChildAt(i);
        spkChild = 0;
    }
}
//----------------------------------------------------------------------------
int Node::AttachChild (Spatial* pkChild)
{
    // Some folks are of the impression that a node can have multiple parents,
    // the scene graph therefore being a DAG.  That is not the case.  The
    // parent-child relationships form a tree.  This assertion is to let folks
    // know this and to warn them that a child is being kidnapped from another
    // parent.  To be safe, you should really call DetachChild before you
    // reattach somewhere else with AttachChild or SetChild.
    assert( pkChild && !pkChild->GetParent() );

    pkChild->SetParent(this);
    m_iUsed++;

    // attach child in first available slot (if any)
    int iQuantity = m_kChild.GetQuantity();
    for (int i = 0; i < iQuantity; i++)
    {
        if (m_kChild[i] == 0)
        {
            m_kChild[i] = pkChild;
            return i;
        }
    }

    // all slots used, increase array size
    m_kChild.Append(pkChild);
    return iQuantity;
}
//----------------------------------------------------------------------------
int Node::DetachChild (Spatial* pkChild)
{
    if (pkChild)
    {
        // search to see if child exists
        for (int i = 0; i < m_kChild.GetQuantity(); i++)
        {
            if (m_kChild[i] == pkChild)
            {
                // child found, detach it
                pkChild->SetParent(0);
                m_kChild[i] = 0;
                m_iUsed--;
                return i;
            }
        }
    }

    return -1;
}
//----------------------------------------------------------------------------
SpatialPtr Node::DetachChildAt (int i)
{
    if (0 <= i && i < m_kChild.GetQuantity())
    {
        SpatialPtr spkChild = m_kChild[i];
        if ( spkChild )
        {
            // child exists in slot, detach it
            spkChild->SetParent(0);
            m_kChild[i] = 0;
            m_iUsed--;
        }
        return spkChild;
    }
    return 0;
}
//----------------------------------------------------------------------------
SpatialPtr Node::SetChild (int i, Spatial* pkChild)
{
    // Some folks are of the impression that a node can have multiple parents,
    // the scene graph therefore being a DAG.  That is not the case.  The
    // parent-child relationships form a tree.  This assertion is to let folks
    // know this and to warn them that a child is being kidnapped from another
    // parent.  To be safe, you should really call DetachChild before you
    // reattach somewhere else with AttachChild or SetChild.
    if (pkChild)
    {
        assert(!pkChild->GetParent());
    }

    if (0 <= i && i < m_kChild.GetQuantity())
    {
        // detach child currently in slot
        SpatialPtr spkPreviousChild = m_kChild[i];
        if (spkPreviousChild)
        {
            spkPreviousChild->SetParent(0);
            m_iUsed--;
        }

        // attach new child to slot
        if (pkChild)
        {
            pkChild->SetParent(this);
            m_iUsed++;
        }

        m_kChild[i] = pkChild;
        return spkPreviousChild;
    }

    // index out of range, increase array size and attach new child
    pkChild->SetParent(this);
    m_kChild.SetElement(i,pkChild);
    m_iUsed++;
    return 0;
}
//----------------------------------------------------------------------------
SpatialPtr Node::GetChild (int i)
{
    return (0 <= i && i < m_kChild.GetQuantity() ? m_kChild[i] : 0);
}
//----------------------------------------------------------------------------
void Node::UpdateWorldData (double dAppTime)
{
    Spatial::UpdateWorldData(dAppTime);

    for (int i = 0; i < m_kChild.GetQuantity(); i++)
    {
        Spatial* pkChild = m_kChild[i];
        if (pkChild)
        {
            pkChild->UpdateGS(dAppTime,false);
        }
    }
}
//----------------------------------------------------------------------------
void Node::UpdateWorldBound ()
{
    if (!WorldBoundIsCurrent)
    {
        bool bFoundFirstBound = false;
        for (int i = 0; i < m_kChild.GetQuantity(); i++)
        {
            Spatial* pkChild = m_kChild[i];
            if (pkChild)
            {
                if (bFoundFirstBound)
                {
                    // merge current world bound with child world bound
                    WorldBound->GrowToContain(pkChild->WorldBound);
                }
                else
                {
                    // set world bound to first non-null child world bound
                    bFoundFirstBound = true;
                    WorldBound->CopyFrom(pkChild->WorldBound);
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
void Node::UpdateState (TStack<GlobalState*>* akGStack,
    TStack<Light*>* pkLStack)
{
    for (int i = 0; i < m_kChild.GetQuantity(); i++)
    {
        Spatial* pkChild = m_kChild[i];
        if (pkChild)
        {
            pkChild->UpdateRS(akGStack,pkLStack);
        }
    }
}
//----------------------------------------------------------------------------
void Node::Draw (Renderer& rkRenderer, bool bNoCull)
{
    if (m_spkEffect == 0)
    {
        for (int i = 0; i < m_kChild.GetQuantity(); i++)
        {
            Spatial* pkChild = m_kChild[i];
            if (pkChild)
            {
                pkChild->OnDraw(rkRenderer,bNoCull);
            }
        }
    }
    else
    {
        // A "global" effect might require multipass rendering, so the Node
        // must be passed to the renderer for special handling.
        rkRenderer.Draw(this);
    }
}
//----------------------------------------------------------------------------
void Node::DoPick (const Ray3x& rkRay, PickArray& rkResults)
{
    if (WorldBound->TestIntersection(rkRay))
    {
        for (int i = 0; i < m_kChild.GetQuantity(); i++)
        {
            Spatial* pkChild = m_kChild[i];
            if (pkChild)
            {
                pkChild->DoPick(rkRay,rkResults);
            }
        }
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* Node::GetObjectByName (const String& rkName)
{
    Object* pkFound = Spatial::GetObjectByName(rkName);
    if (pkFound)
    {
        return pkFound;
    }

    for (int i = 0; i < m_kChild.GetQuantity(); i++)
    {
        Spatial* pkChild = m_kChild[i];
        if (pkChild)
        {
            pkFound = pkChild->GetObjectByName(rkName);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void Node::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    Spatial::GetAllObjectsByName(rkName,rkObjects);

    for (int i = 0; i < m_kChild.GetQuantity(); i++)
    {
        Spatial* pkChild = m_kChild[i];
        if (pkChild)
        {
            pkChild->GetAllObjectsByName(rkName,rkObjects);
        }
    }
}
//----------------------------------------------------------------------------
Object* Node::GetObjectByID (unsigned int uiID)
{
    Object* pkFound = Spatial::GetObjectByID(uiID);
    if (pkFound)
    {
        return pkFound;
    }

    for (int i = 0; i < m_kChild.GetQuantity(); i++)
    {
        Spatial* pkChild = m_kChild[i];
        if (pkChild)
        {
            pkFound = pkChild->GetObjectByID(uiID);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
