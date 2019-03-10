
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
    void set_phi(const double& phi) { phi_ = phi; }
    void set_theta(const double& theta) { theta_ = theta; }
    POINT3D get_pos_cam()
    {
        return pos_cam_;
    }

    void SetCenterPt(const POINT3D& cenPt)
    {
        cen_pt_ = cenPt;
    }
    
    POINT3D GetCenterPt() const { return cen_pt_; }
private:
    double phi_;
    double theta_;

    double zoom_value_;

    POINT3D pos_cam_;
    POINT3D cen_pt_;
    VEC3D vUp_;
    CPoint donw_pt_;
};

#endif
