#ifndef TLINE_H_
#define TLINE_H_

#include "Object2D.h"

class TLine : public Object2D
{
public:
    TLine();
    TLine(const POINT3D& p1, const POINT3D& p2);
    ~TLine();
    //Overridden function
    void Render();
    EntityObject* Clone();
    void Serialize(CArchive &ar);
    bool IsSelectedObject(const Vector3D &dir, const POINT3D& pos, POINT3D &p);
    void DoGripPoint();
    void GetGripPoint(const POINT3D& pt);

    //Basic function
    POINT3D FindIntersectPoint(const TLine& line);
    void SetPoint(const POINT3D& p1, const POINT3D& p2);
    POINT3D MidPoint() const;
    POINT3D get_start_point() const { return pt1_; }
    POINT3D get_end_point() const { return pt2_; }
protected:            // properties for serialize
    POINT3D pt1_;
    POINT3D pt2_;
};

#endif // 
