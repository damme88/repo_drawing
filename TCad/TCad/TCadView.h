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
#include "TPolyLine.h"
#include "TRectangle.h"
#include "TCircle.h"
#include "TBox.h"
#include "TCadDoc.h"
#include "FormBar.h"
#include "JiggBase.h"

class ChildFrame;
class TCadView : public CView
{
protected: // create from serialization only
	TCadView();
	DECLARE_DYNCREATE(TCadView)

    enum DrawingMode
    {
        NONE = 0,
        NORMAL_MODE = 1
    };

// Attributes
public:
	TCadDoc* GetDocument() const;
    ChildFrame* GetChildFrame() const;
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
    POINT3D ConvertWindowToOpenGL(const CPoint &point2D);
    VEC3D GetPPVectorScreen();
    POINT3D GetMousePtOnPlane(POINT3D &gl_point, POINT3D &origin_point);
    POINT3D PointWndToPointPlane(CPoint pt);
    int FindIndexObject(Vector3D &ppVector, Vector3D &gl_point);
    void DrawEntityObject(GLenum mode);
    void ImplementCancel();
    void MakePolyLineObject(const bool& is_closed = false);
    void SetFormBar(FormBar* fb) { form_bar_ = fb; }
    void MakeEntityObject(EntityObject* ents_obj);
    void UpdateObject(EntityObject* newObj, int idx);
    //void CreateBox();
    bool get_is_gird() const { return is_show_grid_; }
    bool get_is_show_axis() const { return is_show_axis_; }
    void ImplementAction(const CPoint& pick_pt);
    void ImplementUndoRedo();
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnInitialUpdate();
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
    EntityObject* entity_obj_;
    FormBar* form_bar_;
    PCam p_cameral_;
    bool r_btn_down_;
    bool l_btn_down_;
    
    GLfloat scaling_;
    BOOL middle_down_;
    CPoint middle_down_pos_;
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

    GLdouble xPos_;
    GLdouble yPos_;
    GLdouble zPos_;

    bool is_show_axis_;
    bool is_show_grid_;
    bool is_grip_;
    EntityObject* pObjGripping_;
    UINT type_2d_;
    UINT type_3d_;
    std::vector<CPoint> pt_list_;
    JiggBase* p_jig_base_;

    GLdouble gldAspect;

    //Drawing style variable
    DrawingMode drawing_mode_;

// Generated message map functions
protected:
    afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDetal, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
public:
    void OnDrawingAxis();
    void OnBtnGrid();
    void OnViewIso();
    void OnViewTop();
    void OnViewLeft();
    void OnViewFront();
    void OnViewBottom();
    void OnViewRight();
    void OnViewBack();
    void OnShowReset();
    void DoSelect();
    void OnDrawing2d(UINT type);
};

#ifndef _DEBUG  // debug version in TCadView.cpp
inline TCadDoc* TCadView::GetDocument() const
   { return reinterpret_cast<TCadDoc*>(m_pDocument); }
#endif

