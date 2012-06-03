#include "WgFixed.h"
namespace WGSoft3D
{
static const dfixed __gl_rcp_tab[] = { /* domain 0.5 .. 1.0-1/16 */
	0x8000, 0x71c7, 0x6666, 0x5d17, 0x5555, 0x4ec4, 0x4924, 0x4444
};

ufixed CountLeadingZeros(ufixed x) {
	ufixed exp = 31;
	
	if (x & 0xffff0000) { 
		exp -= 16; 
		x >>= 16; 
	}
	
	if (x & 0xff00) { 
		exp -= 8; 
		x >>= 8; 
	}
	
	if (x & 0xf0) { 
		exp -= 4; 
		x >>= 4; 
	}
	
	if (x & 0xc) { 
		exp -= 2; 
		x >>= 2; 
	}
	
	if (x & 0x2) { 
		exp -= 1; 
	}
	
	return exp;
	}

int Inverse(int value)
{
	int exp;
	int x;
	
	if (value == FIXED_ZERO) 
		return 0x7fffffff;
	
	bool sign = false;
	
	if (value < 0) {
		sign = true;
		value = -value;
	}
	
	exp = CountLeadingZeros(value);
	x = ((int)__gl_rcp_tab[(value>>(28-exp))&0x7]) << 2;
	exp -= 16;
	
	if (exp <= 0)
		x >>= -exp;
	else
		x <<= exp;
	
	/* two iterations of newton-raphson  x = x(2-ax) */
	x = xMul(x,(FIXED_ONE*2 - xMul(value,x)));
	x = xMul(x,(FIXED_ONE*2 - xMul(value,x)));
	
	if (sign)
		return -x;
	else
		return x;
}



int InvSqrt(int value)
{
	
    int x; 
    
    static const ufixed __gl_rsq_tab[] = { /* domain 0.5 .. 1.0-1/16 */
		0xb504, 0xaaaa, 0xa1e8, 0x9a5f, 0x93cd, 0x8e00, 0x88d6, 0x8432,
    };
    int i, exp;
    if (value == FIXED_ZERO) return 0x7fffffff;
    if (value == FIXED_ONE) return value;
	
	exp = CountLeadingZeros(value);
    x = __gl_rsq_tab[(value>>(28-exp))&0x7]<<1;
	
    exp -= 16;
    if (exp <= 0)
		x >>= -exp>>1;
    else
		x <<= (exp>>1)+(exp&1);
    if (exp&1) x = xMul(x, __gl_rsq_tab[0]);
		
    i = 0;
    do {
	
		x = xMul((x>>1),(FIXED_ONE*3 - xMul(xMul(value,x),x)));
    } while(++i < 3);
	
    return x;
}

static const unsigned short __gl_sin_tab[] = {
#include "WgSinTable.h"
};

int cosx(int value)
{
	int v;
    /* reduce to [0,1) */
    while (value < FIXED_ZERO) value += FIXED_2PI;
    value *= FIXED_R2PI;
    value >>= FIXED_PRECISION;
    value += 0x4000;
	
    /* now in the range [0, 0xffff], reduce to [0, 0xfff] */
    value >>= 4;
	
    v = (value & 0x400) ? __gl_sin_tab[0x3ff - (value & 0x3ff)] : __gl_sin_tab[value & 0x3ff];
    v = xMul(v,FIXED_ONE);
    return (value & 0x800) ? -v : v;
}

int sinx(int value)
{
    int v;
	
    /* reduce to [0,1) */
    while (value < FIXED_ZERO) value += FIXED_2PI;
    value *= FIXED_R2PI;
    value >>= FIXED_PRECISION;
	
    /* now in the range [0, 0xffff], reduce to [0, 0xfff] */
    value >>= 4;
	
    v = (value & 0x400) ? __gl_sin_tab[0x3ff - (value & 0x3ff)] : __gl_sin_tab[value & 0x3ff];
    v = xMul(v,FIXED_ONE);
    return (value & 0x800) ? -v : v;
}
int xsqrt(int value)
{
    int s;
    int i;
    s = (value + FIXED_ONE) >> 1;
    /* 6 iterations to converge */
    for (i = 0; i < 6; i++)
		s = (s + xDiv(value, s)) >> 1;
    return s;
}

int powx(int value, int exponent)
{
	int exp;
    int p, f = value;
	
    
    static const unsigned short __gl_log_tab[] = { /* domain .5 - 1.0 */
		0xffff, 0xd47f, 0xad96, 0x8a62, 0x6a3f, 0x4caf, 0x3151, 0x17d6, 0x0000
    };
    static const unsigned short __gl_alog_tab[] = { /* domain 0 - 1.0 */
		0xffff, 0xeac0, 0xd744, 0xc567, 0xb504, 0xa5fe, 0x9837, 0x8b95, 0x8000
    };
	
    if (exponent == FIXED_ZERO || value == FIXED_ONE)
		return FIXED_ONE;
    if (value == FIXED_ZERO)
		return FIXED_ZERO;
	
    exp = 15;
    if (f & 0xff00) { exp -= 8; f >>= 8; }
    if (f & 0xf0) { exp -= 4; f >>= 4; }
    if (f & 0xc) { exp -= 2; f >>= 2; }
    if (f & 0x2) { exp -= 1; }
    f = value << exp;
	
    /* compute log base 2 */
    value = (f&0x0fff)<<4;
    f = (f >> 12)&0x7;
    p = xMul(__gl_log_tab[f+1]-__gl_log_tab[f],value) + __gl_log_tab[f];
	
    p = xMul(p,exponent) + exponent*exp;
	
	
    
    exp = IntFromFixed(p);
    p = FractionFromFixed(p);
	
    value = (p&0x1fff)<<3;
    p = p >> 13;
    return (xMul(__gl_alog_tab[p+1]-__gl_alog_tab[p],value)+
		__gl_alog_tab[p])>>exp;
}


fixed Inverse(fixed value)
{
	return fixed(Inverse(value.value));
}
fixed InvSqrt(fixed value)
{
	return fixed(InvSqrt(value.value));
}
fixed cosx(fixed value)
{
	return fixed(cosx(value.value));
}

fixed sinx(fixed value)
{
	return fixed(sinx(value.value));
}

fixed xsqrt(fixed value)
{
	return fixed(xsqrt(value.value));
}

fixed powx(fixed value, fixed exponent)
{
	return fixed(powx(value.value,exponent.value));
}
}