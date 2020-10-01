#if !defined(AFX_PIVTHREAD_H__CF6F5D5C_5043_11D4_BD02_C069405E8F79__INCLUDED_)
#define AFX_PIVTHREAD_H__CF6F5D5C_5043_11D4_BD02_C069405E8F79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PivThread.h : header file
//

#include "Vector.h"

/////////////////////////////////////////////////////////////////////////////
// CPivThread thread

class CPivThread : public CWinThread
{
	DECLARE_DYNAMIC(CPivThread)

public:
	CPivThread(CWnd* pWnd);

// Attributes
private:
	HANDLE m_hEventKill;
	VecDatum vecdatum;

// Operations
private:
	void DrawVector();
	void FindPeak();
	void Correlation();
	void CorrAndCorr();

public:
	void KillThread();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPivThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
//protected:
public:
	virtual ~CPivThread();

protected:
	// Generated message map functions
	//{{AFX_MSG(CPivThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIVTHREAD_H__CF6F5D5C_5043_11D4_BD02_C069405E8F79__INCLUDED_)
