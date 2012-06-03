///////////////////////////////////////////////////////////
//                                                       //
//                    WgScreenPolygon.cpp                //
//                                                       //
//  - Implementation for Screen Polygon class            //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgScreenPolygon.h"
#include "WgRenderer.h"
#include "WgZBufferState.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,ScreenPolygon,TriMesh);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(ScreenPolygon,TriMesh);

//----------------------------------------------------------------------------
ScreenPolygon::ScreenPolygon (int iVQuantity, Vector2x* akVertex,
    bool bForeground)
    :
    TriMesh(
        WG_NEW Vector3xArray(iVQuantity,WG_NEW Vector3x[iVQuantity]),
        WG_NEW ShortArray(3*(iVQuantity-2),WG_NEW short[3*(iVQuantity-2)]),
        false)
{
    // assert:  The vertices form a convex polygon and are listed in
    // counterclockwise order.
    assert(iVQuantity >= 3 && akVertex);

    m_akVertex = akVertex;
    m_bForeground = bForeground;

    // construct the 3D vertices
    Vector3x* akSVertex = Vertices->GetData();
    for (int i = 0; i < iVQuantity; i++)
    {
        akSVertex[i].X() = m_akVertex[i].X();
        akSVertex[i].Y() = m_akVertex[i].Y();
        akSVertex[i].Z() = (m_bForeground ? FIXED_ZERO : FIXED_ONE);
    }

    // represent the screen polygon as a triangle fan
    int iTQuantity = iVQuantity - 2;
    short* aiIndex = Indices->GetData();
    for (short i0 = 1, i1 = 2, j = 0; i0 <= iTQuantity; i0++, i1++)
    {
        aiIndex[j++] = 0;
        aiIndex[j++] = i0;
        aiIndex[j++] = i1;
    }

    // disable z-buffering
    ZBufferState* pkZS = WG_NEW ZBufferState;
    pkZS->Enabled = false;
    pkZS->Writable = false;
    SetGlobalState(pkZS);
    UpdateRS();
}
//----------------------------------------------------------------------------
ScreenPolygon::ScreenPolygon ()
{
    m_akVertex = 0;
    m_bForeground = false;
}
//----------------------------------------------------------------------------
ScreenPolygon::~ScreenPolygon ()
{
    WG_DELETE[] m_akVertex;
}
//----------------------------------------------------------------------------
void ScreenPolygon::SetVertex (int i, const Vector2x& rkV)
{
    assert(0 <= i && i < Vertices->GetQuantity());
    m_akVertex[i] = rkV;

    Vector3x* akSVertex = Vertices->GetData();
    akSVertex[i].X() = rkV.X();
    akSVertex[i].Y() = rkV.Y();
}
//----------------------------------------------------------------------------
