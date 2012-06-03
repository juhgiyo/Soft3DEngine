///////////////////////////////////////////////////////////
//                                                       //
//                    WgStringTree.h                     //
//                                                       //
//  - Interface for String Tree class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_STRINGTREE_H__
#define __WG_STRINGTREE_H__

#include "WgFoundationLIB.h"
#include "WgSystem.h"

#include "WgMatrix2.h"
#include "WgMatrix3.h"
#include "WgMatrix4.h"
#include "WgPlane3.h"
//#include "WgLine3.h"
#include "WgQuaternion.h"

namespace WGSoft3D
{

class BoundingVolume;
class ColorRGBA;
class ColorRGB;
class Rtti;

class WG3D_FOUNDATION_ITEM StringTree
{
public:
    // construction and destruction
    StringTree (int iStringQuantity, int iChildQuantity);
    ~StringTree ();

    // strings
    int GetStringQuantity () const;
    void SetString (int i, char* acString);
    char* GetString (int i);

    // children
    int GetChildQuantity () const;
    void SetChild (int i, StringTree* pkChild);
    StringTree* GetChild (int i);


	static void FormatFixed (fixed fValue, size_t uiStringSize,
        char* acString);
    static void FormatFloat (float fValue, size_t uiStringSize,
        char* acString);
    static void FormatDouble (double dValue, size_t uiStringSize,
        char* acString);

private:
    TArray< char* > m_kStrings;
    TArray<StringTree*> m_kChildren;
};


// string creation helpers (native types)
WG3D_FOUNDATION_ITEM char* Format (const Rtti* pkRTTI, const char* acName);
WG3D_FOUNDATION_ITEM char* Format (const char* acString);

WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, bool bValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, char cValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, unsigned char ucValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, short sValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, unsigned short usValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, int iValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, unsigned int uiValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, long lValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, unsigned long ulValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, fixed fValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, float fValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, double dValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, void* pvValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const char* acValue);

WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const BoundingVolume* pkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const ColorRGBA& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const ColorRGB& rkValue);
//WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Line3f& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Matrix2f& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Matrix3f& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Matrix4f& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Plane3f& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Quaternionf& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Vector2f& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Vector3f& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Vector4f& rkValue);

//WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Line3x& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Matrix2x& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Matrix3x& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Matrix4x& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Plane3x& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Quaternionx& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Vector2x& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Vector3x& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Vector4x& rkValue);

//WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Line3d& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Matrix2d& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Matrix3d& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Matrix4d& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Plane3d& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Quaterniond& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Vector2d& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Vector3d& rkValue);
WG3D_FOUNDATION_ITEM char* Format (const char* acPrefix, const Vector4d& rkValue);

template <class T>
StringTree* Format (const char* acTitle, int iQuantity, const T* atValue);

#include "WgStringTree.inl"

}

#endif

