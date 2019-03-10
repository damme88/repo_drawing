#include "stdafx.h"
#include "TArc.h"


TArc::TArc()
{
    radius_ = 0.0;
}


TArc::~TArc()
{

}

EntityObject* TArc::Clone()
{
    TArc* p_arc = new TArc();
    p_arc->pt1_ = pt1_;
    p_arc->pt2_ = pt2_;
    p_arc->pt3_ = pt3_;
    p_arc->pos_pt_ = pos_pt_;
    p_arc->radius_ = radius_;

    return p_arc;
}

void TArc::Render()
{
    glPushMatrix();
    glTranslatef(pos_pt_.x_, pos_pt_.y_, pos_pt_.z_);
    glBegin(GL_LINE_LOOP);
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

void DrawArc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments)
{
    //theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
    float theta = arc_angle / float(num_segments - 1);
    float tangetial_factor = tanf(theta);
    float radial_factor = cosf(theta);

    float x = r * cosf(start_angle);//we now start at the start angle
    float y = r * sinf(start_angle);

    glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
    for (int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x + cx, y + cy);

        float tx = -y;
        float ty = x;

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}