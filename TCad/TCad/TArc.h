
#ifndef TARC_H_
#define TARC_H_

#include "stdafx.h"
#include "Object2D.h"

class TArc : public Object2D
{
private:
   POINT3D pt1_;
   POINT3D pt2_;
   POINT3D pt3_;
   float radius_;
public:
    TArc();
    ~TArc();
    void Render();
    EntityObject* Clone();
    float get_radius() const { return radius_; }
    void set_points(const POINT3D& pt1, const POINT3D& pt2, const POINT3D& pt3);
    bool IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p)
    {
        return true;
    }
    //void set_radius(const float& rad) { radius_ = rad; }
};

#endif

