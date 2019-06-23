#pragma once
#include "TCadView.h"
#include "TBox.h"
// CylinderObjectDlg dialog

class CylinderObjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CylinderObjectDlg)

public:
	CylinderObjectDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CylinderObjectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CYLINDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
