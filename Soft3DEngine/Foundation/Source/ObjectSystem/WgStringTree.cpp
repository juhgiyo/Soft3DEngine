///////////////////////////////////////////////////////////
//                                                       //
//                    WgStringTree.cpp                   //
//                                                       //
//  - Implementation for String Tree class               //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgStringTree.h"
#include "WgBoundingVolume.h"
#include "WgColorRGBA.h"
#include "WgColorRGB.h"
#include "WgRtti.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
StringTree::StringTree (int iStringQuantity, int iChildQuantity)
    :
    m_kStrings(iStringQuantity),
    m_kChildren(iChildQuantity)
{
}
//----------------------------------------------------------------------------
StringTree::~StringTree ()
{
    int i;
    for (i = 0; i < m_kStrings.GetQuantity(); i++)
    {
        WG_DELETE[] m_kStrings[i];
    }

    for (i = 0; i < m_kChildren.GetQuantity(); i++)
    {
        WG_DELETE m_kChildren[i];
    }
}
//----------------------------------------------------------------------------
void StringTree::SetString (int i, char* acString)
{
    assert(0 <= i && i < m_kStrings.GetMaxQuantity());
    m_kStrings.Append(acString);
}
//----------------------------------------------------------------------------
void StringTree::SetChild (int i, StringTree* pkChild)
{
    assert(0 <= i && i < m_kChildren.GetMaxQuantity());
    m_kChildren.Append(pkChild);
}

void StringTree::FormatFixed (fixed fValue, size_t uiStringSize,
							  char* acString)
{
    if (fValue > -Mathx::MAX_REAL)
    {
        if (fValue < Mathx::MAX_REAL)
        {
            System::Sprintf(acString,uiStringSize,"%f",FloatFromFixed(fValue));
        }
        else
        {
            System::Strcpy(acString,uiStringSize,"INFINITY");
        }
    }
    else
    {
        System::Strcpy(acString,uiStringSize,"-INFINITY");
    }
}
//----------------------------------------------------------------------------
void StringTree::FormatFloat (float fValue, size_t uiStringSize,
    char* acString)
{
    if (fValue > -Mathf::MAX_REAL)
    {
        if (fValue < Mathf::MAX_REAL)
        {
            System::Sprintf(acString,uiStringSize,"%f",fValue);
        }
        else
        {
            System::Strcpy(acString,uiStringSize,"INFINITY");
        }
    }
    else
    {
        System::Strcpy(acString,uiStringSize,"-INFINITY");
    }
}
//----------------------------------------------------------------------------
void StringTree::FormatDouble (double dValue, size_t uiStringSize,
    char* acString)
{
    if (dValue > -Mathd::MAX_REAL)
    {
        if (dValue < Mathd::MAX_REAL)
        {
            System::Sprintf(acString,uiStringSize,"%lf",dValue);
        }
        else
        {
            System::Strcpy(acString,uiStringSize,"INFINITY");
        }
    }
    else
    {
        System::Strcpy(acString,uiStringSize,"-INFINITY");
    }
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const Rtti* pkRTTI, const char* acName)
{
    assert(pkRTTI);
    const char* acRTTIName = pkRTTI->GetName();

    size_t uiLength;
    char* acString;
    if (acName)
    {
        uiLength = strlen(acRTTIName) + strlen(acName) + 4;
        acString = WG_NEW char[uiLength];
        System::Sprintf(acString,uiLength,"%s <%s>",acRTTIName,acName);
    }
    else
    {
        uiLength = strlen(acRTTIName) + 2;
        acString = WG_NEW char[uiLength];
        System::Sprintf(acString,uiLength,"%s",acRTTIName);
    }
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acString)
{
    size_t uiSize;
    char* acDuplicate;
    if (acString)
    {
        uiSize = strlen(acString) + 1;
        acDuplicate = WG_NEW char[uiSize];
        System::Strcpy(acDuplicate,uiSize,acString);
    }
    else
    {
        uiSize = strlen("<no title>") + 1;
        acDuplicate = WG_NEW char[uiSize];
        System::Strcpy(acDuplicate,uiSize,"<no title>");
    }
    return acDuplicate;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// formatting of native data
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, bool bValue)
{
    assert(acPrefix);
    size_t uiLength = strlen(acPrefix) + 2 + (bValue ? 4 : 5);
    char* acString = WG_NEW char[uiLength];
    if (bValue)
    {
        System::Sprintf(acString,uiLength,"%s true",acPrefix);
    }
    else
    {
        System::Sprintf(acString,uiLength,"%s false",acPrefix);
    }
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, char cValue)
{
    assert(acPrefix);
    size_t uiLength = strlen(acPrefix) + 2 + 1;
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %c",acPrefix,cValue);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, unsigned char ucValue)
{
    assert(acPrefix);
    const size_t uiSize = 32;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"%u",(unsigned int)ucValue);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, short sValue)
{
    assert(acPrefix);
    const size_t uiSize = 32;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"%hd",sValue);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, unsigned short usValue)
{
    assert(acPrefix);
    const size_t uiSize = 32;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"%hu",usValue);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, int iValue)
{
    assert(acPrefix);
    const size_t uiSize = 32;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"%d",iValue);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, unsigned int uiValue)
{
    assert(acPrefix);
    const size_t uiSize = 32;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"%u",uiValue);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, long lValue)
{
    assert(acPrefix);
    const size_t uiSize = 32;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"%ld",lValue);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, unsigned long ulValue)
{
    assert(acPrefix);
    const size_t uiSize = 32;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"%lu",ulValue);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, fixed fValue)
{
    assert(acPrefix);
    const size_t uiDummySize = 256;
    char acDummy[uiDummySize];
    StringTree::FormatFixed(fValue,uiDummySize,acDummy);
	
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, float fValue)
{
    assert(acPrefix);
    const size_t uiDummySize = 256;
    char acDummy[uiDummySize];
    StringTree::FormatFloat(fValue,uiDummySize,acDummy);

    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, double dValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    StringTree::FormatDouble(dValue,uiSize,acDummy);

    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, void* pvValue)
{
    assert(acPrefix);
    const size_t uiSize = 32;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"%p",pvValue);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const char* acValue)
{
    assert(acPrefix && acValue);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acValue);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acValue);
    return acString;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// formatting of objects
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const BoundingVolume* pkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acX[uiSize], acY[uiSize], acZ[uiSize], acR[uiSize];
    StringTree::FormatFixed(pkValue->GetCenter().X(),uiSize,acX);
    StringTree::FormatFixed(pkValue->GetCenter().Y(),uiSize,acY);
    StringTree::FormatFixed(pkValue->GetCenter().Z(),uiSize,acZ);
    StringTree::FormatFixed(pkValue->GetRadius(),uiSize,acR);

    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(x: %s, y: %s, z: %s, r: %s)",acX,acY,
        acZ,acR);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const ColorRGBA& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(r: %f, g: %f, b: %f, a: %f)",
        rkValue.R(),rkValue.G(),rkValue.B(),rkValue.A());
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const ColorRGB& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(r: %f, g: %f, b: %f)",rkValue.R(),
        rkValue.G(),rkValue.B());
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
// char* WGSoft3D::Format (const char* acPrefix, const Line3f& rkValue)
// {
//     assert(acPrefix);
//     const size_t uiSize = 256;
//     char acDummy[uiSize];
//     System::Sprintf(acDummy,uiSize,
//         "(px: %f, py: %f, pz: %f, dx: %f, dy: %f, dz: %f)",
//         rkValue.Origin.X(),rkValue.Origin.Y(),rkValue.Origin.Z(),
//         rkValue.Direction.X(),rkValue.Direction.Y(),rkValue.Direction.Z());
//     size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
//     char* acString = WG_NEW char[uiLength];
//     System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
//     return acString;
// }
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Matrix2f& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"[c0:(%f,%f),c1:(%f,%f)]",
        rkValue[0][0],rkValue[1][0],
        rkValue[0][1],rkValue[1][1]);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Matrix3f& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,
        "[c0:(%f,%f,%f),c1:(%f,%f,%f),c2:(%f,%f,%f)]",
        rkValue[0][0],rkValue[1][0],rkValue[2][0],
        rkValue[0][1],rkValue[1][1],rkValue[2][1],
        rkValue[0][2],rkValue[1][2],rkValue[2][2]);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Matrix4f& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[256];
    System::Sprintf(acDummy,uiSize,
    "[c0:(%f,%f,%f,%f),c1:(%f,%f,%f,%f),c2:(%f,%f,%f,%f),c3(%f,%f,%f,%f)]",
        rkValue[0][0],rkValue[1][0],rkValue[2][0],rkValue[3][0],
        rkValue[0][1],rkValue[1][1],rkValue[2][1],rkValue[3][1],
        rkValue[0][2],rkValue[1][2],rkValue[2][2],rkValue[3][2],
        rkValue[0][3],rkValue[1][3],rkValue[2][3],rkValue[3][3]);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Plane3f& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,
        "(nx: %f, ny: %f, nz: %f, c: %f)",rkValue.Normal.X(),
        rkValue.Normal.Y(),rkValue.Normal.Z(),rkValue.Constant);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Quaternionf& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,
        "(w: %.3f, x: %.3f, y: %.3f, z: %.3f)",rkValue.W(),
        rkValue.X(),rkValue.Y(),rkValue.Z());
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Vector2f& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acX[uiSize], acY[uiSize];
    StringTree::FormatFloat(rkValue.X(),uiSize,acX);
    StringTree::FormatFloat(rkValue.Y(),uiSize,acY);

    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(x: %s, y: %s)",acX,acY);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Vector3f& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acX[uiSize], acY[uiSize], acZ[uiSize];
    StringTree::FormatFloat(rkValue.X(),uiSize,acX);
    StringTree::FormatFloat(rkValue.Y(),uiSize,acY);
    StringTree::FormatFloat(rkValue.Z(),uiSize,acZ);

    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(x: %s, y: %s, z: %s)",acX,acY,acZ);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Vector4f& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acX[uiSize], acY[uiSize], acZ[uiSize], acW[uiSize];
    StringTree::FormatFloat(rkValue.X(),uiSize,acX);
    StringTree::FormatFloat(rkValue.Y(),uiSize,acY);
    StringTree::FormatFloat(rkValue.Z(),uiSize,acZ);
    StringTree::FormatFloat(rkValue.W(),uiSize,acW);

    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(x: %s, y: %s, z: %s, w: %s)",acX,acY,
        acZ,acW);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
// char* WGSoft3D::Format (const char* acPrefix, const Line3x& rkValue)
// {
//     assert(acPrefix);
//     const size_t uiSize = 256;
//     char acDummy[uiSize];
//     System::Sprintf(acDummy,uiSize,
//         "(px: %f, py: %f, pz: %f, dx: %f, dy: %f, dz: %f)",
//         FloatFromFixed(rkValue.Origin.X()),FloatFromFixed(rkValue.Origin.Y()),FloatFromFixed(rkValue.Origin.Z()),
//         FloatFromFixed(rkValue.Direction.X()),FloatFromFixed(rkValue.Direction.Y()),FloatFromFixed(rkValue.Direction.Z()));
//     size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
//     char* acString = WG_NEW char[uiLength];
//     System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
//     return acString;
// }
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Matrix2x& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"[c0:(%f,%f),c1:(%f,%f)]",
        FloatFromFixed(rkValue[0][0]),FloatFromFixed(rkValue[1][0]),
        FloatFromFixed(rkValue[0][1]),FloatFromFixed(rkValue[1][1]));
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Matrix3x& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,
        "[c0:(%f,%f,%f),c1:(%f,%f,%f),c2:(%f,%f,%f)]",
        FloatFromFixed(rkValue[0][0]),FloatFromFixed(rkValue[1][0]),FloatFromFixed(rkValue[2][0]),
        FloatFromFixed(rkValue[0][1]),FloatFromFixed(rkValue[1][1]),FloatFromFixed(rkValue[2][1]),
        FloatFromFixed(rkValue[0][2]),FloatFromFixed(rkValue[1][2]),FloatFromFixed(rkValue[2][2]));
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Matrix4x& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[256];
    System::Sprintf(acDummy,uiSize,
    "[c0:(%f,%f,%f,%f),c1:(%f,%f,%f,%f),c2:(%f,%f,%f,%f),c3(%f,%f,%f,%f)]",
        FloatFromFixed(rkValue[0][0]),FloatFromFixed(rkValue[1][0]),FloatFromFixed(rkValue[2][0]),FloatFromFixed(rkValue[3][0]),
        FloatFromFixed(rkValue[0][1]),FloatFromFixed(rkValue[1][1]),FloatFromFixed(rkValue[2][1]),FloatFromFixed(rkValue[3][1]),
        FloatFromFixed(rkValue[0][2]),FloatFromFixed(rkValue[1][2]),FloatFromFixed(rkValue[2][2]),FloatFromFixed(rkValue[3][2]),
        FloatFromFixed(rkValue[0][3]),FloatFromFixed(rkValue[1][3]),FloatFromFixed(rkValue[2][3]),FloatFromFixed(rkValue[3][3]));
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Plane3x& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,
        "(nx: %f, ny: %f, nz: %f, c: %f)",FloatFromFixed(rkValue.Normal.X()),
        FloatFromFixed(rkValue.Normal.Y()),FloatFromFixed(rkValue.Normal.Z()),FloatFromFixed(rkValue.Constant));
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Quaternionx& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,
        "(w: %.3f, x: %.3f, y: %.3f, z: %.3f)",FloatFromFixed(rkValue.W()),
        FloatFromFixed(rkValue.X()),FloatFromFixed(rkValue.Y()),FloatFromFixed(rkValue.Z()));
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Vector2x& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acX[uiSize], acY[uiSize];
    StringTree::FormatFixed(rkValue.X(),uiSize,acX);
    StringTree::FormatFixed(rkValue.Y(),uiSize,acY);

    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(x: %s, y: %s)",acX,acY);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Vector3x& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acX[uiSize], acY[uiSize], acZ[uiSize];
    StringTree::FormatFixed(rkValue.X(),uiSize,acX);
    StringTree::FormatFixed(rkValue.Y(),uiSize,acY);
    StringTree::FormatFixed(rkValue.Z(),uiSize,acZ);

    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(x: %s, y: %s, z: %s)",acX,acY,acZ);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Vector4x& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acX[uiSize], acY[uiSize], acZ[uiSize], acW[uiSize];
    StringTree::FormatFixed(rkValue.X(),uiSize,acX);
    StringTree::FormatFixed(rkValue.Y(),uiSize,acY);
    StringTree::FormatFixed(rkValue.Z(),uiSize,acZ);
    StringTree::FormatFixed(rkValue.W(),uiSize,acW);

    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(x: %s, y: %s, z: %s, w: %s)",acX,acY,
        acZ,acW);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
// char* WGSoft3D::Format (const char* acPrefix, const Line3d& rkValue)
// {
//     assert(acPrefix);
//     const size_t uiSize = 256;
//     char acDummy[uiSize];
//     System::Sprintf(acDummy,uiSize,
//         "(px: %lf, py: %lf, pz: %lf, dx: %lf, dy: %lf, dz: %lf)",
//         rkValue.Origin.X(),rkValue.Origin.Y(),rkValue.Origin.Z(),
//         rkValue.Direction.X(),rkValue.Direction.Y(),rkValue.Direction.Z());
//     size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
//     char* acString = WG_NEW char[uiLength];
//     System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
//     return acString;
// }
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Matrix2d& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"[c0:(%lf,%lf),c1:(%lf,%lf)]",
        rkValue[0][0],rkValue[1][0],
        rkValue[0][1],rkValue[1][1]);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Matrix3d& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,
        "[c0:(%lf,%lf,%lf),c1:(%lf,%lf,%lf),c2:(%lf,%lf,%lf)]",
        rkValue[0][0],rkValue[1][0],rkValue[2][0],
        rkValue[0][1],rkValue[1][1],rkValue[2][1],
        rkValue[0][2],rkValue[1][2],rkValue[2][2]);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Matrix4d& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,
    "[c0:(%lf,%lf,%lf,%lf),c1:(%lf,%lf,%lf,%lf),c2:(%lf,%lf,%lf,%lf),"
    "c3(%lf,%lf,%lf,%lf)]",
        rkValue[0][0],rkValue[1][0],rkValue[2][0],rkValue[3][0],
        rkValue[0][1],rkValue[1][1],rkValue[2][1],rkValue[3][1],
        rkValue[0][2],rkValue[1][2],rkValue[2][2],rkValue[3][2],
        rkValue[0][3],rkValue[1][3],rkValue[2][3],rkValue[3][3]);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Plane3d& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,
        "(nx: %lf, ny: %lf, nz: %lf, c: %lf)",rkValue.Normal.X(),
        rkValue.Normal.Y(),rkValue.Normal.Z(),rkValue.Constant);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Quaterniond& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,
        "(w: %.3lf, x: %.3lf, y: %.3lf, z: %.3lf)",rkValue.W(),
        rkValue.X(),rkValue.Y(),rkValue.Z());
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Vector2d& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acX[uiSize], acY[uiSize];
    StringTree::FormatDouble(rkValue.X(),uiSize,acX);
    StringTree::FormatDouble(rkValue.Y(),uiSize,acY);

    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(x: %s, y: %s)",acX,acY);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Vector3d& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acX[uiSize], acY[uiSize], acZ[uiSize];
    StringTree::FormatDouble(rkValue.X(),uiSize,acX);
    StringTree::FormatDouble(rkValue.Y(),uiSize,acY);
    StringTree::FormatDouble(rkValue.Z(),uiSize,acZ);

    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(x: %s, y: %s, z: %s)",acX,acY,acZ);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------
char* WGSoft3D::Format (const char* acPrefix, const Vector4d& rkValue)
{
    assert(acPrefix);
    const size_t uiSize = 256;
    char acX[uiSize], acY[uiSize], acZ[uiSize], acW[uiSize];
    StringTree::FormatDouble(rkValue.X(),uiSize,acX);
    StringTree::FormatDouble(rkValue.Y(),uiSize,acY);
    StringTree::FormatDouble(rkValue.Z(),uiSize,acZ);
    StringTree::FormatDouble(rkValue.W(),uiSize,acW);

    char acDummy[uiSize];
    System::Sprintf(acDummy,uiSize,"(x: %s, y: %s, z: %s, w: %s)",acX,acY,
        acZ,acW);
    size_t uiLength = strlen(acPrefix) + 2 + strlen(acDummy);
    char* acString = WG_NEW char[uiLength];
    System::Sprintf(acString,uiLength,"%s %s",acPrefix,acDummy);
    return acString;
}
//----------------------------------------------------------------------------

