// SatrancH.h : main header file for the SatrancH application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CSatrancHApp:
// See SatrancH.cpp for the implementation of this class
//

class CSatrancHApp : public CWinApp
{
public:
	CSatrancHApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSatrancHApp theApp;