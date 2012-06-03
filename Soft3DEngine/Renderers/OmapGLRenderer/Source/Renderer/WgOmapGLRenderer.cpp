///////////////////////////////////////////////////////////
//                                                       //
//                    WgOmapGLRenderer.cpp               //
//                                                       //
//  - Implementation for OmapGLRenderer class            //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgOmapGLRendererPCH.h"
#include "WgOmapGLRenderer.h"
//#include "WgPBuffer.h"
#include "WgCamera.h"
#include "WgProjectedTextureEffect.h"
#include "WgVector4.h"
#include "WgCachedColorRGBAArray.h"
#include "WgCachedColorRGBArray.h"
#include "WgCachedShortArray.h"
#include "WgCachedVector2Array.h"
#include "WgCachedVector3Array.h"
using namespace WGSoft3D;

GLenum OmapGLRenderer::ms_aeObjectType[Geometry::GT_MAX_QUANTITY] =
{
    GL_POINTS,          // GT_POLYPOINT
    GL_LINES,           // GT_POLYLINE_SEGMENTS
    GL_LINE_STRIP,      // GT_POLYLINE_OPEN
    GL_LINE_LOOP,       // GT_POLYLINE_CLOSED
    GL_TRIANGLES,       // GT_TRIMESH
    GL_TRIANGLE_STRIP,  // GT_TRISTRIP
    GL_TRIANGLE_FAN     // GT_TRIFAN
};

GLenum OmapGLRenderer::ms_aeTextureCorrection[Texture::CM_QUANTITY] =
{
    GL_FASTEST,     // CM_AFFINE
    GL_NICEST       // CM_PERSPECTIVE
};

GLenum OmapGLRenderer::ms_aeTextureApply[Texture::AM_QUANTITY] =
{
    GL_REPLACE,
    GL_DECAL,
    GL_MODULATE,
    GL_BLEND,
    GL_ADD,
    GL_COMBINE
};

GLenum OmapGLRenderer::ms_aeTextureCombineFunc[Texture::ACF_QUANTITY] =
{
    GL_REPLACE,
    GL_MODULATE,
    GL_ADD,
    GL_ADD_SIGNED,
    GL_SUBTRACT,
    GL_INTERPOLATE,
    GL_DOT3_RGB,
    GL_DOT3_RGBA
};

GLenum OmapGLRenderer::ms_aeTextureCombineSrc[Texture::ACS_QUANTITY] = 
{
    GL_TEXTURE,
    GL_PRIMARY_COLOR,
    GL_CONSTANT,
    GL_PREVIOUS
};

GLenum OmapGLRenderer::ms_aeTextureCombineOperand[Texture::ACO_QUANTITY] =
{
    GL_SRC_COLOR,
    GL_ONE_MINUS_SRC_COLOR,
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA
};

GLint OmapGLRenderer::ms_aiTextureCombineScale[Texture::ACSC_QUANTITY] =
{
    1,
    2,
    4
};

GLenum OmapGLRenderer::ms_aeTextureFilter[Texture::FM_QUANTITY] =
{
    GL_NEAREST,
    GL_LINEAR
};

GLenum OmapGLRenderer::ms_aeTextureMipmap[Texture::MM_QUANTITY] =
{
    GL_NEAREST,
    GL_LINEAR,
    GL_NEAREST_MIPMAP_NEAREST,
    GL_NEAREST_MIPMAP_LINEAR,
    GL_LINEAR_MIPMAP_NEAREST,
    GL_LINEAR_MIPMAP_LINEAR
};

GLenum OmapGLRenderer::ms_aeImageComponents[Image::IT_QUANTITY] =
{
    GL_UNSIGNED_SHORT_4_4_4_4,
    GL_RGB,
    GL_UNSIGNED_SHORT_5_5_5_1,
    GL_RGBA,
	GL_UNSIGNED_SHORT_5_6_5
};

GLenum OmapGLRenderer::ms_aeImageFormats[Image::IT_QUANTITY] =
{
    GL_RGBA,
    GL_RGB,
    GL_RGBA,
    GL_RGBA,
	GL_RGB
};

//----------------------------------------------------------------------------
OmapGLRenderer::OmapGLRenderer (const BufferParams& rkBufferParams,
    int iWidth, int iHeight)
    :
    Renderer(rkBufferParams,iWidth,iHeight),
    m_kDLInfo(4,4)
{
    ms_eType = RT_OPENGL;

    // initial world matrix is zero (will always be set properly later)
    memset(m_afWorldMatrix,0,16*sizeof(fixed));
	InitializeState();
}
//----------------------------------------------------------------------------
OmapGLRenderer::~OmapGLRenderer ()
{
}
//----------------------------------------------------------------------------
void OmapGLRenderer::InitializeState ()
{
    // initialize global render state to default settings
	GlobalState::SetGlobalStates();
    SetGlobalState(GlobalState::Default);

    // vertices always exist
    glEnableClientState(GL_VERTEX_ARRAY);

    // colors disabled, current color is WHITE
    glDisableClientState(GL_COLOR_ARRAY);
    glColor4x(ColorRGBA::WHITE.R().value,ColorRGBA::WHITE.G().value,ColorRGBA::WHITE.B().value,ColorRGBA::WHITE.A().value);

    // normals disabled
    glDisableClientState(GL_NORMAL_ARRAY);

    // Get number of supported texture units.  Initially disable them.
    GLint iMaxTextures;
    int i;

    glGetIntegerv(GL_MAX_TEXTURE_UNITS,&iMaxTextures);
    m_iMaxTextures = (int)iMaxTextures;
    for (i = 0; i < m_iMaxTextures; i++)
    {
        glClientActiveTexture(GL_TEXTURE0+i);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
        glActiveTexture(GL_TEXTURE0+i);
        glDisable(GL_TEXTURE_2D);
    }
	if(!m_iMaxTextures)
	{
		m_iMaxTextures=1;
	}

    // set up light model
    m_iMaxLights = 8;  // OpenGL limits the number of lights to eight
    glLightModelxv(GL_LIGHT_MODEL_AMBIENT,(const GLfixed*)(const fixed*)ColorRGBA::BLACK);
    glLightModelx(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
    glDisable(GL_LIGHTING);

     // get stencil buffer size
     GLint iBits = 0;
     glGetIntegerv((GLenum)GL_STENCIL_BITS,&iBits);
     m_iMaxStencilIndices = (iBits > 0 ? (1 << iBits) : 0);

	 glDepthRangex(FIXED_ZERO,FIXED_ONE);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::Activate ()
{
    SetBackgroundColor(m_kBackgroundColor);
    OnViewPortChange();
    OnFrustumChange ();
    if (m_pkCamera)
    {
        OnFrameChange ();
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::SetBackgroundColor (const ColorRGBA& rkColor)
{
    Renderer::SetBackgroundColor(rkColor);
    glClearColorx(rkColor[0].value,rkColor[1].value,rkColor[2].value,rkColor[3].value);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ClearBackBuffer ()
{
   // glEnable(GL_SCISSOR_TEST);
    //glScissor(0,0,m_iWidth,m_iHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    //glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ClearZBuffer ()
{
    //glEnable(GL_SCISSOR_TEST);
    //glScissor(0,0,m_iWidth,m_iHeight);
    //glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
	glClearDepthx(FIXED_ONE);
    glClear(GL_DEPTH_BUFFER_BIT);
    //glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ClearStencilBuffer ()
{
    //glEnable(GL_SCISSOR_TEST);
    //glScissor(0,0,m_iWidth,m_iHeight);
    glStencilMask(~0);
    glClear(GL_STENCIL_BUFFER_BIT);
    //glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ClearBuffers ()
{
    //glEnable(GL_SCISSOR_TEST);
    //glScissor(0,0,m_iWidth,m_iHeight);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
	glClearDepthx(FIXED_ONE);
    glStencilMask(~0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    //glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ClearBackBuffer (int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(iXPos,iYPos,iWidth,iHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ClearZBuffer (int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(iXPos,iYPos,iWidth,iHeight);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ClearStencilBuffer (int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(iXPos,iYPos,iWidth,iHeight);
    glStencilMask(~0);
    glClear(GL_STENCIL_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ClearBuffers (int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(iXPos,iYPos,iWidth,iHeight);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glStencilMask(~0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::SetWorldMatrix ()
{
    if (m_pkGeometry->World.IsRSMatrix())
    {
        const Matrix3x& rkRotate = m_pkGeometry->World.GetRotate();
        const Vector3x& rkScale = m_pkGeometry->World.GetScale();

        m_afWorldMatrix[ 0] = rkScale.X()*rkRotate[0][0];
        m_afWorldMatrix[ 1] = rkScale.X()*rkRotate[1][0];
        m_afWorldMatrix[ 2] = rkScale.X()*rkRotate[2][0];
        m_afWorldMatrix[ 3] = FIXED_ZERO;
        m_afWorldMatrix[ 4] = rkScale.Y()*rkRotate[0][1];
        m_afWorldMatrix[ 5] = rkScale.Y()*rkRotate[1][1];
        m_afWorldMatrix[ 6] = rkScale.Y()*rkRotate[2][1];
        m_afWorldMatrix[ 7] = FIXED_ZERO;
        m_afWorldMatrix[ 8] = rkScale.Z()*rkRotate[0][2];
        m_afWorldMatrix[ 9] = rkScale.Z()*rkRotate[1][2];
        m_afWorldMatrix[10] = rkScale.Z()*rkRotate[2][2];
        m_afWorldMatrix[11] = FIXED_ZERO;
    }
    else
    {
        const Matrix3x& rkMatrix = m_pkGeometry->World.GetMatrix();
        m_afWorldMatrix[ 0] = rkMatrix[0][0];
        m_afWorldMatrix[ 1] = rkMatrix[1][0];
        m_afWorldMatrix[ 2] = rkMatrix[2][0];
        m_afWorldMatrix[ 3] = FIXED_ZERO;
        m_afWorldMatrix[ 4] = rkMatrix[0][1];
        m_afWorldMatrix[ 5] = rkMatrix[1][1];
        m_afWorldMatrix[ 6] = rkMatrix[2][1];
        m_afWorldMatrix[ 7] = FIXED_ZERO;
        m_afWorldMatrix[ 8] = rkMatrix[0][2];
        m_afWorldMatrix[ 9] = rkMatrix[1][2];
        m_afWorldMatrix[10] = rkMatrix[2][2];
        m_afWorldMatrix[11] = FIXED_ZERO;
    }

    const Vector3x& rkTranslate = m_pkGeometry->World.GetTranslate();
    m_afWorldMatrix[12] = rkTranslate.X();
    m_afWorldMatrix[13] = rkTranslate.Y();
    m_afWorldMatrix[14] = rkTranslate.Z();
    m_afWorldMatrix[15] = FIXED_ONE;
}
//----------------------------------------------------------------------------
void OmapGLRenderer::OnFrustumChange ()
{
    if (m_pkCamera)
    {
        fixed fL, fR, fB, fT, fN, fF;
        m_pkCamera->GetFrustum(fL,fR,fB,fT,fN,fF);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        if (m_pkCamera->Perspective)
        {
            glFrustumx(fL.value,fR.value,fB.value,fT.value,fN.value,fF.value);
        }
        else
        {
            glOrtho(fL,fR,fB,fT,fN,fF);
        }
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::OnViewPortChange ()
{
    fixed fL, fR, fT, fB;
    if (m_pkCamera)
    {
        // 3D applications use cameras
        m_pkCamera->GetViewPort(fL,fR,fT,fB);
    }
    else
    {
        // 2D applications do not use camera
        fL = FIXED_ZERO;
        fR = FIXED_ONE;
        fT = FIXED_ONE;
        fB = FIXED_ZERO;
    }

    GLint iX = (fL*m_iWidth).value;
    GLint iY = (GLint)(fB*m_iHeight).value;
    GLsizei iW = (GLsizei)((fR - fL)*m_iWidth).value;
    GLsizei iH = (GLsizei)((fT - fB)*m_iHeight).value;
    glViewport(iX,iY,iW,iH);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::OnFrameChange ()
{
    Vector3x kLoc  = m_pkCamera->GetWorldLocation();
    Vector3x kUVec = m_pkCamera->GetWorldUVector();
    Vector3x kDVec = m_pkCamera->GetWorldDVector();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Vector3x kLookAt = kLoc + kDVec;
    gluLookAt(kLoc.X(),kLoc.Y(),kLoc.Z(),kLookAt.X(),kLookAt.Y(),kLookAt.Z(),
        kUVec.X(),kUVec.Y(),kUVec.Z());
}
//----------------------------------------------------------------------------
void OmapGLRenderer::EnableLighting (int eEnable)
{
    int iQuantity = m_pkGeometry->Lights.GetQuantity();
    if (iQuantity >= m_iMaxLights)
    {
        iQuantity = m_iMaxLights;
    }

    if (iQuantity > 0)
    {
        glEnable(GL_LIGHTING);
        for (int i = 0; i < iQuantity; i++)
        {
            const Light* pkLight = m_pkGeometry->Lights[i];
            if (pkLight->On)
            {
                EnableLight(eEnable,i,pkLight);
            }
        }
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::DisableLighting ()
{
    int iQuantity = m_pkGeometry->Lights.GetQuantity();
    if (iQuantity >= m_iMaxLights)
    {
        iQuantity = m_iMaxLights;
    }

    if (iQuantity > 0)
    {
        for (int i = 0; i < iQuantity; i++)
        {
            const Light* pkLight = m_pkGeometry->Lights[i];
            if (pkLight->On)
            {
                DisableLight(i,pkLight);
            }
        }
        glDisable(GL_LIGHTING);
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::EnableLight (int eEnable, int i, const Light* pkLight)
{
    GLenum eIndex = (GLenum)(GL_LIGHT0 + i);
    glEnable(eIndex);

    // ambient
    ColorRGBA kColor;
    if (eEnable & EL_AMBIENT)
    {
        kColor = pkLight->Intensity*pkLight->Ambient;
        kColor.Clamp();
    }
    else
    {
        kColor = ColorRGBA::BLACK;
    }
    glLightxv(eIndex,GL_AMBIENT,(GLfixed*)(fixed*)kColor);

    // diffuse
    if ((eEnable & EL_DIFFUSE) && pkLight->Type != Light::LT_AMBIENT)
    {
        kColor = pkLight->Intensity*pkLight->Diffuse;
        kColor.Clamp();
    }
    else
    {
        kColor = ColorRGBA::WHITE;
    }
    glLightxv(eIndex,GL_DIFFUSE,(GLfixed*)(fixed*)kColor);

    // specular
    if ((eEnable & EL_SPECULAR) && pkLight->Type != Light::LT_AMBIENT)
    {
        kColor = pkLight->Intensity*pkLight->Specular;
        kColor.Clamp();
    }
    else
    {
        kColor = ColorRGBA::WHITE;
    }
    glLightxv(eIndex,GL_SPECULAR,(GLfixed*)(fixed*)kColor);

    if (pkLight->Attenuate)
    {
        glLightx(eIndex,GL_CONSTANT_ATTENUATION, pkLight->Constant.value);
        glLightx(eIndex,GL_LINEAR_ATTENUATION, pkLight->Linear.value);
        glLightx(eIndex,GL_QUADRATIC_ATTENUATION, pkLight->Quadratic.value);
    }
    else
    {
        glLightx(eIndex,GL_CONSTANT_ATTENUATION,FIXED_ONE);
        glLightx(eIndex,GL_LINEAR_ATTENUATION,FIXED_ZERO);
        glLightx(eIndex,GL_QUADRATIC_ATTENUATION,FIXED_ZERO);
    }

    GLfixed afTemp[4];
    Vector3x kLoc, kDir;

    switch (pkLight->Type)
    {
    case Light::LT_AMBIENT:
        afTemp[0] = FIXED_ZERO;
        afTemp[1] = FIXED_ZERO;
        afTemp[2] = FIXED_ONE;
        afTemp[3] = FIXED_ZERO;
        glLightxv(eIndex,GL_POSITION,(GLfixed*)afTemp);
        break;
    case Light::LT_DIRECTIONAL:
        kDir = pkLight->GetWorldDVector();
        afTemp[0] = (-kDir.X()).value;
        afTemp[1] = (-kDir.Y()).value;
        afTemp[2] = (-kDir.Z()).value;
        afTemp[3] = FIXED_ZERO;
        glLightxv(eIndex,GL_POSITION,(GLfixed*)afTemp);
        break;
    case Light::LT_POINT:
    case Light::LT_SPOT:
        kLoc = pkLight->GetWorldLocation();
        afTemp[0] = kLoc.X().value;
        afTemp[1] = kLoc.Y().value;
        afTemp[2] = kLoc.Z().value;
        afTemp[3] = FIXED_ONE;
        glLightxv(eIndex,GL_POSITION,(GLfixed*)afTemp);
        break;
    default:  // Light::LT_QUANTITY
        assert( false );
        break;
    }

    if (pkLight->Type == Light::LT_SPOT)
    {
        fixed fDegrees = Mathx::RAD_TO_DEG*pkLight->Angle;
        glLightx(eIndex,GL_SPOT_CUTOFF,fDegrees.value);
        kDir = pkLight->GetWorldDVector();
        glLightxv(eIndex,GL_SPOT_DIRECTION,(GLfixed*)(fixed*)kDir);
        glLightx(eIndex,GL_SPOT_EXPONENT,pkLight->Exponent.value);
    }
    else
    {
        GLfixed afDefaultDir[3] = { FIXED_ZERO, FIXED_ZERO, -FIXED_ONE };
        glLightx(eIndex,GL_SPOT_CUTOFF,FixedFromFloat(180.0f));
        glLightxv(eIndex,GL_SPOT_DIRECTION,afDefaultDir);
        glLightx(eIndex,GL_SPOT_EXPONENT,FIXED_ZERO);
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::DisableLight (int i, const Light* pkLight)
{
    GLenum eIndex = (GLenum)(GL_LIGHT0 + i);
    glDisable(eIndex);
}
//----------------------------------------------------------------------------

void OmapGLRenderer::EnableTexture (int iUnit, int i, Effect* pkEffect)
{
    SetActiveTextureUnit(iUnit);
    if (i < pkEffect->UVs.GetQuantity())
    {
        Vector2xArray* pkUVs = pkEffect->UVs[i];
        if (pkUVs)
        {
            EnableUVs(i,pkEffect);
        }
    }

    Texture* pkTexture = pkEffect->Textures[i];
    glEnable(GL_TEXTURE_2D);

    GLuint uiID;
    pkTexture->BIArray.GetID(this,sizeof(GLuint),&uiID);

    if (uiID != 0)
    {
        // texture already exists in OpenGL, just bind it
        glBindTexture(GL_TEXTURE_2D,uiID);
    }
    else
    {
        // texture seen first time, generate name and create data
        glGenTextures((GLsizei)1,&uiID);
        pkTexture->BIArray.Bind(this,sizeof(GLuint),&uiID);

        // bind the texture
        glBindTexture(GL_TEXTURE_2D,uiID);

        // Get texture image data.  Not all textures have image data.
        // For example, AM_COMBINE modes can use primary colors,
        // texture output, and constants to modify fragments via the
        // texture units.
        ImagePtr spkImage = pkTexture->GetImage();
        if (spkImage)
        {
            if (pkTexture->Mipmap == Texture::MM_NEAREST
            ||  pkTexture->Mipmap == Texture::MM_LINEAR)
            {
                glTexImage2D(GL_TEXTURE_2D,0,
                    ms_aeImageFormats[spkImage->GetFormat()],
                    spkImage->GetWidth(),spkImage->GetHeight(),0,
                    ms_aeImageFormats[spkImage->GetFormat()],
                    ms_aeImageComponents[spkImage->GetFormat()],spkImage->GetData());
            }
            else
            {
				glEnable(GL_GENERATE_MIPMAP);
				glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
				glTexImage2D(GL_TEXTURE_2D,0,
                    ms_aeImageFormats[spkImage->GetFormat()],
                    spkImage->GetWidth(),spkImage->GetHeight(),0,
                    ms_aeImageFormats[spkImage->GetFormat()],
                    ms_aeImageComponents[spkImage->GetFormat()],spkImage->GetData());
				glDisable(GL_GENERATE_MIPMAP);
//                  gluBuild2DMipmaps(GL_TEXTURE_2D,
//                      ms_aeImageComponents[spkImage->GetFormat()],
//                      spkImage->GetWidth(),spkImage->GetHeight(),
//                      ms_aeImageFormats[spkImage->GetFormat()],
//                      GL_UNSIGNED_BYTE,spkImage->GetData());
            }
			spkImage->DeleteRawData();
        }

        // set up coordinate mode
        switch (pkTexture->CoordU)
        {
        case Texture::WM_CLAMP:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
            break;
        case Texture::WM_REPEAT:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            break;
        case Texture::WM_CLAMP_BORDER:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
            break;
        case Texture::WM_CLAMP_EDGE:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
			break;
        default:  // Texture::WM_QUANTITY
            break;
        }

        switch (pkTexture->CoordV)
        {
        case Texture::WM_CLAMP:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
            break;
        case Texture::WM_REPEAT:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
            break;
        case Texture::WM_CLAMP_BORDER:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
            break;
        case Texture::WM_CLAMP_EDGE:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
            break;
        default:  // Texture::WM_QUANTITY
            break;
        }

        // set up filter mode
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,
            ms_aeTextureFilter[pkTexture->Filter]);

        // set up mipmap mode
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
            ms_aeTextureMipmap[pkTexture->Mipmap]);
    }

    // set up correction mode
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,
        ms_aeTextureCorrection[pkTexture->Correction]);

    // set up the blend color
    glTexEnvxv(GL_TEXTURE_ENV,GL_TEXTURE_ENV_COLOR,
        (const GLfixed*)(const fixed*)pkTexture->BlendColor);

    // set up apply mode
    if (pkTexture->Apply != Texture::AM_COMBINE)
    {
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,
            ms_aeTextureApply[pkTexture->Apply]);
    }
    else  // AM_COMBINE
    {
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::DisableTexture (int iUnit, int i, Effect* pkEffect)
{
    Texture* pkTexture = pkEffect->Textures[i];

    glDisable(GL_TEXTURE_2D);
    glClientActiveTexture(GL_TEXTURE0+iUnit);

    if (i < pkEffect->UVs.GetQuantity())
    {
        Vector2xArray* pkUVs = pkEffect->UVs[i];
        if (pkUVs)
        {
            DisableUVs(pkUVs);
        }
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::SetActiveTextureUnit (int iUnit)
{
        glClientActiveTexture(GL_TEXTURE0+iUnit);
        glActiveTexture(GL_TEXTURE0+iUnit);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ReleaseTexture (Texture* pkTexture)
{
    // The Macintosh OpenGL appears to have a problem if the UserData value
    // is zero 0 (a null pointer).  The OpenGL reference on glDeleteTextures
    // indicates the zero should be ignored...
    assert(pkTexture);
    GLuint uiID;
    pkTexture->BIArray.GetID(this,sizeof(GLuint),&uiID);
    if (uiID > 0)
    {
        glDeleteTextures((GLsizei)1,(GLuint*)&uiID);
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::SetWorldTransformation ()
{
    // primitive is 3D
    SetWorldMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixx((GLfixed*)m_afWorldMatrix);
    if (m_pkGeometry->World.IsUniformScale())
    {
        if (m_pkGeometry->World.GetUniformScale() != FIXED_ONE)
        {
			glEnable(GL_RESCALE_NORMAL);
        }
    }
    else
    {
        glEnable(GL_NORMALIZE);
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::RestoreWorldTransformation ()
{
    if (m_pkGeometry->World.IsUniformScale())
    {
        if (m_pkGeometry->World.GetUniformScale() != FIXED_ONE)
        {
            glDisable(GL_RESCALE_NORMAL);
        }
    }
    else
    {
        glDisable(GL_NORMALIZE);
    }
	glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
//----------------------------------------------------------------------------
void OmapGLRenderer::SetScreenTransformation ()
{
    // primitive is screen polygon, already in correct coordinates
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();

    // Draw the polygon using an orthogonal frustum.  If the polygon has
    // a z-value of 0.0, it is drawn in front of everything.  If the
    // polygon has a z-value of 1.0, it is drawn in back of everything.
    glMatrixMode(GL_PROJECTION);    
    glPushMatrix();
    glLoadIdentity();
    glOrtho(fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_NEG_ONE));
}
//----------------------------------------------------------------------------
void OmapGLRenderer::RestoreScreenTransformation ()
{
    // restore to a perspective frustum
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
//----------------------------------------------------------------------------
void OmapGLRenderer::EnableVertices ()
{
    // get vertices
    Vector3xArray* pkVertices = m_pkGeometry->Vertices;
    assert(pkVertices);
    Vector3x* akVertex = pkVertices->GetData();
    if (pkVertices->IsExactly(CachedVector3xArray::TYPE))
    {
		// vertices are cached
        CachedVector3xArray* pkCVertices =
            (CachedVector3xArray*)pkVertices;
        GLuint uiID;
        pkCVertices->BIArray.GetID(this,sizeof(GLuint),&uiID);

        if (uiID > 0)
        {
            // vertices already cached, just bind them
            glBindBuffer(GL_ARRAY_BUFFER,uiID);
        }
        else
        {
            // vertices seen first time, generate name and create data
            glGenBuffers((GLsizei)1,&uiID);
            pkCVertices->BIArray.Bind(this,sizeof(GLuint),&uiID);

            // bind the vertices
            glBindBuffer(GL_ARRAY_BUFFER,uiID);

            // copy the data to the buffer
            glBufferData(GL_ARRAY_BUFFER,
                pkVertices->GetQuantity()*sizeof(Vector3x),akVertex,
                GL_STATIC_DRAW);
			pkVertices->DeleteRawData();
        }

        akVertex = 0;
 
    }
	else if(!akVertex)
		return;

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FIXED,0,akVertex);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::DisableVertices ()
{
    if (m_pkGeometry->Vertices->IsExactly(CachedVector3xArray::TYPE))
    {
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::EnableNormals ()
{
    // get normals
    Vector3xArray* pkNormals = m_pkGeometry->Normals;
    Vector3x* akNormal = pkNormals->GetData();
	if (pkNormals->IsExactly(CachedVector3xArray::TYPE))
    {
        // normals are cached
        CachedVector3xArray* pkCNormals = (CachedVector3xArray*)pkNormals;
        GLuint uiID;
        pkCNormals->BIArray.GetID(this,sizeof(GLuint),&uiID);

        if (uiID > 0)
        {
            // normals already cached, just bind them
            glBindBuffer(GL_ARRAY_BUFFER,uiID);
        }
        else
        {
            // normals seen first time, generate name and create data
            glGenBuffers((GLsizei)1,&uiID);
            pkCNormals->BIArray.Bind(this,sizeof(GLuint),&uiID);

            // bind the normals
            glBindBuffer(GL_ARRAY_BUFFER,uiID);

            // copy the data to the buffer
            glBufferData(GL_ARRAY_BUFFER,
                pkNormals->GetQuantity()*sizeof(Vector3x),akNormal,
                GL_STATIC_DRAW);
			pkNormals->DeleteRawData();
        }

        akNormal = 0;
    }
	else if(!akNormal)
		return;

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FIXED,0,akNormal);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::DisableNormals ()
{
    if (m_pkGeometry->Normals->IsExactly(CachedVector3xArray::TYPE))
    {
		glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    glDisableClientState(GL_NORMAL_ARRAY);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::EnableColorRGBAs ()
{
    // get colors
    ColorRGBAArray* pkColors = m_pkLocalEffect->ColorRGBAs;
    ColorRGBA* akColor = pkColors->GetData();
    if (pkColors->IsExactly(CachedColorRGBAArray::TYPE))
    {
        // colors are cached
        CachedColorRGBAArray* pkCColors = (CachedColorRGBAArray*)pkColors;
        GLuint uiID;
        pkCColors->BIArray.GetID(this,sizeof(GLuint),&uiID);

        if (uiID > 0)
        {
            // colors already cached, just bind them
            glBindBuffer(GL_ARRAY_BUFFER,uiID);
        }
        else
        {
            // colors seen first time, generate name and create data
            glGenBuffers((GLsizei)1,&uiID);
            pkCColors->BIArray.Bind(this,sizeof(GLuint),&uiID);

            // bind the colors
            glBindBuffer(GL_ARRAY_BUFFER,uiID);

            // copy the data to the buffer
            glBufferData(GL_ARRAY_BUFFER,
                pkColors->GetQuantity()*sizeof(ColorRGBA),akColor,
                GL_STATIC_DRAW);
			pkCColors->DeleteRawData();
        }

        akColor = 0;

    }
	else if(!akColor)
		return;
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4,GL_FIXED,0,akColor);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::DisableColorRGBAs ()
{
    if (m_pkLocalEffect->ColorRGBAs->IsExactly(CachedColorRGBAArray::TYPE))
    {
		glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    glDisableClientState(GL_COLOR_ARRAY);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::EnableColorRGBs ()
{
    // get colors
    ColorRGBArray* pkColors = m_pkLocalEffect->ColorRGBs;
    ColorRGB* akColor = pkColors->GetData();

    if (pkColors->IsExactly(CachedColorRGBArray::TYPE))
    {
        // colors are cached
        CachedColorRGBArray* pkCColors = (CachedColorRGBArray*)pkColors;
        GLuint uiID;
        pkCColors->BIArray.GetID(this,sizeof(GLuint),&uiID);

        if (uiID > 0)
        {
            // colors already cached, just bind them
            glBindBuffer(GL_ARRAY_BUFFER,uiID);
        }
        else
        {
            // colors seen first time, generate name and create data
            glGenBuffers((GLsizei)1,&uiID);
            pkCColors->BIArray.Bind(this,sizeof(GLuint),&uiID);

            // bind the colors
            glBindBuffer(GL_ARRAY_BUFFER,uiID);

            // copy the data to the buffer
            glBufferData(GL_ARRAY_BUFFER,
                pkColors->GetQuantity()*sizeof(ColorRGB),akColor,
                GL_STATIC_DRAW);
			pkColors->DeleteRawData();
        }

        akColor = 0;
    }
	else if(!akColor)
		return;
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3,GL_FIXED,0,akColor);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::DisableColorRGBs ()
{
    if (m_pkLocalEffect->ColorRGBs->IsExactly(CachedColorRGBArray::TYPE))
    {
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    glDisableClientState(GL_COLOR_ARRAY);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::EnableUVs ( int i, Effect* pkEffect)
{
    // get uv's
	Vector2xArray* pkUVs= pkEffect->UVs[i];
    Vector2x* akUV = pkUVs->GetData();

    if (pkUVs->IsExactly(CachedVector2xArray::TYPE))
    {
        // uv's are cached
        CachedVector2xArray* pkCUVs = (CachedVector2xArray*)pkUVs;
        GLuint uiID;
        pkCUVs->BIArray.GetID(this,sizeof(GLuint),&uiID);

        if (uiID > 0)
        {
            // uv's already cached, just bind them
            glBindBuffer(GL_ARRAY_BUFFER,uiID);
        }
        else
        {
            // uv's seen first time, generate name and create data
            glGenBuffers((GLsizei)1,&uiID);
            pkCUVs->BIArray.Bind(this,sizeof(GLuint),&uiID);

            // bind the uv's
            glBindBuffer(GL_ARRAY_BUFFER,uiID);

            // copy the data to the buffer
            glBufferData(GL_ARRAY_BUFFER,
                pkUVs->GetQuantity()*sizeof(Vector2x),akUV,
                GL_STATIC_DRAW);
			pkEffect->RemoveTextureUVData(i);
        }

        akUV = 0;
    }
	else if(!akUV)
		return;
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
    glTexCoordPointer(2,GL_FIXED,0,akUV);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::DisableUVs (Vector2xArray* pkUVs)
{
    if (pkUVs->IsExactly(CachedVector2xArray::TYPE))
    {
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::DrawElements ()
{
    // get indices
    ShortArray* pkIndices = m_pkGeometry->Indices;
    int iIQuantity = pkIndices->GetQuantity();
    short* aiIndex = pkIndices->GetData();

    bool bCached = pkIndices->IsExactly(CachedShortArray::TYPE);
    if (bCached)
    {
        // indices are cached
        CachedShortArray* pkCIndices = (CachedShortArray*)pkIndices;
        GLuint uiID;
        pkCIndices->BIArray.GetID(this,sizeof(GLuint),&uiID);

        if (uiID > 0)
        {
            // indices already cached, just bind them
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,uiID);
        }
        else
        {
            // indices seen first time, generate name and create data
            glGenBuffers((GLsizei)1,&uiID);
            pkCIndices->BIArray.Bind(this,sizeof(GLuint),&uiID);

            // bind the indices
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,uiID);

            // copy the data to the buffer
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                iIQuantity*sizeof(short),aiIndex,GL_STATIC_DRAW);
			pkCIndices->DeleteRawData();
        }

        aiIndex = 0;
    }
	
    GLenum eType = ms_aeObjectType[m_pkGeometry->m_GeometryType];
    
	if(!bCached && aiIndex==NULL && m_pkGeometry->Vertices->GetQuantity()>0)
		glDrawArrays(eType,0,m_pkGeometry->Vertices->GetQuantity());
	else
		glDrawElements(eType,iIQuantity,GL_UNSIGNED_SHORT,aiIndex);

    if (bCached)
    {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ReleaseArray (CachedColorRGBAArray* pkArray)
{
    assert(pkArray);
    GLuint uiID;
    pkArray->BIArray.GetID(this,sizeof(GLuint),&uiID);
    if (uiID > 0)
    {
        glDeleteBuffers((GLsizei)1,(GLuint*)&uiID);
        pkArray->BIArray.Unbind(this);

    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ReleaseArray (CachedColorRGBArray* pkArray)
{
    assert(pkArray);
    GLuint uiID;
    pkArray->BIArray.GetID(this,sizeof(GLuint),&uiID);
    if (uiID > 0)
    {

        glDeleteBuffers((GLsizei)1,(GLuint*)&uiID);
        pkArray->BIArray.Unbind(this);
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ReleaseArray (CachedShortArray* pkArray)
{
    assert(pkArray);
    GLuint uiID;
    pkArray->BIArray.GetID(this,sizeof(GLuint),&uiID);
    if (uiID > 0)
    {

        glDeleteBuffers((GLsizei)1,(GLuint*)&uiID);
        pkArray->BIArray.Unbind(this);
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ReleaseArray (CachedVector2xArray* pkArray)
{
    assert(pkArray);
    GLuint uiID;
    pkArray->BIArray.GetID(this,sizeof(GLuint),&uiID);
    if (uiID > 0)
    {

        glDeleteBuffers((GLsizei)1,(GLuint*)&uiID);
        pkArray->BIArray.Unbind(this);
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::ReleaseArray (CachedVector3xArray* pkArray)
{
    assert(pkArray);
    GLuint uiID;
    pkArray->BIArray.GetID(this,sizeof(GLuint),&uiID);
    if (uiID > 0)
    {

        glDeleteBuffers((GLsizei)1,(GLuint*)&uiID);
        pkArray->BIArray.Unbind(this);
    }
}
//----------------------------------------------------------------------------
void OmapGLRenderer::SetConstantTransformM (int iOption, fixed* afData)
{
    Matrix4x kM(m_afWorldMatrix,false);
    GetTransform(kM,iOption,afData);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::SetConstantTransformP (int iOption, fixed* afData)
{
    fixed afProjection[16];
    glGetFixedv(GL_PROJECTION_MATRIX,(GLfixed*)afProjection);
    Matrix4x kP(afProjection,false);
    GetTransform(kP,iOption,afData);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::SetConstantTransformMV (int iOption, fixed* afData)
{
    // OpenGL's model-view matrix has vectors in the order (R,U,-D).  Wild
    // Magic requires (R,U,D).  Also, OpenGL's model-view matrix is the
    // transpose of what Wild Magic expects.  These two facts require a
    // sign change in the specified entries to cause -D to be mapped to D.
    fixed afModelView[16];
    glGetFixedv(GL_MODELVIEW_MATRIX,(GLfixed*)afModelView);
    afModelView[ 2] = -afModelView[ 2];
    afModelView[ 6] = -afModelView[ 6];
    afModelView[10] = -afModelView[10];
    afModelView[14] = -afModelView[14];
    Matrix4x kMV(afModelView,false);
    GetTransform(kMV,iOption,afData);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::SetConstantTransformMVP (int iOption, fixed* afData)
{
    fixed afProjection[16];
    glGetFixedv(GL_PROJECTION_MATRIX,(GLfixed*)afProjection);
    Matrix4x kP(afProjection,false);

    // OpenGL's model-view matrix has vectors in the order (R,U,-D).  Wild
    // Magic requires (R,U,D).  Also, OpenGL's model-view matrix is the
    // transpose of what Wild Magic expects.  These two facts required a
    // sign change when accessing only the model-view matrix.  However,
    // OpenGL's projection matrix has that sign change built into it, so
    // unlike SetConstantMVMatrix, there is no need to change signs.
    fixed afModelView[16];
    glGetFixedv(GL_MODELVIEW_MATRIX,(GLfixed*)afModelView);
    Matrix4x kMV(afModelView,false);

    Matrix4x kPMV = kP*kMV;
    GetTransform(kPMV,iOption,afData);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::GetTransform (Matrix4x& rkMat, int iOption,
    fixed* afData)
{
    // Wild Magic uses matrix M, OpenGL uses matrix Transpose(M).  The input
    // matrix is guaranteed to be in OpenGL format.  This ensures that the
    // final matrix is in row-major order and the memcpy to afData produces
    // a fixed[16] array in the format OpenGL expects.

    switch (iOption)
    {
    case ShaderConstant::SCO_MATRIX:
        break;
    case ShaderConstant::SCO_TRANSPOSE:
        rkMat = rkMat.Transpose();
        break;
    case ShaderConstant::SCO_INVERSE:
        rkMat = rkMat.Inverse();
        break;
    case ShaderConstant::SCO_INVERSE_TRANSPOSE:
        rkMat = rkMat.Inverse().Transpose();
        break;
    default:
        assert(false);
        break;
    }

    memcpy(afData,(const fixed*)rkMat,16*sizeof(fixed));
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void OmapGLRenderer::SetPointSize (fixed fSize)
{
    Renderer::SetPointSize(fSize);
    glPointSizex(m_fPointSize.value);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::SetLineWidth (fixed fWidth)
{
    Renderer::SetLineWidth(fWidth);
    glLineWidthx(m_fLineWidth.value);
}
//----------------------------------------------------------------------------
void OmapGLRenderer::SetLineStipple (int iRepeat, unsigned short usPattern)
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// driver and extension information
//----------------------------------------------------------------------------
const char* OmapGLRenderer::GetVendor ()
{
    return (const char*)glGetString(GL_VENDOR);
}
//----------------------------------------------------------------------------
const char* OmapGLRenderer::GetRenderer ()
{
    return (const char*)glGetString(GL_RENDERER);
}
//----------------------------------------------------------------------------
const char* OmapGLRenderer::GetVersion ()
{
    return (const char*)glGetString(GL_VERSION);
}
//----------------------------------------------------------------------------
const char* OmapGLRenderer::GetGluVersion ()
{
    return NULL;//(const char*)glGetString((GLenum)GLU_VERSION);
}
//----------------------------------------------------------------------------
const char* OmapGLRenderer::GetExtensions ()
{
    return (const char*)glGetString(GL_EXTENSIONS);
}
//----------------------------------------------------------------------------
bool OmapGLRenderer::ExtensionSupported (const char* acExt)
{
    // make sure a proper string has been passed
    if (!acExt || acExt[0] == 0)
    {
        return false;
    }

    // Without the typecast on strstr, CodeWarrior 9.x generates an error
    // because its C library appears to define the return value of strstr
    // as 'const char*'.  Other compilers appear to define the return value
    // as 'char*'.
    char* acBegin = (char*)strstr(GetExtensions(),acExt);
    if (acBegin)
    {
        // The extension was found, but make sure it is not a proper substring
        // of another extension.  TO DO:  Should cEnd be compared to tabs or
        // other white space characters?
        char cEnd = *(acBegin + strlen(acExt));
        return cEnd == ' ' || cEnd == 0;
    }

    return false;
}
//----------------------------------------------------------------------------
