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

IMPLEMENT_DYNCREATE(MainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(MainFrame, CFrameWndEx)
    ON_WM_CREATE()
    ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &MainFrame::OnApplicationLook)
    ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &MainFrame::OnUpdateApplicationLook)
    ON_COMMAND(ID_FILE_PRINT, &MainFrame::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &MainFrame::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &MainFrame::OnFilePrintPreview)
    ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &MainFrame::OnUpdateFilePrintPreview)
    ON_COMMAND(ID_DRAWING_AXIS, &MainFrame::OnDrawingAxis)
    ON_UPDATE_COMMAND_UI(ID_BTN_GRID, &MainFrame::OnUpdateDrawingAxis)
    ON_COMMAND(ID_BTN_GRID, &MainFrame::OnBtnGrid)
    ON_COMMAND(ID_VIEW_ISO, &MainFrame::OnViewIso)
    ON_COMMAND(ID_VIEW_TOP, &MainFrame::OnViewTop)
    ON_COMMAND(ID_VIEW_LEFT, &MainFrame::OnViewLeft)
    ON_COMMAND(ID_VIEW_FRONT, &MainFrame::OnViewFront)
    ON_COMMAND(ID_VIEW_BOTTOM, &MainFrame::OnViewBottom)
    ON_COMMAND(ID_VIEW_RIGHT, &MainFrame::OnViewRight)
    ON_COMMAND(ID_VIEW_BACK, &MainFrame::OnViewBack)
    ON_COMMAND(ID_SHOW_RESET, &MainFrame::OnShowReset)
    ON_UPDATE_COMMAND_UI(ID_BTN_GRID, &MainFrame::OnUpdateBtnGrid)
    ON_COMMAND(ID_DRAWING_LINE, &MainFrame::OnDrawingLine)
    ON_COMMAND(ID_DRAWING_POINT, &MainFrame::OnDrawingPoint)
    ON_COMMAND(ID_DRAWING_POLYLINE, &MainFrame::OnDrawingPolyline)
    ON_COMMAND(ID_DRAWING_RECT, &MainFrame::OnDrawingRect)
    ON_COMMAND(ID_DRAWING_CIRCLE, &MainFrame::OnDrawingCircle)
    ON_COMMAND(ID_DRAWING_ARC, &MainFrame::OnDrawingArc)
    ON_COMMAND(ID_BTN_BOX, &MainFrame::OnMakeBox)
END_MESSAGE_MAP()

// MainFrame construction/destruction

MainFrame::MainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}

MainFrame::~MainFrame()
{
}

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

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

	return 0;
}

BOOL MainFrame::OnCreateClient(LPCREATESTRUCT lpCreateStruct, CCreateContext *pContext) 
{
    if (!splitter_.CreateStatic(this, 1, 2)) {
        TRACE0("Failed to create Static windows");
        return FALSE;
    }

    if (!splitter_.CreateView(0, 0, RUNTIME_CLASS(FormBar),
        CSize(250, 400),
        pContext)) {
        TRACE0("Failed to view 0");
        return FALSE;
    }

    if (!splitter_.CreateView(0, 1, RUNTIME_CLASS(TCadView), CSize(800, 400), pContext)) {
        TRACE0("Failed to view 1");
        return FALSE;
    }

    tcad_view_ = reinterpret_cast<TCadView*>(splitter_.GetPane(0, 1));
    form_bar_ = reinterpret_cast<FormBar*>(splitter_.GetPane(0, 0));
    tcad_view_->SetFormBar(form_bar_);
    // Choose BighouseView is activated when start
    splitter_.SetActivePane(0, 1);


    return TRUE;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// MainFrame diagnostics

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// MainFrame message handlers

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
    tcad_view_->OnDrawingAxis();
}

void MainFrame::OnUpdateDrawingAxis(CCmdUI *pCmdUI)
{
    if (tcad_view_ != NULL)
    {
        bool is_show_axis = tcad_view_->get_is_show_axis();
        pCmdUI->SetCheck(is_show_axis);
    }
}

void MainFrame::OnBtnGrid()
{
    tcad_view_->OnBtnGrid();
}

void MainFrame::OnUpdateBtnGrid(CCmdUI *pCmdUI)
{
    if (tcad_view_ != NULL)
    {
       bool is_show_grid = tcad_view_->get_is_gird();
       pCmdUI->SetCheck(is_show_grid);
    }
}

void MainFrame::OnViewIso()
{
    tcad_view_->OnViewIso();
}

void MainFrame::OnViewTop()
{
    tcad_view_->OnViewTop();
}

void MainFrame::OnViewLeft()
{
    tcad_view_->OnViewLeft();
}

void MainFrame::OnViewFront()
{
    tcad_view_->OnViewFront();
}

void MainFrame::OnViewBottom()
{
    tcad_view_->OnViewBottom();
}

void MainFrame::OnViewRight()
{
    tcad_view_->OnViewRight();
}

void MainFrame::OnViewBack()
{
    tcad_view_->OnViewBack();
}

void MainFrame::OnShowReset()
{
    tcad_view_->OnShowReset();
}

void MainFrame::OnDrawingLine()
{
    tcad_view_->OnDrawing2d(Type2D::DR_LINE);
}

void MainFrame::OnDrawingPoint()
{
    tcad_view_->OnDrawing2d(Type2D::DR_POINT);
}

void MainFrame::OnDrawingPolyline()
{
    tcad_view_->OnDrawing2d(Type2D::DR_POLY_LINE);
}

void MainFrame::OnDrawingRect()
{
    tcad_view_->OnDrawing2d(Type2D::DR_RECTANGLE);
}

void MainFrame::OnDrawingCircle()
{
    tcad_view_->OnDrawing2d(Type2D::DR_CIRCLE);
}

void MainFrame::OnDrawingArc()
{
    tcad_view_->OnDrawing2d(Type2D::DR_ARC);
}

void MainFrame::OnMakeBox()
{
    BoxObjectDlg box_dlg;
    if (box_dlg.DoModal() == IDOK)
    {
        float length = box_dlg.get_length();
        float width = box_dlg.get_width();
        float height = box_dlg.get_height();
        VEC3D v_color = box_dlg.get_v_color();

        TBox* tbox = new TBox(length, width, height);
        tbox->set_type(Object3D::BOX_OBJ);
        tbox->set_etype(EntityObject::OBJ_3D);
        tbox->set_color(v_color);

        ObjectInfo* new_obj_info = new ObjectInfo();
        new_obj_info->obj_data_ = tbox;
        new_obj_info->name_ = tbox->get_info();
        form_bar_->AddObjectList(new_obj_info);
    }
}