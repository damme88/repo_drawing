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

// MainFrm.h : interface of the MainFrame class
//

#pragma once
#include "FormBar.h"
#include "TCadView.h"

class MainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	MainFrame();
	DECLARE_DYNCREATE(MainFrame)

// Attributes
public:
    CSplitterWnd splitter_;
// Operations
public:
    BOOL OnCreateClient(LPCREATESTRUCT lpCreateStruct, CCreateContext *pContext);
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~MainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
    TCadView* tcad_view_;
    FormBar* form_bar_;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
    afx_msg void OnDrawingAxis();
    afx_msg void OnUpdateDrawingAxis(CCmdUI *pCmdUI);
    afx_msg void OnBtnGrid();
    afx_msg void OnUpdateBtnGrid(CCmdUI *pCmdUI);
    //View
    afx_msg void OnViewIso();
    afx_msg void OnViewTop();
    afx_msg void OnViewLeft();
    afx_msg void OnViewFront();
    afx_msg void OnViewBottom();
    afx_msg void OnViewRight();
    afx_msg void OnViewBack();
    afx_msg void OnShowReset();
    afx_msg void OnSelect();

    //Drawing 2d
    afx_msg void OnDrawingLine();
    afx_msg void OnDrawingPoint();
    afx_msg void OnDrawingPolyline();
    afx_msg void OnDrawingRect();
    afx_msg void OnDrawingCircle();
    afx_msg void OnDrawingArc();

    //Drawing 3d
    afx_msg void OnMakeBox();
	DECLARE_MESSAGE_MAP()

};


