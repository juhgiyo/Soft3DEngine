///////////////////////////////////////////////////////////
//                                                       //
//                    WgFoundationLIB.h                  //
//                                                       //
//  - Interface for Foundation Library class             //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG3D_FOUNDATIONLIB_H__
#define __WG3D_FOUNDATIONLIB_H__

// For the DLL library.
#ifdef WG3D_FOUNDATION_DLL_EXPORT
#define WG3D_FOUNDATION_ITEM __declspec(dllexport)

// For a client of the DLL library.
#else
#ifdef WG3D_FOUNDATION_DLL_IMPORT
#define WG3D_FOUNDATION_ITEM __declspec(dllimport)

// For the static library.
#else
#define WG3D_FOUNDATION_ITEM

#endif
#endif
#endif
