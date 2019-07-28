// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TCad.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// SettingDlg dialog

IMPLEMENT_DYNAMIC(SettingDlg, CDialogEx)

SettingDlg::SettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_SETTING, pParent)
{

}

SettingDlg::~SettingDlg()
{
}

void SettingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SETTING_COLOR_2D, mColorSetting);
    DDX_Control(pDX, IDC_SETTING_WIDTH, mWidthSetting);
    DDX_Control(pDX, IDC_SETTING_STYLE, mStyleSetting);
}


BEGIN_MESSAGE_MAP(SettingDlg, CDialogEx)
END_MESSAGE_MAP()


BOOL SettingDlg::OnInitDialog()
{
    bool ret = CDialogEx::OnInitDialog();
    mStyleSetting.AddString(_T("SOLID"));
    mStyleSetting.AddString(_T("DOT"));
    mStyleSetting.AddString(_T("DASH"));
    mStyleSetting.AddString(_T("DASH_DOT"));
    mStyleSetting.SetCurSel(0);
    
    mWidthSetting.SetWindowText(_T("0.5"));

    mColorSetting.SetColor(RGB(255, 255, 255));
    mColorSetting.SetColumnsNumber(8);
    return ret;
}
// SettingDlg message handlers

void SettingDlg::OnOK()
{
    UpdateData(TRUE);
    CString str;

    mWidthSetting.GetWindowText(str);
    width_ = _tstof(str);

    COLORREF val = mColorSetting.GetColor();
    int red = GetRValue(val);
    int green = GetGValue(val);
    int blue = GetBValue(val);

    vColor_.x_ = red / 255.0;
    vColor_.y_ = green / 255.0;
    vColor_.z_ = blue / 255.0;

    style_ = mStyleSetting.GetCurSel();
    CDialogEx::OnOK();
}
VEC3D SettingDlg::GetColor()
{
   return vColor_;
}

UINT SettingDlg::GetStyle()
{
    UINT style = StyleLine::ST_SOLID;
    switch (style_)
    {
    case 0:
        style = StyleLine::ST_SOLID;
        break;
    case 1:
        style = StyleLine::ST_DOTTED;
        break;
    case 2:
        style = StyleLine::ST_DASHED;
        break;
    case 3:
        style = StyleLine::ST_DASH_DOT;
        break;
    default:
        break;
    }
    return style;
}

float SettingDlg::GetWidth()
{
    return width_;
}