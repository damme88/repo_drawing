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
#include "BoxObjectDlg.h"


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
    ON_COMMAND(ID_DRAWING_AXIS, &MainFrame::OnDrawingAxis)
    //ON_UPDATE_COMMAND_UI(ID_BTN_GRID, &MainFrame::OnUpdateDrawingAxis)
    ON_COMMAND(ID_BTN_GRID, &MainFrame::OnBtnGrid)
    ON_COMMAND(ID_VIEW_ISO, &MainFrame::OnViewIso)
    ON_COMMAND(ID_VIEW_TOP, &MainFrame::OnViewTop)
    ON_COMMAND(ID_VIEW_LEFT, &MainFrame::OnViewLeft)
    ON_COMMAND(ID_VIEW_FRONT, &MainFrame::OnViewFront)
    ON_COMMAND(ID_VIEW_BOTTOM, &MainFrame::OnViewBottom)
    ON_COMMAND(ID_VIEW_RIGHT, &MainFrame::OnViewRight)
    ON_COMMAND(ID_VIEW_BACK, &MainFrame::OnViewBack)
    ON_COMMAND(ID_SHOW_RESET, &MainFrame::OnShowReset)
   // ON_UPDATE_COMMAND_UI(ID_BTN_GRID, &MainFrame::OnUpdateBtnGrid)
    ON_COMMAND(ID_DRAWING_LINE, &MainFrame::OnDrawingLine)
    ON_COMMAND(ID_DRAWING_POINT, &MainFrame::OnDrawingPoint)
    ON_COMMAND(ID_DRAWING_POLYLINE, &MainFrame::OnDrawingPolyline)
    ON_COMMAND(ID_DRAWING_RECT, &MainFrame::OnDrawingRect)
    ON_COMMAND(ID_DRAWING_CIRCLE, &MainFrame::OnDrawingCircle)
    ON_COMMAND(ID_DRAWING_ARC, &MainFrame::OnDrawingArc)
    ON_COMMAND(ID_BTN_BOX, &MainFrame::OnMakeBox)
    ON_COMMAND(ID_BTN_SELECT, &MainFrame::OnSelect)
END_MESSAGE_MAP()

// MainFrame construction/destruction

MainFrame::MainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
    show_box_ = false;
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

    // GetOwner is an inherited method.
    UINT style = WS_CHILD | CBRS_RIGHT | CBRS_FLOAT_MULTI;
    CString strTitle = _T("Box Object Pane");
    if (!m_object.Create(strTitle, this,CRect(0, 0, 300, 600), TRUE, IDC_OBJECT_PANE, style))
    {
        return 0;
    }

	return 0;
}

TCadView* MainFrame::GetView()
{
    CMDIFrameWnd* pFrame = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd));
    if (pFrame)
    {
        CMDIChildWnd * pChild = pFrame->MDIGetActive();
        if (!pChild)
            return NULL;
        CView * pView = pChild->GetActiveView();
        if (!pView)
            return NULL;
        // Fail if view is of wrong kind
        if (!pView->IsKindOf(RUNTIME_CLASS(TCadView)))
            return NULL;

        return (TCadView *)pView;
    }
    return NULL;
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
	pCmdUI->SetCheck(IsPrintPreview());
}


void MainFrame::OnDrawingAxis()
{
    if (GetView() != NULL)
        GetView()->OnDrawingAxis();
}

//void MainFrame::OnUpdateDrawingAxis(CCmdUI *pCmdUI)
//{
//    if (GetView() != NULL)
//    {
//        bool is_show_axis = GetView()->get_is_show_axis();
//        pCmdUI->SetCheck(is_show_axis);
//    }
//}

void MainFrame::OnBtnGrid()
{
    if (GetView() != NULL)
    {
        GetView()->OnBtnGrid();
    }
    
}

//void MainFrame::OnUpdateBtnGrid(CCmdUI *pCmdUI)
//{
//    if (GetView() != NULL)
//    {
//       bool is_show_grid = GetView()->get_is_gird();
//       pCmdUI->SetCheck(is_show_grid);
//    }
//}

void MainFrame::OnViewIso()
{
    if (GetView() != NULL)
    {

    }
    GetView()->OnViewIso();
}

void MainFrame::OnViewTop()
{
    if (GetView() != NULL)
    {
        GetView()->OnViewTop();
    }
    
}

void MainFrame::OnViewLeft()
{
    if (GetView() != NULL)
    {
        GetView()->OnViewLeft();
    }
   
}

void MainFrame::OnViewFront()
{
    if (GetView() != NULL)
    {
        GetView()->OnViewRight();
    }
}

void MainFrame::OnViewBottom()
{
    if (GetView() != NULL)
    {
        GetView()->OnViewBottom();
    }
}

void MainFrame::OnViewRight()
{
    if (GetView() != NULL)
    {
        GetView()->OnViewRight();
    }
}

void MainFrame::OnViewBack()
{
    if (GetView() != NULL)
    {
        GetView()->OnViewBack();
    }
}

void MainFrame::OnShowReset()
{
    if (GetView() != NULL)
    {
        GetView()->OnViewIso();
    }
}

void MainFrame::OnDrawingLine()
{
    if (GetView() != NULL)
    {
        GetView()->OnDrawing2d(Type2D::DR_LINE);
    }
    
}

void MainFrame::OnDrawingPoint()
{
    if (GetView() != NULL)
    {
        GetView()->OnDrawing2d(Type2D::DR_POINT);
    }
}

void MainFrame::OnDrawingPolyline()
{
    if (GetView() != NULL)
    {
        GetView()->OnDrawing2d(Type2D::DR_POLY_LINE);
    }
}

void MainFrame::OnDrawingRect()
{
    if (GetView() != NULL)
    {
        GetView()->OnDrawing2d(Type2D::DR_RECTANGLE);
    }
}

void MainFrame::OnDrawingCircle()
{
    if (GetView() != NULL)
    {
        GetView()->OnDrawing2d(Type2D::DR_CIRCLE);
    }
}

void MainFrame::OnDrawingArc()
{
    if (GetView() != NULL)
    {
        GetView()->OnDrawing2d(Type2D::DR_ARC);
    }
}

void MainFrame::OnSelect()
{
    if (GetView() != NULL)
    {
        GetView()->DoSelect();
    }
}

void MainFrame::OnMakeBox()
{
    if (GetView() != NULL)
    {
        show_box_ = !show_box_;
        if (show_box_)
        {
            m_object.SetView(GetView());
            m_object.SetType(0);
            m_object.InitDlgVal();
            m_object.EnableDocking(CBRS_ALIGN_ANY);
            DockPane((CBasePane*)&m_object, AFX_IDW_DOCKBAR_LEFT);
            m_object.ShowPane(TRUE, FALSE, TRUE);
        }
        else
        {
            m_object.ShowPane(FALSE, FALSE, FALSE);
        }
    }
}

void MainFrame::UpdateBox(int idx)
{
    TCadView* pView = GetView();
    if (pView)
    {
        m_object.SetView(GetView());
        m_object.SetType(1);
        EntityObject* pEntity = pView->GetDocument()->FindEntity(idx);
        if (pEntity->get_etype() == EntityObject::OBJ_3D)
        {
            Object3D* pObj = static_cast<Object3D*>(pEntity);
            TBox* pBox = static_cast<TBox*>(pObj);
            m_object.FillData(pBox, idx);
        }

        m_object.EnableDocking(CBRS_ALIGN_ANY);
        DockPane((CBasePane*)&m_object, AFX_IDW_DOCKBAR_LEFT);
        m_object.ShowPane(TRUE, FALSE, TRUE);
    }
}