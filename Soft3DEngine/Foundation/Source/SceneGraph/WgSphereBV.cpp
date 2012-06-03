///////////////////////////////////////////////////////////
//                                                       //
//                    WgSphereBV.cpp                     //
//                                                       //
//  - Implementation for Sphere Bounding Volume class    //
//                                                       //
//  - Written By Woong Gyu La a.k.a. Chris               //
//       on 2009.10.07                                   //
//                                                       //
///////////////////////////////////////////////////////////

#include "WgFoundationPCH.h"
#include "WgSphereBV.h"
#include "WgContSphere3.h"
#include "WgIntrRay3Sphere3.h"
#include "WgIntrSphere3Sphere3.h"
using namespace WGSoft3D;

WG3D_IMPLEMENT_RTTI(WGSoft3D,SphereBV,BoundingVolume);
WG3D_IMPLEMENT_DEFAULT_NAME_ID(SphereBV,BoundingVolume);

//----------------------------------------------------------------------------
// The factory function of BoundingVolume creates SphereBV objects.  You may
// delete this and allow another bounding volume class to be the default.
//----------------------------------------------------------------------------
BoundingVolume* BoundingVolume::Create ()
{
    return WG_NEW SphereBV;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
SphereBV::SphereBV ()
    :
    m_kSphere(Vector3x::ZERO,fixed(FIXED_ZERO))
{
}
//----------------------------------------------------------------------------
SphereBV::SphereBV (const Sphere3x& rkSphere)
    :
    m_kSphere(rkSphere)
{
}
//----------------------------------------------------------------------------
void SphereBV::ComputeFromData (const Vector3xArray* pkVertices)
{
    if (pkVertices)
    {
        int iVQuantity = pkVertices->GetQuantity();
        const Vector3x* akVertex = pkVertices->GetData();
        m_kSphere = ContSphereAverage(iVQuantity,akVertex);
    }
}
//----------------------------------------------------------------------------
void SphereBV::TransformBy (const Transformation& rkTransform,
    BoundingVolume* pkResult)
{
    Sphere3x& rkTarget = ((SphereBV*)pkResult)->m_kSphere;
    rkTarget.Center = rkTransform.ApplyForward(m_kSphere.Center);
    rkTarget.Radius = rkTransform.GetNorm()*m_kSphere.Radius;
}
//----------------------------------------------------------------------------
int SphereBV::WhichSide (const Plane3x& rkPlane) const
{
    fixed fDistance = rkPlane.DistanceTo(m_kSphere.Center);

    if (fDistance <= -m_kSphere.Radius)
    {
        return -1;
    }
    else if (fDistance >= m_kSphere.Radius)
    {
        return +1;
    }

    return 0;
}
//----------------------------------------------------------------------------
bool SphereBV::TestIntersection (const Ray3x& rkRay) const
{
    return IntrRay3Sphere3x(rkRay,m_kSphere).Test();
}
//----------------------------------------------------------------------------
bool SphereBV::TestIntersection (const BoundingVolume* pkInput) const
{
    return IntrSphere3Sphere3x(m_kSphere,
        ((SphereBV*)pkInput)->m_kSphere).Test();
}
//----------------------------------------------------------------------------
void SphereBV::CopyFrom (const BoundingVolume* pkInput)
{
    m_kSphere = ((SphereBV*)pkInput)->m_kSphere;
}
//----------------------------------------------------------------------------
void SphereBV::GrowToContain (const BoundingVolume* pkInput)
{
    m_kSphere = MergeSpheres(m_kSphere,((SphereBV*)pkInput)->m_kSphere);
}
//----------------------------------------------------------------------------
bool SphereBV::Contains (const Vector3x& rkPoint) const
{
    return InSphere(rkPoint,m_kSphere);
}
//----------------------------------------------------------------------------

