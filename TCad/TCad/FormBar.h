#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include "ObjectInfo.h"

class TCadView;
// FormBar form view

class FormBar : public CFormView
{
	DECLARE_DYNCREATE(FormBar)
protected:
    std::vector<ObjectInfo*> obj_list_;
protected:
	FormBar();           // protected constructor used by dynamic creation
	virtual ~FormBar();
    void OnInitialUpdate();
    TCadView* GetTCadView();
public:
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
};


