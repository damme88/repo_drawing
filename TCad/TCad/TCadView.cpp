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

// TCadView.cpp : implementation of the TCadView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TCad.h"
#endif

#include "TCadDoc.h"
#include "TCadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// TCadView

IMPLEMENT_DYNCREATE(TCadView, CView)

BEGIN_MESSAGE_MAP(TCadView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &TCadView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSEWHEEL()
    ON_WM_KEYDOWN()
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_DRAWING_AXIS, &TCadView::OnDrawingAxis)
    ON_UPDATE_COMMAND_UI(ID_DRAWING_AXIS, &TCadView::OnUpdateDrawingAxis)
END_MESSAGE_MAP()

// TCadView construction/destruction

TCadView::TCadView()
{
	// TODO: add construction code here
    is_show_axis_ = true;
    rendering_rate_ = 0.5f;

    r_btn_down_ = false;
    l_btn_down_ = false;

    pAmbien_[0] = 0.5f;
    pAmbien_[1] = 0.5f;
    pAmbien_[2] = 0.5f;
    pAmbien_[3] = 1.0f;

    pSpecular_[0] = 0.5f;
    pSpecular_[1] = 0.5f;
    pSpecular_[2] = 0.5f;
    pSpecular_[3] = 1.0f;

    pDiff_[0] = 0.5f;
    pDiff_[1] = 0.5f;
    pDiff_[2] = 0.5f;
    pDiff_[3] = 1.0f;

    shininess_ = 50;

    angle_x_ = 0.0;
    angle_y_ = 0.0;
    angle_z_ = 0.0;
}

TCadView::~TCadView()
{
}

BOOL TCadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

int TCadView::OnCreate(LPCREATESTRUCT lpcs)
{
    if (CView::OnCreate(lpcs) == -1)
        return -1;

    InitOpenGL();

    return 0;
}

BOOL TCadView::InitOpenGL()
{
    m_pDC = new CClientDC(this);
    if (m_pDC == NULL)
        return FALSE;
    if (!SetupPixelFormat())
        return FALSE;

    m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
    if (0 == m_hRC)
        return FALSE;
    if (FALSE == ::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC))
        return FALSE;

    // Clear background by black color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Clear depth
    glClearDepth(1.0f);
    // Enable depth test
    ::glEnable(GL_DEPTH_TEST);

    // Enable color tracking
    ::glEnable(GL_COLOR_MATERIAL);
    ::glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    ::glShadeModel(GL_SMOOTH);
    // Setup lighting and material

    CreateOpenGLFont();
    BuildAxisesList();
    //SetupLight();
    //OnLoadTexture();
    //CreateOpenGLFont();
    return TRUE;
}

BOOL TCadView::SetupPixelFormat()
{
    DWORD dwflag;
    dwflag = PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_GENERIC_ACCELERATED |
        PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA;

    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        dwflag,
        32,
        0,0,0,0,0,0,0,0,
        32,
        0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0 };

    int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

    if (m_nPixelFormat == 0)
    {
        return FALSE;
    }

    if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
    {
        return FALSE;
    }
    return TRUE;
}




// TCadView drawing

void TCadView::OnDraw(CDC* /*pDC*/)
{
	TCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: add draw code for native data here
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ::glClearColor(0, 0, 0, 1.0f);

    RenderScene();
    glFlush();
    ::glFinish();
    ::SwapBuffers(m_pDC->GetSafeHdc());
}

void TCadView::RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();
    p_cameral_.ViewDirection();
    DrawAxis();
    DrawAxisSmall();

    glColor3f(1.0, 0.0, 0.0);
    OnLighting();
    glRotatef(90, 1, 0, 0);
    glutWireTeapot(150.0);
    OffLighting();
}

void TCadView::DrawAxis()
{
    if (is_show_axis_ == true)
    {
        glLineWidth(1.0f);
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0*VALUE_AXIS, 0.0f, 0.0f);
        glVertex3f(VALUE_AXIS, 0.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, VALUE_AXIS, 0.0f);
        glVertex3f(0.0f, -1.0*VALUE_AXIS, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, VALUE_AXIS);
        glVertex3f(0.0f, 0.0f, -1 * VALUE_AXIS);
        glEnd();
    }
}

void TCadView::DrawAxisSmall()
{
    CRect rect;
    GetClientRect(rect);
    CPoint pt;
    pt.x = 66;
    pt.y = rect.Height() - 66;

    GLdouble model_view[16];
    GLdouble projection[16];
    GLint viewport[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLfloat winx = (float)pt.x;
    GLfloat winy = (float)viewport[3] - (float)pt.y;
    GLfloat winz = 0.01;
    //glReadPixels(pt.x, int(winy), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);

    GLdouble glpt[3] = { 0.0, 0.0, 0.0 };
    gluUnProject(winx, winy, winz,
        model_view, projection, viewport,
        glpt, glpt + 1, glpt + 2);
    glPushMatrix();
    glTranslatef(glpt[0], glpt[1], glpt[2]);
    glRotatef(angle_x_, 1.0f, 0.0f, 0.0f);
    glRotatef(angle_y_, 0.0f, 1.0f, 0.0f);
    glRotatef(angle_z_, 0.0f, 0.0f, 1.0f);
    glCallList(axist_list_);
    glPopMatrix();
}


void TCadView::BuildAxisesList()
{
    axist_list_ = glGenLists(1);        // gen list
    glNewList(axist_list_, GL_COMPILE);

    glLineWidth(2.0f);          // make OX axis
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(60.0, 0.0, 0.0);

    glColor3ub(0, 255, 0);      // make OY axis
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 60.0, 0.0);

    glColor3ub(0, 0, 255);     // make OZ axis
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 60.0);
    glEnd();


    glColor3ub(255, 255, 255);
    DrawStringAt(100, 0.0, 0.0, "X");
    DrawStringAt(0.0, 100, 0.0, "Y");
    DrawStringAt(0.0, 0.0, 100, "Z");

    // make X Arrow 
    glPushMatrix();
    glColor3ub(255, 0, 0);
    glTranslatef(60.0, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glutSolidCone(4, 20, 16, 10);
    glPopMatrix();

    // Make Y Arrow
    glPushMatrix();
    glColor3ub(0, 255, 0);
    glTranslatef(0.0, 60.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutSolidCone(4, 20, 16, 10);
    glPopMatrix();

    //Make Z Arrow
    glPushMatrix();
    glColor3ub(0, 0, 255);
    glTranslatef(0.0, 0.0, 60);
    glutSolidCone(4, 20, 16, 10);
    glPopMatrix();
    glEndList();
}

void TCadView::CreateOpenGLFont() 
{
    CFont m_font;
    m_font.CreateFont(-16,               // Height Of Font 
        0,               // Width Of Font 
        0,               // Angle Of Escapement 
        0,               // Orientation Angle 
        FW_NORMAL,       // Font Weight 
        FALSE,           // Italic 
        FALSE,           // Underline 
        FALSE,           // Strikeout 
        ANSI_CHARSET,              // Character Set Identifier 
        OUT_TT_PRECIS,             // Output Precision 
        CLIP_DEFAULT_PRECIS,       // Clipping Precision 
        DEFAULT_QUALITY,           // Output Quality 
        FF_DONTCARE | DEFAULT_PITCH, // Family And Pitch 
        _T("Arial"));
    CFont* m_pOldFont = GetDC()->SelectObject(&m_font);
    m_editCLTip = glGenLists(256);
    m_textTip = glGenLists(256);
    wglUseFontBitmaps(m_pDC->m_hDC, 0, 255, m_editCLTip);
    wglUseFontBitmaps(m_pDC->m_hDC, 0, 255, m_textTip);
    GetDC()->SelectObject(m_pOldFont);
}

void TCadView::DrawStringAt(double x, double y, double z, char* s) 
{
    size_t length = strlen(s);
    if (length > 0 && s) {
        glRasterPos3d(x, y, z);
        glListBase(m_textTip);
        glCallLists(length, GL_UNSIGNED_BYTE, (const GLvoid*)s);
    }
}

void TCadView::OnSize(UINT nType, int cx, int cy) 
{
    CView::OnSize(nType, cx, cy);
    if (cx <= 0 || cy <= 0)
        return;
    cx_ = cx;
    cy_ = cy;

    CClientDC clienDC(this);
    wglMakeCurrent(clienDC.m_hDC, m_hRC);

    // Define viewport = size window
    glViewport(0, 0, cx, cy);

    GLfloat aspect_ratio = (GLdouble)cx / (GLdouble)cy;
    ::glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    SetViewFrustum();
    //::gluPerspective(45.0f, aspect_ratio, 0.01f,200.0f);

    ::glMatrixMode(GL_MODELVIEW);
}


void TCadView::SetViewFrustum()
{
    double left_ = -(double)cx_ *0.5 / rendering_rate_;
    double right_ = (double)cx_ *0.5 / rendering_rate_;
    double top_ = (double)cy_ *0.5 / rendering_rate_;
    double bottom_ = -(double)cy_ *0.5 / rendering_rate_;

    double zfar = 20000 / rendering_rate_;
    zfar = max(20000, rendering_rate_);
    glOrtho(left_, right_, bottom_, top_, -zfar, zfar);
}

BOOL TCadView::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}
// TCadView printing
void TCadView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL TCadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void TCadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void TCadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void TCadView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// TCadView diagnostics

#ifdef _DEBUG
void TCadView::AssertValid() const
{
	CView::AssertValid();
}

void TCadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

TCadDoc* TCadView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(TCadDoc)));
	return (TCadDoc*)m_pDocument;
}
#endif //_DEBUG


// TCadView message handlers


void TCadView::OnDrawingAxis()
{
    is_show_axis_ = !is_show_axis_;
    InvalidateRect(NULL, FALSE);
}


void TCadView::OnUpdateDrawingAxis(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(is_show_axis_);
}


void TCadView::OnLighting()
{
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pAmbien_);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pSpecular_);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pDiff_);
    glMateriali(GL_FRONT, GL_SHININESS, shininess_);

    GLfloat position[] = { 10000.0f, 10000.0f, 50000.0f, 1.0f };
    GLfloat global_ambient[] = { 0.8f, 0.8f, 0.8f, 1 };

    float MatAmbientBack[] = { 0.1f, 0.2f, 0.0f, 1.0f };
    glMaterialfv(GL_BACK, GL_AMBIENT, MatAmbientBack);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE); //this is good command for light

    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#if 0
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    /********clear AntiAliasing - Back Face*******************/
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    /************clear AntiAliasing*Back Face ****************/
#endif
}


void TCadView::OffLighting() 
{
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
}

void TCadView::OnLButtonDown(UINT nFlags, CPoint point) 
{
    l_btn_down_ = true;
    CView::OnLButtonDown(nFlags, point);
}

void TCadView::OnLButtonUp(UINT nFlags, CPoint point) 
{
    l_btn_down_ = false;
    CView::OnLButtonUp(nFlags, point);
}

void TCadView::OnRButtonUp(UINT nFlags, CPoint point)
{
    ms_down_pt_ = CPoint(0, 0);
    p_cameral_.SetDownPt(ms_down_pt_);
    ReleaseCapture();
    r_btn_down_ = false;
    //CView::OnRButtonUp(nFlags, point);
}

void TCadView::OnRButtonDown(UINT nFlags, CPoint point) 
{
    ms_down_pt_ = point;
    p_cameral_.SetDownPt(ms_down_pt_);
    SetCapture();
    r_btn_down_ = true;
    CView::OnRButtonDown(nFlags, point);
}

void TCadView::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (r_btn_down_) 
    {
        p_cameral_.CalAngle(point, cx_, cy_);
    }
    InvalidateRect(NULL, FALSE);
    CView::OnMouseMove(nFlags, point);
    if (GetCapture() == this) 
    {
        ms_down_pt_ = point;
        p_cameral_.SetDownPt(ms_down_pt_);
    }
}

BOOL TCadView::OnMouseWheel(UINT nFlags, short zDetal, CPoint point) 
{
    BOOL ret = FALSE;

    if (zDetal >= 0) 
    {
        ret = TRUE;
    }
    else 
    {
        ret = TRUE;
    }

    //cen_x_ += zoom_value_*lx_;
    //cen_x_ += zoom_value_*ly_;
    InvalidateRect(NULL, FALSE);
    //Set the mouse point
    ms_down_pt_ = point;
    CWnd::OnMouseWheel(nFlags, zDetal, point);
    return  ret;
}

void TCadView::MakeGrid()
{
  



}

void TCadView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    switch (nChar) 
    {
    case VK_UP:
        //y_position_ += 15.0f;
        InvalidateRect(NULL, FALSE);
        break;
    case VK_DOWN:
        //y_position_ -= 15.0f;
        InvalidateRect(NULL, FALSE);
        break;
    case VK_LEFT:
        //x_position_ -= 15.0f;
        InvalidateRect(NULL, FALSE);
        break;
    case VK_RIGHT:
        //x_position_ += 15.0f;
        InvalidateRect(NULL, FALSE);
        break;
    case VK_DELETE: {
        //DeleteShelf();
        InvalidateRect(NULL, FALSE);
        break;
    }
    case VK_ESCAPE: 
    {
        //MainFrame * main_frame = static_cast<MainFrame*>(AfxGetMainWnd());
        //main_frame->HandleEscape();
    }
    case 82:  // R key button
        //RotateShelf();
        InvalidateRect(NULL, FALSE);
        break;
    }
    CView::OnKeyDown(nChar, nRepCnt, nFlags);
}