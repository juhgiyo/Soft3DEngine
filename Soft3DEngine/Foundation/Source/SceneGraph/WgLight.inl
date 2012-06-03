///////////////////////////////////////////////////////////
//                                                       //
//                    WgLight.inl                        //
//                                                       //
//  - Inlines for Light class                            //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Vector3x Light::GetLocation () const
{
    return Local.GetTranslate();
}
//----------------------------------------------------------------------------
inline Vector3x Light::GetDVector () const
{
    return Local.GetRotate().GetColumn(0);
}
//----------------------------------------------------------------------------
inline Vector3x Light::GetUVector () const
{
    return Local.GetRotate().GetColumn(1);
}
//----------------------------------------------------------------------------
inline Vector3x Light::GetRVector () const
{
    return Local.GetRotate().GetColumn(2);
}
//----------------------------------------------------------------------------
inline Vector3x Light::GetWorldLocation () const
{
    return World.GetTranslate();
}
//----------------------------------------------------------------------------
inline Vector3x Light::GetWorldDVector () const
{
    return World.GetRotate().GetColumn(0);
}
//----------------------------------------------------------------------------
inline Vector3x Light::GetWorldUVector () const
{
    return World.GetRotate().GetColumn(1);
}
//----------------------------------------------------------------------------
inline Vector3x Light::GetWorldRVector () const
{
    return World.GetRotate().GetColumn(2);
}
//----------------------------------------------------------------------------

