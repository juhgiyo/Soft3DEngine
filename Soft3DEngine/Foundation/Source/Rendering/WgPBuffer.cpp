///////////////////////////////////////////////////////////
//                                                       //
//                    WgPBuffer.cpp                      //
//                                                       //
//  - Implementation for PBuffer class                   //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#include "WgFoundationPCH.h"
#include "WgPBuffer.h"
#include "WgRenderer.h"
#include "WgTexture.h"
using namespace WGSoft3D;

PBuffer::Creator PBuffer::ms_oCreate = 0;
PBuffer::Destroyer PBuffer::ms_oDestroy = 0;

//----------------------------------------------------------------------------
PBuffer* PBuffer::Create (const BufferParams& rkBufferParams, int iWidth,
    int iHeight, Renderer* pkRenderer)
{
    return ms_oCreate(rkBufferParams,iWidth,iHeight,pkRenderer);
}
//----------------------------------------------------------------------------
void PBuffer::Destroy (PBuffer* pkBuffer)
{
    ms_oDestroy(pkBuffer);
}
//----------------------------------------------------------------------------
PBuffer::PBuffer (const BufferParams& rkBufferParams, int iWidth, int iHeight,
    Renderer* pkRenderer)
    :
    m_kBufferParams(rkBufferParams)
{
    m_pkRenderer = pkRenderer;
    m_pkTarget = pkRenderer->GetTarget();
    m_iWidth = iWidth;
    m_iHeight = iHeight;
}
//----------------------------------------------------------------------------
PBuffer::~PBuffer ()
{
}
//----------------------------------------------------------------------------
const BufferParams& PBuffer::GetBufferParams () const
{
    return m_kBufferParams;
}
//----------------------------------------------------------------------------
void PBuffer::SetRenderer (Renderer* pkRenderer)
{
    m_pkRenderer = pkRenderer;
}
//----------------------------------------------------------------------------
Renderer* PBuffer::GetRenderer ()
{
    return m_pkRenderer;
}
//----------------------------------------------------------------------------
Texture* PBuffer::GetTarget ()
{
    return m_pkTarget;
}
//----------------------------------------------------------------------------
int PBuffer::GetWidth () const
{
    return m_iWidth;
}
//----------------------------------------------------------------------------
int PBuffer::GetHeight () const
{
    return m_iHeight;
}
//----------------------------------------------------------------------------
void PBuffer::CopyToTarget (bool bRelease) const
{
    if (!m_pkTarget)
    {
        return;
    }

    // Make certain that the image data exists so that we can copy the
    // pbuffer data to it.
    Image* pkImage = m_pkTarget->GetImage();
    unsigned char* aucData;
    if (pkImage)
    {
        aucData = pkImage->GetData();
    }
    else
    {
        aucData = WG_NEW unsigned char[4*m_iWidth*m_iHeight];
        pkImage = WG_NEW Image(Image::IT_RGBA8888,m_iWidth,m_iHeight,
            aucData);
        m_pkTarget->SetImage(pkImage);
    }

    // Allow the renderer to free up the VRAM associated with the previous
    // texture image.
    if (bRelease)
    {
        m_pkRenderer->ReleaseTexture(m_pkTarget);
    }

    // NOTE:  The derived classes must provide the final step of copying the
    // pbuffer data to the image.
}
//----------------------------------------------------------------------------

