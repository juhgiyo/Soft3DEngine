///////////////////////////////////////////////////////////
//                                                       //
//                    WgRay2.inl                         //
//                                                       //
//  - Inlines for Ray 2 class                            //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
template <class Real>
Ray2<Real>::Ray2 ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
template <class Real>
Ray2<Real>::Ray2 (const Vector2<Real>& rkOrigin,
    const Vector2<Real>& rkDirection)
    :
    Origin(rkOrigin),
    Direction(rkDirection)
{
}
//----------------------------------------------------------------------------
