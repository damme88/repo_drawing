#pragma once
#include "BoxObjectDlg.h"
#include "TCadView.h"

// CdockPaneExp
class BoxObjectPanel : public CDockablePane
{
	DECLARE_DYNAMIC(BoxObjectPanel)

public:
	BoxObjectPanel();
	virtual ~BoxObjectPanel();

    void SetView(TCadView* view) { dialog_box.SetView(view); }
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nSize, int cx, int cy);
protected:
    BoxObjectDlg dialog_box;
    CButton insertBtn_;

protected:
	DECLARE_MESSAGE_MAP()
};


