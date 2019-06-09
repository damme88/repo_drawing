
#include "stdafx.h"
#include "TPolyLine.h"

TPolyLine::TPolyLine()
{
    is_closed_ = false;
}

TPolyLine::~TPolyLine()
{

}

void TPolyLine::AddPoint(const POINT3D& pt)
{
    pt_list_.push_back(pt);
}

void TPolyLine::SetPointAt(const int& idx, const POINT3D& pt)
{
    if (pt_list_.size() > idx)
        pt_list_.at(idx) = pt;
}

void TPolyLine::Render()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(color_value_.x_, color_value_.y_, color_value_.z_);
    glLineWidth(0.5);
    for (int i = 0; i < pt_list_.size(); ++i)
    {
        POINT3D pt = pt_list_.at(i);
        glVertex3f(pt.x_, pt.y_, pt.z_);
    }
    glEnd();
}

EntityObject* TPolyLine::Clone()
{
    TPolyLine* new_ents = new TPolyLine();
    return new_ents;
}