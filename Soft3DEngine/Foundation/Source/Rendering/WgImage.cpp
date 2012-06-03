///////////////////////////////////////////////////////////
//                                                       //
//                    WgImage.cpp                        //
//                                                       //
//  - Implementation for Image class                     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgImage.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,Image,Object);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(Image,Object);

int Image::ms_aiBytesPerPixel[Image::IT_QUANTITY] =
{
    2, 3, 2, 4
};

//----------------------------------------------------------------------------
Image::Image (TextureFormat eFormat, int iWidth, int iHeight, unsigned char* aucData, bool bRequireDelete,
    const char* acImageName, bool bRequirePowerOfTwo)
{
    if (bRequirePowerOfTwo)
    {
        assert(IsPowerOfTwo(iWidth) && IsPowerOfTwo(iHeight));
    }

    m_eFormat = eFormat;
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_iQuantity = iWidth*iHeight;
    m_aucData = aucData;

    if (acImageName)
    {
        SetName(acImageName);
    }
    else
    {
        // Generate the unique image name.
        const size_t uiSize = 32;
        char acFilename[uiSize];
        System::Sprintf(acFilename,uiSize,"image%u.mif",GetID());
        SetName(acFilename);
    }
	m_bRequireDelete =bRequireDelete;
}
//----------------------------------------------------------------------------
Image::Image ()
{
    m_eFormat = IT_QUANTITY;
    m_iWidth = 0;
    m_iHeight = 0;
    m_iQuantity = 0;
    m_aucData = 0;
	m_bRequireDelete=true;
}
//----------------------------------------------------------------------------
Image::~Image ()
{
 	if(m_bRequireDelete&&m_aucData)
 	    WG_DELETE[] m_aucData;
}
void Image::DeleteRawData()
{
	if(m_bRequireDelete && m_aucData)
	    WG_DELETE[] m_aucData;
	m_aucData=NULL;
}
//----------------------------------------------------------------------------
bool Image::IsPowerOfTwo (int iValue)
{
    return (iValue != 0) && ((iValue & -iValue) == iValue);
}
//----------------------------------------------------------------------------
