///////////////////////////////////////////////////////////
//                                                       //
//                    WgMemory.h                         //
//                                                       //
//  - Interface for Custum Memory class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_MEMORY_H__
#define  __WG_MEMORY_H__

#ifndef WG_MEMORY_MANAGER

// Use the default memory manager.
#define WG_NEW new
#define WG_DELETE delete

#else //WG_MEMORY_MANAGER

// Use the default memory manager.
#define WG_NEW new
#define WG_DELETE delete
#endif //WG_MEMORY_MANAGER

#endif //__WG_MEMORY_H__