
#ifndef TCIRCLE_H_
#define TCIRCLE_H_

#include "stdafx.h"
#include "Object2D.h"

class TCircle : public Object2D
{
private:
    float radius_;
    
public:
    TCircle();
    ~TCircle();
    void Render();
    EntityObject* Clone();
    float get_radius() const { return radius_; }
    void set_radius(const float& rad) { radius_ = rad; }
    bool IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p)
    {
        return true;
    }
};

#endif

