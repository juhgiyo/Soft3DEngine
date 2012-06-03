///////////////////////////////////////////////////////////
//                                                       //
//                    WgTexture.cpp                      //
//                                                       //
//  - Implementation for Texture class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgTexture.h"
#include "WgRenderer.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,Texture,Object);


//----------------------------------------------------------------------------
Texture::Texture (Image* pkImage)
    :
    BlendColor(ColorRGBA(fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO))),
    BorderColor(ColorRGBA::INVALID),
    m_spkImage(pkImage),
    BIArray(1,1)
{
    Correction = CM_PERSPECTIVE;
    Apply = AM_REPLACE;
    CoordU = WM_CLAMP_EDGE;
    CoordV = WM_CLAMP_EDGE;
    Filter = FM_LINEAR;
    Mipmap = MM_LINEAR_LINEAR;
    Texgen = TG_NONE;
    CombineFuncRGB = ACF_REPLACE;
    CombineFuncAlpha = ACF_REPLACE;
    CombineSrc0RGB = ACS_TEXTURE;
    CombineSrc1RGB = ACS_TEXTURE;
    CombineSrc2RGB = ACS_TEXTURE;
    CombineSrc0Alpha = ACS_TEXTURE;
    CombineSrc1Alpha = ACS_TEXTURE;
    CombineSrc2Alpha = ACS_TEXTURE;
    CombineOp0RGB = ACO_SRC_COLOR;
    CombineOp1RGB = ACO_SRC_COLOR;
    CombineOp2RGB = ACO_SRC_COLOR;
    CombineOp0Alpha = ACO_SRC_COLOR;
    CombineOp1Alpha = ACO_SRC_COLOR;
    CombineOp2Alpha = ACO_SRC_COLOR;
    CombineScaleRGB = ACSC_ONE;
    CombineScaleAlpha = ACSC_ONE;
    m_iOffscreenIndex = -1;
}
//----------------------------------------------------------------------------
Texture::~Texture ()
{
    // Inform all renderers using this texture that it is being destroyed.
    // This allows the renderer to free up any associated resources.
    const TArray<BindInfo>& rkArray = BIArray.GetArray();
    for (int i = rkArray.GetQuantity()-1; i >= 0; i--)
    {
        rkArray[i].User->ReleaseTexture(this);
    }
}
//----------------------------------------------------------------------------
void Texture::SetImage (ImagePtr spkImage)
{
    m_spkImage = spkImage;
    Changed();
}
//----------------------------------------------------------------------------
void Texture::Changed ()
{
    // Inform all renderers using this texture has changed.  This allows the
    // renderer to free up any associated resources and the texture to be
    // rebound during the next drawing pass.
    const TArray<BindInfo>& rkArray = BIArray.GetArray();
    for (int i = rkArray.GetQuantity()-1; i >= 0; i--)
    {
        rkArray[i].User->ReleaseTexture(this);
    }
}
void Texture::DeleteImageRawData()
{
	m_spkImage->DeleteRawData();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* Texture::GetObjectByName (const String& rkName)
{
    Object* pkFound = Object::GetObjectByName(rkName);
    if (pkFound)
    {
        return pkFound;
    }

    if (m_spkImage)
    {
        pkFound = m_spkImage->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void Texture::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    Object::GetAllObjectsByName(rkName,rkObjects);

    if (m_spkImage)
    {
        m_spkImage->GetAllObjectsByName(rkName,rkObjects);
    }
}
//----------------------------------------------------------------------------
Object* Texture::GetObjectByID (unsigned int uiID)
{
    Object* pkFound = Object::GetObjectByID(uiID);
    if (pkFound)
    {
        return pkFound;
    }

    if (m_spkImage)
    {
        pkFound = m_spkImage->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
