// FormBar.cpp : implementation file
//

#include "stdafx.h"
#include "TCad.h"
#include "FormBar.h"
#include "MainFrm.h"
#include "TCadView.h"

// FormBar

IMPLEMENT_DYNCREATE(FormBar, CFormView)

FormBar::FormBar()
	: CFormView(IDD_FORMBAR)
{

}

FormBar::~FormBar()
{
    if (obj_list_.size() > 0)
    {
        obj_list_.clear();
    }
}

void FormBar::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_OBJECT, list_object);
}

BEGIN_MESSAGE_MAP(FormBar, CFormView)
ON_WM_SIZE()
ON_BN_CLICKED(IDC_BTN_INSERT, &FormBar::OnBnClickedBtnInsert)
END_MESSAGE_MAP()


// FormBar diagnostics

#ifdef _DEBUG
void FormBar::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void FormBar::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void FormBar::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
    list_object.SetExtendedStyle(list_object.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    list_object.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
    list_object.InsertColumn(1, _T("Properties"), LVCFMT_LEFT, 50);
    list_object.InsertColumn(2, _T("Type"), LVCFMT_LEFT, 50);

}
// FormBar message handlers
void FormBar::OnSize(UINT nType, int cx, int cy) 
{
    EnableScrollBarCtrl(SB_VERT, FALSE);

    CRect rect_wnd;
    CRect rect_obj;
    GetClientRect(rect_wnd);
    if (list_object.m_hWnd != NULL) 
    {
        list_object.GetWindowRect(rect_obj);
        list_object.SetWindowPos(NULL, 2, 2, rect_wnd.Width(), rect_obj.Height(), SWP_SHOWWINDOW);
    }
    CFormView::OnSize(nType, cx, cy);
}

void FormBar::AddObjectList(ObjectInfo* obj_info)
{
    obj_list_.push_back(obj_info);
    int idx = obj_list_.size();
    if ((idx - 1) >= 0)
    {
        list_object.InsertItem(idx-1, obj_info->name_);
        list_object.SetItemText(idx-1, 1, obj_info->properties_);
        list_object.SetItemText(idx-1, 2, obj_info->type_);
    }
}

void FormBar::OnBnClickedBtnInsert()
{
    int row = list_object.GetSelectionMark();
    if (row < obj_list_.size())
    {
        ObjectInfo* obj_info = obj_list_.at(row);
        EntityObject* ent_obj = obj_info->obj_data_;
        GetTCadView()->MakeEntityObject(ent_obj);
    }
}


TCadView* FormBar::GetTCadView()
{
    TCadApp *pApp = (TCadApp*)AfxGetApp();
    MainFrame* pMainFrame = (MainFrame*)pApp->m_pMainWnd;
    TCadView* pView = reinterpret_cast<TCadView*>(pMainFrame->splitter_.GetPane(0, 1));
    return pView;
}