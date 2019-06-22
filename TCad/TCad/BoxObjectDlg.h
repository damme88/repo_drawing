#pragma once
#include "afxwin.h"
#include "afxcolorbutton.h"
#include "TCadView.h"
#include "TBox.h"

// BoxDlgObject dialog

class BoxObjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BoxObjectDlg)

public:
    enum InsertType
    {
       BOX_POINT,
       BOX_LINE,
       BOX_REGION
    };

    enum TypeDlg
    {
        INSERT_OBJ = 0,
        UPDATE_OBJ = 1,
    };
    BoxObjectDlg(const float& l, const float& w, const float& h, CWnd* pParent = NULL);
	BoxObjectDlg(CWnd* pParent = NULL);   // standard constructor
    void ResetValue();
	virtual ~BoxObjectDlg();

    float get_length() const { return length_; }
    void set_length(double l) { length_ = l; }
    float get_width() const { return width_; }
    void set_width(double w) { width_ = w; }
    float get_height() const { return height_; }
    void set_height(double h) { height_ = h; }
    VEC3D get_v_color() const { return v_clor_; }
    void set_color(VEC3D vColor) { v_clor_ = vColor; }
    void set_angle(double angle) { angle_ = angle; }
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_BOX };
#endif

protected:
    CEdit edt_box_length_;
    CEdit edt_box_width_;
    CEdit edt_box_height_;

    float length_;
    float width_;
    float height_;
    VEC3D v_clor_;
    float angle_;
    CMFCColorButton val_color_;
    bool is_insert_;
    TCadView* cad_view_;
    int type_dlg_;
    int update_idx_;

protected:
    BOOL OnInitDialog();
    void InitVal();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
    void SetIdxUpdated(const int& idx) { update_idx_ = idx; }
    bool IsInsert() const { return is_insert_; }
    void SetView(TCadView* pView) {
        cad_view_ = pView;
    }
    void setType(int type);
public:
    afx_msg void InsertBox();
    afx_msg void UpdateBox();
    afx_msg void OnComboChanged();
protected:
    CComboBox mComboxInsertType;
private:
    CEdit mEditAngle;
};
