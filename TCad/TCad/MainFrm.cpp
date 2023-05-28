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

// MainFrm.cpp : implementation of the MainFrame class
//

#include "stdafx.h"
#include "TCad.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(MainFrame, CMDIFrameWndEx)
    ON_WM_CREATE()
    ON_WM_CLOSE()
    ON_COMMAND(ID_WINDOW_MANAGER, &MainFrame::OnWindowManager)
    ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &MainFrame::OnApplicationLook)
    ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &MainFrame::OnUpdateApplicationLook)
    ON_COMMAND(ID_FILE_PRINT, &MainFrame::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &MainFrame::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &MainFrame::OnFilePrintPreview)
    ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &MainFrame::OnUpdateFilePrintPreview)
    ON_COMMAND(ID_APP_SETTING, &MainFrame::OnSettingInfo)
    ON_COMMAND(ID_DRAWING_AXIS, &MainFrame::OnDrawingAxis)
    ON_UPDATE_COMMAND_UI(ID_DRAWING_AXIS, &MainFrame::OnUpdateDrawingAxis)
    ON_COMMAND(ID_BTN_SELECT, &MainFrame::OnSelect)
    ON_UPDATE_COMMAND_UI(ID_BTN_SELECT, &MainFrame::OnUpdateSelect)
    ON_COMMAND(ID_BTN_GRID, &MainFrame::OnBtnGrid)
    ON_UPDATE_COMMAND_UI(ID_BTN_GRID, &MainFrame::OnUpdateBtnGrid)
    ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
    ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
    ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
    ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
    ON_COMMAND_RANGE(ID_DRAWING_POINT, ID_DRAWING_ARC, &MainFrame::OnHandle2D)
    ON_UPDATE_COMMAND_UI_RANGE(ID_DRAWING_POINT, ID_DRAWING_ARC, &MainFrame::OnUpdate2DObj)
END_MESSAGE_MAP()

// MainFrame construction/destruction

MainFrame::MainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
    show_box_ = false;
    drawing2d_id_ = 0;
    drawing3d_id_ = 0;
}

MainFrame::~MainFrame()
{

}

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

    CMDITabInfo mdiTabParams;
    mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // other styles available...
    mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
    mdiTabParams.m_bTabIcons = FALSE;    // set to TRUE to enable document icons on MDI taba
    mdiTabParams.m_bAutoColor = TRUE;    // set to FALSE to disable auto-coloring of MDI tabs
    mdiTabParams.m_bDocumentMenu = TRUE; // enable the document menu at the right edge of the tab area
    EnableMDITabbedGroups(TRUE, mdiTabParams);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

    // set the visual manager used to draw all user interface elements
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));

    // Enable enhanced windows management dialog
    EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

    // Switch the order of document name and application name on the window title bar. This
    // improves the usability of the taskbar because the document name is visible with the thumbnail.
    ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}

TCadView* MainFrame::GetView()
{
    TCadView * pCadView = NULL;
    CMDIFrameWnd* pFrame = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd));
    if (pFrame)
    {
        CMDIChildWnd * pChild = pFrame->MDIGetActive();
        if (pChild != NULL)
        {
            CView* pView = pChild->GetActiveView();
            if (pView != NULL)
            {
                if (pView->IsKindOf(RUNTIME_CLASS(TCadView)))
                {
                    pCadView = STATIC_DOWNCAST(TCadView, pView);
                }
            }
        }
    }

    if (pCadView == NULL)
    {
        if (GetFormBar() != NULL)
        {
            pCadView = GetFormBar()->GetTCadView();
        }
    }
    
    return pCadView;
}


BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// MainFrame diagnostics

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
    CMDIFrameWndEx::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
    CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// MainFrame message handlers

void MainFrame::OnWindowManager()
{
    ShowWindowsDialog();
}

void MainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void MainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void MainFrame::OnFilePrint()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void MainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // force Print Preview mode closed
	}
}

void MainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
    if (GetView() != NULL)
    {
        pCmdUI->Enable(TRUE);
        pCmdUI->SetCheck(IsPrintPreview());
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void MainFrame::OnSettingInfo()
{
    if (GetView() != NULL)
    {
        GetView()->OnSettingInfo();
    }
}

void MainFrame::OnDrawingAxis()
{
    if (GetView() != NULL)
    {
        GetView()->OnDrawingAxis();
    }
}

void MainFrame::OnUpdateDrawingAxis(CCmdUI *pCmdUI)
{
    if (GetView() != NULL)
    {
        bool state = GetView()->get_is_show_axis();
        pCmdUI->SetCheck(state);
        pCmdUI->Enable(TRUE);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void MainFrame::OnBtnGrid()
{
    if (GetView() != NULL)
    {
        GetView()->OnBtnGrid();
    }
    
}

void MainFrame::OnUpdateBtnGrid(CCmdUI *pCmdUI)
{
    if (GetView() != NULL)
    {
        bool state = GetView()->get_is_gird();
        pCmdUI->SetCheck(state);
        pCmdUI->Enable(TRUE);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}


void MainFrame::OnHandle2D(UINT nId)
{
    if (GetView() != NULL)
    {
        TCadView* pView = GetView();
        switch (nId)
        {
        case ID_DRAWING_LINE:
        {
            pView->OnDrawing2d(Type2D::DR_LINE);
            drawing2d_id_ = ID_DRAWING_LINE;
            break;
        }
        case ID_DRAWING_POLYLINE:
        {
            pView->OnDrawing2d(Type2D::DR_POLY_LINE);
            drawing2d_id_ = ID_DRAWING_POLYLINE;
            break;
        }
        case ID_DRAWING_CIRCLE:
        {
            pView->OnDrawing2d(Type2D::DR_CIRCLE);
            drawing2d_id_ = ID_DRAWING_CIRCLE;
            break;
        }
        case ID_DRAWING_RECT:
        {
            pView->OnDrawing2d(Type2D::DR_RECTANGLE);
            drawing2d_id_ = ID_DRAWING_RECT;
            break;
        }
        case ID_DRAWING_ARC:
        {
            pView->OnDrawing2d(Type2D::DR_ARC);
            drawing2d_id_ = ID_DRAWING_ARC;
            break;
        }
        case ID_DRAWING_POINT:
        {
            pView->OnDrawing2d(Type2D::DR_POINT);
            drawing2d_id_ = ID_DRAWING_POINT;
            break;
        }
        default:
        {
            drawing2d_id_ = 0;
            break;
        }
        }
    }
}

void MainFrame::OnUpdate2DObj(CCmdUI* pCmdUI)
{
    if (GetView() != NULL)
    {
        bool state = (drawing2d_id_ == pCmdUI->m_nID ? TRUE : FALSE);
        pCmdUI->SetCheck(state);
        pCmdUI->Enable(TRUE);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}


void MainFrame::OnSelect()
{
    if (GetView() != NULL)
    {
        GetView()->DoSelect();
        drawing2d_id_ = 0;
    }
}

void MainFrame::OnUpdateSelect(CCmdUI* pCmdUI)
{
    if (GetView() != NULL)
    {
        pCmdUI->Enable(TRUE);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}



void MainFrame::SetStateDrawing(const INT& state) 
{ 
    drawing2d_id_ = state; 
    drawing3d_id_ = state; 
}


FormBar* MainFrame::GetFormBar()
{
    CMDIFrameWndEx* pFrame = ((CMDIFrameWndEx*)(AfxGetApp()->m_pMainWnd));
    if (pFrame)
    {
        CMDIChildWnd * pChild = pFrame->MDIGetActive();
        if (!pChild)
            return NULL;
        CView * pView = pChild->GetActiveView();
        if (!pView)
            return NULL;
        if (!pView->IsKindOf(RUNTIME_CLASS(FormBar)))
            return NULL;

        return (FormBar *)pView;
    }
    return NULL;
}

void MainFrame::OnEditUndo()
{
    TCadDoc* pDoc = NULL;
    pDoc = GetView()->GetDocument();
    if (pDoc)
    {
        pDoc->UndoData();
    }
}

void MainFrame::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
    if (GetView() != NULL)
    {
        TCadDoc	*pDoc = GetView()->GetDocument();
        if (pDoc)
        {
            bool state = pDoc->GetOnUndoState();
            pCmdUI->Enable(state);
        }
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void MainFrame::OnEditRedo()
{
    if (GetView() != NULL)
    {
        TCadDoc* pDoc = NULL;
        pDoc = GetView()->GetDocument();
        if (pDoc)
        {
            pDoc->RedoData();
        }
    }
}

void MainFrame::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
    if (GetView() != NULL)
    {
        TCadDoc	*pDoc = GetView()->GetDocument();
        if (pDoc)
        {
            bool state = pDoc->GetOnRedoState();
            pCmdUI->Enable(state);
        }
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}
