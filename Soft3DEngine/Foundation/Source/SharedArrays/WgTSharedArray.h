///////////////////////////////////////////////////////////
//                                                       //
//                    WgTSharedArray.h                   //
//                                                       //
//  - Interface for Generic Shared Array Class           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_TSHAREDARRAY_H__
#define __WG_TSHAREDARRAY_H__

#include "WgFoundationLIB.h"
#include "WgObject.h"

namespace WGSoft3D
{

template <class T>
class TSharedArray : public Object
{
    WG3D_DECLARE_TEMPLATE_RTTI;
    WG3D_DECLARE_NAME_ID;

public:
    TSharedArray (int iQuantity = 0, T* atArray = 0, bool bRequiredDelete=true);
    TSharedArray (const TSharedArray& rkShared);
    virtual ~TSharedArray ();

    TSharedArray& operator= (const TSharedArray& rkShared);

    int GetQuantity () const;
    T* GetData () const;
    operator const T* () const;
    operator T* ();
    const T& operator[] (int i) const;
    T& operator[] (int i);

    // This will not cause a reallocation of the array.  The idea is to
    // allow only some of the data to be considered valid.  The caller is
    // responsible for remembering the total quantity that was passed to the
    // constructor.
    void SetActiveQuantity (int iActiveQuantity);

	void DeleteRawData();
protected:
    int m_iQuantity;
    T* m_atArray;
	bool m_bRequireDelete;
};

#include "WgTSharedArray.inl"

}

#endif

