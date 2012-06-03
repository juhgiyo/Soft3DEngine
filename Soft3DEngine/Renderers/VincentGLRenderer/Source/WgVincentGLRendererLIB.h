///////////////////////////////////////////////////////////
//                                                       //
//                    WgVincentGLRendererLIB.h           //
//                                                       //
//  - Interface for VincentGL Rendering Library class    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_VINCENTGLRENDERERLIB_H__
#define __WG_VINCENTGLRENDERERLIB_H__

// For the DLL library.
#ifdef WG3D_RENDERER_DLL_EXPORT
#define WG3D_RENDERER_ITEM __declspec(dllexport)

// For a client of the DLL library.
#else
#ifdef WG3D_RENDERER_DLL_IMPORT
#define WG3D_RENDERER_ITEM __declspec(dllimport)

// For the static library.
#else
#define WG3D_RENDERER_ITEM

#endif
#endif
#endif

