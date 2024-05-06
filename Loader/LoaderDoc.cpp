
// LoaderDoc.cpp : implementation of the CLoaderDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Loader.h"
#endif
#include "LoaderView.h"
#include "LoaderDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLoaderDoc

IMPLEMENT_DYNCREATE(CLoaderDoc, CDocument)

BEGIN_MESSAGE_MAP(CLoaderDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CLoaderDoc::OnFileOpen)
END_MESSAGE_MAP()


// CLoaderDoc construction/destruction

CLoaderDoc::CLoaderDoc() noexcept
{
	// TODO: add one-time construction code here

}

CLoaderDoc::~CLoaderDoc()
{
}

BOOL CLoaderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CLoaderDoc serialization

void CLoaderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CLoaderDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CLoaderDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CLoaderDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CLoaderDoc diagnostics

#ifdef _DEBUG
void CLoaderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLoaderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLoaderDoc commands


void CLoaderDoc::OnFileOpen()
{
	// TODO: Add your command handler code here
	// ビューのポインタを取得する
	CLoaderView* pView = ((CLoaderView*)(((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView()));

	// ファイルを開くダイアログを作成する
	CFileDialog cDlg(TRUE, "png", "*.png",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"png files(*.png)|*.png||", NULL);

	// ファイルを開くダイアログのタイトルを設定する
	cDlg.m_ofn.lpstrTitle = "Open PNG File";

	// ダイアログを開く
	if (cDlg.DoModal() != IDOK) return;

	// ダイアログで指定されたファイル名を取得し、それをアプリケーションのタイトルに設定する
	SetTitle(cDlg.GetFileName());
	// ビュークラスのOpenBitmapFile関数を実行する
	pView->OpenBitmapFile(cDlg.GetPathName());
}
