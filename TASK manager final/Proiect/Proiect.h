// Proiect.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#include "tlhelp32.h" 
//#include "toolhelp.h"
#endif 



// CProiectApp:
// See Proiect.cpp for the implementation of this class



class CProiectApp : public CWinApp
{
public:
	CProiectApp();
	
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CProiectApp theApp;
