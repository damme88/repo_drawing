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
}

BoxObjectDlg::BoxObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_BOX, pParent)
{
    length_ = 200;
    width_ = 100;
    height_ = 300;

    cad_view_ = NULL;
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
}


BEGIN_MESSAGE_MAP(BoxObjectDlg, CDialogEx)
    ON_BN_CLICKED(ID_INSERT_BOX, &BoxObjectDlg::InsertBox)
END_MESSAGE_MAP()


BOOL BoxObjectDlg::OnInitDialog()
{
    BOOL ret = CDialogEx::OnInitDialog();
    CString str;
    str.Format(_T("%f"), length_); edt_box_length_.SetWindowText(str);
    str.Format(_T("%f"), width_); edt_box_width_.SetWindowText(str);
    str.Format(_T("%f"), height_); edt_box_height_.SetWindowText(str);

    val_color_.SetColor(RGB(255, 255, 255));
    val_color_.SetColumnsNumber(8);
    return ret;
}
// BoxDlgObject message handlers
void BoxObjectDlg::InsertBox()
{
    CString str;
    edt_box_length_.GetWindowText(str);
    length_ = _ttof(str);
    edt_box_width_.GetWindowText(str);
    width_ = _ttof(str);
    edt_box_height_.GetWindowText(str);
    height_ = _ttof(str);

    COLORREF val = val_color_.GetColor();
    int red = GetRValue(val);
    int green = GetGValue(val);
    int blue = GetBValue(val);

    v_clor_.x_ = red / 255.0;
    v_clor_.y_ = green / 255.0;
    v_clor_.z_ = blue / 255.0;

    TBox* tbox = new TBox(length_, width_, height_);
    tbox->set_type(Object3D::BOX_OBJ);
    tbox->set_etype(EntityObject::OBJ_3D);
    tbox->set_color(v_clor_);
    if (cad_view_ != NULL)
    {
        cad_view_->MakeEntityObject(tbox);
    }
}