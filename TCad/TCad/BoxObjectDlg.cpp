// BoxDlgObject.cpp : implementation file
//

#include "stdafx.h"
#include "TCad.h"
#include "BoxObjectDlg.h"
#include "afxdialogex.h"


// BoxDlgObject dialog

IMPLEMENT_DYNAMIC(BoxObjectDlg, CDialogEx)

BoxObjectDlg::BoxObjectDlg(const float& l, const float& w, const float& h, CWnd* pParent/*NULL*/)
    : CDialogEx(IDD_DLG_BOX, pParent)
{
   
    length_ = l;
    width_ = w;
    height_ = h;
    is_insert_ = false;
    cad_view_ = NULL;
    type_dlg_ = INSERT_OBJ;
    angle_ = 0.0;
    update_idx_ = -1;
}

BoxObjectDlg::BoxObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_BOX, pParent)
{
    length_ = 200;
    width_ = 100;
    height_ = 300;
    angle_ = 0.0;
    v_clor_ = VEC3D(0.0, 1.0, 0.0);
    type_dlg_ = INSERT_OBJ;
    cad_view_ = NULL;
    update_idx_ = -1;
}
void BoxObjectDlg::ResetValue()
{
    length_ = 200;
    width_ = 100;
    height_ = 300;
    angle_ = 0.0;
    v_clor_ = VEC3D(0.0, 1.0, 0.0);
    InitVal();
    update_idx_ = -1;
}

BoxObjectDlg::~BoxObjectDlg()
{
}

void BoxObjectDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDT_LENGTH, edt_box_length_);
    DDX_Control(pDX, IDC_EDT_WIDTH, edt_box_width_);
    DDX_Control(pDX, IDC_EDT_HEIGHT, edt_box_height_);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON1, val_color_);
    DDX_Control(pDX, IDC_INSERT_BOX_TYPE, mComboxInsertType);
    DDX_Control(pDX, IDC_BOX_ANGLE, mEditAngle);
}


BEGIN_MESSAGE_MAP(BoxObjectDlg, CDialogEx)
    ON_BN_CLICKED(ID_INSERT_BOX, &BoxObjectDlg::InsertBox)
    ON_BN_CLICKED(ID_UPDATE_BOX, &BoxObjectDlg::UpdateBox)
    ON_CBN_SELENDOK(IDC_INSERT_BOX_TYPE, &BoxObjectDlg::OnComboChanged)
END_MESSAGE_MAP()


BOOL BoxObjectDlg::OnInitDialog()
{
    BOOL ret = CDialogEx::OnInitDialog();
    InitVal();
    return ret;
}

void BoxObjectDlg::InitVal()
{
    CString str;
    str.Format(_T("%f"), length_); edt_box_length_.SetWindowText(str);
    str.Format(_T("%f"), width_); edt_box_width_.SetWindowText(str);
    str.Format(_T("%f"), height_); edt_box_height_.SetWindowText(str);
    str.Format(_T("%f"), angle_);  mEditAngle.SetWindowText(str);

    val_color_.SetColor(RGB(v_clor_.x_ * 255, v_clor_.y_ * 255, v_clor_.z_ * 255));
    val_color_.SetColumnsNumber(8);

    mComboxInsertType.AddString(_T("Point"));
    mComboxInsertType.AddString(_T("Select Line"));
    mComboxInsertType.AddString(_T("Select Region"));
    mComboxInsertType.SetCurSel(0);

    if (type_dlg_ == INSERT_OBJ)
    {
        GetDlgItem(ID_INSERT_BOX)->EnableWindow(TRUE);
        GetDlgItem(ID_INSERT_BOX)->SetFocus();
    }
    else
    {
        GetDlgItem(ID_INSERT_BOX)->EnableWindow(FALSE);
        GetDlgItem(ID_UPDATE_BOX)->EnableWindow(TRUE);
    }
    UpdateData(FALSE);
}
void BoxObjectDlg::setType(int type) 
{
    type_dlg_ = type; 
    if (type_dlg_ == INSERT_OBJ)
    {
        GetDlgItem(ID_INSERT_BOX)->EnableWindow(TRUE);
        GetDlgItem(ID_UPDATE_BOX)->EnableWindow(FALSE);
        mComboxInsertType.EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(ID_INSERT_BOX)->EnableWindow(FALSE);
        GetDlgItem(ID_UPDATE_BOX)->EnableWindow(TRUE);
        mComboxInsertType.EnableWindow(FALSE);
    }
    UpdateData(FALSE);
}

// BoxDlgObject message handlers
void BoxObjectDlg::UpdateBox()
{
    CString str;
    edt_box_length_.GetWindowText(str);
    length_ = _ttof(str);
    edt_box_width_.GetWindowText(str);
    width_ = _ttof(str);
    edt_box_height_.GetWindowText(str);
    height_ = _ttof(str);
    mEditAngle.GetWindowText(str);
    angle_ = _ttof(str);

    COLORREF val = val_color_.GetColor();
    int red = GetRValue(val);
    int green = GetGValue(val);
    int blue = GetBValue(val);

    v_clor_.x_ = red / 255.0;
    v_clor_.y_ = green / 255.0;
    v_clor_.z_ = blue / 255.0;

    TBox* tbox = new TBox(length_, width_, height_);
    tbox->set_angle(angle_);
    tbox->set_color(v_clor_);
    tbox->set_type(Object3D::BOX_OBJ);
    tbox->set_etype(EntityObject::OBJ_3D);

    if (cad_view_ != NULL)
    {
        cad_view_->UpdateObject(tbox, update_idx_);
    }
    delete tbox;
}

void BoxObjectDlg::InsertBox()
{
    CString str;
    edt_box_length_.GetWindowText(str);
    length_ = _ttof(str);
    edt_box_width_.GetWindowText(str);
    width_ = _ttof(str);
    edt_box_height_.GetWindowText(str);
    height_ = _ttof(str);
    mEditAngle.GetWindowText(str);
    angle_ = _ttof(str);

    COLORREF val = val_color_.GetColor();
    int red = GetRValue(val);
    int green = GetGValue(val);
    int blue = GetBValue(val);

    v_clor_.x_ = red / 255.0;
    v_clor_.y_ = green / 255.0;
    v_clor_.z_ = blue / 255.0;

    TBox* tbox = new TBox(length_, width_, height_);
    tbox->set_angle(angle_);
    tbox->set_type(Object3D::BOX_OBJ);
    tbox->set_etype(EntityObject::OBJ_3D);
    tbox->set_color(v_clor_);
    if (cad_view_ != NULL)
    {
        cad_view_->MakeEntityObject(tbox);
    }
}

void BoxObjectDlg::OnComboChanged()
{
    int idx = mComboxInsertType.GetCurSel();
    switch (idx)
    {
    case BOX_POINT:
    {
        edt_box_height_.EnableWindow(TRUE);
        edt_box_length_.EnableWindow(TRUE);
        edt_box_width_.EnableWindow(TRUE);
    }
        break;
    case BOX_LINE:
    {
        edt_box_height_.EnableWindow(TRUE);
        edt_box_length_.EnableWindow(TRUE);
        edt_box_width_.EnableWindow(FALSE);
    }
        break;
    case BOX_REGION:
    {
        edt_box_length_.EnableWindow(FALSE);
        edt_box_width_.EnableWindow(FALSE);
        edt_box_height_.EnableWindow(TRUE);
    }
        break;
    default:
        break;
    }
}