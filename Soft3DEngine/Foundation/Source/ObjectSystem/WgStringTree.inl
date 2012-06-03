///////////////////////////////////////////////////////////
//                                                       //
//                    WgStringTree.inl                   //
//                                                       //
//  - Inlines for String Tree class                      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline int StringTree::GetStringQuantity () const
{
    return m_kStrings.GetQuantity();
}
//----------------------------------------------------------------------------
inline char* StringTree::GetString (int i)
{
    if (0 <= i && i < m_kStrings.GetQuantity())
    {
        return m_kStrings[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
inline int StringTree::GetChildQuantity () const
{
    return m_kChildren.GetQuantity();
}
//----------------------------------------------------------------------------
inline StringTree* StringTree::GetChild (int i)
{
    if (0 <= i && i < m_kChildren.GetQuantity())
    {
        return m_kChildren[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
template <class T>
StringTree* Format (const char* acTitle, int iQuantity, const T* atValue)
{
    StringTree* pkTree = WG_NEW StringTree(1,1);
    pkTree->SetString(0,Format(acTitle));

    StringTree* pkSubtree = WG_NEW StringTree(iQuantity+1,0);
    pkSubtree->SetString(0,Format("quantity =",iQuantity));
    for (int i = 0; i < iQuantity; i++)
    {
        const size_t uiSize = 256;
        char acPrefix[uiSize];
        System::Sprintf(acPrefix,uiSize,"%d: ",i);
        T tValue = atValue[i];
        pkSubtree->SetString(i+1,Format(acPrefix,tValue));
    }

    pkTree->SetChild(0,pkSubtree);

    return pkTree;
}
//----------------------------------------------------------------------------

