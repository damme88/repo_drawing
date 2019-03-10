#pragma once
#include "afxwin.h"
#include "afxcolorbutton.h"


// BoxDlgObject dialog

class BoxObjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BoxObjectDlg)

public:
    BoxObjectDlg(const float& l, const float& w, const float& h, CWnd* pParent = NULL);
	BoxObjectDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~BoxObjectDlg();

    float get_length() const { return length_; }
    float get_width() const { return width_; }
    float get_height() const { return height_; }
    VEC3D get_v_color() const { return v_clor_; }
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
protected:
    BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
protected:
    CMFCColorButton val_color_;
};
