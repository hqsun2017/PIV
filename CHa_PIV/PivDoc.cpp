// PivDoc.cpp : implementation of the CPivDoc class
//

#include "stdafx.h"
#include "CHa_PIV.h"

#include "PivDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPivDoc

IMPLEMENT_DYNCREATE(CPivDoc, CDocument)

BEGIN_MESSAGE_MAP(CPivDoc, CDocument)
	//{{AFX_MSG_MAP(CPivDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPivDoc construction/destruction

CPivDoc::CPivDoc()
{
	// TODO: add one-time construction code here

}

CPivDoc::~CPivDoc()
{
}

BOOL CPivDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPivDoc serialization

void CPivDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPivDoc diagnostics

#ifdef _DEBUG
void CPivDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPivDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPivDoc commands
