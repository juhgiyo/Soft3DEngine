///////////////////////////////////////////////////////////
//                                                       //
//                    WgObject.h                         //
//                                                       //
//  - Interface for Alpha State class                    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_OBJECT_H__
#define __WG_OBJECT_H__

#include "WgFoundationLIB.h"
#include "WgRtti.h"
#include "WgNameID.mcr"
#include "WgSmartPointer.h"
#include "WgStringTree.h"

namespace WGSoft3D
{

class Controller;

class WG3D_FOUNDATION_ITEM Object
{
// root class of object system
public:
    virtual ~Object ();
protected:
    Object ();

// run-time type information system
public:
    static const Rtti TYPE;
    virtual const Rtti& GetType () const;
    bool IsExactly (const Rtti& rkType) const;
    bool IsDerived (const Rtti& rkType) const;
    bool IsExactlyTypeOf (const Object* pkObject) const;
    bool IsDerivedTypeOf (const Object* pkObject) const;

// controller system
public:
    void SetController (Controller* pkController);
    int GetControllerQuantity () const;
    Controller* GetController (int i) const;
    void RemoveController (Controller* pkController);
    void RemoveAllControllers ();
    bool UpdateControllers (double dAppTime);
private:
    // controllers (Pointer used directly to avoid circular headers)
    TList<Pointer<Controller> >* m_pkControllerList;

// name-ID system
public:
    void SetName (const String& rkName);
    const String& GetName () const;
    unsigned int GetID () const;
    static unsigned int GetNextID ();
    virtual Object* GetObjectByName (const String& rkName);
    virtual void GetAllObjectsByName (const String& rkName,TArray<Object*>& rkObjects);
    virtual Object* GetObjectByID (unsigned int uiID);
private:
    String m_kName;
    unsigned int m_uiID;
    static unsigned int ms_uiNextID;

// smart pointer system
public:
    void IncrementReferences ();
    void DecrementReferences ();
    int GetReferences () const;
    static THashTable<unsigned int,Object*>* InUse;
private:
    int m_iReferences;
};

// static and dynamic type casting
template <class T> T* StaticCast (Object* pkObj);
template <class T> const T* StaticCast (const Object* pkObj);
template <class T> T* DynamicCast (Object* pkObj);
template <class T> const T* DynamicCast (const Object* pkObj);

typedef Pointer<Object> ObjectPtr;
#include "WgObject.inl"

}

#endif

