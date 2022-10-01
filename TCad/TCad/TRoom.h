#ifndef TROOM_H_
#define TROOM_H_

#include "stdafx.h"
#include "Object2D.h"

class TRoom : public Object2D
{
public:
    TRoom();
    ~TRoom();
    void Render();
    void SetPoints(const POINT3D& pt1, const POINT3D& pt2);
    EntityObject* Clone();
    bool IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p);
    void Serialize(CArchive &ar);
protected:
    POINT3D pt1_;
    POINT3D pt2_;
    double thick_;
};

#endif

