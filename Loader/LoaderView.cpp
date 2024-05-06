
// LoaderView.cpp : implementation of the CLoaderView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Loader.h"
#endif

#include "LoaderDoc.h"
#include "LoaderView.h"

#include "Task.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLoaderView

IMPLEMENT_DYNCREATE(CLoaderView, CView)

BEGIN_MESSAGE_MAP(CLoaderView, CView)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CLoaderView construction/destruction

CLoaderView::CLoaderView() noexcept
{
	// TODO: add construction code here

}

CLoaderView::~CLoaderView()
{
}

BOOL CLoaderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLoaderView drawing

void CLoaderView::OnDraw(CDC* pDC)
{
	CLoaderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect cClip; // 更新領域
	int nResult; // 更新領域の取得状況

	// クリッピングを判定する
	nResult = pDC->GetClipBox(&cClip);

	// クリッピング領域が空だったり、エラーが生じたらreturn
	if (nResult == ERROR || nResult == NULLREGION) { return; }

	// メモリDCの情報を通常のDC(表画面)に転送する
	pDC->BitBlt(cClip.left, cClip.top, cClip.Width(), cClip.Height(), &dcMem, cClip.left, cClip.top, SRCCOPY);
}


// CLoaderView diagnostics

#ifdef _DEBUG
void CLoaderView::AssertValid() const
{
	CView::AssertValid();
}

void CLoaderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLoaderDoc* CLoaderView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLoaderDoc)));
	return (CLoaderDoc*)m_pDocument;
}
#endif //_DEBUG


// CLoaderView message handlers


void CLoaderView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CDC* pDC;//通常のデバイスコンテキストを格納するポインタ
	CRect cClient;//クライアント領域
	CBrush cBrush;//ブラシ
	CBrush* pOldBrush;//ブラシのストック変数

	// ビットマップオブジェクトの動的確保
	pBitmap = new CBitmap();

	// クライアント領域の取得
	GetClientRect(&cClient);

	// 現在のDCのポインタを取得
	pDC = GetDC();

	// 通常のDCとメモリDCに互換性をつける
	dcMem.CreateCompatibleDC(pDC);

	// 通常のDCの互換性のあるビットマップをメモリ上に作成
	pBitmap->CreateCompatibleBitmap(pDC, cClient.Width(), cClient.Height());

	//ビットマップとメモリDCの関連付け
	pOldBitmap = dcMem.SelectObject(pBitmap);

	//白のBrushを作成
	cBrush.CreateSolidBrush(RGB(255, 255, 255));

	//現在のbrushのポインタをpOldBrushとして残しておく
	pOldBrush = dcMem.SelectObject(&cBrush);

	// クライアント領域でbitmapをコピー
	dcMem.PatBlt(0, 0, cClient.Width(), cClient.Height(), PATCOPY);

	//昔のBrushに戻す
	dcMem.SelectObject(pOldBrush);

	//DCを解放
	ReleaseDC(pDC);

	CImage image;
	image.Load(_T("C:\\Users\\hyungjinkim\\dev\\ImageProcess\\images\\hole2.png"));
	CBitmap bmpRGB;
	BITMAP bm;
	bmpRGB.Attach(image.Detach());
	bmpRGB.GetBitmap(&bm);

	LPBYTE lpBits = new BYTE[bm.bmHeight * bm.bmWidth];
	CBitmap bmpGray;
	bmpGray.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 8, lpBits);
	BITMAP bmgray;
	bmpGray.GetBitmap(&bmgray);
	PBYTE bitgray = (PBYTE)bmgray.bmBits;
	for (long i = 0; i < bm.bmHeight * bm.bmWidth * 4; i += 4)
	{
		PBYTE bits = (PBYTE)bm.bmBits;
		BYTE gray = 
			BYTE(0.1 * bits[i + 0] + 0.6 * bits[i + 1] + 0.3 * bits[i + 2]);
		bitgray[i / 4] = gray;
	}
	CBitmap* dst_bmp;
	BITMAP* bmp;
	CTask::Filter(dst_bmp, bmpGray);
	//CTask::Filter2(dst_bmp, *dst_bmp);
	OpenBitmapFile(dst_bmp);

	m_histogram.SetConf(0, 255, 0, 1);
	m_histogram.ClearValue();
	m_histogram.SetValue(10, 0.2);
	m_histogram.SetValue(50, 0.5);
	m_histogram.ClearVertical();
	m_histogram.AddVertical(70);
}


void CLoaderView::OnDestroy()
{
	// TODO: Add your message handler code here
	// ストックしておいたビットマップを割り当てる
	dcMem.SelectObject(pOldBitmap);

	// ビットマップオブジェクトを削除する
	pBitmap->DeleteObject();

	// メモリデバイスコンテキストの削除
	dcMem.DeleteDC();

	// 正規のOnDestroyを実行する
	CView::OnDestroy();
}
void CLoaderView::OpenBitmapFile(CString strFileName)
{
	//BITMAP bmp; // ビットマップ構造体
	//HBITMAP hBmp; // ビットマップハンドル
	CRect cClient; // クライアント領域

	// クライアント領域を得る
	GetClientRect(&cClient);

	CImage image;
	image.Load(strFileName);

	//// ビットマップのハンドル取得
	// メモリDCに割り当てられているビットマップを外す
	dcMem.SelectObject(pOldBitmap);

	// 先ほどまで割り当てられていたビットマップの情報を消去
	pBitmap->DeleteObject();

	// ビットマップハンドルからCBitmapのポインタを取得
	//pBitmap = (CBitmap*)CBitmap::FromHandle(hBmp);
	pBitmap->Attach(image.Detach());

	// ビットマップ゜をメモリDCに割り当て
	pOldBitmap = dcMem.SelectObject(pBitmap);

	//更新処理
	InvalidateRect(&cClient);
}
void CLoaderView::OpenBitmapFile(CBitmap* bmp)
{
	CRect cClient; // クライアント領域

	// クライアント領域を得る
	GetClientRect(&cClient);

	//// ビットマップのハンドル取得
	// メモリDCに割り当てられているビットマップを外す
	dcMem.SelectObject(pOldBitmap);

	// 先ほどまで割り当てられていたビットマップの情報を消去
	pBitmap->DeleteObject();

	// ビットマップハンドルからCBitmapのポインタを取得
	//pBitmap = (CBitmap*)CBitmap::FromHandle(hBmp);
	pBitmap->Attach(bmp->Detach());

	// ビットマップ゜をメモリDCに割り当て
	pOldBitmap = dcMem.SelectObject(pBitmap);
	//更新処理
	InvalidateRect(&cClient);
}
void CLoaderView::DrawHistogram()
{
	CRect cClient; // クライアント領域
	GetClientRect(&cClient);

	pOldBitmap = dcMem.SelectObject(pBitmap);
	InvalidateRect(&cClient);
}


int CLoaderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  Add your specialized creation code here
	m_histogram.Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, lpCreateStruct->cy/2, lpCreateStruct->cx , lpCreateStruct->cy/2),
		this, 0);
	return 0;
}


void CLoaderView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_histogram.MoveWindow(0, cy/2, cx, cy/2);
}
