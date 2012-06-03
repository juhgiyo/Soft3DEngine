///////////////////////////////////////////////////////////
//                                                       //
//                    WgRay3.inl                         //
//                                                       //
//  - Inlines for Ray 3 class                            //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
template <class Real>
Ray3<Real>::Ray3 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
template <class Real>
Ray3<Real>::Ray3 (const Vector3<Real>& rkOrigin,
    const Vector3<Real>& rkDirection)
    :
    Origin(rkOrigin),
    Direction(rkDirection)
{
}
//----------------------------------------------------------------------------
