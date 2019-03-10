#include "stdafx.h"
#include "PCam.h"


PCam::PCam()
{
    phi_ = 30;
    theta_ = 30;
    zoom_value_ = 0.0;
    
    cen_pt_.x_ = 0;
    cen_pt_.y_ = 0;
    cen_pt_.z_ = 0;

    vUp_.x_ = 0;
    vUp_.y_ = 0;
    vUp_.z_ = 0;
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
    vEye.x_ = sin(theta_rad)*cos(phi_rad);
    vEye.y_ = cos(theta_rad)*cos(phi_rad);
    vEye.z_ = sin(phi_rad);

    VEC3D vUp;
    VEC3D vZ(0, 0, 1);
    VEC3D vTemp;
    vUp = vEye*vTemp;
    // Tinh toan vector up khi xoay truc toa do z 1 vong tron
    if ((phi_ >= 0 && phi_ < 90) || (phi_ <= 0 && phi_ > -90) || phi_ > 270 || phi_ < -270)
    {
        vTemp = vZ*vEye; // Tich huu huong
    }
    else 
    {
        vTemp = vEye*vZ;
    }

    if (vTemp.abs() < 0.01)
    {
        vUp.x_ = -sin(phi_rad);
        vUp.y_ = cos(phi_rad);
        vUp.z_ = 0.0;
    }
    else
    {
        vUp = vEye*vTemp;
    }
    vUp.Unit();

    gluLookAt(vEye.x_, vEye.y_, vEye.z_,
        cen_pt_.x_, cen_pt_.y_, cen_pt_.z_,
        vUp.x_,
        vUp.y_,
        vUp.z_);

    pos_cam_ = vEye;
    vUp_ = vUp;
}