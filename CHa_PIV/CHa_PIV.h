// CHa_PIV.h : main header file for the CHA_PIV application
//

#if !defined(AFX_CHA_PIV_H__EDFC3487_303E_11D2_8000_00C04F7E2C13__INCLUDED_)
#define AFX_CHA_PIV_H__EDFC3487_303E_11D2_8000_00C04F7E2C13__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHa_PIVApp:
// See CHa_PIV.cpp for the implementation of this class
//

class CHa_PIVApp : public CWinApp
{
public:
	CHa_PIVApp();

// Attributes
public:

// Operations
private:

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHa_PIVApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHa_PIVApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateAppAbout(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHA_PIV_H__EDFC3487_303E_11D2_8000_00C04F7E2C13__INCLUDED_)
