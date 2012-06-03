///////////////////////////////////////////////////////////
//                                                       //
//                    WgNameID.h                         //
//                                                       //
//  - Interface for Name ID class                        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
#define WG3D_DECLARE_NAME_ID \
public: \
    virtual Object* GetObjectByName (const String& rkName); \
    virtual void GetAllObjectsByName (const String& rkName, \
        TArray<Object*>& rkObjects); \
    virtual Object* GetObjectByID (unsigned int uiID)
//----------------------------------------------------------------------------
#define WG3D_IMPLEMENT_DEFAULT_NAME_ID(classname,baseclassname) \
Object* classname::GetObjectByName (const String& rkName) \
{ \
    return baseclassname::GetObjectByName(rkName); \
} \
\
void classname::GetAllObjectsByName (const String& rkName, \
    TArray<Object*>& rkObjects) \
{ \
    baseclassname::GetAllObjectsByName(rkName,rkObjects); \
} \
\
Object* classname::GetObjectByID (unsigned int uiID) \
{ \
    return baseclassname::GetObjectByID(uiID); \
}
//----------------------------------------------------------------------------

