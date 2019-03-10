#include "stdafx.h"
#include "TCircle.h"


TCircle::TCircle()
{
    radius_ = 0.0;
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
    glPushMatrix();
    glTranslatef(pos_pt_.x_, pos_pt_.y_, pos_pt_.z_);
    glBegin(GL_LINE_LOOP);
    glColor3f(color_value_.x_, color_value_.y_, color_value_.z_);
    for (int i = 0; i <= 360; i++) 
    {
        double angle = 2 * M_PI * i / 360;
        double x = cos(angle);
        double y = sin(angle);
        glVertex2d(x*radius_, y*radius_);
    }
    glEnd();
    glPopMatrix();
}