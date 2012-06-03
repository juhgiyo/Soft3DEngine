///////////////////////////////////////////////////////////
//                                                       //
//                    WgProjectedTextureEffect.cpp       //
//                                                       //
//  - Implementation for Projected Texture Effect class  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgFoundationPCH.h"
#include "WgProjectedTextureEffect.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,ProjectedTextureEffect,Effect);


//----------------------------------------------------------------------------
ProjectedTextureEffect::ProjectedTextureEffect (Image* pkImage,
												Camera* pkCamera, Texture::ApplyMode iApplyMode)
    :
    m_spkCamera(pkCamera)
{
    Draw = &Renderer::DrawProjectedTexture;

    Texture* pkTexture = WG_NEW Texture;
    pkTexture->SetImage(pkImage);
    pkTexture->Apply = iApplyMode;
    pkTexture->Filter = Texture::FM_LINEAR;
    pkTexture->Mipmap = Texture::MM_LINEAR_LINEAR;
    pkTexture->Texgen = Texture::TG_PROJECTED_TEXTURE;
    Textures.Append(pkTexture);
    UVs.Append(0);
}
//----------------------------------------------------------------------------
ProjectedTextureEffect::ProjectedTextureEffect ()
{
    Draw = &Renderer::DrawProjectedTexture;
}
//----------------------------------------------------------------------------
ProjectedTextureEffect::~ProjectedTextureEffect ()
{
}
//----------------------------------------------------------------------------
Effect* ProjectedTextureEffect::Clone ()
{
    ProjectedTextureEffect* pkClone = WG_NEW ProjectedTextureEffect;
    DoCloning(pkClone);
    return pkClone;
}
//----------------------------------------------------------------------------
void ProjectedTextureEffect::DoCloning (Effect* pkClone)
{
    Effect::DoCloning(pkClone);

    ProjectedTextureEffect* pkDClone = (ProjectedTextureEffect*)pkClone;
    pkDClone->m_spkCamera = m_spkCamera;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* ProjectedTextureEffect::GetObjectByName (const String& rkName)
{
    Object* pkFound = Effect::GetObjectByName(rkName);
    if (pkFound)
    {
        return pkFound;
    }

    if (m_spkCamera)
    {
        pkFound = m_spkCamera->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void ProjectedTextureEffect::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    Effect::GetAllObjectsByName(rkName,rkObjects);

    if (m_spkCamera)
    {
        m_spkCamera->GetAllObjectsByName(rkName,rkObjects);
    }
}
//----------------------------------------------------------------------------
Object* ProjectedTextureEffect::GetObjectByID (unsigned int uiID)
{
    Object* pkFound = Effect::GetObjectByID(uiID);
    if (pkFound)
    {
        return pkFound;
    }

    if (m_spkCamera)
    {
        pkFound = m_spkCamera->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
