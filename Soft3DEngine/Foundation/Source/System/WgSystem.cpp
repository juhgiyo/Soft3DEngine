///////////////////////////////////////////////////////////
//                                                       //
//                    WgSystem.cpp                       //
//                                                       //
//  - Implementation for System class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#include "WgFoundationPCH.h"
#include "WgSystem.h"
using namespace WGSoft3D;

// support for GetTime
#ifndef _WIN32_WCE
#include <sys/timeb.h>
#else //_WIN32_WCE
#include <time.h>
#endif //_WIN32_WCE

static long gs_lInitialSec = 0;
static long gs_lInitialUSec = 0;
static bool gs_bInitializedTime = false;

//----------------------------------------------------------------------------
unsigned int System::MakeRGB (unsigned char ucR, unsigned char ucG,
							  unsigned char ucB)
{
    return (ucR | (ucG << 8) | (ucB << 16) | (0xFF << 24));
}
//----------------------------------------------------------------------------
unsigned int System::MakeRGBA (unsigned char ucR, unsigned char ucG,
							   unsigned char ucB, unsigned char ucA)
{
    return (ucR | (ucG << 8) | (ucB << 16) | (ucA << 24));
}
//----------------------------------------------------------------------------
#ifndef _WIN32_WCE
double System::GetTime ()
{
	struct timeb kTB;
	
    if (!gs_bInitializedTime)
    {
        gs_bInitializedTime = true;
        ftime(&kTB);
        gs_lInitialSec = (long)kTB.time;
        gs_lInitialUSec = 1000*kTB.millitm;
    }
	
    ftime(&kTB);
    long lCurrentSec = (long)kTB.time;
    long lCurrentUSec = 1000*kTB.millitm;
    long lDeltaSec = lCurrentSec - gs_lInitialSec;
    long lDeltaUSec = lCurrentUSec -gs_lInitialUSec;
    if (lDeltaUSec < 0)
    {
        lDeltaUSec += 1000000;
        lDeltaSec--;
    }
	
    return 0.001*(double)(1000*lDeltaSec + lDeltaUSec/1000);
}
#endif //_WIN32_WCE
//----------------------------------------------------------------------------
void* System::Memcpy (void* pvDst, size_t uiDstSize, const void* pvSrc,
					  size_t uiSrcSize)
{
#ifdef WG3D_USING_VC80
    errno_t uiError = memcpy_s(pvDst,uiDstSize,pvSrc,uiSrcSize);
    if (uiError == 0)
    {
        return pvDst;
    }
    else
    {
        return 0;
    }
#else
    if (!pvDst || uiDstSize == 0 || !pvSrc || uiSrcSize == 0)
    {
        // Be consistent with the behavior of memcpy_s.
        return 0;
    }
	
    if (uiSrcSize > uiDstSize)
    {
        // The source memory is too large to copy to the destination.  To
        // be consistent with memcpy_s, return null as an indication that the
        // copy failed.
        return 0;
    }
    memcpy(pvDst,pvSrc,uiSrcSize);
    return pvDst;
#endif
}
//----------------------------------------------------------------------------
int System::Sprintf (char* acDst, size_t uiDstSize, const char* acFormat, ...)
{
    if (!acDst || uiDstSize == 0 || !acFormat)
    {
        return -1;
    }

    va_list acArgs;
    va_start(acArgs,acFormat);

#ifdef WG3D_USING_VC80
    int iNumWritten = vsprintf_s(acDst,uiDstSize,acFormat,acArgs);
#else
    int iNumWritten = vsprintf(acDst,acFormat,acArgs);
#endif
	
    va_end(acArgs);
    return iNumWritten;
}
//----------------------------------------------------------------------------
char* System::Strcpy (char* acDst, size_t uiDstSize, const char* acSrc)
{
#ifdef WG3D_USING_VC80
    errno_t uiError = strcpy_s(acDst,uiDstSize,acSrc);
    if (uiError == 0)
    {
        return acDst;
    }
    else
    {
        return 0;
    }
#else
    if (!acDst || uiDstSize == 0 || !acSrc)
    {
        // Be consistent with the behavior of strcpy_s.
        return 0;
    }

    size_t uiSrcLen = strlen(acSrc);
    if (uiSrcLen + 1 > uiDstSize)
    {
        // The source string is too large to copy to the destination.  To
        // be consistent with strcpy_s, return null as an indication that the
        // copy failed.
        return 0;
    }
    strncpy(acDst,acSrc,uiSrcLen);
    acDst[uiSrcLen] = 0;
    return acDst;
#endif
}
//----------------------------------------------------------------------------
char* System::Strcat (char* acDst, size_t uiDstSize, const char* acSrc)
{
#ifdef WG3D_USING_VC80
    errno_t uiError = strcat_s(acDst,uiDstSize,acSrc);
    if (uiError == 0)
    {
        return acDst;
    }
    else
    {
        return 0;
    }
#else
    if (!acDst || uiDstSize == 0 || !acSrc)
    {
        // Be consistent with the behavior of strcat_s.
        return 0;
    }
	
    size_t uiSrcLen = strlen(acSrc);
    size_t uiDstLen = strlen(acDst);
    size_t uiSumLen = uiSrcLen + uiDstLen;
    if (uiSumLen + 1 > uiDstSize)
    {
        // The source string is too large to append to the destination.  To
        // be consistent with strcat_s, return null as an indication that
        // the concatenation failed.
        return 0;
    }
    strncat(acDst,acSrc,uiSrcLen);
    acDst[uiSumLen] = 0;
    return acDst;
#endif
}
//----------------------------------------------------------------------------
char* System::Strncpy (char* acDst, size_t uiDstSize, const char* acSrc,
					   size_t uiSrcSize)
{
#ifdef WG3D_USING_VC80
    errno_t uiError = strncpy_s(acDst,uiDstSize,acSrc,uiSrcSize);
    if (uiError == 0)
    {
        return acDst;
    }
    else
    {
        return 0;
    }
#else
    if (!acDst || uiDstSize == 0 || !acSrc || uiSrcSize == 0)
    {
        // Be consistent with the behavior of strncpy_s.
        return 0;
    }
	
    if (uiSrcSize + 1 > uiDstSize)
    {
        // The source string is too large to copy to the destination.  To
        // be consistent with strncpy_s, return null as an indication that
        // the copy failed.
        return 0;
    }
    strncpy(acDst,acSrc,uiSrcSize);
    return acDst;
#endif
}
//----------------------------------------------------------------------------
char* System::Strtok (char* acToken, const char* acDelimiters,
					  char*& racNextToken)
{
#ifdef WG3D_USING_VC80
    return strtok_s(acToken,acDelimiters,&racNextToken);
#else
    (void)racNextToken;  // avoid warning in release mode
    return strtok(acToken,acDelimiters);
#endif
}
//----------------------------------------------------------------------------