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
}

BEGIN_MESSAGE_MAP(FormBar, CFormView)
ON_WM_SIZE()
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
}
// FormBar message handlers
void FormBar::OnSize(UINT nType, int cx, int cy) 
{
    EnableScrollBarCtrl(SB_VERT, FALSE);
    CFormView::OnSize(nType, cx, cy);
}

TCadView* FormBar::GetTCadView()
{
    return NULL;
}