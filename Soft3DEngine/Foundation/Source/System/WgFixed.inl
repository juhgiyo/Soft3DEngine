///////////////////////////////////////////////////////////
//                                                       //
//                    WgFixed.inl                        //
//                                                       //
//  - Inlines for Fixed Precision class                  //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.01                                   //
//                                                       //
///////////////////////////////////////////////////////////
inline int FixedFromInt(int value)
{
	return value << FIXED_PRECISION;
}

inline int FixedFromFloat(float value)
{
	if (value >= 32767.5f)
		return 0x7fffffff;
	else if (value <= -32768.0f)
		return 0x80000000;
	else
		return static_cast<int>(value * static_cast<float>(FIXED_ONE));
}
inline float FloatFromFixed(int value)
{
	return static_cast<float>(static_cast<double>(value) * (1.0f/static_cast<float>(FIXED_ONE)));
}
inline int   IntFromFixed(int value)
{
	return value >> FIXED_PRECISION;
}
inline int FractionFromFixed(int value)
{
	return value & ((1 << FIXED_PRECISION) - 1);
}
static inline int xabs(int value)
{
	if (value < 0) 
	{
		return -value;
	} 
	else 
	{
		return value;
	}
}
static inline int xMin(int first, int second)
{
	return first < second ? first : second;
}

static inline int xMax(int first, int second)
{
	return first > second ? first : second;
}
inline int xMul(int a, int b)
{
	return (int) (((dfixed) a * (dfixed) b)  >> FIXED_PRECISION);
}
inline int xDiv(int a, int b)
{
	
	if ((b >> 24) && (b >> 24) + 1) {
		return xMul(a >> 8, Inverse(b >> 8));
	} else {
		return xMul(a, Inverse(b));
	}
}
inline int FastSqrt(int value)
{
	return value <= 0 ? 0 : Inverse(InvSqrt(value));
}


// inline fixed FixedFromInt(int value)
// {
// 	return fixed(FixedFromInt(value));
// }
// inline fixed FixedFromFloat(float value)
// {
// 	return fixed(FixedFromFloat(value));
// }
inline float FloatFromFixed(fixed value)
{
	return FloatFromFixed(value.value);
}
inline int   IntFromFixed(fixed value)
{
	return IntFromFixed(value.value);
}
inline int FractionFromFixed(fixed value)
{
	return FractionFromFixed(value.value);
}
static inline fixed xabs(fixed value)
{
	return fixed(xabs(value.value));
}
static inline fixed xMin(fixed first, fixed second)
{
	return fixed(xMin(first.value,second.value));
}
static inline fixed xMax(fixed first, fixed second)
{
	return fixed(xMax(first.value,second.value));
}
inline fixed xMul(fixed a, fixed b)
{
	return fixed(xMul(a.value,b.value));
}
inline fixed xDiv(fixed a, fixed b)
{
	return fixed(xDiv(a.value,b.value));
}
inline fixed FastSqrt(fixed value)
{
	return fixed(FastSqrt(value.value));
}