
// LoaderView.h : interface of the CLoaderView class
//

#pragma once
#include "LoaderDoc.h"
#include "Plot.h"

class CLoaderView : public CView
{
protected: // create from serialization only
	CLoaderView() noexcept;
	DECLARE_DYNCREATE(CLoaderView);

// Attributes
public:
	CLoaderDoc* GetDocument() const;

	CDC dcMem; // メモリデバイスコンテキスト
	CBitmap* pOldBitmap; // ストックビットマップ
	CBitmap* pBitmap; // ビットマップ
	CPlot m_histogram;
	CWnd m_child;
	void OpenBitmapFile(CString strFileName);
	void OpenBitmapFile(CBitmap * bmp);
	void DrawHistogram();

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CLoaderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in LoaderView.cpp
inline CLoaderDoc* CLoaderView::GetDocument() const
   { return reinterpret_cast<CLoaderDoc*>(m_pDocument); }
#endif

