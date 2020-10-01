#if !defined(AFX_MYDLG_H__00DA8821_311D_11D2_8000_00C04F7E2C13__INCLUDED_)
#define AFX_MYDLG_H__00DA8821_311D_11D2_8000_00C04F7E2C13__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// mydlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGridSel dialog

class CGridSel : public CDialog
{
// Construction
public:
	CGridSel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGridSel)
	enum { IDD = IDD_GRIDSEL };
	UINT	m_nSizeX;
	UINT	m_nSizeY;
	UINT	m_nStepX;
	UINT	m_nStepY;
	double	m_dfAmp;
	BOOL	m_bWindowed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridSel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGridSel)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLG_H__00DA8821_311D_11D2_8000_00C04F7E2C13__INCLUDED_)
