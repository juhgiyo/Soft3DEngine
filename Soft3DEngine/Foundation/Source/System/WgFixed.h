///////////////////////////////////////////////////////////
//                                                       //
//                    WgFixed.h                          //
//                                                       //
//  - Interface for Fixed Precision class                //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////
#include "WgFoundationLIB.h"

#ifndef __WG3D_FIXED_H__
#define __WG3D_FIXED_H__
namespace WGSoft3D
{
#define FIXED_PRECISION 16
#define FIXED_ONE (1<<FIXED_PRECISION)
#define FIXED_ZERO	  0						// representation of 0
#define FIXED_HALF	  0x08000				// 0.5 
#define FIXED_NEG_ONE ((-1)<<FIXED_PRECISION)

#define FIXED_2PI		FixedFromFloat(6.28318530717958647692f)
#define FIXED_R2PI		FixedFromFloat(1.0f/6.28318530717958647692f)

//typedef int fixed;
typedef unsigned int ufixed;
typedef __int64	dfixed;


// Fixed as Int Mathematic Operation
inline int xMul(int a, int b);
inline int xDiv(int a, int b); 

inline int FixedFromInt(int value);
inline int FixedFromFloat(float value);
inline float FloatFromFixed(int value);
inline int   IntFromFixed(int value);
inline int   FractionFromFixed(int value);
WG3D_FOUNDATION_ITEM ufixed CountLeadingZeros(ufixed x);

static inline int xabs(int value);
WG3D_FOUNDATION_ITEM int xsqrt(int value);
WG3D_FOUNDATION_ITEM int sinx(int value);
WG3D_FOUNDATION_ITEM int cosx(int value);
WG3D_FOUNDATION_ITEM int powx(int value, int exponent);

static inline int xMin(int first, int second);
static inline int xMax(int first, int second);

WG3D_FOUNDATION_ITEM int Inverse(int value);
WG3D_FOUNDATION_ITEM int InvSqrt(int value);
inline int FastSqrt(int value);

// Fixed class Mathematic Operation
class fixed;
inline fixed xMul(fixed a, fixed b);
inline fixed xDiv(fixed a, fixed b); 

//inline fixed FixedFromInt(int value);
//inline fixed FixedFromFloat(float value);
inline float FloatFromFixed(fixed value);
inline int   IntFromFixed(fixed value);
inline int   FractionFromFixed(fixed value);

static inline fixed xabs(fixed value);
WG3D_FOUNDATION_ITEM fixed xsqrt(fixed value);
WG3D_FOUNDATION_ITEM fixed sinx(fixed value);
WG3D_FOUNDATION_ITEM fixed cosx(fixed value);
WG3D_FOUNDATION_ITEM fixed powx(fixed value, fixed exponent);

static inline fixed xMin(fixed first, fixed second);
static inline fixed xMax(fixed first, fixed second);

WG3D_FOUNDATION_ITEM fixed Inverse(fixed value);
WG3D_FOUNDATION_ITEM fixed InvSqrt(fixed value);
inline fixed FastSqrt(fixed value);


class fixed{
public:
	fixed()
	{
		value=FIXED_ZERO;
	}
	fixed(const int x)
	{
		value=x;
	}
	fixed(const fixed &rkF)
	{
		value=rkF.value;
	}
	inline fixed& operator =(const fixed &rkF)
	{
		value=rkF.value;
		return *this;
	}
	inline fixed& operator =(const int val)
	{
		value=val;
		return *this;
	}

	// comparison
    bool operator== (const fixed& rkF) const
	{
		return value==rkF.value;
	}
    bool operator!= (const fixed& rkF) const
	{
		return value!=rkF.value;
	}
    bool operator<  (const fixed& rkF) const
	{
		return (value<rkF.value);
	}
    bool operator<= (const fixed& rkF) const
	{
		return (value<=rkF.value);
	}
    bool operator>  (const fixed& rkF) const
	{
		return (value>rkF.value);
	}
    bool operator>= (const fixed& rkF) const
	{
		return (value>=rkF.value);
	}

	bool operator== (const int val) const
	{
		return value==val;
	}
    bool operator!= (const int val) const
	{
		return value!=val;
	}
    bool operator<  (const int val) const
	{
		return value<val;
	}
    bool operator<= (const int val) const
	{
		return value<=val;
	}
    bool operator>  (const int val) const
	{
		return value>val;
	}
    bool operator>= (const int val) const
	{
		return value>=val;
	}

	inline fixed operator+ (const fixed& rkF) const
	{
		return fixed(value+rkF.value);
	}
    inline fixed operator- (const fixed& rkF) const
	{
		return fixed(value-rkF.value);
	}
    inline fixed operator* (const fixed& rkF) const
	{
		float val1=FloatFromFixed(value);
		float val2=FloatFromFixed(rkF);
		return fixed(FixedFromFloat(val1*val2));
	}
    inline fixed operator/ (const fixed& rkF) const
	{
		float val1=FloatFromFixed(value);
		float val2=FloatFromFixed(rkF);
		return fixed(FixedFromFloat(val1/val2));
	}

	inline fixed operator+ (const int val) const
	{
		return fixed(value+val);
	}
	inline fixed operator- (const int val) const
	{
		return fixed(value-val);
	}
    inline fixed operator* (const int val) const
	{
		float val1=FloatFromFixed(value);
		float val2=FloatFromFixed(val);
		return fixed(FixedFromFloat(val1*val2));
	}
    inline fixed operator/ (const int val) const
	{
		float val1=FloatFromFixed(value);
		float val2=FloatFromFixed(val);
		return fixed(FixedFromFloat(val1/val2));
	}
    inline fixed operator- () const
	{
		float x=FloatFromFixed(value);
		x*=-1.0f;
		return fixed(FixedFromFloat(x));
	}
	inline fixed operator+ () const
	{
		float x=FloatFromFixed(value);
		x = +x;
		return fixed(FixedFromFloat(x));
	}
	
    // arithmetic updates
    inline fixed& operator+= (const fixed& rkF)
	{
		value+=rkF.value;
		return *this;
	}
    inline fixed& operator-= (const fixed& rkF)
	{
		value-=rkF.value;
		return *this;
	}
    inline fixed& operator*= (const fixed& rkF)
	{
		float val1=FloatFromFixed(value);
		float val2=FloatFromFixed(rkF);
		value=FixedFromFloat(val1*val2);
		return *this;
	}
    inline fixed& operator/= (const fixed& rkF)
	{
		float val1=FloatFromFixed(value);
		float val2=FloatFromFixed(rkF);
		value= FixedFromFloat(val1/val2);
		return *this;
	}

    inline fixed& operator+= (const int val)
	{
		value+=val;
		return *this;
	}
    inline fixed& operator-= (const int val)
	{
		value-=val;
		return *this;
	}
    inline fixed& operator*= (const int val)
	{
		float val1=FloatFromFixed(value);
		float val2=FloatFromFixed(val);
		value=FixedFromFloat(val1*val2);
		return *this;
	}
    inline fixed& operator/= (const int val)
	{
		float val1=FloatFromFixed(value);
		float val2=FloatFromFixed(val);
		value= FixedFromFloat(val1/val2);
		return *this;
	}
	int value;
};

// Global Fixed Arithmetic Operator
inline int operator *(const int &val,const fixed &val2)
{
	float fval1=FloatFromFixed(val);
	float fval2=FloatFromFixed(val2);
	return FixedFromFloat(fval1*fval2);
}
inline int operator /(const int &val, const fixed &val2)
{
	float fval1=FloatFromFixed(val);
	float fval2=FloatFromFixed(val2);
	return FixedFromFloat(fval1/fval2);
}
inline int operator +(const int &val,const fixed &val2)
{
	return val-val2.value;
}
inline int operator -(const int &val, const fixed &val2)
{
	return val-val2.value;
}

// Global Fixed Comparison Operator
inline bool operator== (const int &val, const fixed &val2)
{
	return val==val2.value;
}
inline bool operator!= (const int &val, const fixed &val2)
{
	return val!=val2.value;
}
inline bool operator<  (const int &val, const fixed &val2)
{
	return val<val2.value;
}
inline bool operator<= (const int &val, const fixed &val2)
{
	return val<=val2.value;
}
inline bool operator>  (const int &val, const fixed &val2)
{
	return val>val2.value;
}
inline bool operator>= (const int &val, const fixed &val2)
{
	return val>=val2.value;
}
#include "WgFixed.inl"
}
#endif