#include "stdafx.h"
#include "Object2D.h"
#include "TLine.h"

Object2D::Object2D()
{
    e_type_ = OBJ_2D;
    pos_pt_.Set(0.0, 0.0, 0.0);
    color_value_.Set(1.0, 1.0, 1.0);
    width_ = 0.1;
    style_ = ST_SOLID_DEF;
}


Object2D::~Object2D()
{

}


void Object2D::Serialize(CArchive &ar)
{
    EntityObject::Serialize(ar);
    if (ar.IsStoring())
    {
        ar << g_type_;
        ar << color_value_.x_;
        ar << color_value_.y_;
        ar << color_value_.z_;
    }
    else
    {
        ar >> g_type_;
        ar >> color_value_.x_;
        ar >> color_value_.y_;
        ar >> color_value_.z_;
    }
}

void Object2D::DoGripPoint()
{
    EntityObject::DoGripPoint();
    return;
}


void Object2D::GetGripPoint(const POINT3D& pt)
{
    EntityObject::GetGripPoint(pt);
    return;
}
