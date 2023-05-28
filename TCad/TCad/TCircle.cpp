#include "stdafx.h"
#include "TCircle.h"


TCircle::TCircle()
{
    radius_ = 0.0;
    center_pt_ = pos_pt_;
    e_type_  = OBJ_2D;
    g_type_ = CIRCLE;
}


TCircle::~TCircle()
{

}

EntityObject* TCircle::Clone()
{
    TCircle* p_circle = new TCircle();
    p_circle->pos_pt_ = pos_pt_;
    p_circle->radius_ = radius_;
    return p_circle;
}

void TCircle::Render()
{
    style_ = SettingInfo::getInstance()->GetStyle();
    width_ = SettingInfo::getInstance()->width_;

    glPushMatrix();
    glTranslatef(pos_pt_.x_, pos_pt_.y_, pos_pt_.z_);

    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);

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

    for (int i = 0; i <= 360; i++) 
    {
        double angle = 2 * M_PI * i / 360;
        double x = cos(angle);
        double y = sin(angle);
        glNormal3f(0.0, 0.0, 1.0);
        glVertex2d(x*radius_, y*radius_);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glPopMatrix();
}

bool TCircle::IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p)
{
    POINT3D pt = pos;
    float distance = pt.distance(pos_pt_);
    float sub_val = abs(distance - radius_);
    if (sub_val < EPSILON_LARGE)
    {
        return true;
    }
    return false;
}

void TCircle::Serialize(CArchive &ar)
{
    Object2D::Serialize(ar);
    if (ar.IsStoring())
    {
        ar << radius_;
        ar << center_pt_.x_;
        ar << center_pt_.y_;
        ar << center_pt_.z_;
    }
    else
    {
        ar >> radius_;
        ar >> center_pt_.x_;
        ar >> center_pt_.y_;
        ar >> center_pt_.z_;
    }
}