// PivDoc.h : interface of the CPivDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIVDOC_H__EDFC348D_303E_11D2_8000_00C04F7E2C13__INCLUDED_)
#define AFX_PIVDOC_H__EDFC348D_303E_11D2_8000_00C04F7E2C13__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CPivDoc : public CDocument
{
protected: // create from serialization only
	CPivDoc();
	DECLARE_DYNCREATE(CPivDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPivDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPivDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPivDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIVDOC_H__EDFC348D_303E_11D2_8000_00C04F7E2C13__INCLUDED_)
