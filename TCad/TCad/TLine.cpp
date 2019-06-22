
#include "stdafx.h"
#include "TLine.h"

TLine::TLine()
{
    pt1_ = POINT3D(0, 0, 0);
    pt2_ = POINT3D(0, 0, 0);
    g_type_ = LINE;
    e_type_ = OBJ_2D;
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

POINT3D TLine::FindIntersectPoint(const TLine& line)
{
    POINT3D pt;
    POINT3D p1 = this->pt1_;
    POINT3D p2 = this->pt2_;

    POINT3D p3 = line.pt1_;
    POINT3D p4 = line.pt2_;

    float a_val = 0.0;
    float b_val = 0.0;
    if ( abs(p1.x_ - p2.x_) > 0.0001)
    {
        a_val = (p1.y_ - p2.y_) / (p1.x_ - p2.x_);
        b_val = (p2.y_*p1.x_ - p1.y_*p2.x_) / (p1.x_ - p2.x_);
    }
    else
    {
        b_val = (p1.y_ + p2.y_)*0.5;
    }
    
    float c_val = 0.0;
    float d_val = 0.0;
    if (abs(p3.x_ - p4.x_) > 0.0001)
    {
        c_val = (p3.y_ - p4.y_) / (p3.x_ - p4.x_);
        d_val = (p4.y_*p3.x_ - p3.y_*p4.x_) / (p3.x_ - p4.x_);
    }
    else
    {
        d_val = (p3.y_ + p4.y_)*0.5;
    }

    float x_p = 0.0;
    float y_p = 0.0;
    if (abs(a_val - c_val) > 0.0001)
    {
        x_p = (d_val - b_val) / (a_val - c_val);
        y_p = (a_val*d_val - b_val*c_val) / (a_val - c_val);
    }
    else
    {
        x_p = 0.0;
        y_p = 0.0;
    }

    pt.x_ = x_p;
    pt.y_ = y_p;
    pt.z_ = 0.0;
    return pt;
}

void TLine::Render()
{
#ifdef OPENGL_12
    if (is_selected_)
        glColor3f(1.0, 0.0, 0);
    else
        glColor3f(color_value_.x_, color_value_.y_, color_value_.z_);
    glBegin(GL_LINES);
    glLineWidth(0.5);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(pt1_.x_, pt1_.y_, pt1_.z_);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(pt2_.x_, pt2_.y_, pt2_.z_);
    glEnd();
#else
    GLfloat arrVertices[6];
    arrVertices[0] = pt1_.x_;
    arrVertices[1] = pt1_.y_;
    arrVertices[2] = pt1_.z_;
    arrVertices[3] = pt2_.x_;
    arrVertices[4] = pt2_.y_;
    arrVertices[5] = pt2_.z_;
    if (is_selected_)
        glColor3f(1.0, 0.0, 0);
    else
        glColor3f(color_value_.x_, color_value_.y_, color_value_.z_);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, arrVertices);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);

#endif
}

EntityObject* TLine::Clone()
{
    TLine* new_ents = new TLine();
    new_ents->pt1_ = this->pt1_;
    new_ents->pt2_ = this->pt2_;

    return new_ents;
}

bool TLine::IsSelectedObject(const Vector3D &dir, const POINT3D& pos, POINT3D &p)
{
    POINT3D pt = pos;
    float dis_start = pt.distance(pt1_);
    float dis_end = pt.distance(pt2_);
    float dis_line = pt1_.distance(pt2_);
    if (dis_start < EPSILON) 
        return true;
    if (dis_end < EPSILON) 
        return true;

    double sum_dis = dis_start + dis_end;
    double sub_dis = abs(dis_line - sum_dis);
    if (sub_dis < EPSILON_SMALL)
        return true;
    return false;
}