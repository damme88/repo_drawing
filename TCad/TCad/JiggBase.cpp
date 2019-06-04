
#include "stdafx.h"
#include "JiggBase.h"

JiggBase::JiggBase()
{
    base_pt_ = POINT3D(0, 0, 0);
    state_jigg_ = JIGGING;
}

JiggBase::~JiggBase()
{

}


JigLine::JigLine()
{
    p_line_jig_ = NULL;
}

JigLine::~JigLine()
{
    if (p_line_jig_ != NULL)
    {
        delete p_line_jig_;
        p_line_jig_ = NULL;
    }
}

void JigLine::AddData(const POINT3D& pt)
{
    if (pt_list_.empty())
    {
        pt_list_.push_back(pt);
    }
    else
    {
        pt_list_.at(0) = pt;
    }
}

void JigLine::MakeJiggObj()
{
    if (!pt_list_.empty())
    {
        POINT3D pt1 = base_pt_;
        POINT3D pt2 = pt_list_.at(0);

        if (p_line_jig_ == NULL)
        {
            p_line_jig_ = new TLine(pt1, pt2);
            TLine* p_line = (TLine*)p_line_jig_;
        }
        else
        {
            TLine* p_line = (TLine*)p_line_jig_;
            p_line->SetPoint(pt1, pt2);
        }
    }
}

void JigLine::DoJigg()
{
    if (p_line_jig_ != NULL)
    {
        p_line_jig_->Render();
    }
    
}

void JigLine::KeyEvent(int type)
{
    switch (type)
    {
    case KEY_ENTER:
    {
        state_jigg_ = END_JIG;
    }
        break;
    case KEY_SPACE:
    {
        ;//
    }
        break;
    case KEY_ESC:
    {
        state_jigg_ = STOP_JIGG;
        pt_list_.clear();
    }
    break;
    default:
        break;
    }
}

//////////////////////////////////////////////////////////////////////////
/* Define Jig Circle*/
JigCircle::JigCircle()
{
    p_circle_jig_ = NULL;
}

JigCircle::~JigCircle()
{
    if (p_circle_jig_ != NULL)
    {
        delete p_circle_jig_;
        p_circle_jig_ = NULL;
    }
}

void JigCircle::AddData(const POINT3D& pt)
{
    if (pt_list_.empty())
    {
        pt_list_.push_back(pt);
    }
    else
    {
        pt_list_.at(0) = pt;
    }
}

void JigCircle::MakeJiggObj()
{
    if (!pt_list_.empty())
    {
        POINT3D pt1 = base_pt_;
        POINT3D pt2 = pt_list_.at(0);
        if (p_circle_jig_ == NULL)
        {
            p_circle_jig_ = new TCircle();
        }
        TCircle* new_circle = (TCircle*)p_circle_jig_;
        new_circle->set_pos(pt1);
        double distance = pt1.distance(pt2);
        new_circle->set_radius(distance);

        t_point_.SetPoint(pt1);
    }
}

void JigCircle::DoJigg()
{
    if (p_circle_jig_ != NULL)
    {
        p_circle_jig_->Render();
        t_point_.Render();
    }
}

void JigCircle::KeyEvent(int type)
{
    switch (type)
    {
    case KEY_ENTER:
    {
        state_jigg_ = END_JIG;
    }
    break;
    case KEY_SPACE:
    {
        ;
    }
    break;
    case KEY_ESC:
    {
        ;
    }
    default:
        break;
    }
}