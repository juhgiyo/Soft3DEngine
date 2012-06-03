///////////////////////////////////////////////////////////
//                                                       //
//                    WgObject.cpp                       //
//                                                       //
//  - Implementation for Object class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgObject.h"
#include "WgController.h"
using namespace WGSoft3D;

const Rtti Object::TYPE("WGSoft3D.Object",0);
unsigned int Object::ms_uiNextID = 0;
THashTable<unsigned int,Object*>* Object::InUse = 0;

//----------------------------------------------------------------------------
Object::Object ()
{
    m_pkControllerList = 0;
    m_iReferences = 0;
    m_uiID = ms_uiNextID++;

    if (!InUse)
    {
        InUse = WG_NEW THashTable<unsigned int,Object*>(1024);
    }

    InUse->Insert(m_uiID,this);
}
//----------------------------------------------------------------------------
Object::~Object ()
{
    RemoveAllControllers();
    assert(InUse);
    bool bFound = InUse->Remove(m_uiID);
    assert(bFound);
    (void)bFound;  // avoid compiler warning in release build
}
//----------------------------------------------------------------------------
void Object::DecrementReferences ()
{
    if (--m_iReferences == 0)
    {
        WG_DELETE this;
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// controllers
//----------------------------------------------------------------------------
void Object::SetController (Controller* pkController)
{
    // Controllers may not be controlled.  This avoids arbitrarily complex
    // graphs of Objects.  It is possible to allowed controlled controllers,
    // but modify and proceed at your own risk...
    if (IsDerived(Controller::TYPE))
    {
        assert(false);
        return;
    }

    // controller must exist
    if (!pkController)
    {
        assert(pkController);
        return;
    }

    // check if controller is already in the list
    TList<ControllerPtr>* pkList;
    for (pkList = m_pkControllerList; pkList; pkList = pkList->Next())
    {
        if (pkList->Item() == pkController)
        {
            // controller already exists, nothing to do
            return;
        }
    }

    // bind controller to object
    pkController->SetObject(this);

    // controller not in current list, add it
    pkList = WG_NEW TList<ControllerPtr>;
    pkList->Item() = pkController;
    pkList->Next() = m_pkControllerList;
    m_pkControllerList = pkList;
}
//----------------------------------------------------------------------------
int Object::GetControllerQuantity () const
{
    int iControllerQuantity = 0;

    TList<ControllerPtr>* pkList;
    for (pkList = m_pkControllerList; pkList; pkList = pkList->Next())
    {
        iControllerQuantity++;
    }

    return iControllerQuantity;
}
//----------------------------------------------------------------------------
Controller* Object::GetController (int i) const
{
    assert(i >= 0);

    TList<ControllerPtr>* pkList = m_pkControllerList;
    for (int j = 0; j < i; j++, pkList = pkList->Next())
    {
        if (!pkList)
        {
            // i >= iControllerQuantity
            return 0;
        }
    }
    return (pkList ? pkList->Item() : 0);
}
//----------------------------------------------------------------------------
void Object::RemoveController (Controller* pkController)
{
    // check if controller is in list
    TList<ControllerPtr>* pkList = m_pkControllerList;
    TList<ControllerPtr>* pkPrev = 0;
    for (/**/; pkList; pkPrev = pkList, pkList = pkList->Next())
    {
        if (pkList->Item() == pkController)
        {
            // unbind controller from object
            pkController->SetObject(0);

            // remove the controller
            if (pkPrev)
            {
                // controller not at front of list
                pkPrev->Next() = pkList->Next();
            }
            else
            {
                // controller at front of list
                assert(pkList == m_pkControllerList);
                m_pkControllerList = pkList->Next();
            }
            pkList->Next() = 0;
            WG_DELETE pkList;
            return;
        }
    }
}
//----------------------------------------------------------------------------
void Object::RemoveAllControllers ()
{
    while (m_pkControllerList)
    {
        m_pkControllerList->Item()->SetObject(0);
        m_pkControllerList->Item() = 0;
        TList<ControllerPtr>* pkSave = m_pkControllerList->Next();
        WG_DELETE m_pkControllerList;
        m_pkControllerList = pkSave;
    }
}
//----------------------------------------------------------------------------
bool Object::UpdateControllers (double dAppTime)
{
    bool bSomeoneUpdated = false;
    TList<ControllerPtr>* pkList;
    for (pkList = m_pkControllerList; pkList!=NULL; pkList = pkList->Next())
    {
        Controller* pkController = pkList->Item();
        assert(pkController);
        if (pkController->Update(dAppTime))
        {
            bSomeoneUpdated = true;
        }
    }
    return bSomeoneUpdated;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* Object::GetObjectByName (const String& rkName)
{
    if (rkName == m_kName)
    {
        return this;
    }

    TList<ControllerPtr>* pkList;
    for (pkList = m_pkControllerList; pkList!=NULL; pkList = pkList->Next())
    {
        Controller* pkController = pkList->Item();
        if (pkController)
        {
            Object* pkFound = pkController->GetObjectByName(rkName);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void Object::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    if (rkName == m_kName)
    {
        rkObjects.Append(this);
    }

    TList<ControllerPtr>* pkList;
    for (pkList = m_pkControllerList; pkList!=NULL; pkList = pkList->Next())
    {
        Controller* pkController = pkList->Item();
        if (pkController)
        {
            pkController->GetAllObjectsByName(rkName,rkObjects);
        }
    }
}
//----------------------------------------------------------------------------
Object* Object::GetObjectByID (unsigned int uiID)
{
    if (uiID == m_uiID)
    {
        return this;
    }

    TList<ControllerPtr>* pkList;
    for (pkList = m_pkControllerList; pkList!=NULL; pkList = pkList->Next())
    {
        Controller* pkController = pkList->Item();
        if (pkController)
        {
            Object* pkFound = pkController->GetObjectByID(uiID);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------

