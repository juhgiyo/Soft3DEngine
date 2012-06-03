///////////////////////////////////////////////////////////
//                                                       //
//                    WgBumpMapEffect.cpp                //
//                                                       //
//  - Implementation for Bump Map Effect class           //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.09                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgBumpMapEffect.h"
#include "WgTriMesh.h"
#include "WgCachedColorRGBArray.h"
#include "WgCachedVector2Array.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,BumpMapEffect,Effect);


//----------------------------------------------------------------------------
BumpMapEffect::BumpMapEffect (Image* pkPrimary, Vector2xArray* pkPrimaryUVs,
    Image* pkNormalMap, Vector2xArray* pkNormalUVs, Light* pkLight)
    :
    m_spkLight(pkLight)
{
    Draw = &Renderer::DrawBumpMap;
    int iVQuantity = pkPrimaryUVs->GetQuantity();
    ColorRGB* akColor = WG_NEW ColorRGB[iVQuantity];

    if (pkPrimaryUVs->IsExactly(CachedVector2xArray::TYPE))
    {
        assert(pkNormalUVs->IsExactly(CachedVector2xArray::TYPE));
        ColorRGBs = WG_NEW CachedColorRGBArray(iVQuantity,akColor);
    }
    else
    {
        ColorRGBs = WG_NEW ColorRGBArray(iVQuantity,akColor);
    }

    // primary texture
    Texture* pkTexture = WG_NEW Texture;
    pkTexture->SetImage(pkPrimary);
    pkTexture->Apply = Texture::AM_REPLACE;
    pkTexture->Filter = Texture::FM_LINEAR;
    pkTexture->Mipmap = Texture::MM_LINEAR_LINEAR;
    Textures.Append(pkTexture);
    UVs.Append(pkPrimaryUVs);

    // normal map texture
    pkTexture = WG_NEW Texture;
    pkTexture->SetImage(pkNormalMap);
    pkTexture->Apply = Texture::AM_COMBINE;
    pkTexture->Filter = Texture::FM_LINEAR;
    pkTexture->Mipmap = Texture::MM_LINEAR;
    pkTexture->CombineFuncRGB = Texture::ACF_DOT3_RGB;
    pkTexture->CombineSrc0RGB = Texture::ACS_TEXTURE;
    pkTexture->CombineOp0RGB = Texture::ACO_SRC_COLOR;
    pkTexture->CombineSrc1RGB = Texture::ACS_PRIMARY_COLOR;
    pkTexture->CombineOp1RGB = Texture::ACO_SRC_COLOR;
    Textures.Append(pkTexture);
    UVs.Append(pkNormalUVs);

    m_bNeedsRecalculation = true;
}
//----------------------------------------------------------------------------
BumpMapEffect::BumpMapEffect ()
{
    Draw = &Renderer::DrawBumpMap;
}
//----------------------------------------------------------------------------
BumpMapEffect::~BumpMapEffect ()
{
}
//----------------------------------------------------------------------------
Effect* BumpMapEffect::Clone ()
{
    BumpMapEffect* pkClone = WG_NEW BumpMapEffect;
    DoCloning(pkClone);
    return pkClone;
}
//----------------------------------------------------------------------------
void BumpMapEffect::DoCloning (Effect* pkClone)
{
    Effect::DoCloning(pkClone);

    BumpMapEffect* pkDClone = (BumpMapEffect*)pkClone;
    pkDClone->m_spkLight = m_spkLight;
}
//----------------------------------------------------------------------------
void BumpMapEffect::ComputeLightVectors (Triangles* pkMesh)
{
    // Generate light direction vectors in the surface local space and store
    // them in the color array for interpolation via the rasterizer.

    // Compute the world direction from the light to the world translation
    // of the triangle mesh.
    Vector3x kWDir;
    switch (m_spkLight->Type)
    {
    case Light::LT_DIRECTIONAL:
        kWDir = -m_spkLight->GetWorldDVector();
        break;
    case Light::LT_POINT:
    case Light::LT_SPOT:
        kWDir = m_spkLight->GetWorldLocation() - pkMesh->World.GetTranslate();
        break;
    default:
        // ambient light, nothing we can do to handle this
        return;
    }

    // Transform the world light vector into model space.  If the light is
    // directional, then kMLight is a vector (M,0).  If the light is
    // positional (point/spot), then kMLight is a point (M,1).
    Vector3x kMLight = pkMesh->World.InvertVector(kWDir);

    // Get the triangle mesh vertices and texture coordinates.
    int iVQuantity = pkMesh->Vertices->GetQuantity();
    Vector3x* akVertex = pkMesh->Vertices->GetData();
    Vector2x* akUV = UVs[0]->GetData();

    // Set the light vectors to (0,0,0) as a flag that the quantity has not
    // yet been computed.  The probability that a light vector is actually
    // (0,0,0) should be small, so the flag system should save computation
    // time overall.
    ColorRGB* akLVec = ColorRGBs->GetData();
    memset(akLVec,0,iVQuantity*sizeof(ColorRGB));

    // Get the triangle mesh normals.  These must exist to obtain correct
    // bump mapping, but if they do not exist, a safe thing to do in a
    // Release build is to return all black colors.
    if (!pkMesh->Normals)
    {
        assert(false);
        return;
    }
    Vector3x* akNormal = pkMesh->Normals->GetData();

    int iTQuantity = pkMesh->GetTriangleQuantity();
    for (int iT = 0; iT < iTQuantity; iT++)
    {
        // get the triangle vertices and attributes
        short iV0, iV1, iV2;
        if (!pkMesh->GetTriangle(iT,iV0,iV1,iV2))
        {
            continue;
        }
        Vector3x* apkV[3] = {&akVertex[iV0], &akVertex[iV1], &akVertex[iV2]};
        Vector3x* apkN[3] = {&akNormal[iV0], &akNormal[iV1], &akNormal[iV2]};
        Vector2x* apkUV[3] = {&akUV[iV0], &akUV[iV1], &akUV[iV2]};
        ColorRGB* apkC[3] = {&akLVec[iV0], &akLVec[iV1], &akLVec[iV2]};

        for (int i = 0; i < 3; i++)
        {
            ColorRGB& rkColor = *apkC[i];
            if (rkColor != ColorRGB::BLACK)
            {
                continue;
            }

            int iP = (i == 0) ? 2 : i - 1;
            int iN = (i + 1) % 3;

            // compute edge vectors at the specified vertex
            Vector3x kDP1 = *apkV[iN] - *apkV[i];
            Vector3x kDP2 = *apkV[iP] - *apkV[i];

            // estimate a tangent surface vector
            Vector3x kTangent;
            bool bDegenerate = false;

            if (Mathx::FAbs(kDP1.Length()) < Mathx::ZERO_TOLERANCE
            ||  Mathx::FAbs(kDP2.Length()) < Mathx::ZERO_TOLERANCE)
            {
                // The triangle is very small, call it degenerate.
                bDegenerate = true;
            }
            else
            {
                // difference of surface parameters along triangle edge
                fixed fDU1 = apkUV[iN]->X() - apkUV[i]->X();
                fixed fDV1 = apkUV[iN]->Y() - apkUV[i]->Y();

                if (Mathx::FAbs(fDV1) < Mathx::ZERO_TOLERANCE)
                {
                    // The triangle effectively has no variation in the v
                    // texture coordinate.
                    if (Mathx::FAbs(fDU1) < Mathx::ZERO_TOLERANCE)
                    {
                        // The triangle effectively has no variation in the u
                        // coordinate.  Since the texture coordinates do not
                        // effectively vary on this triangle, treat it as a
                        // degenerate parametric surface.
                        bDegenerate = true;
                    }
                    else
                    {
                        // The variation is effectively all in u, so set the
                        // tangent T = dP/du.
                        kTangent = kDP1/fDU1;
                    }
                }
                else
                {
                    // difference of surface parameters along triangle edge
                    fixed fDU2 = apkUV[iP]->X() - apkUV[i]->X();
                    fixed fDV2 = apkUV[iP]->Y() - apkUV[i]->Y();
                    fixed fDet = fDV1*fDU2 - fDV2*fDU1;

                    if (Mathx::FAbs(fDet) >= Mathx::ZERO_TOLERANCE)
                    {
                        // The triangle vertices form three collinear points
                        // in parameter space, so
                        //   dP/du = (dv1*dP2-dv2*dP1)/(dv1*du2-dv2*du1)
                        kTangent = (fDV1*kDP2-fDV2*kDP1)/fDet;
                    }
                    else
                    {
                        // The triangle vertices are collinear in parameter
                        // space.
                        bDegenerate = true;
                    }
                }
            }

            if (bDegenerate)
            {
                // The texture coordinate mapping is not properly defined for
                // this.  Just say that the tangent space light vector points
                // in the same direction as the surface normal.
                rkColor.R() = apkN[i]->X();
                rkColor.G() = apkN[i]->Y();
                rkColor.B() = apkN[i]->Z();
                continue;
            }

            // Project T into the tangent plane by projecting out the surface
            // normal, then make it unit length.
            kTangent -= apkN[i]->Dot(kTangent)*(*apkN[i]);
            kTangent.Normalize();

            // compute the bitangent B, another tangent perpendicular to T
            Vector3x kBitangent = apkN[i]->UnitCross(kTangent);

            // When generating bump/normal maps, folks usually work in a
            // left-handed screen space with the origin at the upper right,
            // u to the right, and v down, while we apply the textures with
            // the origin at the lower left, u right, v up, so we need to flip
            // the kBitangent (v-axis) to get a proper transformation to the
            // surface local texture space.
            Matrix3x kRotTS(
                kTangent.X(),   kTangent.Y(),   kTangent.Z(),
              -kBitangent.X(), -kBitangent.Y(), -kBitangent.Z(),
                apkN[i]->X(),   apkN[i]->Y(),   apkN[i]->Z());

            // compute the tangent space light direction
            Vector3x kTSDir;
            if (m_spkLight->Type == Light::LT_DIRECTIONAL)
            {
                kTSDir = kMLight;
            }
            else  // light is positional
            {
                kTSDir = kMLight - *apkV[i];
            }

            kTSDir.Normalize();
            kTSDir = kRotTS*kTSDir;

            // Transform the light vector into [0,1]^3 to make it a valid
            // ColorRGB object.
            rkColor.R() = FIXED_HALF*(kTSDir.X() + FIXED_ONE);
            rkColor.G() = FIXED_HALF*(kTSDir.Y() + FIXED_ONE);
            rkColor.B() = FIXED_HALF*(kTSDir.Z() + FIXED_ONE);
        }
    }

    m_bNeedsRecalculation = false;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* BumpMapEffect::GetObjectByName (const String& rkName)
{
    Object* pkFound = Effect::GetObjectByName(rkName);
    if (pkFound)
    {
        return pkFound;
    }

    if (m_spkLight)
    {
        pkFound = m_spkLight->GetObjectByName(rkName);
        if (pkFound)
        {
            return pkFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void BumpMapEffect::GetAllObjectsByName (const String& rkName,
    TArray<Object*>& rkObjects)
{
    Effect::GetAllObjectsByName(rkName,rkObjects);

    if (m_spkLight)
    {
        m_spkLight->GetAllObjectsByName(rkName,rkObjects);
    }
}
//----------------------------------------------------------------------------
Object* BumpMapEffect::GetObjectByID (unsigned int uiID)
{
    Object* pkFound = Effect::GetObjectByID(uiID);
    if (pkFound)
    {
        return pkFound;
    }

    if (m_spkLight)
    {
        pkFound = m_spkLight->GetObjectByID(uiID);
        if (pkFound)
        {
            return pkFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
