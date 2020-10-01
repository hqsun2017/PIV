// MyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CHa_PIV.h"
#include "MyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridSel dialog


CGridSel::CGridSel(CWnd* pParent /*=NULL*/)
	: CDialog(CGridSel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGridSel)
	m_nSizeX = 16;
	m_nSizeY = 16;
	m_nStepX = 0;
	m_nStepY = 0;
	m_dfAmp = 0.0;
	m_bWindowed = FALSE;
	//}}AFX_DATA_INIT
}


void CGridSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridSel)
	DDX_Text(pDX, IDC_ED_SIZEX, m_nSizeX);
	DDX_Text(pDX, IDC_ED_SIZEY, m_nSizeY);
	DDX_Text(pDX, IDC_ED_STEPX, m_nStepX);
	DDX_Text(pDX, IDC_ED_STEPY, m_nStepY);
	DDX_Text(pDX, IDC_ED_AMPLIFIER, m_dfAmp);
	DDX_Check(pDX, IDC_CHECK_WINDOWED, m_bWindowed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGridSel, CDialog)
	//{{AFX_MSG_MAP(CGridSel)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridSel message handlers
