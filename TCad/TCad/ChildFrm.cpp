// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ChildFrm.cpp : implementation of the ChildFrame class
//

#include "stdafx.h"
#include "TCad.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ChildFrame

IMPLEMENT_DYNCREATE(ChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(ChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &ChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &ChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &ChildFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &ChildFrame::OnUpdateFilePrintPreview)
    ON_WM_MDIACTIVATE()
END_MESSAGE_MAP()

// ChildFrame construction/destruction

ChildFrame::ChildFrame()
{
	// TODO: add member initialization code here
}

ChildFrame::~ChildFrame()
{
}


BOOL ChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

BOOL ChildFrame::OnCreateClient(LPCREATESTRUCT lpCreateStruct, CCreateContext *pContext)
{
    if (!splitter_.CreateStatic(this, 1, 2)) 
    {
        TRACE0("Failed to create Static windows");
        return FALSE;
    }

    CRect rect;
    GetClientRect(rect);
    INT width = rect.Width();
    INT height = rect.Height();

    if (!splitter_.CreateView(0, 0, RUNTIME_CLASS(FormBar), CSize(width*0.25, height), pContext))
    {
        TRACE0("Failed to view 0");
        return FALSE;
    }

    if (!splitter_.CreateView(0, 1, RUNTIME_CLASS(TCadView), CSize(width*0.75, height), pContext))
    {
        TRACE0("Failed to view 1");
        return FALSE;
    }

    tcad_view_ = reinterpret_cast<TCadView*>(splitter_.GetPane(0, 1));
    form_bar_ = reinterpret_cast<FormBar*>(splitter_.GetPane(0, 0));
    tcad_view_->SetFormBar(form_bar_);
    form_bar_->SetTCadView(tcad_view_);

    splitter_.SetActivePane(0, 0);
    return TRUE;
}


MainFrame* ChildFrame::GetMainframe()
{
    return (MainFrame*)GetParentFrame();
}

void ChildFrame::FreeObjSelected()
{
    if (GetMainframe() != NULL)
    {
        GetMainframe()->SetStateDrawing(0);
    }
}
// ChildFrame diagnostics

#ifdef _DEBUG
void ChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void ChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// ChildFrame message handlers

void ChildFrame::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void ChildFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // force Print Preview mode closed
	}
}

void ChildFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}

void ChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
    CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

    CMDIChildWnd * pChild = static_cast<CMDIChildWnd*>(pActivateWnd);
    if (!pChild)
        return;
    CView * pView = pChild->GetActiveView();
    if (pView && pView->IsKindOf(RUNTIME_CLASS(TCadView)))
    {
        TCadView* pCadView = static_cast<TCadView*>(pView);
    }
}