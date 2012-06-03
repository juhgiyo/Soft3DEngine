///////////////////////////////////////////////////////////
//                                                       //
//              WgTCachedArray.h                         //
//                                                       //
//  - Interface for Generic Cached Array class           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.08                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_TCACHEDARRAY_H__
#define __WG_TCACHEDARRAY_H__

#include "WgFoundationLIB.h"
#include "WgTSharedArray.h"
#include "WgBindInfo.h"
#include "WgRenderer.h"

namespace WGSoft3D
{

template <class T>
class TCachedArray : public TSharedArray<T>
{
    WG3D_DECLARE_TEMPLATE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    TCachedArray (int iQuantity = 0, T* atArray = 0,bool bRequireDelete=true);
    virtual ~TCachedArray ();

private:
 //   using TSharedArray<T>::FACTORY_MAP_SIZE;
 //   using TSharedArray<T>::ms_pkFactory;

    // prevent these from being called
    TCachedArray (const TCachedArray& rkCArray);
    TCachedArray& operator= (const TCachedArray& rkCArray);

// internal use
public:
    // store renderer-specific information for binding/unbinding arrays
    BindInfoArray BIArray;
};

#include "WgTCachedArray.inl"

}

#endif

