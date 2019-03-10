#ifndef TPOINT_H_
#define TPOINT_H_
#include "stdafx.h"
#include "Object2D.h"


class TPoint : public Object2D
{
public:
    TPoint();
    TPoint(const POINT3D& pt);
    TPoint(const float& x, const float& y, const float z);
    ~TPoint();
    void Render();
    EntityObject* Clone();
    bool IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p)
    {
        return true;
    }
private:
    POINT3D pt_;
};

#endif 
