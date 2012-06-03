///////////////////////////////////////////////////////////
//                                                       //
//             WgTCachedArray.inl                        //
//                                                       //
//  - Inlines for Generic Cached Array class  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
template <class T>
TCachedArray<T>::TCachedArray (int iQuantity, T* atArray,bool bRequireDelete)
    :
    TSharedArray<T>(iQuantity,atArray,bRequireDelete),
    BIArray(1,1)
{
}
//----------------------------------------------------------------------------
template <class T>
TCachedArray<T>::TCachedArray (const TCachedArray&)
{
    // Copying of cached data is not allowed.
    assert(false);
}
//----------------------------------------------------------------------------
template <class T>
TCachedArray<T>::~TCachedArray ()
{
    // Inform all renderers using this array that it is being destroyed.
    // This allows the renderer to free up any associated resources.
    const TArray<BindInfo>& rkArray = BIArray.GetArray();
    for (int i = rkArray.GetQuantity()-1; i >= 0; i--)
    {
        rkArray[i].User->ReleaseArray(this);
    }
}
//----------------------------------------------------------------------------
template <class T>
TCachedArray<T>& TCachedArray<T>::operator= (const TCachedArray&)
{
    // Copying of cached data is not allowed.
    assert(false);
    return this;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
template <class T>
Object* TCachedArray<T>::GetObjectByName (const String& rkName)
{
    return TSharedArray<T>::GetObjectByName(rkName);
}
//----------------------------------------------------------------------------
template <class T>
void TCachedArray<T>::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    TSharedArray<T>::GetAllObjectsByName(rkName,rkObjects);
}
//----------------------------------------------------------------------------
template <class T>
Object* TCachedArray<T>::GetObjectByID (unsigned int uiID)
{
    return TSharedArray<T>::GetObjectByID(uiID);
}
//----------------------------------------------------------------------------
