#include "stdafx.h"
#include "EntityObject.h"
#include "Object2D.h"


IMPLEMENT_SERIAL(EntityObject, CObject, VERSIONABLE_SCHEMA | LASTER_VERSION)

EntityObject::EntityObject()
{
    is_selected_ = false;
    e_type_ = NONE;
}


EntityObject::~EntityObject()
{

}

void EntityObject::Serialize(CArchive &ar)
{
    CObject::Serialize(ar);
    if (ar.IsStoring())
    {
        CRuntimeClass* pruntime = EntityObject::GetRuntimeClass();
        pruntime->m_wSchema = LASTER_VERSION;
        ar.SerializeClass(pruntime);

        ar << e_type_;
        ar << pos_pt_.x_;
        ar << pos_pt_.y_;
        ar << pos_pt_.z_;
    }
    else
    {
        ar.SerializeClass(RUNTIME_CLASS(EntityObject));
        UINT nVersion = ar.GetObjectSchema();

        ar >> e_type_;
        ar >> pos_pt_.x_;
        ar >> pos_pt_.y_;
        ar >> pos_pt_.z_;
    }
}

void EntityObject::Render()
{

}

EntityObject* EntityObject::Clone()
{
    return NULL;
}
 bool EntityObject::IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p)
 {
     return false;
 }