#ifndef TLINE_H_
#define TLINE_H_

#include "Object2D.h"

class TLine : public Object2D
{
public:
    TLine();
    TLine(const POINT3D& p1, const POINT3D& p2);
    void SetPoint(const POINT3D& p1, const POINT3D& p2);
    POINT3D MidPoint() const;
    ~TLine();
    void Render();
    EntityObject* Clone();
    POINT3D FindIntersectPoint(const TLine& line);
    bool IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p)
    {
        return true;
    }
protected:
    POINT3D pt1_;
    POINT3D pt2_;
};

#endif // 
