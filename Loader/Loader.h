
// Loader.h : main header file for the Loader application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLoaderApp:
// See Loader.cpp for the implementation of this class
//

class CLoaderApp : public CWinApp
{
public:
	CLoaderApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLoaderApp theApp;
