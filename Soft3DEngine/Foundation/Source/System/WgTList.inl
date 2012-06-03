///////////////////////////////////////////////////////////
//                                                       //
//                    WgTList.inl                        //
//                                                       //
//  - Inlines for Generic List class                     //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
template <class T>
TList<T>::TList ()
{
    m_pkNext = 0;
}
//----------------------------------------------------------------------------
template <class T>
TList<T>::TList (const T& rtItem, TList* pkNext)
    :
    m_tItem(rtItem)
{
    m_pkNext = pkNext;
}
//----------------------------------------------------------------------------
template <class T>
TList<T>::~TList ()
{
}
//----------------------------------------------------------------------------
template <class T>
void TList<T>::SetItem (const T& rtItem)
{
    m_tItem = rtItem;
}
//----------------------------------------------------------------------------
template <class T>
T& TList<T>::Item ()
{
    return m_tItem;
}
//----------------------------------------------------------------------------
template <class T>
const T& TList<T>::GetItem () const
{
    return m_tItem;
}
//----------------------------------------------------------------------------
template <class T>
void TList<T>::SetNext (TList* pkNext)
{
    m_pkNext = pkNext;
}
//----------------------------------------------------------------------------
template <class T>
TList<T>*& TList<T>::Next ()
{
    return m_pkNext;
}
//----------------------------------------------------------------------------
template <class T>
const TList<T>* TList<T>::GetNext () const
{
    return m_pkNext;
}
//----------------------------------------------------------------------------
template <class T>
int TList<T>::GetQuantity () const
{
    int iQuantity = 0;
    for (const TList<T>* pkIter = this; pkIter; pkIter = pkIter->m_pkNext)
    {
        iQuantity++;
    }
    return iQuantity;
}
//----------------------------------------------------------------------------

