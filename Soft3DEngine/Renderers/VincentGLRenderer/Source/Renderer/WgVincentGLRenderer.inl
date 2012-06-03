
inline void gluLookAt(fixed eyex, fixed eyey, fixed eyez,
			   fixed centerx, fixed centery, fixed centerz,
			   fixed upx, fixed upy, fixed upz)
{
	
	fixed m[16];
	fixed x[3], y[3], z[3];
	fixed mag;
	
	/* Make rotation matrix */
	
	/* Z vector */
	z[0] = eyex - centerx;
	z[1] = eyey - centery;
	z[2] = eyez - centerz;
	
	mag=xsqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
	if (mag.value) {			
		z[0] /= mag;
		z[1] /= mag;
		z[2] /= mag;
	}
	
	/* Y vector */
	y[0] = upx;
	y[1] = upy;
	y[2] = upz;
	
	/* X vector = Y cross Z */
	x[0] = y[1] * z[2] - y[2] * z[1];
	x[1] = -y[0] * z[2] + y[2] * z[0];
	x[2] = y[0] * z[1] - y[1] * z[0];
	
	/* Recompute Y = Z cross X */
	y[0] = z[1] * x[2] - z[2] * x[1];
	y[1] = -z[0] * x[2] + z[2] * x[0];
	y[2] = z[0] * x[1] - z[1] * x[0];
	
	/* cross product gives area of parallelogram, which is < 1.0 for
    * non-perpendicular unit-length vectors; so normalize x, y here
    */
	
	mag=xsqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
	if (mag.value) {
		x[0] /= mag;
		x[1] /= mag;
		x[2] /= mag;
	}
	
	mag=xsqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
	if (mag.value) {
		y[0] /= mag;
		y[1] /= mag;
		y[2] /= mag;
	}
	
#define M(row,col)  m[col*4+row]
	M(0, 0) = x[0];
	M(0, 1) = x[1];
	M(0, 2) = x[2];
	M(0, 3) = FIXED_ZERO;
	M(1, 0) = y[0];
	M(1, 1) = y[1];
	M(1, 2) = y[2];
	M(1, 3) = FIXED_ZERO;
	M(2, 0) = z[0];
	M(2, 1) = z[1];
	M(2, 2) = z[2];
	M(2, 3) = FIXED_ZERO;
	M(3, 0) = FIXED_ZERO;
	M(3, 1) = FIXED_ZERO;
	M(3, 2) = FIXED_ZERO;
	M(3, 3) = FIXED_ONE;
#undef M
	glMultMatrixx((int*)m);
	/* Translate Eye to Origin */
	glTranslatex((-eyex).value,(-eyey).value,(-eyez).value);
}


inline  void glOrtho (fixed left, fixed right, fixed bottom, fixed top, fixed iNear, fixed iFar)
{
	fixed m[16];
	fixed rml = right - left;
	fixed fmn = iFar - iNear;
	fixed tmb = top - bottom;
	fixed _1over_rml;
	fixed _1over_fmn;
	fixed _1over_tmb;
	
	if (rml == FIXED_ZERO || fmn == FIXED_ZERO || tmb ==FIXED_ZERO) {
		return;
	}
	
	_1over_rml = FIXED_ONE / rml;
	_1over_fmn = FIXED_ONE / fmn;
	_1over_tmb = FIXED_ONE / tmb;
	
	m[0] = FixedFromFloat(2.0f)* _1over_rml;
	m[1] = FixedFromFloat(FIXED_ZERO);
	m[2] = FixedFromFloat(FIXED_ZERO);
	m[3] = FixedFromFloat(FIXED_ZERO);
	
	m[4] = FixedFromFloat(FIXED_ZERO);
	m[5] = FixedFromFloat(2.0f) * _1over_tmb;
	m[6] = FixedFromFloat(FIXED_ZERO);
	m[7] = FixedFromFloat(FIXED_ZERO);
	
	m[8] = FixedFromFloat(FIXED_ZERO);
	m[9] = FixedFromFloat(FIXED_ZERO);
	m[10] = FixedFromFloat(-2.0f) * _1over_fmn;
	m[11] = FixedFromFloat(FIXED_ZERO);
	
	m[12] = (right + left) *  _1over_rml;
	m[13] = (top + bottom) *  _1over_tmb;
	m[14] = (iFar + iNear) * _1over_fmn;
	m[15] = FIXED_ONE;
	
	glMultMatrixx((int*)m);
}

