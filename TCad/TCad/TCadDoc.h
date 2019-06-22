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

// TCadDoc.h : interface of the TCadDoc class
//


#pragma once
#include "DataList.h"
#include "EntityObject.h"

class TCadDoc : public CDocument
{
protected: // create from serialization only
	TCadDoc();
	DECLARE_DYNCREATE(TCadDoc)

// Attributes
public:
    void FreeSelected();
    void SetSelected(int idx);
    void RenderEntity(GLenum mode);
    void AppendEntity(EntityObject* entity);
    bool HasObject();
    long GetNumberObject();
    int FindIdxObject(const Vector3D& ppVector, const POINT3D& gl_pt);
    EntityObject* FindEntity(int idx);
    void DeleteObject();
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~TCadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    DataList<EntityObject*> data_list_;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
