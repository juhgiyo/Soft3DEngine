///////////////////////////////////////////////////////////
//                                                       //
//                    WgSmartPointer.h                   //
//                                                       //
//  - Interface for Smart Pointer class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#ifndef __WG_SMARTPOINTER_H__
#define __WG_SMARTPOINTER_H__

#include "WgFoundationLIB.h"
#include "WgSystem.h"

namespace WGSoft3D
{

template <class T>
class Pointer
{
public:
    // construction and destruction
    Pointer (T* pkObject = 0);
    Pointer (const Pointer& rkPointer);
    ~Pointer ();

    // implicit conversions
    operator T* () const;
    T& operator* () const;
    T* operator-> () const;

    // assignment
    Pointer& operator= (T* pkObject);
    Pointer& operator= (const Pointer& rkReference);

    // comparisons
    bool operator== (T* pkObject) const;
    bool operator!= (T* pkObject) const;
    bool operator== (const Pointer& rkReference) const;
    bool operator!= (const Pointer& rkReference) const;

protected:
    // the shared object
    T* m_pkObject;
};

#include "WgSmartPointer.inl"

}

#endif

