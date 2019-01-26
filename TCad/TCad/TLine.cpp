
#include "stdafx.h"
#include "TLine.h"

TLine::TLine()
{

}

TLine::TLine(const POINT3D& p1, const POINT3D& p2)
{
    pt1_ = p1;
    pt2_ = p2;
}

TLine::~TLine()
{

}

void TLine::SetPoint(const POINT3D& p1, const POINT3D& p2)
{
    pt1_ = p1;
    pt2_ = p2;
}

POINT3D TLine::MidPoint() const
{
    POINT3D mid_pt;
    mid_pt.x_ = (pt1_.x_ + pt2_.x_) / 2.0;
    mid_pt.y_ = (pt1_.y_ + pt2_.y_) / 2.0;
    mid_pt.z_ = (pt1_.z_ + pt2_.z_) / 2.0;

    return mid_pt;
}

void TLine::Render()
{
    glBegin(GL_LINES);
    glLineWidth(0.5);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(pt1_.x_, pt1_.y_, pt1_.z_);
    glVertex3f(pt2_.x_, pt2_.y_, pt2_.z_);
    glEnd();
}