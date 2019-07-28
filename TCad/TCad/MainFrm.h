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
#include "TCadView.h"
#include "BoxObjectPanel.h"
#include "SettingInfo.h"

class MainFrame : public CMDIFrameWndEx
{

    DECLARE_DYNCREATE(MainFrame)
public: // create from serialization only
	MainFrame();
// Attributes
public:
// Operations
    void UpdateBox(int idx);
    void OnMakeBox();
    void SetStateDrawing(const INT& state);
public:
    //BOOL OnCreateClient(LPCREATESTRUCT lpCreateStruct, CCreateContext *pContext);
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
    TCadView* GetView();
protected:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;


    BoxObjectPanel m_object;
    bool show_box_;
    INT view_id_;
    INT drawing2d_id_;
    INT drawing3d_id_;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnEditUndo();
    afx_msg void OnEditRedo();
    afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
    afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
    afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
    //Setting
    afx_msg void OnSettingInfo();

    afx_msg void OnDrawingAxis();
    afx_msg void OnUpdateDrawingAxis(CCmdUI *pCmdUI);

    afx_msg void OnBtnGrid();
    afx_msg void OnUpdateBtnGrid(CCmdUI *pCmdUI);
    //View
    afx_msg void OnHandleView(UINT nId);
    afx_msg void OnUpdateViewEye(CCmdUI* pCmdUI);
    //2d
    afx_msg void OnHandle2D(UINT nId);
    afx_msg void OnUpdate2DObj(CCmdUI* pCmdUI);

    //Basic
    afx_msg void OnShowReset();
    afx_msg void OnUpdateReset(CCmdUI* pCmdUI);
    afx_msg void OnSelect();
    afx_msg void OnUpdateSelect(CCmdUI* pCmdUI);
    //Drawing 3d
    afx_msg void OnHandle3D(UINT nId);
    afx_msg void OnUpdate3DObj(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

};


