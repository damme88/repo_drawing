#ifndef TPOLYLINE_H_
#define TPOLYLINE_H_
#include "stdafx.h"
#include "Object2D.h"

class TPolyLine : public Object2D
{
public:
    TPolyLine();
    ~TPolyLine();
    void AddPoint(const POINT3D& pt);
    void SetPointAt(const int& idx, const POINT3D& pt);
    void Render();
    EntityObject* Clone();
    bool IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p)
    {
        return true;
    }
protected:
    std::vector<POINT3D> pt_list_;
};

#endif // 
