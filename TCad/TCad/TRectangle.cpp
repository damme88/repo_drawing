
#include "stdafx.h"
#include "TRectangle.h"

TRectangle::TRectangle()
{
    pt1_ = POINT3D(0, 0, 0);
    pt2_ = POINT3D(0, 0, 0);
}

TRectangle::~TRectangle()
{

}

void TRectangle::SetPoints(const POINT3D& pt1, const POINT3D& pt2)
{
    pt1_ = pt1;
    pt2_ = pt2;
}

EntityObject* TRectangle::Clone()
{
    TRectangle* new_rect = new TRectangle();
    new_rect->pt1_ = this->pt1_;
    new_rect->pt2_ = this->pt2_;
    return new_rect;
}

void TRectangle::Render()
{
    VEC3D vNormal = pos_cam_ - POINT3D(0, 0, 0);
    vNormal.Unit();
    POINT3D pt_bottom;
    pt_bottom.x_ = pt1_.x_;
    pt_bottom.y_ = pt2_.y_;
    pt_bottom.z_ = 0.0;

    POINT3D pt_top;
    pt_top.x_ = pt2_.x_;
    pt_top.y_ = pt1_.y_;
    pt_top.z_ = 0.0;
    glBegin(GL_LINE_LOOP);
    glColor3f(color_value_.x_, color_value_.y_, color_value_.z_);
    glVertex3f(pt1_.x_, pt1_.y_, pt1_.z_);
    glVertex3f(pt_top.x_, pt_top.y_, pt_top.z_);
    glVertex3f(pt2_.x_, pt2_.y_, pt2_.z_);
    glVertex3f(pt_bottom.x_, pt_bottom.y_, pt_bottom.z_);
    glEnd();
}