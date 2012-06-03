///////////////////////////////////////////////////////////
//                                                       //
//                    WgTSharedArry.inl                  //
//                                                       //
//  - Inlines for Generic Shared Array class             //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template <class T>
TSharedArray<T>::TSharedArray (int iQuantity, T* atArray, bool bRequiredDelete)
{
    m_iQuantity = iQuantity;
    m_atArray = atArray;
	m_bRequireDelete=bRequiredDelete;
}
//----------------------------------------------------------------------------
template <class T>
TSharedArray<T>::TSharedArray (const TSharedArray& rkShared)
{
    m_atArray = 0;
    *this = rkShared;
}
//----------------------------------------------------------------------------
template <class T>
TSharedArray<T>::~TSharedArray ()
{
	if(m_bRequireDelete && m_atArray)	
	    WG_DELETE[] m_atArray;
}
//----------------------------------------------------------------------------
template <class T>
TSharedArray<T>& TSharedArray<T>::operator= (const TSharedArray& rkShared)
{
	if(m_bRequireDelete)
		WG_DELETE[] m_atArray;
    m_iQuantity = rkShared.m_iQuantity;
    if (rkShared.m_atArray)
    {
		if(m_bRequireDelete)
		{
			m_atArray = WG_NEW T[m_iQuantity];
			for (int i = 0; i < m_iQuantity; i++)
			{
				m_atArray[i] = rkShared.m_atArray[i];
			}
		}
		else
		{
			m_atArray=rkShared.m_atArray;
		}
		m_bRequireDelete=rkShared.m_bRequireDelete;
		
    }
    else
    {
        m_atArray = 0;
    }
    return *this;
}
//----------------------------------------------------------------------------
template <class T>
int TSharedArray<T>::GetQuantity () const
{
    return m_iQuantity;
}
//----------------------------------------------------------------------------
template <class T>
T* TSharedArray<T>::GetData () const
{
    return m_atArray;
}
template <class T>
void TSharedArray<T>::DeleteRawData()
{
	if(m_bRequireDelete && m_atArray)	
		WG_DELETE[] m_atArray;
	m_atArray=NULL;
}
//----------------------------------------------------------------------------
template <class T>
TSharedArray<T>::operator const T* () const
{
    return m_atArray;
}
//----------------------------------------------------------------------------
template <class T>
TSharedArray<T>::operator T* ()
{
    return m_atArray;
}
//----------------------------------------------------------------------------
template <class T>
const T& TSharedArray<T>::operator[] (int i) const
{
    assert(0 <= i && i < m_iQuantity);
    return m_atArray[i];
}
//----------------------------------------------------------------------------
template <class T>
T& TSharedArray<T>::operator[] (int i)
{
    assert(0 <= i && i < m_iQuantity);
    return m_atArray[i];
}
//----------------------------------------------------------------------------
template <class T>
void TSharedArray<T>::SetActiveQuantity (int iActiveQuantity)
{
    assert(iActiveQuantity >= 0);
    m_iQuantity = iActiveQuantity;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
template <class T>
Object* TSharedArray<T>::GetObjectByName (const String& rkName)
{
    return Object::GetObjectByName(rkName);
}
//----------------------------------------------------------------------------
template <class T>
void TSharedArray<T>::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    Object::GetAllObjectsByName(rkName,rkObjects);
}
//----------------------------------------------------------------------------
template <class T>
Object* TSharedArray<T>::GetObjectByID (unsigned int uiID)
{
    return Object::GetObjectByID(uiID);
}
//----------------------------------------------------------------------------
