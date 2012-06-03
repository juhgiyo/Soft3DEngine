///////////////////////////////////////////////////////////
//                                                       //
//                    WgPBuffer.h                        //
//                                                       //
//  - Interface for PBuffer class                        //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#ifndef __WG_PBUFFER_H__
#define __WG_PBUFFER_H__

#include "WgFoundationLIB.h"
#include "WgBufferParams.h"

namespace WGSoft3D
{

class Renderer;
class Texture;

class WG3D_FOUNDATION_ITEM PBuffer
{
public:
    // Abstract base class.  The PBuffer::Create and PBuffer::Destroy
    // functions form a factory.
    static PBuffer* Create (const BufferParams& rkBufferParams, int iWidth,
        int iHeight, Renderer* pkRenderer);
    static void Destroy (PBuffer* pkBuffer);

    PBuffer (const BufferParams& rkBufferParams, int iWidth, int iHeight,
        Renderer* pkRenderer);
    virtual ~PBuffer ();

    virtual void Enable () = 0;
    virtual void Disable () = 0;
    virtual void Bind () = 0;
    virtual void Release () = 0;
    virtual void CopyToTarget (bool bRelease) const;

    const BufferParams& GetBufferParams () const;
    void SetRenderer (Renderer* pkRenderer);
    Renderer* GetRenderer ();
    Texture* GetTarget ();
    int GetWidth () const;
    int GetHeight () const;

protected:
    BufferParams m_kBufferParams;
    Renderer* m_pkRenderer;
    Texture* m_pkTarget;
    int m_iWidth;
    int m_iHeight;

    // The pbuffer factory.  Each derived class implements a Creator and a
    // Destroyer and assigns the function pointers to the static data members
    // declared here.  Since only one derived class exists on a platform,
    // there is no chance of one derived class overwriting another's function
    // pointers.
    typedef PBuffer* (*Creator)(const BufferParams&, int, int, Renderer*);
    typedef void (*Destroyer)(PBuffer*);
    static Creator ms_oCreate;
    static Destroyer ms_oDestroy;
};

}

#endif

