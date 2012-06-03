///////////////////////////////////////////////////////////
//                                                       //
//                    WgGeomtry.cpp                      //
//                                                       //
//  - Implementation for Geometry class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgGeometry.h"
#include "WgLight.h"
#include "WgTexture.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,Geometry,Spatial);


//----------------------------------------------------------------------------
Geometry::Geometry ()
    :
    ModelBound(BoundingVolume::Create()),
    Lights(8,8)
{
    memset(States,0,GlobalState::MAX_STATE*sizeof(GlobalState*));
}
//----------------------------------------------------------------------------
Geometry::Geometry (Vector3xArrayPtr spkVertices)
    :
    Vertices(spkVertices),
    ModelBound(BoundingVolume::Create()),
    Lights(8,8)
{
    memset(States,0,GlobalState::MAX_STATE*sizeof(GlobalState*));
    UpdateModelBound();
}
//----------------------------------------------------------------------------
Geometry::~Geometry ()
{
}
//----------------------------------------------------------------------------
void Geometry::UpdateMS (bool bUpdateNormals)
{
    UpdateModelBound();
    if (bUpdateNormals)
    {
        UpdateModelNormals();
    }
}
//----------------------------------------------------------------------------
void Geometry::UpdateModelBound ()
{
    ModelBound->ComputeFromData(Vertices);
}
//----------------------------------------------------------------------------
void Geometry::UpdateWorldBound ()
{
    ModelBound->TransformBy(World,WorldBound);
}
//----------------------------------------------------------------------------
void Geometry::UpdateState (TStack<GlobalState*>* akGStack,
    TStack<Light*>* pkLStack)
{
    // update global state
    int i;
    for (i = 0; i < GlobalState::MAX_STATE; i++)
    {
        GlobalState* pkGState = 0;
        akGStack[i].GetTop(pkGState);
        assert( pkGState );
        States[i] = pkGState;
    }

    // update lights
    Light* const* akLight = pkLStack->GetData();
    int iQuantity = pkLStack->GetQuantity();
    Lights.RemoveAll();
    for (i = 0; i < iQuantity; i++)
    {
        Lights.Append(akLight[i]);
    }
}
//----------------------------------------------------------------------------
void Geometry::Draw (Renderer& rkRenderer, bool)
{
    rkRenderer.Draw(this);
}
//----------------------------------------------------------------------------
Geometry::PickRecord::PickRecord (Geometry* pkIObject, fixed fT)
    :
    Spatial::PickRecord(pkIObject,fT)
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* Geometry::GetObjectByName (const String& rkName)
{
    Object* pkFound = Spatial::GetObjectByName(rkName);
    if (pkFound)
    {
        return pkFound;
    }

    if (Vertices)
    {
        pkFound = Vertices->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (Normals)
    {
        pkFound = Normals->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (ModelBound)
    {
        pkFound = ModelBound->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void Geometry::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    Spatial::GetAllObjectsByName(rkName,rkObjects);

    if (Vertices)
    {
        Vertices->GetAllObjectsByName(rkName,rkObjects);
    }

    if (Normals)
    {
        Normals->GetAllObjectsByName(rkName,rkObjects);
    }

    if (ModelBound)
    {
        ModelBound->GetAllObjectsByName(rkName,rkObjects);
    }
}
//----------------------------------------------------------------------------
Object* Geometry::GetObjectByID (unsigned int uiID)
{
    Object* pkFound = Spatial::GetObjectByID(uiID);
    if (pkFound)
    {
        return pkFound;
    }

    if (Vertices)
    {
        pkFound = Vertices->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (Normals)
    {
        pkFound = Normals->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (ModelBound)
    {
        pkFound = ModelBound->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
