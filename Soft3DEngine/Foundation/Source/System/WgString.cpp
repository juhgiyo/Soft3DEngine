///////////////////////////////////////////////////////////
//                                                       //
//                    WgString.cpp                       //
//                                                       //
//  - Implementation for String class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgString.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
String::String (const char* acText)
{
    if (acText)
    {
        m_iLength = (int)strlen(acText);
        m_acText = WG_NEW char[m_iLength+1];
        const size_t uiSize = (size_t)(m_iLength + 1);
        System::Strcpy(m_acText,uiSize,acText);
    }
    else
    {
        m_iLength = 0;
        m_acText = WG_NEW char[1];
        m_acText[0] = 0;
    }
}
//----------------------------------------------------------------------------
String::String (int iLength, const char* acText)
{
    if (iLength < 0 || (iLength > 0 && !acText))
    {
        assert(false);
        iLength = 0;
    }

#ifdef _DEBUG
    // make sure acText has as many non-null characters as specified
    if (iLength > 0)
    {
        int i;
        for (i = 0; i < iLength; i++)
        {
            if (acText[i] == 0)
            {
                break;
            }
        }
        assert(i == iLength);
    }
#endif

    m_iLength = iLength;
    if (m_iLength > 0)
    {
        const size_t uiSrcSize = (size_t)m_iLength;
        const size_t uiDstSize = (size_t)(m_iLength + 1);
        m_acText = WG_NEW char[uiDstSize];
        System::Strncpy(m_acText,uiDstSize,acText,uiSrcSize);
        m_acText[m_iLength] = 0;
    }
    else
    {
        m_acText = WG_NEW char[1];
        m_acText[0] = 0;
    }
}
//----------------------------------------------------------------------------
String::String (const String& rkString)
{
    m_acText = 0;
    *this = rkString;
}
//----------------------------------------------------------------------------
String::~String ()
{
    WG_DELETE[] m_acText;
}
//----------------------------------------------------------------------------
String& String::operator= (const String& rkString)
{
    m_iLength = rkString.m_iLength;
    WG_DELETE[] m_acText;
    const size_t uiSize = (size_t)(m_iLength + 1);
    m_acText = WG_NEW char[uiSize];
    System::Strcpy(m_acText,uiSize,rkString.m_acText);
    return *this;
}
//----------------------------------------------------------------------------
String& String::operator+= (const String& rkString)
{
    m_iLength += rkString.m_iLength;
    const size_t uiSize = (size_t)(m_iLength + 1);
    char* acNew = WG_NEW char[uiSize];
    System::Strcpy(acNew,uiSize,m_acText);
    WG_DELETE[] m_acText;
    m_acText = System::Strcat(acNew,uiSize,rkString.m_acText);   
    return *this;
}
//----------------------------------------------------------------------------
String String::operator+ (const String& rkString)
{
    int iLength = m_iLength + rkString.m_iLength;
    const size_t uiSize = (size_t)(iLength + 1);
    char* acNew = WG_NEW char[uiSize];
    System::Strcpy(acNew,uiSize,m_acText);
    System::Strcat(acNew,uiSize,rkString.m_acText);
    String kAppended(iLength,acNew);
    WG_DELETE[] acNew;
    return kAppended;
}
//----------------------------------------------------------------------------
bool String::operator== (const String& rkString) const
{
    return m_iLength == rkString.m_iLength
        && memcmp(m_acText,rkString.m_acText,m_iLength) == 0;
}
//----------------------------------------------------------------------------
bool String::operator!= (const String& rkString) const
{
    return m_iLength != rkString.m_iLength
        || memcmp(m_acText,rkString.m_acText,m_iLength) != 0;
}
//----------------------------------------------------------------------------
String::operator unsigned int () const
{
    unsigned int uiKey = 0;
    for (int i = 0; i < m_iLength; i++)
    {
        uiKey += (uiKey << 5) + m_acText[i];
    }
    return uiKey;
}
//----------------------------------------------------------------------------
String String::ToUpper () const
{
    String kCopy(*this);
    for (int i = 0; i < m_iLength; i++)
    {
        kCopy.m_acText[i] = toupper(m_acText[i]);
    }
    return kCopy;
}
//----------------------------------------------------------------------------
String String::ToLower () const
{
    String kCopy(*this);
    for (int i = 0; i < m_iLength; i++)
    {
        kCopy.m_acText[i] = tolower(m_acText[i]);
    }
    return kCopy;
}
//----------------------------------------------------------------------------

