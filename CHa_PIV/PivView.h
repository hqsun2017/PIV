// PivView.h : interface of the CPivView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIVVIEW_H__EDFC348F_303E_11D2_8000_00C04F7E2C13__INCLUDED_)
#define AFX_PIVVIEW_H__EDFC348F_303E_11D2_8000_00C04F7E2C13__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPivView : public CView
{
protected: // create from serialization only
	CPivView();
	DECLARE_DYNCREATE(CPivView)

// Attributes
private:
	HENHMETAFILE hMeta;
	LARGE_INTEGER litmp;
	LONGLONG QPart,QPart1,QPart2;
	double dfreq,dfratioxy,dfinterval;

public:
	CPivDoc* GetDocument();

// Operations
private:
	void ThreadCtrl(int ntmp);
	bool IsPowerOf2(int n);

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPivView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPivView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPivView)
	afx_msg LONG OnFinished(UINT wParam,LONG lParam);
	afx_msg void OnBmpRead1();
	afx_msg void OnBmpRead2();
	afx_msg void OnCCFFT();
	afx_msg void OnPCFFT();
	afx_msg void OnCCFHT();
	afx_msg void OnPause();
	afx_msg void OnBmpShow1();
	afx_msg void OnBmpShow2();
	afx_msg void OnStop();
	afx_msg void OnGridSel();
	afx_msg void OnVecRead();
	afx_msg void OnVecSave();
	afx_msg void OnVecShow();
	afx_msg void OnUpdateBmpRead1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBmpRead2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBmpShow1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBmpShow2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCCFFT(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePCFFT(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCCFHT(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGridsel(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVecRead(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVecSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVecShow(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PivView.cpp
inline CPivDoc* CPivView::GetDocument()
   { return (CPivDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIVVIEW_H__EDFC348F_303E_11D2_8000_00C04F7E2C13__INCLUDED_)
