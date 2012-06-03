///////////////////////////////////////////////////////////
//                                                       //
//                    WgPlanarShadowEffect.cpp           //
//                                                       //
//  - Implementation for Planar Shadow Effect class      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgPlanarShadowEffect.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,PlanarShadowEffect,Effect);

//----------------------------------------------------------------------------
PlanarShadowEffect::PlanarShadowEffect (int iQuantity)
{
    Draw = &Renderer::DrawPlanarShadow;

    assert(iQuantity > 0);
    m_iQuantity = iQuantity;
    m_aspkPlane = WG_NEW TriMeshPtr[m_iQuantity];
    m_aspkProjector = WG_NEW LightPtr[m_iQuantity];
    m_akShadowColor = WG_NEW ColorRGBA[m_iQuantity];
}
//----------------------------------------------------------------------------
PlanarShadowEffect::PlanarShadowEffect ()
{
    Draw = &Renderer::DrawPlanarShadow;
    m_iQuantity = 0;
    m_aspkPlane = 0;
    m_aspkProjector = 0;
    m_akShadowColor = 0;
}
//----------------------------------------------------------------------------
PlanarShadowEffect::~PlanarShadowEffect ()
{
    WG_DELETE[] m_aspkPlane;
    WG_DELETE[] m_aspkProjector;
    WG_DELETE[] m_akShadowColor;
}
//----------------------------------------------------------------------------
Effect* PlanarShadowEffect::Clone ()
{
    PlanarShadowEffect* pkClone = WG_NEW PlanarShadowEffect(m_iQuantity);
    DoCloning(pkClone);
    return pkClone;
}
//----------------------------------------------------------------------------
void PlanarShadowEffect::DoCloning (Effect* pkClone)
{
    Effect::DoCloning(pkClone);

    PlanarShadowEffect* pkDClone = (PlanarShadowEffect*)pkClone;
    for (int i = 0; i < m_iQuantity; i++)
    {
        pkDClone->m_aspkPlane[i] = m_aspkPlane[i];
        pkDClone->m_aspkProjector[i] = m_aspkProjector[i];
        pkDClone->m_akShadowColor[i] = m_akShadowColor[i];
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* PlanarShadowEffect::GetObjectByName (const String& rkName)
{
    Object* pkFound = Effect::GetObjectByName(rkName);
    if (pkFound)
    {
        return pkFound;
    }

    int i;

    if (m_aspkPlane)
    {
        for (i = 0; i < m_iQuantity; i++)
        {
            if (m_aspkPlane[i])
            {
                pkFound = m_aspkPlane[i]->GetObjectByName(rkName);
                if (pkFound)
                {
                    return pkFound;
                }
            }
        }
    }

    if (m_aspkProjector)
    {
        for (i = 0; i < m_iQuantity; i++)
        {
            if (m_aspkProjector[i])
            {
                pkFound = m_aspkProjector[i]->GetObjectByName(rkName);
                if (pkFound)
                {
                    return pkFound;
                }
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void PlanarShadowEffect::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    Effect::GetAllObjectsByName(rkName,rkObjects);

    int i;

    if (m_aspkPlane)
    {
        for (i = 0; i < m_iQuantity; i++)
        {
            if (m_aspkPlane[i])
            {
                m_aspkPlane[i]->GetAllObjectsByName(rkName,rkObjects);
            }
        }
    }

    if (m_aspkProjector)
    {
        for (i = 0; i < m_iQuantity; i++)
        {
            if (m_aspkProjector[i])
            {
                m_aspkProjector[i]->GetAllObjectsByName(rkName,rkObjects);
            }
        }
    }
}
//----------------------------------------------------------------------------
Object* PlanarShadowEffect::GetObjectByID (unsigned int uiID)
{
    Object* pkFound = Effect::GetObjectByID(uiID);
    if (pkFound)
    {
        return pkFound;
    }

    int i;

    if (m_aspkPlane)
    {
        for (i = 0; i < m_iQuantity; i++)
        {
            if (m_aspkPlane[i])
            {
                pkFound = m_aspkPlane[i]->GetObjectByID(uiID);
                if (pkFound)
                {
                    return pkFound;
                }
            }
        }
    }

    if (m_aspkProjector)
    {
        for (i = 0; i < m_iQuantity; i++)
        {
            if (m_aspkProjector[i])
            {
                pkFound = m_aspkProjector[i]->GetObjectByID(uiID);
                if (pkFound)
                {
                    return pkFound;
                }
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
