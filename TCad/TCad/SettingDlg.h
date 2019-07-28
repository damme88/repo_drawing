#pragma once
#include "afxcolorbutton.h"
#include "afxwin.h"


// SettingDlg dialog

class SettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SettingDlg)

public:
	SettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~SettingDlg();

    VEC3D GetColor();
    float GetWidth();
    UINT GetStyle();
    BOOL OnInitDialog();
    void OnOK();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
private:
	DECLARE_MESSAGE_MAP()
    CMFCColorButton mColorSetting;
    CEdit mWidthSetting;
    CComboBox mStyleSetting;

    float width_;
    UINT style_;
    VEC3D vColor_;
};
