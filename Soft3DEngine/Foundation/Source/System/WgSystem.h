///////////////////////////////////////////////////////////
//                                                       //
//                    WgSystem.h                         //
//                                                       //
//  - Interface for System class                         //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG3D_SYSTEM_H__
#define __WG3D_SYSTEM_H__

#ifdef _WIN32_WCE
#pragma warning(disable:4717)
#pragma warning(disable:4530)
#endif //_WIN32_WCE

#include "WgFoundationLIB.h"
#include "WgPlatforms.h"

// common standard library headers
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <math.h>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef _WIN32_WCE
	#include <time.h>
	#include <stream.h>
#else
	#include <ctime>
	#include <iostream>
	#include <fstream>
#endif



// STL headers
#include <algorithm>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "WgMemory.h"

namespace WGSoft3D
{
class WG3D_FOUNDATION_ITEM System
{
public:
    // swap byte order (size = 2, 4, or 8)
//    static void SwapBytes (int iSize, void* pvValue);
//    static void SwapBytes (int iSize, int iQuantity, void* pvValue);

    // The output is stored in little endian format.
 //   static bool IsBigEndian ();
 //   static void EndianCopy (int iSize, const void* pvSrc, void* pvDst);
 //   static void EndianCopy (int iSize, int iQuantity, const void* pvSrc, void* pvDst);

    // time utility (return value is seconds)
#ifndef _WIN32_WCE
    static double GetTime ();
#endif //_WIN32_WCE
    // File support for buffer load and save.
//     static bool Load (const char* acFilename, char*& racBuffer, int& riSize);
//     static bool Save (const char* acFilename, const char* acBuffer,int iSize);
//     static bool Append (const char* acFilename, char* acBuffer, int iSize);

    // Buffer read and write, file read and write, for character data.  The
    // endianness is irrelevant.
//     static int Read1 (const char* acBuffer, int iQuantity, void* pvData);
//     static int Write1 (char* acBuffer, int iQuantity, const void* pvData);
//     static int Read1 (FILE* pkFile, int iQuantity, void* pvData);
//     static int Write1 (FILE* pkFile, int iQuantity, const void* pvData);

    // Buffer read and write, file read and write.  The operations store the
    // results in little-endian order.  The return value is the number of
    // bytes read or written.  The function name suffix indicates the number
    // of bytes transferred per item.
//     static int Read2le (const char* acBuffer, int iQuantity, void* pvData);
//     static int Read4le (const char* acBuffer, int iQuantity, void* pvData);
//     static int Read8le (const char* acBuffer, int iQuantity, void* pvData);
//     static int Write2le (char* acBuffer, int iQuantity, const void* pvData);
//     static int Write4le (char* acBuffer, int iQuantity, const void* pvData);
//     static int Write8le (char* acBuffer, int iQuantity, const void* pvData);
//     static int Read2le (FILE* pkFile, int iQuantity, void* pvData);
//     static int Read4le (FILE* pkFile, int iQuantity, void* pvData);
//     static int Read8le (FILE* pkFile, int iQuantity, void* pvData);
//     static int Write2le (FILE* pkFile, int iQuantity, const void* pvData);
//     static int Write4le (FILE* pkFile, int iQuantity, const void* pvData);
//     static int Write8le (FILE* pkFile, int iQuantity, const void* pvData);

    // Buffer read and write, file read and write.  The operations store the
    // results in big-endian order.  The return value is the number of
    // bytes read or written.  The function name suffix indicates the number
    // of bytes transferred per item.
//     static int Read2be (const char* acBuffer, int iQuantity, void* pvData);
//     static int Read4be (const char* acBuffer, int iQuantity, void* pvData);
//     static int Read8be (const char* acBuffer, int iQuantity, void* pvData);
//     static int Write2be (char* acBuffer, int iQuantity, const void* pvData);
//     static int Write4be (char* acBuffer, int iQuantity, const void* pvData);
//     static int Write8be (char* acBuffer, int iQuantity, const void* pvData);
//     static int Read2be (FILE* pkFile, int iQuantity, void* pvData);
//     static int Read4be (FILE* pkFile, int iQuantity, void* pvData);
//     static int Read8be (FILE* pkFile, int iQuantity, void* pvData);
//     static int Write2be (FILE* pkFile, int iQuantity, const void* pvData);
//     static int Write4be (FILE* pkFile, int iQuantity, const void* pvData);
//     static int Write8be (FILE* pkFile, int iQuantity, const void* pvData);

    // This is needed on the Macintosh because of its complicated application
    // structure.  In particular, this function is used in Xcode projects and
    // ignores the directory entry, but assumes that the data files required
    // by an application are added to the Resources folder of the projects.
    // The other platforms concatenate the directory and filename, the result
    // stored in class-static memory (so be careful with threads).
//     static const char* GetPath (const char* acDirectory,
//         const char* acFilename);

    // Creation of colors, hides endianness.
    static unsigned int MakeRGB (unsigned char ucR, unsigned char ucG,
        unsigned char ucB);
    static unsigned int MakeRGBA (unsigned char ucR, unsigned char ucG,
        unsigned char ucB, unsigned char ucA);

    // Wrappers for standard I/O functions to support security enhancements
    // related to buffer overruns.  TO DO:  For now these support MSVC8.0
    // and fall back to the older standard I/O functions on other platforms.
    // Implementations may be provided for those other platforms to adhere
    // to the destination buffer size specification.
//    static FILE* Fopen (const char* acFilename, const char* acMode);
//    static int Fprintf (FILE* pkFile, const char* acFormat, ...);
//    static int Fclose (FILE* pkFile);
    static void* Memcpy (void* pvDst, size_t uiDstSize, const void* pvSrc,
        size_t uiSrcSize);
    static int Sprintf (char* acDst, size_t uiDstSize, const char* acFormat,
        ...);
    static char* Strcpy (char* acDst, size_t uiDstSize, const char* acSrc);
    static char* Strcat (char* acDst, size_t uiDstSize, const char* acSrc);
    static char* Strncpy (char* acDst, size_t uiDstSize, const char* acSrc,
        size_t uiSrcSize);
    static char* Strtok (char* acToken, const char* acDelimiters,
        char*& racNextToken);

private:
    enum { SYSTEM_MAX_PATH = 1024 };
    static char ms_acPath[SYSTEM_MAX_PATH];
};
}
#include "WgFixed.h"

#include "WgTArray.h"
#include "WgTHashTable.h"
#include "WgTList.h"
#include "WgTStack.h"
#include "WgString.h"

#endif
