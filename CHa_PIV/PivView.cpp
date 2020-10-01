// PivView.cpp : implementation of the CPivView class
//

#include "stdafx.h"
#include "CHa_PIV.h"

#include "PivDoc.h"
#include "PivView.h"
#include <math.h>

#include "PivThread.h"
#include "Globe.h"
#include "tFunc.h"
#include "MyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

#define COLOR_FILL  RGB(0,255,0)

/////////////////////////////////////////////////////////////////////////////
// CPivView

IMPLEMENT_DYNCREATE(CPivView, CView)

BEGIN_MESSAGE_MAP(CPivView, CView)
	//{{AFX_MSG_MAP(CPivView)
	ON_MESSAGE(WM_FINISHED,OnFinished)
	ON_COMMAND(ID_BMP_READ1, OnBmpRead1)
	ON_COMMAND(ID_BMP_READ2, OnBmpRead2)
	ON_COMMAND(ID_APP_CC_FFT, OnCCFFT)
	ON_COMMAND(ID_APP_CC_FHT, OnCCFHT)
	ON_COMMAND(ID_APP_PAUSE, OnPause)
	ON_COMMAND(ID_BMP_SHOW1, OnBmpShow1)
	ON_COMMAND(ID_BMP_SHOW2, OnBmpShow2)
	ON_COMMAND(ID_APP_STOP, OnStop)
	ON_COMMAND(ID_APP_GRIDSEL, OnGridSel)
	ON_COMMAND(ID_VEC_READ, OnVecRead)
	ON_COMMAND(ID_VEC_SAVE, OnVecSave)
	ON_COMMAND(ID_VEC_SHOW, OnVecShow)
	ON_UPDATE_COMMAND_UI(ID_BMP_READ1, OnUpdateBmpRead1)
	ON_UPDATE_COMMAND_UI(ID_BMP_READ2, OnUpdateBmpRead2)
	ON_UPDATE_COMMAND_UI(ID_BMP_SHOW1, OnUpdateBmpShow1)
	ON_UPDATE_COMMAND_UI(ID_BMP_SHOW2, OnUpdateBmpShow2)
	ON_UPDATE_COMMAND_UI(ID_APP_CC_FFT, OnUpdateCCFFT)
	ON_UPDATE_COMMAND_UI(ID_APP_GRIDSEL, OnUpdateGridsel)
	ON_UPDATE_COMMAND_UI(ID_APP_PAUSE, OnUpdatePause)
	ON_UPDATE_COMMAND_UI(ID_APP_STOP, OnUpdateStop)
	ON_UPDATE_COMMAND_UI(ID_VEC_READ, OnUpdateVecRead)
	ON_UPDATE_COMMAND_UI(ID_VEC_SAVE, OnUpdateVecSave)
	ON_UPDATE_COMMAND_UI(ID_VEC_SHOW, OnUpdateVecShow)
	ON_UPDATE_COMMAND_UI(ID_APP_CC_FHT, OnUpdateCCFHT)
	ON_COMMAND(ID_APP_PC_FFT, OnPCFFT)
	ON_UPDATE_COMMAND_UI(ID_APP_PC_FFT, OnUpdatePCFFT)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPivView construction/destruction

CPivView::CPivView()
{
	// TODO: add construction code here
	hMeta=NULL; g_nStateRun=0; g_bShowCtrl=SHOWNONE;
	dfratioxy=1.0; dfinterval=0.4;
	g_fr0=new double[(g_vgSet.nGridSizeX)*(g_vgSet.nGridSizeY)];
	g_fr1=new double[(g_vgSet.nGridSizeX)*(g_vgSet.nGridSizeY)];
	g_frc=new double[(g_vgSet.nGridSizeX)*(g_vgSet.nGridSizeY)];
	g_fHanningX=new double[g_vgSet.nGridSizeX];
	g_fHanningY=new double[g_vgSet.nGridSizeY];
}

CPivView::~CPivView()
{
	if(hMeta!=NULL) DeleteEnhMetaFile(hMeta);
	if(g_fr0!=NULL) delete[] g_fr0;
	if(g_fr1!=NULL) delete[] g_fr1;
	if(g_frc!=NULL) delete[] g_frc;
	if(g_fHanningX!=NULL) delete[] g_fHanningX;
	if(g_fHanningY!=NULL) delete[] g_fHanningY;
}

BOOL CPivView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPivView drawing

void CPivView::OnDraw(CDC* pDC)
{
	CPivDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	int norgx,norgy;
	CRect rect;
	GetClientRect(&rect);
	if(g_pThread!=NULL)
	{
		g_pThread->SuspendThread();
		g_vect.DrawVec(pDC,rect.Width(),rect.Height(),g_nVecTot);
		g_pThread->ResumeThread();
	}
	if((g_bShowCtrl&SHOWBMP1)!=SHOWNONE)
	{
		norgx=(rect.Width()-g_bmp1.GetWidth())/2;
		if(norgx<0) norgx=0;
		norgy=(rect.Height()-g_bmp1.GetHeight())/2;
		if(norgy<0) norgy=0;
		g_bmp1.DrawDIB(pDC,norgx,norgy);
	}
	if((g_bShowCtrl&SHOWBMP2)!=SHOWNONE)
	{
		norgx=(rect.Width()-g_bmp2.GetWidth())/2;
		if(norgx<0) norgx=0;
		norgy=(rect.Height()-g_bmp2.GetHeight())/2;
		if(norgy<0) norgy=0;
		g_bmp2.DrawDIB(pDC,norgx,norgy);
	}
	if((g_bShowCtrl&SHOWVEC)!=SHOWNONE) g_vect.DrawVec(pDC,rect.Width(),rect.Height());
}

/////////////////////////////////////////////////////////////////////////////
// CPivView printing

BOOL CPivView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPivView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPivView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPivView diagnostics

#ifdef _DEBUG
void CPivView::AssertValid() const
{
	CView::AssertValid();
}

void CPivView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPivDoc* CPivView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPivDoc)));
	return (CPivDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPivView message handlers

LONG CPivView::OnFinished(UINT wParam,LONG lParam) 
{
	if(g_pThread!=NULL)
	{
		g_pThread->KillThread();
		g_pThread=NULL;
	}

	g_vect.SetFlag(TRUE);
	g_nStateRun=0;
	g_bShowCtrl=SHOWVEC;
	////////////////////////////////////
	QueryPerformanceCounter(&litmp);
	QPart2=litmp.QuadPart;
	double dftime=(double)(QPart2-QPart1-QPart)/dfreq;
	CString strout;
	strout.Format("Number=%d,Time=%f",g_nVecTot,dftime);
	MessageBox(strout);
	////////////////////////////////////

	return 0L;
}

void CPivView::OnBmpRead1() 
{
	// TODO: Add your command handler code here
	CString strFil;

	CFileDialog fdlg(TRUE,"bmp",NULL,OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_ENABLEHOOK | OFN_OVERWRITEPROMPT
		| OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,"bitmap(*.bmp)|*.bmp|All files(*.*)|*.*|",AfxGetApp()->m_pMainWnd);
	
	if(fdlg.DoModal()==IDOK) strFil=fdlg.GetPathName();
	else return;

	g_bmp1.Load(strFil);
	g_bmp1.SortGreyLevel();
	g_bPicOk1=TRUE;
}

void CPivView::OnBmpRead2() 
{
	// TODO: Add your command handler code here
	CString strFil;

	CFileDialog fdlg(TRUE,"bmp",NULL,OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_ENABLEHOOK | OFN_OVERWRITEPROMPT
		| OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,"bitmap(*.bmp)|*.bmp|All files(*.*)|*.*|",AfxGetApp()->m_pMainWnd);
	
	if(fdlg.DoModal()==IDOK) strFil=fdlg.GetPathName();
	else return;

	g_bmp2.Load(strFil);
	g_bmp2.SortGreyLevel();
	g_bPicOk2=TRUE;
}

void CPivView::ThreadCtrl(int ntmp)
{
	if(0==g_nStateRun)
	{
		if(g_bmp1!=g_bmp2) {MessageBox("Pictures are unequal!"); return;}

		g_vect.ImplementVec(g_vgSet,g_bmp1.GetWidth(),g_bmp1.GetHeight());
		g_vect.GetInfoHead(g_vecinfo);
		g_nVecXSeq=0; g_nVecYSeq=0; g_nVecTot=0;

		g_pThread=new CPivThread(this);

		if(NULL==g_pThread) {MessageBox("Can't creat a thread!"); return;}

		ASSERT_VALID(g_pThread);
		g_pThread->m_pThreadParams=NULL;
		if(!g_pThread->CreateThread(CREATE_SUSPENDED)) {delete g_pThread; return;}
		VERIFY(g_pThread->SetThreadPriority(THREAD_PRIORITY_IDLE));
		////////////////////////////////////
		QueryPerformanceFrequency(&litmp);
		dfreq=(double)litmp.QuadPart;

		QueryPerformanceCounter(&litmp); QPart1=litmp.QuadPart;
		QueryPerformanceCounter(&litmp); QPart2=litmp.QuadPart;
		QPart=QPart2-QPart1;

		QueryPerformanceCounter(&litmp); QPart1=litmp.QuadPart;
		////////////////////////////////////
		g_nStateRun=1; g_nKernel=ntmp;
		g_pThread->ResumeThread();
	}
	else ResumeThread(g_pThread->m_hThread);
}

void CPivView::OnCCFFT() 
{
	// TODO: Add your command handler code here
	ThreadCtrl(0);
}

void CPivView::OnPCFFT() 
{
	// TODO: Add your command handler code here
	ThreadCtrl(1);
}

bool CPivView::IsPowerOf2(int n)
{
	int bits=0;
	while(n) {bits+=n&1; n>>=1;}
	return (1==bits);
}

void CPivView::OnCCFHT() 
{
	// TODO: Add your command handler code here
	if(!IsPowerOf2(g_vgSet.nGridSizeX) || !IsPowerOf2(g_vgSet.nGridSizeY))
	{
		MessageBox("The size for FHT must be power of 2!");
		return;
	}

	ThreadCtrl(2);
}

void CPivView::OnPause() 
{
	// TODO: Add your command handler code here
	if(1==g_nStateRun) SuspendThread(g_pThread->m_hThread);
}

void CPivView::OnBmpShow1() 
{
	// TODO: Add your command handler code here
	g_bShowCtrl=SHOWBMP1;
	Invalidate();
}

void CPivView::OnBmpShow2() 
{
	// TODO: Add your command handler code here
	g_bShowCtrl=SHOWBMP2;
	Invalidate();
}

void CPivView::OnStop() 
{
	// TODO: Add your command handler code here
	if(1==g_nStateRun)
	{
		DWORD dwExitCode;
		GetExitCodeThread(g_pThread->m_hThread,&dwExitCode);
		if(g_pThread->m_hThread!=NULL)
		{
			TerminateThread(g_pThread->m_hThread,dwExitCode);
			delete g_pThread;
			g_pThread=0; g_nStateRun=0;
		}
	}
}

void CPivView::OnGridSel() 
{
	// TODO: Add your command handler code here
	g_vect.GetVectGrid(g_vgSet);

	CGridSel dlg;

	dlg.m_nSizeX=g_vgSet.nGridSizeX;
	dlg.m_nSizeY=g_vgSet.nGridSizeY;
	dlg.m_nStepX=g_vgSet.nGridStepX;
	dlg.m_nStepY=g_vgSet.nGridStepY;
	dlg.m_dfAmp=g_vgSet.dfAmp;
	dlg.m_bWindowed=g_bWindowed;
	if(dlg.DoModal()==IDOK)
	{
		//free the space for complex matrix
		if(g_fr0!=NULL) delete[] g_fr0;
		if(g_fr1!=NULL) delete[] g_fr1;
		if(g_frc!=NULL) delete[] g_frc;
		if(g_fHanningX!=NULL) delete[] g_fHanningX;
		if(g_fHanningY!=NULL) delete[] g_fHanningY;

		//setup size and step of grid
		g_vgSet.nGridSizeX=dlg.m_nSizeX;
		g_vgSet.nGridSizeY=dlg.m_nSizeY;
		g_vgSet.nGridStepX=dlg.m_nStepX;
		g_vgSet.nGridStepY=dlg.m_nStepY;
		g_vgSet.dfAmp=dlg.m_dfAmp;
		g_bWindowed=dlg.m_bWindowed;
		g_vect.SetAmplifer(g_vgSet.dfAmp);

		//Alloc the space for complex matrix
		g_fr0=new double[(g_vgSet.nGridSizeX)*(g_vgSet.nGridSizeY)];
		g_fr1=new double[(g_vgSet.nGridSizeX)*(g_vgSet.nGridSizeY)];
		g_frc=new double[(g_vgSet.nGridSizeX)*(g_vgSet.nGridSizeY)];
		g_fHanningX=new double[g_vgSet.nGridSizeX];
		g_fHanningY=new double[g_vgSet.nGridSizeY];
		Hanning(g_vgSet.nGridSizeX,g_fHanningX);
		Hanning(g_vgSet.nGridSizeY,g_fHanningY);
	}
}

void CPivView::OnVecRead() 
{
	// TODO: Add your command handler code here	
	CString strFil;

	CFileDialog fdlg(TRUE,"vec",NULL,OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_ENABLEHOOK | OFN_OVERWRITEPROMPT
		| OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,"vecmap(*.vec)|*.vec|All files(*.*)|*.*|",AfxGetApp()->m_pMainWnd);

	if(fdlg.DoModal()==IDOK) strFil=fdlg.GetPathName();
	else return;

	g_vect.Load(strFil);
	if(g_vect.GetFlag()!=TRUE) MessageBox("There are some errors in opening file");
}

void CPivView::OnVecSave() 
{
	// TODO: Add your command handler code here
	CString strfil,strext;

	CFileDialog fdlg(FALSE,"VEC",NULL,OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_ENABLEHOOK | OFN_OVERWRITEPROMPT
		| OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,"bin(*.vec)|*.vec|Metafile(*.wmf)|*.wmf|",AfxGetApp()->m_pMainWnd);

	if(fdlg.DoModal()==IDOK)
	{
		strfil=fdlg.GetPathName();
		strext=fdlg.GetFileExt(); strext.MakeLower();
	}
	else return;

	if("vec"==strext) g_vect.Save(strfil);
	if("wmf"==strext)
	{
		if(hMeta!=NULL) DeleteEnhMetaFile(hMeta);
		CMetaFileDC Meta;
		Meta.CreateEnhanced(NULL,strfil,NULL,NULL);
		//Meta.SetBkMode(TRANSPARENT); Meta.SetMapMode(MM_TEXT);
		g_vect.DrawVec(&Meta);
		hMeta=Meta.CloseEnhanced();

		if(OpenClipboard())
		{
			EmptyClipboard();
			SetClipboardData(CF_ENHMETAFILE,hMeta); //place it on the clipboard
			CloseClipboard();
		}
	}
}

void CPivView::OnVecShow() 
{
	// TODO: Add your command handler code here	
	g_bShowCtrl|=SHOWVEC;
	Invalidate();
}

void CPivView::OnUpdateBmpRead1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(1!=g_nStateRun);
}

void CPivView::OnUpdateBmpRead2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(1!=g_nStateRun);
}

void CPivView::OnUpdateBmpShow1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((1!=g_nStateRun)&&(TRUE==g_bPicOk1));
}

void CPivView::OnUpdateBmpShow2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((1!=g_nStateRun)&&(TRUE==g_bPicOk2));
}

void CPivView::OnUpdateCCFFT(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((TRUE==g_bPicOk1)&&(TRUE==g_bPicOk2)&&(1!=g_nStateRun));
}

void CPivView::OnUpdatePCFFT(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((TRUE==g_bPicOk1)&&(TRUE==g_bPicOk2)&&(1!=g_nStateRun));
}

void CPivView::OnUpdateCCFHT(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((TRUE==g_bPicOk1)&&(TRUE==g_bPicOk2)&&(1!=g_nStateRun));
}

void CPivView::OnUpdateGridsel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(1!=g_nStateRun);
}

void CPivView::OnUpdatePause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(1==g_nStateRun);
}

void CPivView::OnUpdateStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(1==g_nStateRun);
}

void CPivView::OnUpdateVecRead(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(1!=g_nStateRun);
}

void CPivView::OnUpdateVecSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((1!=g_nStateRun)&&(TRUE==g_vect.GetFlag()));
}

void CPivView::OnUpdateVecShow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((1!=g_nStateRun)&&(TRUE==g_vect.GetFlag()));
}
