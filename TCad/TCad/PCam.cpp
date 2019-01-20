#include "stdafx.h"
#include "PCam.h"


PCam::PCam()
{
    phi_ = 45;
    theta_ = 45;
    zoom_value_ = 0.0;

    eye_x_ = 0.0f;
    eye_y_ = 0.0f;
    eye_z_ = 0.0f;
    cen_x_ = 0.0f;
    cen_y_ = 0.0f;
    cen_z_ = 0.0f;
    up_x_ = 0.0f;
    up_y_ = 0.0f;
    up_z_ = 1.0f;
    lx_ = 0;
    ly_ = 0;
    lz_ = 0;
}


PCam::~PCam()
{
}

void PCam::CalAngle(CPoint point, int cx, int cy)
{
    int ix = point.x - donw_pt_.x;
    int iy = point.y - donw_pt_.y;

    float anglex = ix * 180.0f / cx;
    theta_ += anglex;
    if (theta_ > 360)
        theta_ -= 360;
    if (theta_ < 360);
    theta_ += 360;

    float angley = iy * 180.0f / cy;
    phi_ += angley;
    if (phi_ > 360)
        phi_ -= 360;
    if (phi_ < -360)
        phi_ += 360;
}

void PCam::ViewDirection()
{
    double phi_rad = phi_*M_PI / 180.0;
    double theta_rad = theta_*M_PI / 180.0;

    VEC3D vEye;
    vEye.v[0] = sin(theta_rad)*cos(phi_rad);
    vEye.v[1] = cos(theta_rad)*cos(phi_rad);
    vEye.v[2] = sin(phi_rad);
     
    VEC3D vUp;
    vUp.v[0] = up_x_;
    vUp.v[1] = up_y_;
    vUp.v[2] = up_z_*cos(phi_rad);
    vUp.Unit();

    gluLookAt(cen_x_ + vEye.v[0],
        cen_y_ + vEye.v[1],
        cen_z_ + vEye.v[2],
        cen_x_ + lx_, cen_y_ + ly_, cen_z_ + lz_,
        vUp.v[0],
        vUp.v[1],
        vUp.v[2]);
}