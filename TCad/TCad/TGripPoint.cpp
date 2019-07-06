#include "stdafx.h"
#include "TGripPoint.h"


TGripPoint::TGripPoint()
{
    color_ = K_WHITE;
    style_ = RECTANGLE;
}


TGripPoint::~TGripPoint()
{
    
}

void TGripPoint::Render()
{
    if (style_ == CIRCLE)
    {
        for (int i = 0; i < m_gripPoints.size(); ++i)
        {
            POINT3D pt_pos = m_gripPoints.at(i);
            glPushMatrix();
            glTranslatef(pt_pos.x_, pt_pos.y_, pt_pos.z_);
            glBegin(GL_LINE_LOOP);
            glColor3f(color_.x_, color_.y_, color_.z_);
            for (int i = 0; i <= 360; i++)
            {
                double angle = 2 * M_PI * i / 360;
                double x = cos(angle);
                double y = sin(angle);
                glNormal3f(0.0, 0.0, 1.0);
                glVertex2d(x*20.0, y*20.0);
            }
            glEnd();
            glPopMatrix();
        }
    }
    else
    {
        for (int i = 0; i < m_gripPoints.size(); ++i)
        {
            POINT3D pt_pos = m_gripPoints.at(i);
            std::vector<POINT3D> list_pt = CalPoints(pt_pos);
            if (list_pt.size() > 1)
            {
                POINT3D pt1 = list_pt.at(0);
                POINT3D pt2 = list_pt.at(1);
                POINT3D pt_bottom;
                pt_bottom.x_ = pt1.x_;
                pt_bottom.y_ = pt2.y_;
                pt_bottom.z_ = 0.0;

                POINT3D pt_top;
                pt_top.x_ = pt2.x_;
                pt_top.y_ = pt1.y_;
                pt_top.z_ = 0.0;
                glBegin(GL_LINE_LOOP);
                glColor3f(color_.x_, color_.y_, color_.z_);
                glVertex3f(pt1.x_, pt1.y_, pt1.z_);
                glVertex3f(pt_top.x_, pt_top.y_, pt_top.z_);
                glVertex3f(pt2.x_, pt2.y_, pt2.z_);
                glVertex3f(pt_bottom.x_, pt_bottom.y_, pt_bottom.z_);
                glEnd();
            }
        }
    }
}

void TGripPoint::AddGrip(const POINT3D& pt)
{
    m_gripPoints.push_back(pt);
}

void TGripPoint::RemoveAll()
{
    m_gripPoints.clear();
}

int TGripPoint::CheckGripPoint(const POINT3D& pt)
{
    for (int i = 0; i < m_gripPoints.size(); i++)
    {
        double dis = m_gripPoints.at(i).distance(pt);
        if (dis < EPSILON_LARGE + 20)
        {
            return 1;
        }
    }

    return 0;
}

std::vector<POINT3D> TGripPoint::CalPoints(POINT3D& pt)
{
    VEC3D vHor = VEC3D(1.0, 0.0, 0.0);
    VEC3D vVer = VEC3D(0.0, 1.0, 0.0);

    VEC3D vTemp1 = vHor * 8;
    VEC3D vTemp2 = vVer * 8;

    POINT3D midPt1 = pt + vTemp1;

    POINT3D pt1 = midPt1 + vTemp2;
    POINT3D pt2 = pt1 - VEC3D(vHor * 16);
    POINT3D pt3 = pt2 - VEC3D(vVer * 16);
    POINT3D pt4 = pt3 + VEC3D(vHor * 16);

    std::vector<POINT3D> list_pt;
    list_pt.push_back(pt1);
    //list_pt.push_back(pt2);
    list_pt.push_back(pt3);
    //list_pt.push_back(pt4);

    return list_pt;
}