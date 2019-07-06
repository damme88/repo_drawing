#ifndef TGRIP_POINT_H_
#define TGRIP_POINT_H_
#include "stdafx.h"

class TGripPoint
{
public:
    TGripPoint();
    ~TGripPoint();
    enum StyleDrawing
    {
        RECTANGLE = 0,
        CIRCLE = 1,
    };
    void set_style(UINT sType) { style_ = sType; }
    void set_color(VEC3D color) { color_ = color; }
    void Render();
    void AddGrip(const POINT3D& pt);
    void RemoveAll();
    int CheckGripPoint(const POINT3D& pt);
    std::vector<POINT3D> CalPoints(POINT3D& pt);
private:
    std::vector<POINT3D> m_gripPoints;
    UINT style_;
    VEC3D color_;
};

#endif

