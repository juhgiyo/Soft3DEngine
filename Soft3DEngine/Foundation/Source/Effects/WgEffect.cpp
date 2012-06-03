///////////////////////////////////////////////////////////
//                                                       //
//                    WgEffect.cpp                       //
//                                                       //
//  - Implementation for Effect class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgEffect.h"
#include "WgLight.h"
#include "WgTexture.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,Effect,Object);


//----------------------------------------------------------------------------
Effect::Effect ()
    :
    Textures(8,8),
    UVs(8,8)
{
    Draw = &Renderer::DrawPrimitive;
}
//----------------------------------------------------------------------------
Effect::~Effect ()
{
}
void Effect::RemoveColorRGBData()
{
	ColorRGBs->DeleteRawData();
}
void Effect::RemoveColorRGBAData()
{
	ColorRGBAs->DeleteRawData();
}
void Effect::RemoveTextureRawData(int i)
{
	TexturePtr ptr=Textures[i];
	if(ptr)
		ptr->DeleteImageRawData();
}
void Effect::RemoveTextureUVData(int i)
{
	Vector2xArrayPtr ptr=UVs[i];
	if(ptr)
		ptr->DeleteRawData();

}
//----------------------------------------------------------------------------
Effect* Effect::Clone ()
{
    Effect* pkClone = WG_NEW Effect;
    DoCloning(pkClone);
    return pkClone;
}
//----------------------------------------------------------------------------
void Effect::DoCloning (Effect* pkClone)
{
    pkClone->Draw = Draw;
    pkClone->ColorRGBs = ColorRGBs;
    pkClone->ColorRGBAs = ColorRGBAs;

    int i;
    for (i = 0; i < Textures.GetQuantity(); i++)
    {
        pkClone->Textures.Append(Textures[i]);
    }

    for (i = 0; i < UVs.GetQuantity(); i++)
    {
        pkClone->UVs.Append(UVs[i]);
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* Effect::GetObjectByName (const String& rkName)
{
    Object* pkFound = Object::GetObjectByName(rkName);
    if (pkFound)
    {
        return pkFound;
    }

    if (ColorRGBs)
    {
        pkFound = ColorRGBs->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (ColorRGBAs)
    {
        pkFound = ColorRGBAs->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    int i;
    for (i = 0; i < Textures.GetQuantity(); i++)
    {
        if (Textures[i])
        {
            pkFound = Textures[i]->GetObjectByName(rkName);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    for (i = 0; i < UVs.GetQuantity(); i++)
    {
        if (UVs[i])
        {
            pkFound = UVs[i]->GetObjectByName(rkName);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void Effect::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    Object::GetAllObjectsByName(rkName,rkObjects);

    if (ColorRGBs)
    {
        ColorRGBs->GetAllObjectsByName(rkName,rkObjects);
    }

    if (ColorRGBAs)
    {
        ColorRGBAs->GetAllObjectsByName(rkName,rkObjects);
    }

    int i;
    for (i = 0; i < Textures.GetQuantity(); i++)
    {
        if (Textures[i])
        {
            Textures[i]->GetAllObjectsByName(rkName,rkObjects);
        }
    }

    for (i = 0; i < UVs.GetQuantity(); i++)
    {
        if (UVs[i])
        {
            UVs[i]->GetAllObjectsByName(rkName,rkObjects);
        }
    }
}
//----------------------------------------------------------------------------
Object* Effect::GetObjectByID (unsigned int uiID)
{
    Object* pkFound = Object::GetObjectByID(uiID);
    if (pkFound)
    {
        return pkFound;
    }

    if (ColorRGBs)
    {
        pkFound = ColorRGBs->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    if (ColorRGBAs)
    {
        pkFound = ColorRGBAs->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    int i;
    for (i = 0; i < Textures.GetQuantity(); i++)
    {
        if (Textures[i])
        {
            pkFound = Textures[i]->GetObjectByID(uiID);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    for (i = 0; i < UVs.GetQuantity(); i++)
    {
        if (UVs[i])
        {
            pkFound = UVs[i]->GetObjectByID(uiID);
            if (pkFound)
            {
                return pkFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
