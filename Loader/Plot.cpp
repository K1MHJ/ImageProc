// Plot.cpp : implementation file
//

#include "pch.h"
#include "Loader.h"
#include "Plot.h"


// CPlot

IMPLEMENT_DYNAMIC(CPlot, CWnd)

CPlot::CPlot()
{
	max_x = 100;
	min_x = 0;
	max_y = 1;
	min_y = 0;
}

CPlot::~CPlot()
{
}


BEGIN_MESSAGE_MAP(CPlot, CWnd)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CPlot message handlers
void CPlot::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnClose();
}


int CPlot::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CDC* dc = GetDC();

	ReleaseDC(dc);
	return 0;
}


void CPlot::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
}


BOOL CPlot::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	cs.dwExStyle |= WS_EX_TRANSPARENT;
	return CWnd::PreCreateWindow(cs);
}


BOOL CPlot::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CWnd::OnEraseBkgnd(pDC);
}
void CPlot::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	CRect cClip;
	int nResult; // 更新領域の取得状況
	nResult = dc.GetClipBox(&cClip);
	if (nResult == ERROR || nResult == NULLREGION) { return; }

	CPen* oldPen, curPen;
	CBrush* oldBrush, curBrush;
	curPen.CreatePen(BS_SOLID, 2, RGB(255, 0, 0));
	oldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
	oldPen = dc.SelectObject(&curPen);

	dc.Rectangle(cClip);
	int n = 0;
	for (auto i : m_data) {
		int nx = cClip.Width() / (max_x - min_x) * (i.x - min_x);
		int ny = cClip.Height() - cClip.Height() / (max_y - min_y) * (i.y - min_y);
		if (n == 0) {
			dc.MoveTo(nx, ny); n++;
		}
		else {
			dc.LineTo(nx, ny);
		}
	}
	for (auto i : m_v) {
		int nx = cClip.Width() / (max_x - min_x) * (i - min_x);
		dc.MoveTo(nx, 0);
		dc.LineTo(nx, cClip.Height());
	}
	dc.SelectObject(oldBrush);
	dc.SelectObject(oldPen);
}


BOOL CPlot::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


HBRUSH CPlot::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CPlot::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	Invalidate();
}

void CPlot::SetConf(float Xmin, float Xmax, float Ymin, float Ymax)
{
	max_x = Xmax;
	min_x = Xmin;
	max_y = Ymax;
	min_y = Ymin;
}
void CPlot::ClearValue()
{
	m_data.clear();
}
void CPlot::SetValue(float x, float y)
{
	m_data.push_back(Item{ x, y });
	m_data.sort([](const Item& numA, const Item& numB) {
		return (numA.x > numB.x);
		}
	);
}
void CPlot::ClearVertical()
{
	m_v.clear();
}
void CPlot::AddVertical(float x)
{
	m_v.push_back(x);
}
