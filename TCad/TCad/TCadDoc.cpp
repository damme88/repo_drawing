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

// TCadDoc.cpp : implementation of the TCadDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TCad.h"
#endif

#include "TCadDoc.h"
#include "TLine.h"
#include "TCircle.h"
#include "TPoint.h"
#include "TRectangle.h"
#include "TPolyLine.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// TCadDoc

IMPLEMENT_DYNCREATE(TCadDoc, CDocument)

BEGIN_MESSAGE_MAP(TCadDoc, CDocument)
    ON_COMMAND(ID_FILE_SAVE, &TCadDoc::OnFileSave)
    ON_COMMAND(ID_FILE_SAVE_AS, &TCadDoc::OnFileSaveAs)
END_MESSAGE_MAP()


// TCadDoc construction/destruction

TCadDoc::TCadDoc()
{
	// TODO: add one-time construction code here
    on_undo_ = false;
    on_redo_ = false;
    undo_limit_ = 0;
}

TCadDoc::~TCadDoc()
{
}

BOOL TCadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}

void TCadDoc::AppendEntity(EntityObject* entity)
{
    if (entity != NULL)
    {
        data_list_.InsertBack(entity);

        if (on_undo_ == false) on_undo_ = true;
    }
}

void TCadDoc::DeleteObject()
{
    DataNote<EntityObject*>* temp = data_list_.head();
    while (temp != NULL)
    {
        bool is_select = temp->get_data()->get_selected();
        if (is_select)
        {
            DataNote<EntityObject*>* next = temp->get_next();
            data_list_.RemoveObject(temp);
            temp = next;
            continue;
        }
        temp = temp->get_next();
    }
}

void TCadDoc::FreeSelected()
{
    DataNote<EntityObject*>* temp = data_list_.head();
    while (temp != NULL)
    {
        bool is_select = temp->get_data()->get_selected();
        if (is_select)
        {
            temp->get_data()->set_selected(false);
        }
        temp = temp->get_next();
    }
}

void TCadDoc::SetSelected(int idx)
{
   UINT ix = 0;
   DataNote<EntityObject*>* temp = data_list_.head();
   while (temp != NULL)
   {
       if (ix == idx)
       {
           EntityObject* pObject = temp->get_data();
           if (pObject != NULL)
           {
               bool is_select = pObject->get_selected();
               pObject->set_selected(!is_select);

               //Call gript point
               pObject->DoGripPoint();
               break;
           }
           
       }
       temp = temp->get_next();
       ix++;
   }
}

EntityObject* TCadDoc::ImplementGripPoint(const POINT3D& pt)
{
    DataNote<EntityObject*>* temp = data_list_.head();
    while (temp != NULL)
    {
        EntityObject* pObject = temp->get_data();
        if (pObject != NULL)
        {
            bool is_select = pObject->get_selected();
            if (is_select == true)
            {
                pObject->GetGripPoint(pt);
                if (pObject->get_on_grip() == true)
                {
                    break;
                }
            }
        }
        temp = temp->get_next();
    }
    if (temp != NULL)
    {
        return temp->get_data();
    }
    return NULL;
}

EntityObject* TCadDoc::FindEntity(int idx)
{
    UINT ix = 0;
    EntityObject* pEnt = NULL;
    DataNote<EntityObject*>* temp = data_list_.head();
    while (temp != NULL)
    {
        if (ix == idx)
        {
            pEnt = temp->get_data();
            break;
        }
        temp = temp->get_next();
        ix++;
    }

    return pEnt;
}

void TCadDoc::RenderEntity(GLenum mode)
{
    DataNote<EntityObject*>* temp = data_list_.head();
    while (temp != NULL)
    {
        temp->get_data()->Render();
        temp = temp->get_next();
    }
}

bool TCadDoc::HasObject()
{
    int number = GetNumberObject();

    return (number > 0 ? true : false);
}

long TCadDoc::GetNumberObject()
{
    long count = 0;
    DataNote<EntityObject*>* temp = data_list_.head();
    while (temp != NULL)
    {
        temp = temp->get_next();
        count++;
    }
    return count;
}

int TCadDoc::FindIdxObject(const Vector3D& ppVector, const POINT3D& gl_pt)
{
    int idx = 0; 
    int indexFound = -1;
    bool has_point = false;
    POINT3D intersectWithPt(0.0, 0.0, 0.0);
    DataNote<EntityObject*>* pObject = data_list_.head();
    while (pObject != NULL)
    {
        if (pObject->get_data()->get_etype() == EntityObject::OBJ_3D)
        {
            POINT3D retPt(0, 0, 0);
            bool is_select = pObject->get_data()->IsSelectedObject(ppVector, gl_pt, retPt);
            if (is_select)
            {
                if (!has_point)
                {
                    //Neu chua tim dc giao diem nao thi gan giao diem = retpt
                    intersectWithPt = retPt;
                    has_point = true;
                    indexFound = idx;
                }
                else
                {
                    //Neu da tim dc giao diem roi. Nhung giao diem do la object nam o vi tri sau.
                    // No tim dc truoc vi tuy nam sau nhung chi so idx no lai nam trc
                    // Kiem tra giao diem da co voi giao diem vua tim dc => 1 vector
                    // neu vector nay nguoc chieu voi vector vuong goc screen.
                    // => lay retPt( de  uu tien lua chon object o phia truoc)
                    Vector3D u = intersectWithPt - retPt;
                    if (u.scalar(ppVector) < 0)
                    {
                        intersectWithPt = retPt;
                        indexFound = idx;
                    }
                }

            }
        }
        else if (pObject->get_data()->get_etype() == EntityObject::OBJ_2D)
        {
            POINT3D retPt(0, 0, 0);
            bool is_select = pObject->get_data()->IsSelectedObject(ppVector, gl_pt, retPt);
            if (is_select)
            {
                indexFound = idx;
            }
        }
        
        pObject = pObject->get_next();
        idx++;
    }

#ifdef SHOW_LINE_INTERSECTH
    VEC3D vDir = ppVector;
    vDir = vDir * 1000;
    POINT3D p1 = intersectWithPt + vDir;

    TLine* new_line = new TLine(intersectWithPt, p1);
    new_line->set_color(VEC3D(1.0, 1.0, 1.0));
    new_line->set_etype(Object2D::LINE);
    new_line->set_type(EntityObject::OBJ_2D);
    //new_line->set_pos_cam(p_cameral_.get_pos_cam());
    AppendEntity(new_line);
#endif
    return indexFound;
}

// TCadDoc serialization

void TCadDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
        int nCount = GetNumberObject();
        ar << nCount;
        DataNote<EntityObject*>* temp = data_list_.head();
        while (temp != NULL)
        {
            EntityObject* pEntity = temp->get_data();
            if (pEntity->get_etype() == EntityObject::OBJ_2D)
            {
                Object2D* pObj2d = static_cast<Object2D*>(pEntity);
                int type = pObj2d->get_type();
                ar << type;
            }
            pEntity->Serialize(ar);
            temp = temp->get_next();
        }
	}
	else
	{
        int nCount = 0;
        ar >> nCount;

        for (int i = 0; i < nCount; i++)
        {
            int nType = 0;
            ar >> nType;
            EntityObject* pEntity = NULL;
            if (nType == Object2D::POINT)
            {
                pEntity = new TPoint();
            }
            else if (nType == Object2D::LINE)
            {
                pEntity = new TLine();
            }
            else if (nType == Object2D::CIRCLE)
            {
                pEntity = new TCircle();
            }
            else if (nType == Object2D::POLY_LINE)
            {
                pEntity = new TPolyLine();
            }
            else if (nType == Object2D::RECTANGLE)
            {
                pEntity = new TRectangle();
            }

            if (pEntity != NULL)
            {
                pEntity->Serialize(ar);
                AppendEntity(pEntity);
            }
        }
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void TCadDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void TCadDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void TCadDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// TCadDoc diagnostics

#ifdef _DEBUG
void TCadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void TCadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void TCadDoc::UndoData()
{
    DataNote<EntityObject*>* pNodeEnd = data_list_.GetLast();
    if (pNodeEnd != NULL)
    {
        EntityObject* pObjEnd = pNodeEnd->get_data();
        if (pObjEnd != NULL)
        {
            if (undo_limit_ < 10)
            {
                undo_limit_++;
                EntityObject* clone_obj = pObjEnd->Clone();
                data_stack_.push(clone_obj);
                data_list_.RemoveEnd();

                if (on_redo_ == false) on_redo_ = true;
                if (HasObject() == false)
                {
                    on_undo_ = false;
                }
            }
            else
            {
                on_undo_ = false;
            }
        }
    }
}

void TCadDoc::RedoData()
{
    NodeData<EntityObject*>* nodeData = data_stack_.GetLast();
    if (nodeData != NULL)
    {
        EntityObject* redoObj = nodeData->get_data();
        if (redoObj)
        {
            EntityObject* clone_obj = redoObj->Clone();
            if (clone_obj != NULL)
            {
                AppendEntity(clone_obj);
                delete redoObj;
                redoObj = NULL;
                data_stack_.pop();

                if (data_stack_.head() == NULL)
                {
                    on_redo_ = false;
                }
            }
        }
    }
}

// TCadDoc commands
void TCadDoc::OnFileSave()
{
    CString doc_name_str = this->GetPathName();
    bool is_exist = CheckExistPath(doc_name_str);
    if (is_exist)
    {
        CDocument::DoSave(doc_name_str);
    }
    else
    {
        OnFileSaveAs();
    }
}

void TCadDoc::OnFileSaveAs()
{
    char strFilter[] = { "Text Files (*.tcd)|*.tcd|" };
    CFileDialog FileDlg(FALSE, CString(".tcd"), NULL, 0, CString(strFilter));
    if (FileDlg.DoModal() == IDOK)
    {
        CString strName = FileDlg.GetFileName(); //filename
        CString strPath = FileDlg.GetFolderPath(); //filepath (folders)
        strPath += (_T("\\")) + strName;
        CDocument::DoSave(strPath);
    }
}

bool TCadDoc::CheckExistPath(CString path)
{
    CFile fil;
    if (fil.Open(path, CFile::modeRead | CFile::shareDenyNone))
    {
        fil.Close();
        return true;
    }
    return false;
}