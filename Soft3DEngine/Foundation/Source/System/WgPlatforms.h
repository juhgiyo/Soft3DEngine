///////////////////////////////////////////////////////////
//                                                       //
//                    WgPlatforms.h                      //
//                                                       //
//  - Interface for Platforms class                      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_PLATFORMS_H__
#define __WG_PLATFORMS_H__

#include "WgFoundationLIB.h"


//----------------------------------------------------------------------------
// Microsoft Windows 2000/XP platform
//----------------------------------------------------------------------------
#if defined(_WIN32)

#if defined(_MSC_VER)

// Microsoft Visual C++ specific pragmas.  MSVC6 is version 12.00, MSVC7.0 is
// version 13.00, and MSVC7.1 is version 13.10.  MSVC8.0 is version 14.00.
#if _MSC_VER < 1300
#define WG3D_USING_VC6
#elif _MSC_VER < 1310
#define WG3D_USING_VC70
#elif _MSC_VER < 1400
#define WG3D_USING_VC71
#else
#define WG3D_USING_VC80
#endif

#if defined(WG3D_USING_VC6)

// Disable the warning "non dll-interface class FOO used as base for
// dll-interface class BAR."  These occur in the derivations
// class Binary2D : public ImageInt2D; class Binary3D : public ImageInt3D;
#pragma warning( disable : 4275 )

// Disable the warning about truncating the debug names to 255 characters.
// This warning shows up often with STL code in MSVC6, but not MSVC7.
#pragma warning( disable : 4786 )

// This warning is disabled because MSVC6 warns about not finding
// implementations for the pure virtual functions that occur in the template
// classes 'template <class Real>' when explicitly instantiating the classes.
// NOTE:  If you create your own template classes that will be explicitly
// instantiated, you should re-enable the warning to make sure that in fact
// all your member data and functions have been defined and implemented.
#pragma warning( disable : 4661 )

#endif

// The use of WG3D_ITEM to export an entire class generates warnings when
// member data and functions involving templates or inlines occur.  To avoid
// the warning, WG3D_ITEM can be applied only to those items that really need
// to be exported.  I do not want to go to that effort.
#pragma warning( disable : 4251 ) 

// Enable the warning: "loop control variable declared in the for-loop is
// used outside the for-loop scope.  The default level 3 warnings do not
// enable this (level 4 does), but should since allowing the outside scope
// is a Microsoft extension.
// #pragma warning( error : 4289 )

typedef __int64 Integer64;

#endif

// Specialized instantiation of static members in template classes before or
// after the class itself is instantiated is not a problem with Visual Studio
// .NET 2003 (VC 7.1), but VC 6 likes the specialized instantiation to occur
// after the class instantiation.
// #define WG3D_INSTANTIATE_BEFORE
//----------------------------------------------------------------------------
#endif
#endif