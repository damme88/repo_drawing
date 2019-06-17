// CdockPaneExp.cpp : implementation file
//

#include "stdafx.h"
#include "TCad.h"
#include "BoxObjectPanel.h"
#include "MainFrm.h"
// CdockPaneExp

IMPLEMENT_DYNAMIC(BoxObjectPanel, CDockablePane)

BoxObjectPanel::BoxObjectPanel()
{

}

BoxObjectPanel::~BoxObjectPanel()
{
}


BEGIN_MESSAGE_MAP(BoxObjectPanel, CDockablePane)
ON_WM_CREATE()
ON_WM_SIZE()
ON_WM_CLOSE()
END_MESSAGE_MAP()


int BoxObjectPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct))
        return -1;
    dialog_box.Create(IDD_DLG_BOX, this);
    dialog_box.ShowWindow(SW_SHOW);
    return 0;
}

void BoxObjectPanel::OnSize(UINT nSize, int cx, int cy)
{
    CRect rect_wnd;
    CRect rect_obj;
    GetClientRect(rect_wnd);
    if (dialog_box.m_hWnd != NULL)
    {
        dialog_box.GetWindowRect(rect_obj);
        dialog_box.SetWindowPos(NULL, 0, 0, rect_wnd.Width(), rect_wnd.Height(), SWP_SHOWWINDOW);
    }

    CDockablePane::OnSize(nSize, cx, cy);
}
// CdockPaneExp message handlers


