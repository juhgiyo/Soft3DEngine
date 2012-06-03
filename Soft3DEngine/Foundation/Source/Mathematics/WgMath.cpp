///////////////////////////////////////////////////////////
//                                                       //
//                    WgMath.cpp                         //
//                                                       //
//  - Implementation for Math class                      //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.06                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgMath.h"

namespace WGSoft3D
{
const fixed Mathx::EPSILON = FixedFromFloat(FLT_EPSILON);
const fixed Mathx::ZERO_TOLERANCE = FixedFromFloat(1e-06f);
const fixed Mathx::MAX_REAL = FixedFromFloat(FLT_MAX);
const fixed Mathx::PI = FixedFromFloat((float)4.0*atan(1.0));
const fixed Mathx::TWO_PI = FixedFromFloat((float)(4.0*atan(1.0)*2.0));
const fixed Mathx::HALF_PI = FixedFromFloat((float)(4.0*atan(1.0)*0.5));
const fixed Mathx::INV_PI = FixedFromFloat(1.0f/((float)4.0*atan(1.0)));
const fixed Mathx::INV_TWO_PI = FixedFromFloat(1.0f/((float)(4.0*atan(1.0)*2.0)));
const fixed Mathx::DEG_TO_RAD = FixedFromFloat(((float)4.0*atan(1.0))/180.0f);
const fixed Mathx::RAD_TO_DEG = FixedFromFloat(180.0f/((float)4.0*atan(1.0)));
const fixed Mathx::LN_2 = FixedFromFloat(Math<float>::Log(2.0f));
const fixed Mathx::LN_10 = FixedFromFloat(Math<float>::Log(10.0f));
const fixed Mathx::INV_LN_2 = FixedFromFloat(1.0f/(Math<float>::Log(2.0f)));
const fixed Mathx::INV_LN_10 = FixedFromFloat(1.0f/(Math<float>::Log(10.0f)));

template<> const float Math<float>::EPSILON = FLT_EPSILON;
template<> const float Math<float>::ZERO_TOLERANCE = 1e-06f;
template<> const float Math<float>::MAX_REAL = FLT_MAX;
template<> const float Math<float>::PI = (float)(4.0*atan(1.0));
template<> const float Math<float>::TWO_PI = 2.0f*Math<float>::PI;
template<> const float Math<float>::HALF_PI = 0.5f*Math<float>::PI;
template<> const float Math<float>::INV_PI = 1.0f/Math<float>::PI;
template<> const float Math<float>::INV_TWO_PI = 1.0f/Math<float>::TWO_PI;
template<> const float Math<float>::DEG_TO_RAD = Math<float>::PI/180.0f;
template<> const float Math<float>::RAD_TO_DEG = 180.0f/Math<float>::PI;
template<> const float Math<float>::LN_2 = Math<float>::Log(2.0f);
template<> const float Math<float>::LN_10 = Math<float>::Log(10.0f);
template<> const float Math<float>::INV_LN_2 = 1.0f/Math<float>::LN_2;
template<> const float Math<float>::INV_LN_10 = 1.0f/Math<float>::LN_10;

template<> const double Math<double>::EPSILON = DBL_EPSILON;
template<> const double Math<double>::ZERO_TOLERANCE = 1e-08;
template<> const double Math<double>::MAX_REAL = DBL_MAX;
template<> const double Math<double>::PI = 4.0*atan(1.0);
template<> const double Math<double>::TWO_PI = 2.0*Math<double>::PI;
template<> const double Math<double>::HALF_PI = 0.5*Math<double>::PI;
template<> const double Math<double>::INV_PI = 1.0/Math<double>::PI;
template<> const double Math<double>::INV_TWO_PI = 1.0/Math<double>::TWO_PI;
template<> const double Math<double>::DEG_TO_RAD = Math<double>::PI/180.0;
template<> const double Math<double>::RAD_TO_DEG = 180.0/Math<double>::PI;
template<> const double Math<double>::LN_2 = Math<double>::Log(2.0);
template<> const double Math<double>::LN_10 = Math<double>::Log(10.0);
template<> const double Math<double>::INV_LN_2 = 1.0/Math<double>::LN_2;
template<> const double Math<double>::INV_LN_10 = 1.0/Math<double>::LN_10;


//----------------------------------------------------------------------------
//
// Fixed Math Implementation
//
//----------------------------------------------------------------------------
fixed Mathx::ACos (fixed fValue)
{
    if (fValue>FIXED_NEG_ONE)
    {
        if (fValue < FIXED_ONE)
        {
            return fixed(FixedFromFloat((float)acos((double)FloatFromFixed(fValue))));
        }
        else
        {
            return fixed(FIXED_ZERO);
        }
    }
    else
    {
        return Mathx::PI;
    }
}
//----------------------------------------------------------------------------

fixed Mathx::ASin (fixed fValue)
{
    if ( fValue>FIXED_NEG_ONE)
    {
        if (fValue < FIXED_ONE)
        {
            return fixed(FixedFromFloat((float)asin((double)FloatFromFixed(fValue))));
        }
        else
        {
            return Mathx::HALF_PI;
        }
    }
    else
    {
        return -Mathx::HALF_PI;
    }
}
//----------------------------------------------------------------------------

fixed Mathx::ATan (fixed fValue)
{
    return fixed(FixedFromFloat((float)atan((double)FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::ATan2 (fixed fY, fixed fX)
{
    return fixed(FixedFromFloat((float)atan2((double)FloatFromFixed(fY),(double)FloatFromFixed(fX))));
}
//----------------------------------------------------------------------------

fixed Mathx::Ceil (fixed fValue)
{
    return fixed(FixedFromFloat((float)ceil((double)FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::Cos (fixed fValue)
{
    return fixed(FixedFromFloat(cos(FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::Exp (fixed fValue)
{
    return fixed(FixedFromFloat((float)exp((double)FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::FAbs (fixed fValue)
{
    return fixed(FixedFromFloat(fabs(FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::Floor (fixed fValue)
{
    return fixed(FixedFromFloat((float)floor((double)FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::FMod (fixed fX, fixed fY)
{
    return fixed(FixedFromFloat((float)fmod((double)FloatFromFixed(fX),(double)FloatFromFixed(fY))));
}
//----------------------------------------------------------------------------

fixed Mathx::InvSqrt (fixed fValue)
{

    return fixed(FixedFromFloat((float)(1.0/sqrt(FloatFromFixed(fValue)))));
}
//----------------------------------------------------------------------------

fixed Mathx::Log (fixed fValue)
{
    return fixed(FixedFromFloat((float)log((double)FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::Log2 (fixed fValue)
{
    return fixed(FixedFromFloat(Mathf::Log2(FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::Log10 (fixed fValue)
{
    return fixed(FixedFromFloat(Mathf::Log10(FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::Pow (fixed fBase, fixed fExponent)
{
    return fixed(FixedFromFloat(Mathf::Pow(FloatFromFixed(fBase),FloatFromFixed(fExponent))));
}
//----------------------------------------------------------------------------
fixed Mathx::Sin (fixed fValue)
{
    return fixed(FixedFromFloat(Mathf::Sin(FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::Sqr (fixed fValue)
{
    return fixed(FixedFromFloat(Mathf::Sqr(FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::Sqrt (fixed fValue)
{
    return fixed(FixedFromFloat(Mathf::Sqrt(FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------

fixed Mathx::Tan (fixed fValue)
{
    return fixed(FixedFromFloat((float)tan((double)FloatFromFixed(fValue))));
}
//----------------------------------------------------------------------------


fixed Mathx::Sign (fixed fValue)
{
    if (fValue > FIXED_ZERO)
    {
        return fixed(FIXED_ONE);
    }
	
    if (fValue < FIXED_ZERO)
    {
        return fixed(FIXED_NEG_ONE);
    }
	
    return fixed(FIXED_ZERO);
}
//----------------------------------------------------------------------------

fixed Mathx::UnitRandom (unsigned int uiSeed)
{
    if (uiSeed > 0)
    {
        srand(uiSeed);
    }
	
    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return fixed(FixedFromFloat((float)dRatio));
}
//----------------------------------------------------------------------------

fixed Mathx::SymmetricRandom (unsigned int uiSeed)
{
    if (uiSeed > 0.0)
    {
        srand(uiSeed);
    }
	
    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return fixed(FixedFromFloat((float)(2.0*dRatio - 1.0)));
}
//----------------------------------------------------------------------------

fixed Mathx::IntervalRandom (fixed fMin, fixed fMax, unsigned int uiSeed)
{
    if (uiSeed > 0)
    {
        srand(uiSeed);
    }
	
    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return fMin+(fMax-fMin)* fixed(FixedFromFloat(((float)dRatio)));
}
//----------------------------------------------------------------------------

fixed Mathx::FastSin0 (fixed fAngle)
{
    fixed fASqr = fAngle*fAngle;
    fixed fResult = FixedFromFloat((float)7.61e-03);
    fResult *= fASqr;
    fResult -= FixedFromFloat((float)1.6605e-01);
    fResult *= fASqr;
    fResult += FIXED_ONE;
    fResult *= fAngle;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastSin1 (fixed fAngle)
{
    fixed fASqr = fAngle*fAngle;
    fixed fResult = -FixedFromFloat((float)2.39e-08);
    fResult *= fASqr;
    fResult += FixedFromFloat((float)2.7526e-06);
    fResult *= fASqr;
    fResult -= FixedFromFloat((float)1.98409e-04);
    fResult *= fASqr;
    fResult += FixedFromFloat((float)8.3333315e-03);
    fResult *= fASqr;
    fResult -= FixedFromFloat((float)1.666666664e-01);
    fResult *= fASqr;
    fResult += FIXED_ONE;
    fResult *= fAngle;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastCos0 (fixed fAngle)
{
    fixed fASqr = fAngle*fAngle;
    fixed fResult = FixedFromFloat((float)3.705e-02);
    fResult *= fASqr;
    fResult -= FixedFromFloat((float)4.967e-01);
    fResult *= fASqr;
    fResult += FIXED_ONE;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastCos1 (fixed fAngle)
{
    fixed fASqr = fAngle*fAngle;
    fixed fResult = FixedFromFloat(-(float)2.605e-07);
    fResult *= fASqr;
    fResult += FixedFromFloat((float)2.47609e-05);
    fResult *= fASqr;
    fResult -= FixedFromFloat((float)1.3888397e-03);
    fResult *= fASqr;
    fResult += FixedFromFloat((float)4.16666418e-02);
    fResult *= fASqr;
    fResult -= FixedFromFloat((float)4.999999963e-01);
    fResult *= fASqr;
    fResult += FIXED_ONE;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastTan0 (fixed fAngle)
{
    fixed fASqr = fAngle*fAngle;
    fixed fResult = FixedFromFloat((float)2.033e-01);
    fResult *= fASqr;
    fResult += FixedFromFloat((float)3.1755e-01);
    fResult *= fASqr;
    fResult += FIXED_ONE;
    fResult *= fAngle;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastTan1 (fixed fAngle)
{
    fixed fASqr = fAngle*fAngle;
    fixed fResult = FixedFromFloat((float)9.5168091e-03);
    fResult *= fASqr;
    fResult += FixedFromFloat((float)2.900525e-03);
    fResult *= fASqr;
    fResult += FixedFromFloat((float)2.45650893e-02);
    fResult *= fASqr;
    fResult += FixedFromFloat((float)5.33740603e-02);
    fResult *= fASqr;
    fResult += FixedFromFloat((float)1.333923995e-01);
    fResult *= fASqr;
    fResult += FixedFromFloat((float)3.333314036e-01);
    fResult *= fASqr;
    fResult += FIXED_ONE;
    fResult *= fAngle;
    return fResult;
}
//----------------------------------------------------------------------------

fixed Mathx::FastInvSin0 (fixed fValue)
{
    fixed fRoot = Mathx::Sqrt(fixed(FIXED_ONE)-fValue);
    fixed fResult = FixedFromFloat(-(float)0.0187293);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0742610);
    fResult *= fValue;
    fResult -= FixedFromFloat((float)0.2121144);
    fResult *= fValue;
    fResult += FixedFromFloat((float)1.5707288);
    fResult = Mathx::HALF_PI - fRoot*fResult;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastInvSin1 (fixed fValue)
{
    fixed fRoot = Mathx::Sqrt(FAbs(fixed(FIXED_ONE)-fValue));
    fixed fResult = FixedFromFloat(-(float)0.0012624911);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0066700901);
    fResult *= fValue;
    fResult -= FixedFromFloat((float)0.0170881256);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0308918810);
    fResult *= fValue;
    fResult -= FixedFromFloat((float)0.0501743046);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0889789874);
    fResult *= fValue;
    fResult -= FixedFromFloat((float)0.2145988016);
    fResult *= fValue;
    fResult += FixedFromFloat((float)1.5707963050);
    fResult = Mathx::HALF_PI - fRoot*fResult;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastInvCos0 (fixed fValue)
{
    fixed fRoot = Mathx::Sqrt(fixed(FIXED_ONE)-fValue);
    fixed fResult = FixedFromFloat(-(float)0.0187293);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0742610);
    fResult *= fValue;
    fResult -= FixedFromFloat((float)0.2121144);
    fResult *= fValue;
    fResult += FixedFromFloat((float)1.5707288);
    fResult *= fRoot;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastInvCos1 (fixed fValue)
{
    fixed fRoot = Mathx::Sqrt(FAbs(fixed(FIXED_ONE)-fValue));
    fixed fResult = FixedFromFloat(-(float)0.0012624911);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0066700901);
    fResult *= fValue;
    fResult -= FixedFromFloat((float)0.0170881256);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0308918810);
    fResult *= fValue;
    fResult -= FixedFromFloat((float)0.0501743046);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0889789874);
    fResult *= fValue;
    fResult -= FixedFromFloat((float)0.2145988016);
    fResult *= fValue;
    fResult += FixedFromFloat((float)1.5707963050);
    fResult *= fRoot;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastInvTan0 (fixed fValue)
{
    fixed fVSqr = fValue*fValue;
    fixed fResult = FixedFromFloat((float)0.0208351);
    fResult *= fVSqr;
    fResult -= FixedFromFloat((float)0.085133);
    fResult *= fVSqr;
    fResult += FixedFromFloat((float)0.180141);
    fResult *= fVSqr;
    fResult -= FixedFromFloat((float)0.3302995);
    fResult *= fVSqr;
    fResult += FixedFromFloat((float)0.999866);
    fResult *= fValue;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastInvTan1 (fixed fValue)
{
    fixed fVSqr = fValue*fValue;
    fixed fResult = FixedFromFloat((float)0.0028662257);
    fResult *= fVSqr;
    fResult -= FixedFromFloat((float)0.0161657367);
    fResult *= fVSqr;
    fResult += FixedFromFloat((float)0.0429096138);
    fResult *= fVSqr;
    fResult -= FixedFromFloat((float)0.0752896400);
    fResult *= fVSqr;
    fResult += FixedFromFloat((float)0.1065626393);
    fResult *= fVSqr;
    fResult -= FixedFromFloat((float)0.1420889944);
    fResult *= fVSqr;
    fResult += FixedFromFloat((float)0.1999355085);
    fResult *= fVSqr;
    fResult -= FixedFromFloat((float)0.3333314528);
    fResult *= fVSqr;
    fResult += FIXED_ONE;
    fResult *= fValue;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastNegExp0 (fixed fValue)
{
    fixed fResult = FixedFromFloat((float)0.0038278);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0292732);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.2507213);
    fResult *= fValue;
    fResult += FIXED_ONE;
    fResult *= fResult;
    fResult *= fResult;
    fResult = FIXED_ONE/fResult;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastNegExp1 (fixed fValue)
{
    fixed fResult =FixedFromFloat((float)0.00026695);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.00227723);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.03158565);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.24991035);
    fResult *= fValue;
    fResult += FIXED_ONE;
    fResult *= fResult;
    fResult *= fResult;
    fResult = FIXED_ONE/fResult;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastNegExp2 (fixed fValue)
{
    fixed fResult = FixedFromFloat((float)0.000014876);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.000127992);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.002673255);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.031198056);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.250010936);
    fResult *= fValue;
    fResult += FIXED_ONE;
    fResult *= fResult;
    fResult *= fResult;
    fResult = FIXED_ONE/fResult;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

fixed Mathx::FastNegExp3 (fixed fValue)
{
    fixed fResult = FixedFromFloat((float)0.0000006906);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0000054302);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0001715620);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0025913712);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.0312575832);
    fResult *= fValue;
    fResult += FixedFromFloat((float)0.2499986842);
    fResult *= fValue;
    fResult += FIXED_ONE;
    fResult *= fResult;
    fResult *= fResult;
    fResult = FIXED_ONE/fResult;
    return fixed(fResult);
}
//----------------------------------------------------------------------------

}
