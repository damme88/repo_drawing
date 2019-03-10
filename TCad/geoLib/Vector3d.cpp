
#include "stdafx.h"
#include <math.h>
#include "Vector3d.h"


Vector3D::Vector3D() {

}

Vector3D::Vector3D(float x, float y, float z) {
    x_ = x;
    y_ = y;
    z_ = z;
}

Vector3D::Vector3D(float v1[3]) {
    x_ = v1[0]; y_ = v1[1]; z_ = v1[2];
}

Vector3D::~Vector3D() {

}

double Vector3D::scalar(const Vector3D& v1) {
    return x_ * v1.x_ + y_ * v1.y_ + z_ * v1.z_;
}

void Vector3D::Set(double x, double y, double z) {
    x_ = x;
    y_ = y;
    z_ = z;
}

// Get vector Unit
Vector3D Vector3D::Unit() {
    Vector3D temp;
    double d = sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    temp.x_ = x_ / d;
    temp.y_ = y_ / d;
    temp.z_ = z_ / d;
    return temp;
}

// GetMoudle
double Vector3D::abs() {
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

float Vector3D::distance(Vector3D pt)
{
    float valx = (pt.x_ - x_)*(pt.x_ - x_);
    float valy = (pt.y_ - y_)*(pt.y_ - y_);
    float valz = (pt.z_ - z_)*(pt.z_ - z_);

    return sqrt(valx + valy + valz);
}