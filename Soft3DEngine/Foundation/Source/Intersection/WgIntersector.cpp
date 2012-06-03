///////////////////////////////////////////////////////////////
//                                                           //
//                    WgIntersector.cpp                      //
//                                                           //
//  - Implementation for Intersector class                   //
//                                                           //
//  - Written By Woong Gyu La a.k.a. Chris                   //
//       on 2009.10.06                                       //
//                                                           //
///////////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgIntersector.h"

namespace WGSoft3D
{

//----------------------------------------------------------------------------

Intersector2x::Intersector2x ()
{
    m_fContactTime = FIXED_ZERO;
    m_iIntersectionType = IT_EMPTY;
}
//----------------------------------------------------------------------------

Intersector2x::~Intersector2x ()
{
}
//----------------------------------------------------------------------------

fixed Intersector2x::GetContactTime () const
{
    return m_fContactTime;
}
//----------------------------------------------------------------------------

int Intersector2x::GetIntersectionType () const
{
    return m_iIntersectionType;
}
//----------------------------------------------------------------------------

bool Intersector2x::Test ()
{
    // stub for derived class
    assert(false);
    return false;
}
//----------------------------------------------------------------------------

bool Intersector2x::Find ()
{
    // stub for derived class
    assert(false);
    return false;
}
//----------------------------------------------------------------------------

bool Intersector2x::Test (fixed, const Vector2x&, const Vector2x&)
{
    // stub for derived class
    assert(false);
    return false;
}
//----------------------------------------------------------------------------

bool Intersector2x::Find (fixed, const Vector2x&, const Vector2x&)
{
    // stub for derived class
    assert(false);
    return false;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

Intersector3x::Intersector3x ()
{
	m_fContactTime = FIXED_ZERO;
	m_iIntersectionType = IT_EMPTY;
}
//----------------------------------------------------------------------------

Intersector3x::~Intersector3x ()
{
}
//----------------------------------------------------------------------------

fixed Intersector3x::GetContactTime () const
{
	return m_fContactTime;
}
//----------------------------------------------------------------------------

int Intersector3x::GetIntersectionType () const
{
	return m_iIntersectionType;
}
//----------------------------------------------------------------------------

bool Intersector3x::Test ()
{
	// stub for derived class
	assert(false);
	return false;
}
//----------------------------------------------------------------------------

bool Intersector3x::Find ()
{
	// stub for derived class
	assert(false);
	return false;
}
//----------------------------------------------------------------------------

bool Intersector3x::Test (fixed, const Vector3x&, const Vector3x&)
{
	// stub for derived class
	assert(false);
	return false;
}
//----------------------------------------------------------------------------

bool Intersector3x::Find (fixed, const Vector3x&, const Vector3x&)
{
	// stub for derived class
	assert(false);
	return false;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// explicit instantiation
//----------------------------------------------------------------------------
template WG3D_FOUNDATION_ITEM
class Intersector<float,Vector2f>;

template WG3D_FOUNDATION_ITEM
class Intersector<float,Vector3f>;

template WG3D_FOUNDATION_ITEM
class Intersector<double,Vector2d>;

template WG3D_FOUNDATION_ITEM
class Intersector<double,Vector3d>;
//----------------------------------------------------------------------------
}

