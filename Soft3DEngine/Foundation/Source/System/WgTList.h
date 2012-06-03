///////////////////////////////////////////////////////////
//                                                       //
//                    WgTArray.h                         //
//                                                       //
//  - Interface for Generic List class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_TLIST_H__
#define __WG_TLIST_H__

#include "WgFoundationLIB.h"

// The class T is either native data or is class data that has the following
// member functions:
//   T::T ()
//   T::T (const T&);
//   T& T::operator= (const T&)

namespace WGSoft3D
{

template <class T>
class TList
{
public:
    // construction
    TList ();
    TList (const T& rtItem, TList* pkNext);
    ~TList ();

    // member access
    void SetItem (const T& rtItem);
    T& Item ();
    const T& GetItem () const;
    void SetNext (TList* pkNext);
    TList*& Next ();
    const TList* GetNext () const;

    // total number of nodes in the list, including this one
    int GetQuantity () const;

private:
    T m_tItem;
    TList* m_pkNext;
};

#include "WgTList.inl"

}

#endif

