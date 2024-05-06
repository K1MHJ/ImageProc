#pragma once
#include <list>
#include <vector>
// CPlot
class CPlot : public CWnd
{
	typedef struct {
		float x;
		float y;
	}Item;
	DECLARE_DYNAMIC(CPlot)
	std::list<Item> m_data;
public:
	CPlot();
	virtual ~CPlot();
		
	void SetConf(float Xmin, float Xmax, float Ymin, float Ymax);
	void ClearValue();
	void SetValue(float x, float y);
	void ClearVertical();
	void AddVertical(float x);
protected:
	float max_x, min_x;
	float max_y, min_y;
	std::vector<float> m_v;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


