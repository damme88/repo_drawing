#include "stdafx.h"
#include "TRoom.h"
#include "TLine.h"

TRoom::TRoom()
{
    pt1_ = POINT3D(0, 0, 0);
    pt2_ = POINT3D(0, 0, 0);
    g_type_ = RECTANGLE;
    e_type_ = OBJ_2D;
    thick_ = 5.0;
    color_value_.x_ = 0.0;
    color_value_.y_ = 1.0;
    color_value_.z_ = 0.0;
}

TRoom::~TRoom()
{

}

void TRoom::SetPoints(const POINT3D& pt1, const POINT3D& pt2)
{
    pt1_ = pt1;
    pt2_ = pt2;
}

EntityObject* TRoom::Clone()
{
    TRoom* new_rom = new TRoom();
    new_rom->pt1_ = this->pt1_;
    new_rom->pt2_ = this->pt2_;
    return new_rom;
}

void TRoom::Render()
{
    style_ = SettingInfo::getInstance()->GetStyle();
    //color_value_ = SettingInfo::getInstance()->color_;
    width_ = SettingInfo::getInstance()->width_;

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
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(width_);
    glLineStipple(1, style_);

    if (is_selected_)
    {
        glColor3f(1.0, 0.0, 0.0);
    }
    else
    {
        glColor3f(color_value_.x_, color_value_.y_, color_value_.z_);
    }

    glVertex3f(pt1_.x_, pt1_.y_, pt1_.z_);
    glVertex3f(pt_top.x_, pt_top.y_, pt_top.z_);
    glVertex3f(pt2_.x_, pt2_.y_, pt2_.z_);
    glVertex3f(pt_bottom.x_, pt_bottom.y_, pt_bottom.z_);
    glDisable(GL_LINE_STIPPLE);
    glEnd();

    POINT3D pt_bottom_inside = pt1_;
    pt_bottom_inside.x_ += thick_;
    pt_bottom_inside.y_ -= thick_;

    POINT3D pt_top_inside = pt2_;
    pt_top_inside.x_ -= thick_;
    pt_top_inside.y_ += thick_;

    glBegin(GL_POLYGON);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(pt_top_inside.x_, pt_top_inside.y_, 0);
    glVertex3f(pt_bottom_inside.x_, pt_top_inside.y_, 0);
    glVertex3f(pt_bottom_inside.x_, pt_bottom_inside.y_, 0);
    glVertex3f(pt_top_inside.x_, pt_bottom_inside.y_, 0);
    glEnd();
}

bool TRoom::IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p)
{
    bool ret = false;
    POINT3D pt_bottom;
    pt_bottom.x_ = pt1_.x_;
    pt_bottom.y_ = pt2_.y_;
    pt_bottom.z_ = 0.0;

    POINT3D pt_top;
    pt_top.x_ = pt2_.x_;
    pt_top.y_ = pt1_.y_;
    pt_top.z_ = 0.0;

    TLine* pLine1 = new TLine(pt1_, pt_top);
    TLine* pLine2 = new TLine(pt_top, pt2_);
    TLine* pLine3 = new TLine(pt2_, pt_bottom);
    TLine* pLine4 = new TLine(pt_bottom, pt1_);

    bool is_selected_ = false;
    is_selected_ = pLine1->IsSelectedObject(dir, pos, p);
    if (is_selected_ == true)
    {
        delete pLine1;
        delete pLine2;
        delete pLine3;
        delete pLine4;
        ret = true;
    }
    else
    {
        is_selected_ = pLine2->IsSelectedObject(dir, pos, p);
        if (is_selected_ == true)
        {
            delete pLine1;
            delete pLine2;
            delete pLine3;
            delete pLine4;
            ret = true;
        }
        else
        {
            is_selected_ = pLine3->IsSelectedObject(dir, pos, p);
            if (is_selected_ == true)
            {
                delete pLine1;
                delete pLine2;
                delete pLine3;
                delete pLine4;
                ret = true;
            }
            else
            {
                is_selected_ = pLine4->IsSelectedObject(dir, pos, p);
                if (is_selected_ == true)
                {
                    delete pLine1;
                    delete pLine2;
                    delete pLine3;
                    delete pLine4;
                    ret = true;
                }
                else
                {
                    delete pLine1;
                    delete pLine2;
                    delete pLine3;
                    delete pLine4;
                    ret = false;
                }
            }
        }
    }
    return ret;
}

void TRoom::Serialize(CArchive &ar)
{
    Object2D::Serialize(ar);
    if (ar.IsStoring())
    {
        ar << pt1_.x_;
        ar << pt1_.y_;
        ar << pt1_.z_;
        ar << pt2_.x_;
        ar << pt2_.y_;
        ar << pt2_.z_;
    }
    else
    {
        ar >> pt1_.x_;
        ar >> pt1_.y_;
        ar >> pt1_.z_;
        ar >> pt2_.x_;
        ar >> pt2_.y_;
        ar >> pt2_.z_;
    }
}

