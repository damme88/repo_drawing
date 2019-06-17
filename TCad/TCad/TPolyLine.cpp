
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
    if (is_selected_)
    {
        glColor3f(1.0, 0.0, 0.0);
    }
    else
    {
        glColor3f(color_value_.x_, color_value_.y_, color_value_.z_);
    }
    
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

bool TPolyLine::IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p)
{
    bool ret = false;
    TLine* pline = NULL;
    if (pt_list_.size() <= 0)
        return ret;

    for (int i = 0; i < pt_list_.size() -1; ++i)
    {
        POINT3D pt1 = pt_list_.at(i);
        POINT3D pt2 = pt_list_.at(i + 1);
        pline = new TLine(pt1, pt2);
        bool is_selected = pline->IsSelectedObject(dir, pos, p);
        if (is_selected == true)
        {
            ret = true;
            break;
        }
        delete pline;
        pline = NULL;
    }

    if (ret == false && is_closed_ == true)
    {
        pline = new TLine(*pt_list_.begin(), *pt_list_.end());
        bool ret = pline->IsSelectedObject(dir, pos, p);
        delete pline;
        pline = NULL;
    }

    return ret;
}