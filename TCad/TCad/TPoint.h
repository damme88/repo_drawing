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
private:
    POINT3D pt_;
};

#endif 
