#ifndef TPOLYLINE_H_
#define TPOLYLINE_H_
#include "stdafx.h"
#include "Object2D.h"
#include "TLine.h"

class TPolyLine : public Object2D
{
public:
    TPolyLine();
    ~TPolyLine();
    void AddPoint(const POINT3D& pt);
    void SetPointAt(const int& idx, const POINT3D& pt);
    void Render();
    EntityObject* Clone();
    bool IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p);
    std::vector<POINT3D> GetPointsList() const { return pt_list_; }
    void FreePoint() { pt_list_.clear(); }
    bool IsClosed() const { return is_closed_; }
    void SetClosed(const bool& isClosed) { is_closed_ = isClosed; }
protected:
    std::vector<POINT3D> pt_list_;
    bool is_closed_;
};

#endif // 
