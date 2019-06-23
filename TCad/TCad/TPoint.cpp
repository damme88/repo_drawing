
#include "stdafx.h"
#include "TPoint.h"

TPoint::TPoint()
{
    pt_.Set(0, 0, 0);
}

TPoint::TPoint(const POINT3D& pt)
{
    pt_ = pt;
    g_type_ = POINT;
    e_type_ = OBJ_2D;
}

TPoint::TPoint(const float& x, const float& y, const float z)
{
    pt_.x_ = x;
    pt_.y_ = y;
    pt_.z_ = z;
}

TPoint::~TPoint()
{

}

void TPoint::Render()
{
    glBegin(GL_POINTS);
    glColor3f(color_value_.x_, color_value_.y_, color_value_.z_);
    glPointSize(3.0);
    glVertex3f(pt_.x_, pt_.y_, pt_.z_);
    glEnd();
}

EntityObject* TPoint::Clone()
{
    TPoint* new_enst = new TPoint();
    return new_enst;
}

bool TPoint::IsSelectedObject(const Vector3D &dir, const POINT3D& pos, POINT3D &p)
{
    bool ret = false;
    double dis = pt_.distance(pos);
    if (dis < EPSILON_SMALL)
    {
        ret = true;
    }
    return ret;
}

void TPoint::Serialize(CArchive &ar)
{
    Object2D::Serialize(ar);
    if (ar.IsStoring())
    {
        ar << pt_.x_;
        ar << pt_.y_;
        ar << pt_.z_;
    }
    else
    {
        ar >> pt_.x_;
        ar >> pt_.y_;
        ar >> pt_.z_;
    }
}