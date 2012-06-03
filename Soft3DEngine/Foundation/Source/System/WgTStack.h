///////////////////////////////////////////////////////////
//                                                       //
//                    WgTStack.h                         //
//                                                       //
//  - Interface for Generic Stack class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
#ifndef __WG_TSTACK_H__
#define __WG_TSTACK_H__

#include "WgFoundationLIB.h"

// The class T is either native data or is class data that has the following
// member functions:
//   T::T ()
//   T::T (const T&);
//   T& T::operator= (const T&)

namespace WGSoft3D
{

template <class T>
class TStack
{
public:
    TStack (int iMaxQuantity = 64);
    ~TStack ();

    bool IsEmpty () const;
    bool IsFull () const;
    void Push (const T& rkItem);
    void Pop (T& rkItem);
    void Clear ();
    bool GetTop (T& rkItem) const;

    // for iteration over the stack elements
    int GetQuantity () const;
    const T* GetData () const;

private:
    int m_iMaxQuantity, m_iTop;
    T* m_atStack;
};

#include "WgTStack.inl"

}

#endif

