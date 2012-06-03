//----------------------------------------------------------------------------
template <class Real, class TVector>
Intersector<Real,TVector>::Intersector ()
{
    m_fContactTime = (Real)0.0;
    m_iIntersectionType = IT_EMPTY;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
Intersector<Real,TVector>::~Intersector ()
{
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
Real Intersector<Real,TVector>::GetContactTime () const
{
    return m_fContactTime;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
int Intersector<Real,TVector>::GetIntersectionType () const
{
    return m_iIntersectionType;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
bool Intersector<Real,TVector>::Test ()
{
    // stub for derived class
    assert(false);
    return false;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
bool Intersector<Real,TVector>::Find ()
{
    // stub for derived class
    assert(false);
    return false;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
bool Intersector<Real,TVector>::Test (Real, const TVector&, const TVector&)
{
    // stub for derived class
    assert(false);
    return false;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
bool Intersector<Real,TVector>::Find (Real, const TVector&, const TVector&)
{
    // stub for derived class
    assert(false);
    return false;
}
//----------------------------------------------------------------------------

