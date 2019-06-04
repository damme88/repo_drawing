
#ifndef JIG_BASE_H_
#define JIG_BASE_H_

#include "TLine.h"
#include "TCircle.h"
#include "TPoint.h"
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
    };

    enum StateJigg
    {
        JIGGING = 0,
        STOP_JIGG = 1,
        END_JIG = 2,
    };

    virtual void DoJigg() = 0;
    virtual void AddData(const POINT3D& pt) = 0;
    virtual void MakeJiggObj() = 0;
    virtual void KeyEvent(int type) = 0;
    void set_base_point(const POINT3D& pt) { base_pt_ = pt; }
    UINT GetStateJigg() const { return state_jigg_; }
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
    void AddData(const POINT3D& pt);
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
    void AddData(const POINT3D& pt);
    void MakeJiggObj();
    void KeyEvent(int type);
protected:
    TCircle* p_circle_jig_;
    TPoint t_point_;
    std::vector<POINT3D> pt_list_;
};

#endif