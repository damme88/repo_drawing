#ifndef TRECTANGLE_H_
#define TRECTANGLE_H_
#include "stdafx.h"
#include "Object2D.h"
#include "TLine.h"

class TRectangle : public Object2D
{
public:
    TRectangle();
    ~TRectangle();
    void Render();
    void SetPoints(const POINT3D& pt1, const POINT3D& pt2);
    EntityObject* Clone();
    bool IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p)
    {
        return true;
    }
protected:
    POINT3D pt1_;
    POINT3D pt2_;

};

#endif // 
