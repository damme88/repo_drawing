#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include "ObjectInfo.h"
#include "afxcolorbutton.h"

class TCadView;
// FormBar form view

class FormBar : public CFormView
{
	DECLARE_DYNCREATE(FormBar)
protected:
    std::vector<ObjectInfo*> obj_list_;
    TCadView* m_TcadView;
protected:
	FormBar();           // protected constructor used by dynamic creation
	virtual ~FormBar();
    void OnInitialUpdate();
public:
    COLORREF GetColorBase();
    void SetTCadView(TCadView* view) { m_TcadView = view; }
    TCadView* GetTCadView();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMBAR };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
private:
    CMFCColorButton m_ColorBase;
};


