
#ifndef JIG_BASE_H_
#define JIG_BASE_H_

#include "TLine.h"
#include "TCircle.h"
#include "TPoint.h"
#include "TRectangle.h"
#include "TPolyLine.h"
#include "..\geoLib\Vector3d.h"

class JiggBase
{
public:
    JiggBase();
    ~JiggBase();

    enum KeyEventType
    {
        KEY_NONE = 0,
        KEY_ENTER = 1,
        KEY_SPACE = 2,
        KEY_ESC = 3,
        KEY_ADD = 4, // Polyline
    };

    enum StateJigg
    {
        JIGGING = 0,
        STOP_JIGG = 1,
        END_JIG = 2,
    };

    virtual void DoJigg() = 0;
    virtual void SetData(const POINT3D& pt) = 0;
    virtual void MakeJiggObj() = 0;
    virtual void KeyEvent(int type) = 0;
    void set_base_point(const POINT3D& pt) { base_pt_ = pt; }
    POINT3D get_base_point()const { return base_pt_; }
    UINT GetStateJigg() const { return state_jigg_; }
    void SetStartJigg(const UINT& state) { state_jigg_ = state; }
protected:
    POINT3D base_pt_;
    UINT state_jigg_;
};


class JigLine : public JiggBase
{
public:
    JigLine();
    ~JigLine();
    void DoJigg();
    void SetData(const POINT3D& pt);
    void MakeJiggObj();
    void KeyEvent(int type);
    TLine* GetObj() const { return p_line_jig_; }
protected:
    TLine* p_line_jig_;
    std::vector<POINT3D> pt_list_;
};

class JigCircle : public JiggBase
{
public:
    JigCircle();
    ~JigCircle();
    void DoJigg();
    void SetData(const POINT3D& pt);
    void MakeJiggObj();
    void KeyEvent(int type);
    TCircle* GetObj() const { return p_circle_jig_; }
protected:
    TCircle* p_circle_jig_;
    TPoint t_point_;
    std::vector<POINT3D> pt_list_;
};

class JigRectangle : public JiggBase
{
public:
    JigRectangle();
    ~JigRectangle();
    void DoJigg();
    void SetData(const POINT3D& pt);
    void MakeJiggObj();
    void KeyEvent(int type);
    TRectangle* GetObj() const { return p_rect_jig_; }
protected:
    TRectangle* p_rect_jig_;
    std::vector<POINT3D> pt_list_;
};

class JigPolyLine : public JiggBase
{
public:
    JigPolyLine();
    ~JigPolyLine();
    void DoJigg();
    void SetData(const POINT3D& pt);
    void MakeJiggObj();
    void KeyEvent(int type);
    void AddData(const POINT3D& pt);
    JigPolyLine* GetObj() const { p_poly_line_; }

protected:
    TPolyLine* p_poly_line_;
    std::vector<POINT3D> pt_list_;

};

#endif