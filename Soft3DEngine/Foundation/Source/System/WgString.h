///////////////////////////////////////////////////////////
//                                                       //
//                    WgString.h                         //
//                                                       //
//  - Interface for String class                         //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG3D_STRING_H__
#define __WG3D_STRING_H__

#include "WgFoundationLIB.h"
#include "WgSystem.h"

namespace WGSoft3D
{

class WG3D_FOUNDATION_ITEM String
{
public:
    // construction and destruction
    String (const char* acText = 0);
    String (int iLength, const char* acText);
    String (const String& rkString);
    ~String ();

    // member access
    int GetLength () const;
    operator const char* () const;

    // assignment, comparisons, implicit conversion (support for hash tables)
    String& operator= (const String& rkString);
    String& operator+= (const String& rkString);
    String operator+ (const String& rkString);
    bool operator== (const String& rkString) const;
    bool operator!= (const String& rkString) const;
    operator unsigned int () const;

    // memory and disk footprint (support for streaming)
    int GetMemoryUsed () const;
    int GetDiskUsed () const;

    // Case-related
    String ToUpper () const;
    String ToLower () const;

private:
    // Text is stored as null-terminated character string in memory.  The
    // length counts all but the non-null character.  When written to disk,
    // the length is stored first and all but the non-null character are
    // stored second.
    int m_iLength;
    char* m_acText;
};

#include "WgString.inl"

}

#endif

