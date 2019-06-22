#pragma once
#include "BoxObjectDlg.h"
#include "CylinderObjectDlg.h"
#include "TCadView.h"

// CdockPaneExp
class BoxObjectPanel : public CDockablePane
{
	DECLARE_DYNAMIC(BoxObjectPanel)

public:
	BoxObjectPanel();
	virtual ~BoxObjectPanel();

    void SetView(TCadView* view) { dialog_box.SetView(view); }
    void SetType(int type) { dialog_box.setType(type); }
    void FillData(TBox* pBox, int idx);
    void InitDlgVal() { dialog_box.ResetValue(); };
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nSize, int cx, int cy);
protected:
    BoxObjectDlg dialog_box;
    CButton insertBtn_;

protected:
	DECLARE_MESSAGE_MAP()
};


