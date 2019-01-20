
#ifndef P_CAMERA_
#define P_CAMERA_
#include "stdafx.h"

class PCam
{
public:
    PCam();
    ~PCam();
    void ViewDirection();
    void CalAngle(CPoint point, int cx, int cy);
    void SetDownPt(CPoint pt) { donw_pt_ = pt; }
private:
    double phi_;
    double theta_;

    double zoom_value_;
    double eye_x_;
    double eye_y_;
    double eye_z_;
    double lx_;
    double ly_;
    double lz_;
    double cen_x_;
    double cen_y_;
    double cen_z_;

    double up_x_;
    double up_y_;
    double up_z_;
    CPoint donw_pt_;
};

#endif
