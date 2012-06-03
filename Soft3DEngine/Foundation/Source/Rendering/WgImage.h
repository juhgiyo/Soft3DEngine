///////////////////////////////////////////////////////////
//                                                       //
//                    WgImage.h                          //
//                                                       //
//  - Interface for Image class                          //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_IMAGE_H__
#define __WG_IMAGE_H__

#include "WgFoundationLIB.h"
#include "WgObject.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM Image : public Object
{
    WG3D_DECLARE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    typedef enum _texFormat// Format
    {
        IT_RGBA4444,
        IT_RGB888,
        IT_RGBA5551,
        IT_RGBA8888,
		IT_RGB565,
        IT_QUANTITY
    }TextureFormat;

    // Construction and destruction.  WgImage accepts responsibility for
    // deleting the input array.  The WgObject::m_acName field is used as a
    // unique identifier for the image for purposes of sharing.  The caller of
    // the constructor may provided a name.  If not, the constructor generates
    // a unique name "imageN.wmif" where N is the WgObject::m_uiID field. A
    // global map of images is maintained for sharing purposes.
    Image (TextureFormat eFormat, int iWidth, int iHeight, unsigned char* aucData, bool bRequireDelete=true,
        const char* acImageName = 0, bool bRequirePowerOfTwo = true);
    virtual ~Image ();

    // member access
    TextureFormat GetFormat () const;
    int GetBytesPerPixel () const;
    int GetWidth () const;
    int GetHeight () const;
    int GetQuantity () const;
    unsigned char* GetData () const;
    unsigned char* operator() (int i);

	void DeleteRawData();
protected:
    // support for streaming
    Image ();

    static bool IsPowerOfTwo (int iValue);

    TextureFormat m_eFormat;
    int m_iWidth, m_iHeight, m_iQuantity;
    unsigned char* m_aucData;
	bool m_bRequireDelete;

    static int ms_aiBytesPerPixel[IT_QUANTITY];
};

typedef Pointer<Image> ImagePtr;
#include "WgImage.inl"

}

#endif

