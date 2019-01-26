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

// TCadView.h : interface of the TCadView class
//

#pragma once
#include "PCam.h"
#include <vector>
#include "TLine.h"
#include "TPoint.h"

class TCadView : public CView
{
protected: // create from serialization only
	TCadView();
	DECLARE_DYNCREATE(TCadView)

// Attributes
public:
	TCadDoc* GetDocument() const;

// Operations
public:
    int OnCreate(LPCREATESTRUCT lpcs);
    BOOL InitOpenGL();
    BOOL SetupPixelFormat();
    void RenderScene();
    void DrawAxis();
    void DrawAxisSmall();
    void SetViewFrustum();
    void BuildAxisesList();
    void DrawStringAt(double x, double y, double z, char* s);
    void CreateOpenGLFont();
    void OnLighting();
    void OffLighting();
    void MakeGrid(double width, double height, double distance);
    VEC3D ConvertWindowToOpenGL(const CPoint &point2D);
    VEC3D GetPPVectorScreen();
    POINT3D GetMousePtOnPlane(POINT3D &gl_point, POINT3D &origin_point);
    void DrawEntityObject();
    void Update2DObjState(UINT type);
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~TCadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    PCam p_cameral_;
    bool r_btn_down_;
    bool l_btn_down_;
    

    GLfloat angle_x_;
    GLfloat angle_y_;
    GLfloat angle_z_;

    GLfloat pAmbien_[4];
    GLfloat pSpecular_[4];
    GLfloat pDiff_[4];
    GLfloat  shininess_;

    GLuint  axist_list_;
    GLuint m_textTip;
    GLuint m_editCLTip;
    CPoint ms_down_pt_;
    GLfloat rendering_rate_;
    HGLRC m_hRC;
    CDC* m_pDC;

    int cx_; // size of window
    int cy_;

    bool is_show_axis_;
    bool is_show_grid_;
    UINT type_2d_;
    bool is_line_;
    bool is_point_;
    std::vector<CPoint> pt_list_;
// Generated message map functions
protected:
    afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDetal, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnDrawingAxis();
    afx_msg void OnUpdateDrawingAxis(CCmdUI *pCmdUI);
    afx_msg void OnBtnGrid();
    afx_msg void OnViewIso();
    afx_msg void OnViewTop();
    afx_msg void OnViewLeft();
    afx_msg void OnViewFront();
    afx_msg void OnViewBottom();
    afx_msg void OnViewRight();
    afx_msg void OnViewBack();
    afx_msg void OnUpdateBtnGrid(CCmdUI *pCmdUI);
    afx_msg void OnDrawingLine();
    afx_msg void OnUpdateDrawingLine(CCmdUI *pCmdUI);
    afx_msg void OnDrawingPoint();
    afx_msg void OnUpdateDrawingPoint(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in TCadView.cpp
inline TCadDoc* TCadView::GetDocument() const
   { return reinterpret_cast<TCadDoc*>(m_pDocument); }
#endif

