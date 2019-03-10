
#include "stdafx.h"
#include "TPoint.h"

TPoint::TPoint()
{
    pt_.Set(0, 0, 0);
}

TPoint::TPoint(const POINT3D& pt)
{
    pt_ = pt;
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