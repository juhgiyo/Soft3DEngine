///////////////////////////////////////////////////////////
//                                                       //
//                    WgTransformation.cpp               //
//                                                       //
//  - Implementation for Transformation class            //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////


#include "WgFoundationPCH.h"
#include "WgTransformation.h"
using namespace WGSoft3D;

const Transformation Transformation::IDENTITY;

//----------------------------------------------------------------------------
Transformation::Transformation ()
    :
    m_kMatrix(fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ONE)),
    m_kTranslate(fixed(FIXED_ZERO),fixed(FIXED_ZERO),fixed(FIXED_ZERO)),
    m_kScale(fixed(FIXED_ONE),fixed(FIXED_ONE),fixed(FIXED_ONE))
{
    // default transform is the identity
    m_bIsIdentity = true;
    m_bIsRSMatrix = true;
    m_bIsUniformScale = true;
}
//----------------------------------------------------------------------------
Transformation::~Transformation ()
{
}
//----------------------------------------------------------------------------
void Transformation::MakeIdentity ()
{
    m_kMatrix = Matrix3x::IDENTITY;
    m_kTranslate = Vector3x::ZERO;
    m_kScale = Vector3x(fixed(FIXED_ONE),fixed(FIXED_ONE),fixed(FIXED_ONE));
    m_bIsIdentity = true;
    m_bIsRSMatrix = true;
    m_bIsUniformScale = true;
}
//----------------------------------------------------------------------------
void Transformation::MakeUnitScale ()
{
    assert(m_bIsRSMatrix);

    m_kScale = Vector3x(fixed(FIXED_ONE),fixed(FIXED_ONE),fixed(FIXED_ONE));
    m_bIsUniformScale = true;
}
//----------------------------------------------------------------------------
fixed Transformation::GetNorm () const
{
    if (m_bIsRSMatrix)
    {
        fixed fMax = Mathx::FAbs(m_kScale.X());
        if (Mathx::FAbs(m_kScale.Y()) > fMax)
        {
            fMax = Mathx::FAbs(m_kScale.Y());
        }
        if (Mathx::FAbs(m_kScale.Z()) > fMax)
        {
            fMax = Mathx::FAbs(m_kScale.Z());
        }
        return fMax;
    }

    // A general matrix.  Use the max-column-sum matrix norm.  The spectral
    // norm (the maximum absolute value of the eigenvalues) is smallerthan or
    // equal to this norm.  Therefore, this function returns an approximation
    // to the maximum scale.
    fixed fMaxColSum =
        Mathx::FAbs(m_kMatrix[0][0]) +
        Mathx::FAbs(m_kMatrix[1][0]) +
        Mathx::FAbs(m_kMatrix[2][0]);

    fixed fColSum =
        Mathx::FAbs(m_kMatrix[0][1]) +
        Mathx::FAbs(m_kMatrix[1][1]) +
        Mathx::FAbs(m_kMatrix[2][1]);

    if (fColSum > fMaxColSum)
    {
        fMaxColSum = fColSum;
    }

    fColSum =
        Mathx::FAbs(m_kMatrix[0][2]) +
        Mathx::FAbs(m_kMatrix[1][2]) +
        Mathx::FAbs(m_kMatrix[2][2]);

    if (fColSum > fMaxColSum)
    {
        fMaxColSum = fColSum;
    }

    return fMaxColSum;
}
//----------------------------------------------------------------------------
void Transformation::SetRotate (const Matrix3x& rkRotate)
{
    m_kMatrix = rkRotate;
    m_bIsIdentity = false;
    m_bIsRSMatrix = true;
}
//----------------------------------------------------------------------------
void Transformation::SetTranslate (const Vector3x& rkTranslate)
{
    m_kTranslate = rkTranslate;
    m_bIsIdentity = false;
}
//----------------------------------------------------------------------------
void Transformation::SetScale (const Vector3x& rkScale)
{
    assert(m_bIsRSMatrix && rkScale.X() != FIXED_ZERO && rkScale.Y() != FIXED_ZERO
        && rkScale.Z() != FIXED_ZERO);

    m_kScale = rkScale;
    m_bIsIdentity = false;
    m_bIsUniformScale = false;
}
//----------------------------------------------------------------------------
void Transformation::SetUniformScale (fixed fScale)
{
    assert(m_bIsRSMatrix && fScale != FIXED_ZERO);
    m_kScale = Vector3x(fScale,fScale,fScale);
    m_bIsIdentity = false;
    m_bIsUniformScale = true;
}
//----------------------------------------------------------------------------
void Transformation::SetMatrix (const Matrix3x& rkMatrix)
{
    m_kMatrix = rkMatrix;
    m_bIsIdentity = false;
    m_bIsRSMatrix = false;
    m_bIsUniformScale = false;
}
//----------------------------------------------------------------------------
Vector3x Transformation::ApplyForward (const Vector3x& rkInput) const
{
    if (m_bIsIdentity)
    {
        // Y = X
        return rkInput;
    }

    if (m_bIsRSMatrix)
    {
        // Y = R*S*X + T
        Vector3x kOutput(m_kScale.X()*rkInput.X(),m_kScale.Y()*rkInput.Y(),
            m_kScale.Z()*rkInput.Z());
        kOutput = m_kMatrix*kOutput + m_kTranslate;
        return kOutput;
    }

    // Y = M*X + T
    Vector3x kOutput = m_kMatrix*rkInput + m_kTranslate;
    return kOutput;
}
//----------------------------------------------------------------------------
void Transformation::ApplyForward (int iQuantity, const Vector3x* akInput,
    Vector3x* akOutput) const
{
    if (m_bIsIdentity)
    {
        // Y = X
        size_t uiSize = iQuantity*sizeof(Vector3x);
        System::Memcpy(akOutput,uiSize,akInput,uiSize);
    }
    else
    {
        int i;
        if (m_bIsRSMatrix)
        {
            // Y = R*S*X + T
            for (i = 0; i < iQuantity; i++)
            {
                akOutput[i].X() = m_kScale.X()*akInput[i].X();
                akOutput[i].Y() = m_kScale.Y()*akInput[i].Y();
                akOutput[i].Z() = m_kScale.Z()*akInput[i].Z();
                akOutput[i] = m_kMatrix*akOutput[i] + m_kTranslate;
            }
        }
        else
        {
            // Y = M*X + T
            for (i = 0; i < iQuantity; i++)
            {
                akOutput[i] = m_kMatrix*akInput[i] + m_kTranslate;
            }
        }
    }
}
//----------------------------------------------------------------------------
Vector3x Transformation::ApplyInverse (const Vector3x& rkInput) const
{
    if (m_bIsIdentity)
    {
        // X = Y
        return rkInput;
    }

    Vector3x kOutput = rkInput - m_kTranslate;
    if (m_bIsRSMatrix)
    {
        // X = S^{-1}*R^t*(Y - T)
        kOutput = kOutput*m_kMatrix;
        if (m_bIsUniformScale)
        {
            kOutput /= GetUniformScale();
        }
        else
        {
            // The direct inverse scaling is
            //   kOutput.X() /= m_kScale.X();
            //   kOutput.Y() /= m_kScale.Y();
            //   kOutput.Z() /= m_kScale.Z();
            // When division is much more expensive than multiplication,
            // three divisions are replaced by one division and nine
            // multiplications.
            fixed fSXY = m_kScale.X()*m_kScale.Y();
            fixed fSXYZ = fSXY*m_kScale.Z();
            fixed fInvSXYZ = FIXED_ONE/fSXYZ;
            fixed fInvSXY = fInvSXYZ*m_kScale.Z();
            fixed fInvXScale = fInvSXY*m_kScale.Y();
            fixed fInvYScale = fInvSXY*m_kScale.X();
            fixed fInvZScale = fInvSXYZ*fSXY;
            kOutput.X() *= fInvXScale;
            kOutput.Y() *= fInvYScale;
            kOutput.Z() *= fInvZScale;
        }
    }
    else
    {
        // X = M^{-1}*(Y - T)
        kOutput = m_kMatrix.Inverse()*kOutput;
    }

    return kOutput;
}
//----------------------------------------------------------------------------
void Transformation::ApplyInverse (int iQuantity, const Vector3x* akInput,
    Vector3x* akOutput) const
{
    if (m_bIsIdentity)
    {
        // X = Y
        size_t uiSize = iQuantity*sizeof(Vector3x);
        System::Memcpy(akOutput,uiSize,akInput,uiSize);
        return;
    }

    Vector3x kDiff;
    int i;
    if (m_bIsRSMatrix)
    {
        // X = S^{-1}*R^t*(Y - T)
        if (m_bIsUniformScale)
        {
            fixed fInvScale = FIXED_ONE/GetUniformScale();
            for (i = 0; i < iQuantity; i++)
            {
                kDiff = akInput[i] - m_kTranslate;
                akOutput[i] = fInvScale*(kDiff*m_kMatrix);
            }
        }
        else
        {
            // The direct inverse scaling is
            //   fInvXScale = 1.0f/m_kScale.X();
            //   fInvYScale = 1.0f/m_kScale.Y();
            //   fInvZScale = 1.0f/m_kScale.Z();
            // When division is much more expensive than multiplication, three
            // divisions are replaced by one division and ten multiplications.
            fixed fSXY = m_kScale.X()*m_kScale.Y();
            fixed fSXYZ = fSXY*m_kScale.Z();
            fixed fInvSXYZ = FIXED_ONE/fSXYZ;
            fixed fInvSXY = fInvSXYZ*m_kScale.Z();
            fixed fInvXScale = fInvSXY*m_kScale.Y();
            fixed fInvYScale = fInvSXY*m_kScale.X();
            fixed fInvZScale = fInvSXYZ*fSXY;
            for (i = 0; i < iQuantity; i++)
            {
                kDiff = akInput[i] - m_kTranslate;
                akOutput[i] = kDiff*m_kMatrix;
                akOutput[i].X() *= fInvXScale;
                akOutput[i].Y() *= fInvYScale;
                akOutput[i].Z() *= fInvZScale;
            }
        }
    }
    else
    {
        // X = M^{-1}*(Y - T)
        Matrix3x kInverse = m_kMatrix.Inverse();
        for (i = 0; i < iQuantity; i++)
        {
            kDiff = akInput[i] - m_kTranslate;
            akOutput[i] = kInverse*kDiff;
        }
    }
}
//----------------------------------------------------------------------------
Vector3x Transformation::InvertVector (const Vector3x& rkInput) const
{
    if ( m_bIsIdentity )
    {
        // X = Y
        return rkInput;
    }

    Vector3x kOutput;
    if (m_bIsRSMatrix)
    {
        // X = S^{-1}*R^t*Y
        kOutput = rkInput*m_kMatrix;
        if (m_bIsUniformScale)
        {
            kOutput /= GetUniformScale();
        }
        else
        {
            // The direct inverse scaling is
            //   kOutput.X() /= m_kScale.X();
            //   kOutput.Y() /= m_kScale.Y();
            //   kOutput.Z() /= m_kScale.Z();
            // When division is much more expensive than multiplication,
            // three divisions are replaced by one division and ten
            // multiplications.
            fixed fSXY = m_kScale.X()*m_kScale.Y();
            fixed fSXYZ = fSXY*m_kScale.Z();
            fixed fInvSXYZ = FIXED_ONE/fSXYZ;
            fixed fInvSXY = fInvSXYZ*m_kScale.Z();
            fixed fInvXScale = fInvSXY*m_kScale.Y();
            fixed fInvYScale = fInvSXY*m_kScale.X();
            fixed fInvZScale = fInvSXYZ*fSXY;
            kOutput.X() *= fInvXScale;
            kOutput.Y() *= fInvYScale;
            kOutput.Z() *= fInvZScale;
        }
    }
    else
    {
        // X = M^{-1}*Y
        kOutput = m_kMatrix.Inverse()*rkInput;
    }

    return kOutput;
}
//----------------------------------------------------------------------------
Plane3x Transformation::ApplyForward (const Plane3x& rkInput) const
{
    if (m_bIsIdentity)
    {
        return rkInput;
    }

    Plane3x kOutput;
    if (m_bIsRSMatrix)
    {
        // Let X represent points in model space and Y = R*S*X+T represent
        // points in world space where S are the world scales, R is the world
        // rotation, and T is the world translation.  The inverse transform is
        // X = S^{-1}*R^t*(Y-T).  The model plane is Dot(N0,X) = C0.
        // Replacing the formula for X in it and applying some algebra leads
        // to the world plane Dot(N1,Y) = C1 where N1 = R*S^{-1}*N0 and
        // C1 = C0+Dot(N1,T).  If S is not the identity, then N1 is not unit
        // length.  We need to normalize N1 and adjust C1:  N1' = N1/|N1| and
        // C1' = C1/|N1|.
        if (m_bIsUniformScale)
        {
            kOutput.Normal = m_kMatrix*rkInput.Normal;
            kOutput.Constant = GetUniformScale()*rkInput.Constant +
                kOutput.Normal.Dot(m_kTranslate);
            return kOutput;
        }

        kOutput.Normal = rkInput.Normal;

        // The direct inverse scaling is
        //   kOutput.X() /= m_kScale.X();
        //   kOutput.Y() /= m_kScale.Y();
        //   kOutput.Z() /= m_kScale.Z();
        // When division is much more expensive than multiplication,
        // three divisions are replaced by one division and ten
        // multiplications.
        fixed fSXY = m_kScale.X()*m_kScale.Y();
        fixed fSXYZ = fSXY*m_kScale.Z();
        fixed fInvSXYZ = FIXED_ONE/fSXYZ;
        fixed fInvSXY = fInvSXYZ*m_kScale.Z();
        fixed fInvXScale = fInvSXY*m_kScale.Y();
        fixed fInvYScale = fInvSXY*m_kScale.X();
        fixed fInvZScale = fInvSXYZ*fSXY;
        kOutput.Normal.X() *= fInvXScale;
        kOutput.Normal.Y() *= fInvYScale;
        kOutput.Normal.Z() *= fInvZScale;
        kOutput.Normal = m_kMatrix*kOutput.Normal;
    }
    else
    {
        // Let X represent points in model space and Y = M*X+T represent
        // points in world space.  The inverse transform is X = M^{-1}*(Y-T).
        // The model plane is Dot(N0,X) = C0.  Replacing the formula for X in
        // it and applying some algebra leads to the world plane
        // Dot(N1,Y) = C1 where N1 = M^{-T}*N0/|M^{-1}*N0| (superscript -T
        // denotes the transpose of the inverse) and
        // C1 = C0/|M^{-1}*N0|+Dot(N1,T).
        Matrix3x kInverse = m_kMatrix.Inverse();
        kOutput.Normal = rkInput.Normal*kInverse;
    }

    fixed fInvLength = FIXED_ONE/kOutput.Normal.Length();
    kOutput.Normal *= fInvLength;
    kOutput.Constant = fInvLength*rkInput.Constant +
        kOutput.Normal.Dot(m_kTranslate);

    return kOutput;
}
//----------------------------------------------------------------------------
void Transformation::Product (const Transformation& rkA,
    const Transformation& rkB)
{
    if (rkA.IsIdentity())
    {
        *this = rkB;
        return;
    }

    if (rkB.IsIdentity())
    {
        *this = rkA;
        return;
    }

    if (rkA.m_bIsRSMatrix && rkB.m_bIsRSMatrix)
    {
        if (rkA.m_bIsUniformScale)
        {
            SetRotate(rkA.m_kMatrix*rkB.m_kMatrix);

            SetTranslate(rkA.GetUniformScale()*(
                rkA.m_kMatrix*rkB.m_kTranslate) + rkA.m_kTranslate);

            if (rkB.IsUniformScale())
            {
                SetUniformScale(rkA.GetUniformScale()*rkB.GetUniformScale());
            }
            else
            {
                SetScale(rkA.GetUniformScale()*rkB.GetScale());
            }

            return;
        }
    }

    // In all remaining cases, the matrix cannot be written as R*S*X+T.
    Matrix3x kMA = (rkA.m_bIsRSMatrix ?
        rkA.m_kMatrix.TimesDiagonal(rkA.m_kScale) :
        rkA.m_kMatrix);

    Matrix3x kMB = (rkB.m_bIsRSMatrix ?
        rkB.m_kMatrix.TimesDiagonal(rkB.m_kScale) :
        rkB.m_kMatrix);

    SetMatrix(kMA*kMB);
    SetTranslate(kMA*rkB.m_kTranslate+rkA.m_kTranslate);
}
//----------------------------------------------------------------------------
void Transformation::Inverse (Transformation& rkInverse) const
{
    if (m_bIsIdentity)
    {
        rkInverse = *this;
        return;
    }

    if (m_bIsRSMatrix)
    {
        if (m_bIsUniformScale)
        {
            rkInverse.m_kMatrix = GetRotate().Transpose()/GetUniformScale();
        }
        else
        {
            Matrix3x kRS = m_kMatrix.TimesDiagonal(m_kScale);
            rkInverse.m_kMatrix = kRS.Inverse();
        }
    }
    else
    {
        rkInverse.m_kMatrix = m_kMatrix.Inverse();
    }

    rkInverse.m_kTranslate = -(rkInverse.m_kMatrix*m_kTranslate);
    rkInverse.m_bIsIdentity = false;
    rkInverse.m_bIsRSMatrix = false;
    rkInverse.m_bIsUniformScale = false;
}
//----------------------------------------------------------------------------
