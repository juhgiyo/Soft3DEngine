///////////////////////////////////////////////////////////
//                                                       //
//                    WgTHashTable.h                     //
//                                                       //
//  - Interface for Generic Hash Table class             //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_THASHTABLE_H__
#define __WG_THASHTABLE_H__


#include "WgFoundationLIB.h"

// The class TKEY is either native data or is class data that has the
// following member functions:
//   TKEY::TKEY ()
//   TKEY& TKEY::operator= (const TKEY&)
//   bool TKEY::operator== (const TKEY&) const
//   bool TKEY::operator!= (const TKEY&) const
//   TKEY::operator unsigned int () const
// The implicit conversion to unsigned int is used to select a hash table
// index for the T object.  The return value need not be within the range of
// hash table indices.  THashTable will use modular arithmetic to make this
// happen.
//
// The class TVALUE is either native data or is class data that has the
// following member functions:
//   TVALUE::TVALUE ()
//   TVALUE& TVALUE::operator= (const TVALUE&)

#include "WgSystem.h"

namespace WGSoft3D
{

template <class TKEY, class TVALUE>
class THashTable
{
public:
    // construction and destruction
    THashTable (int iTableSize);
    ~THashTable ();

    // element access
    int GetQuantity () const;

    // insert a key-value pair into the hash table
    bool Insert (const TKEY& rtKey, const TVALUE& rtValue);

    // search for a key and returns it value (null, if key does not exist)
    TVALUE* Find (const TKEY& rtKey) const;

    // remove key-value pairs from the hash table
    bool Remove (const TKEY& rtKey);
    void RemoveAll ();

    // linear traversal of table
    TVALUE* GetFirst (TKEY* ptKey) const;
    TVALUE* GetNext (TKEY* ptKey) const;

    // user-specified key-to-index construction
    int (*UserHashFunction)(const TKEY&);

private:
    class HashItem
    {
    public:
        TKEY m_tKey;
        TVALUE m_tValue;
        HashItem* m_pkNext;
    };

    // Default key-to-index construction (override by user-specified when
    // requested).
    int HashFunction (const TKEY& rtKey) const;

    // hash table
    int m_iTableSize;
    int m_iQuantity;
    HashItem** m_apkTable;

    // iterator for traversal
    mutable int m_iIndex;
    mutable HashItem* m_pkItem;
};

#include "WgTHashTable.inl"

}

#endif
