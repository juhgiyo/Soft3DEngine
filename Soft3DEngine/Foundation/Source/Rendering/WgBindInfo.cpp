///////////////////////////////////////////////////////////
//                                                       //
//                    WgBindInfo.cpp                     //
//                                                       //
//  - Implementation for Bind Info class                 //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgBindInfo.h"
using namespace WGSoft3D;

//----------------------------------------------------------------------------
BindInfo::BindInfo ()
{
    User = 0;
    memset(ID,0,8*sizeof(char));
}
//----------------------------------------------------------------------------
BindInfoArray::BindInfoArray (int iQuantity, int iGrowBy)
    :
    m_kBind(iQuantity,iGrowBy)
{
}
//----------------------------------------------------------------------------
const TArray<BindInfo>& BindInfoArray::GetArray () const
{
    return m_kBind;
}
//----------------------------------------------------------------------------
void BindInfoArray::Bind (Renderer* pkUser, int iSize, const void* pvID)
{
    assert(1 <= iSize && iSize <= 8);

    BindInfo kInfo;
    kInfo.User = pkUser;
    size_t uiDstSize = 8*sizeof(char);
    size_t uiSrcSize = iSize*sizeof(char);
    System::Memcpy(kInfo.ID,uiDstSize,pvID,uiSrcSize);
    m_kBind.Append(kInfo);
}
//----------------------------------------------------------------------------
void BindInfoArray::Unbind (Renderer* pkUser)
{
    int i;
    for (i = 0; i < m_kBind.GetQuantity(); i++)
    {
        if (m_kBind[i].User == pkUser)
        {
            m_kBind.Remove(i);
            break;
        }
    }
}
//----------------------------------------------------------------------------
void BindInfoArray::GetID (Renderer* pkUser, int iSize, void* pvID)
{
    assert(1 <= iSize && iSize <= 8);

    int i;
    for (i = 0; i < m_kBind.GetQuantity(); i++)
    {
        if (m_kBind[i].User == pkUser)
        {
            size_t uiDstSize = 8*sizeof(char);
            size_t uiSrcSize = iSize*sizeof(char);
            System::Memcpy(pvID,uiDstSize,m_kBind[i].ID,uiSrcSize);
            break;
        }
    }

    // The resource is not yet bound to the renderer.
    if (i == m_kBind.GetQuantity())
    {
        memset(pvID,0,iSize*sizeof(char));
    }
}
//----------------------------------------------------------------------------

