// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved
//
// The Wild Magic Library (WM3) source code is supplied under the terms of
// the license agreement
//     http://www.geometrictools.com/License/WildMagic3License.pdf
// and may not be copied or disclosed except in accordance with the terms
// of that agreement.

#include "Wm3FoundationPCH.h"
#include "Wm3SkinController.h"
#include "Wm3Geometry.h"
#include "Wm3Node.h"
using namespace Wm3;

WM3_IMPLEMENT_RTTI(Wm3,SkinController,Controller);
WM3_IMPLEMENT_STREAM(SkinController);
WM3_IMPLEMENT_DEFAULT_NAME_ID(SkinController,Controller);

//----------------------------------------------------------------------------
SkinController::SkinController (int iVertexQuantity, int iBoneQuantity,
    Node** apkBones, float** aafWeight, Vector3f** aakOffset)
{
    m_iVertexQuantity = iVertexQuantity;
    m_iBoneQuantity = iBoneQuantity;
    m_apkBones = apkBones;
    m_aafWeight = aafWeight;
    m_aakOffset = aakOffset;
}
//----------------------------------------------------------------------------
SkinController::SkinController ()
{
    m_iVertexQuantity = 0;
    m_iBoneQuantity = 0;
    m_apkBones = 0;
    m_aafWeight = 0;
    m_aakOffset = 0;
}
//----------------------------------------------------------------------------
SkinController::~SkinController ()
{
    WM3_DELETE[] m_apkBones;
    Deallocate<float>(m_aafWeight);
    Deallocate<Vector3f>(m_aakOffset);
}
//----------------------------------------------------------------------------
bool SkinController::Update (double dAppTime)
{
    if (!Controller::Update(dAppTime))
    {
        return false;
    }

    // The skin vertices are calculated in the bone world coordinate system,
    // so the TriMesh world transform must be the identity.
    Geometry* pkGeom = StaticCast<Geometry>(m_pkObject);
    pkGeom->World = Transformation::IDENTITY;
    pkGeom->WorldIsCurrent = true;

    // compute the skin vertex locations
    assert(m_iVertexQuantity == pkGeom->Vertices->GetQuantity());
    Vector3f* akVertex = pkGeom->Vertices->GetData();
    for (int i = 0; i < m_iVertexQuantity; i++)
    {
        Vector3f kTmp = m_apkBones[0]->World.ApplyForward(m_aakOffset[i][0]);
        akVertex[i] = m_aafWeight[i][0]*kTmp;
        for (int j = 1; j < m_iBoneQuantity; j++)
        {
            if (m_aafWeight[i][j] != 0.0f)
            {
                kTmp = m_apkBones[j]->World.ApplyForward(m_aakOffset[i][j]);
                akVertex[i] += m_aafWeight[i][j]*kTmp;
            }
        }
    }

    pkGeom->UpdateMS();
    return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SkinController::Load (Stream& rkStream, Stream::Link* pkLink)
{
    WM3_BEGIN_DEBUG_STREAM_LOAD;

    Controller::Load(rkStream,pkLink);

    // native data
    rkStream.Read(m_iVertexQuantity);
    rkStream.Read(m_iBoneQuantity);

    int i;

    Allocate<float>(m_iBoneQuantity,m_iVertexQuantity,m_aafWeight);
    for (i = 0; i < m_iVertexQuantity; i++)
    {
        rkStream.Read(m_iBoneQuantity,m_aafWeight[i]);
    }

    Allocate<Vector3f>(m_iBoneQuantity,m_iVertexQuantity,m_aakOffset);
    for (i = 0; i < m_iVertexQuantity; i++)
    {
        rkStream.Read(m_iBoneQuantity,m_aakOffset[i]);
    }

    // link data
    for (i = 0; i < m_iBoneQuantity; i++)
    {
        Object* pkObject;
        rkStream.Read(pkObject);  // m_apkBones[i]
        pkLink->Add(pkObject);
    }

    WM3_END_DEBUG_STREAM_LOAD(SkinController);
}
//----------------------------------------------------------------------------
void SkinController::Link (Stream& rkStream, Stream::Link* pkLink)
{
    Controller::Link(rkStream,pkLink);

    m_apkBones = WM3_NEW Node*[m_iBoneQuantity];
    for (int i = 0; i < m_iBoneQuantity; i++)
    {
        Object* pkLinkID = pkLink->GetLinkID();
        m_apkBones[i] = (Node*)rkStream.GetFromMap(pkLinkID);
    }

}
//----------------------------------------------------------------------------
bool SkinController::Register (Stream& rkStream) const
{
    if (!Controller::Register(rkStream))
    {
        return false;
    }

    for (int j = 0; j < m_iBoneQuantity; j++)
    {
        if (m_apkBones[j])
        {
            m_apkBones[j]->Register(rkStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void SkinController::Save (Stream& rkStream) const
{
    WM3_BEGIN_DEBUG_STREAM_SAVE;

    Controller::Save(rkStream);

    // native data
    rkStream.Write(m_iVertexQuantity);
    rkStream.Write(m_iBoneQuantity);

    int i;
    for (i = 0; i < m_iVertexQuantity; i++)
    {
        rkStream.Write(m_iBoneQuantity,m_aafWeight[i]);
    }

    for (i = 0; i < m_iVertexQuantity; i++)
    {
        rkStream.Write(m_iBoneQuantity,m_aakOffset[i]);
    }

    // link data
    rkStream.Write(m_iBoneQuantity,(Object**)m_apkBones);

    WM3_END_DEBUG_STREAM_SAVE(SkinController);
}
//----------------------------------------------------------------------------
StringTree* SkinController::SaveStrings (const char*)
{
    int iCQuantity = 2*m_iVertexQuantity + 2;
    StringTree* pkTree = WM3_NEW StringTree(3,iCQuantity);

    // strings
    pkTree->SetString(0,Format(&TYPE,GetName()));
    pkTree->SetString(1,Format("vertex quantity = ",m_iVertexQuantity));
    pkTree->SetString(2,Format("bone quantity = ",m_iBoneQuantity));

    // children
    pkTree->SetChild(0,Controller::SaveStrings());
    pkTree->SetChild(1,Format("bones",m_iBoneQuantity,m_apkBones));

    const size_t uiTitleSize = 256;
    char acTitle[uiTitleSize];
    int i;
    iCQuantity = 2;
    for (i = 0; i < m_iVertexQuantity; i++)
    {
        System::Sprintf(acTitle,uiTitleSize,"weights for vertex %d",i);
        pkTree->SetChild(iCQuantity++,Format(acTitle,m_iBoneQuantity,
            m_aafWeight[i]));
    }

    for (i = 0; i < m_iVertexQuantity; i++)
    {
        System::Sprintf(acTitle,uiTitleSize,"offsets for vertex %d",i);
        pkTree->SetChild(iCQuantity++,Format(acTitle,m_iBoneQuantity,
            m_aakOffset[i]));
    }

    return pkTree;
}
//----------------------------------------------------------------------------
int SkinController::GetMemoryUsed () const
{
    return sizeof(SkinController) - sizeof(Controller) +
        m_iBoneQuantity*sizeof(m_apkBones[0]) +
        m_iVertexQuantity*m_iBoneQuantity*sizeof(m_aafWeight[0][0]) +
        m_iVertexQuantity*m_iBoneQuantity*sizeof(m_aakOffset[0][0]);
}
//----------------------------------------------------------------------------
int SkinController::GetDiskUsed (const StreamVersion& rkVersion) const
{
    return Controller::GetDiskUsed(rkVersion) +
        sizeof(m_iVertexQuantity) +
        sizeof(m_iBoneQuantity) +
        m_iVertexQuantity*m_iBoneQuantity*sizeof(m_aafWeight[0][0]) +
        m_iVertexQuantity*m_iBoneQuantity*sizeof(m_aakOffset[0][0]) +
        m_iBoneQuantity*sizeof(m_apkBones[0]);
}
//----------------------------------------------------------------------------

