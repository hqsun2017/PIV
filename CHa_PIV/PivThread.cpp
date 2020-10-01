// PivThread.cpp : implementation file
//

#include "stdafx.h"
#include "CHa_PIV.h"
#include "PivThread.h"
#include "Globe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPivThread

IMPLEMENT_DYNAMIC(CPivThread,CWinThread)

CPivThread::CPivThread(CWnd* pWnd)
{
	m_bAutoDelete=FALSE;
	m_pMainWnd=pWnd;
    
	//kill event starts out in the signaled state
	m_hEventKill=CreateEvent(NULL,TRUE,FALSE,NULL);
}

CPivThread::~CPivThread()
{
	CloseHandle(m_hEventKill);
}

BOOL CPivThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	// loop but check for kill notification
	while(WaitForSingleObject(m_hEventKill,0)==WAIT_TIMEOUT) CorrAndCorr();

	//avoid entering standard message loop by returning FALSE
	return FALSE;//return TRUE;
}

int CPivThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPivThread,CWinThread)
	//{{AFX_MSG_MAP(CPivThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPivThread message handlers

void CPivThread::KillThread()
{
	// Note: this function is called in the context of other threads,not the thread itself.

    //reset the m_hEventKill which signals the thread to shutdown
	VERIFY(SetEvent(m_hEventKill));

	//allow thread to run at higher priority during kill process
	SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
	WaitForSingleObject(m_hThread,INFINITE);

	//now delete CWinThread object since no longer necessary
	delete this;
}

void CPivThread::CorrAndCorr()
{
	Correlation();//correlation
	FindPeak(); DrawVector();

	g_nVecTot++; g_nVecXSeq++;
	if(g_nVecXSeq==g_vecinfo.nVecWidth) {g_nVecXSeq=0; g_nVecYSeq++;}

	if(g_nVecTot==g_vecinfo.nVecSize)
	{
		//reset the m_hEventKill which signals the thread to shutdown
		VERIFY(SetEvent(m_hEventKill));
		m_pMainWnd->PostMessage(WM_FINISHED);
	}
}

void CPivThread::Correlation()
{
	int nx,ny;

	//cross-correlation
	for(ny=0;ny<g_vgSet.nGridSizeY;ny++) for(nx=0;nx<g_vgSet.nGridSizeX;nx++)
	{
		g_fr0[ny*g_vgSet.nGridSizeX+nx]=(double)(g_bmp1.GetPixelValue((g_nVecXSeq*g_vgSet.nGridStepX+nx),(g_nVecYSeq*g_vgSet.nGridStepY+ny)));
		g_fr1[ny*g_vgSet.nGridSizeX+nx]=(double)(g_bmp2.GetPixelValue((g_nVecXSeq*g_vgSet.nGridStepX+nx),(g_nVecYSeq*g_vgSet.nGridStepY+ny)));
		if(g_bWindowed)
		{
			g_fr0[ny*g_vgSet.nGridSizeX+nx]*=g_fHanningX[nx]*g_fHanningY[ny];
			g_fr1[ny*g_vgSet.nGridSizeX+nx]*=g_fHanningX[nx]*g_fHanningY[ny];
		}
	}
	if(g_nKernel==0)//RealFFT
		g_corr2d.CircleProcess(g_vgSet.nGridSizeX,g_vgSet.nGridSizeY,g_fr0,g_fr1,g_frc);
	if(g_nKernel==1)//Phase coorelation
		g_phase2d.CircleProcess(g_vgSet.nGridSizeX,g_vgSet.nGridSizeY,g_fr0,g_fr1,g_frc);
	if(g_nKernel==2)//FHT
		g_fht2d.Correlation(g_vgSet.nGridSizeX,g_vgSet.nGridSizeY,g_fr0,g_fr1,g_frc);
}

void CPivThread::FindPeak()
{
	int nx,ny,nmax_x,nmax_y;
	double dfind,dfxv,dfyv;

	nmax_x=0; nmax_y=0; dfind=g_frc[0];
	for(ny=0;ny<g_vgSet.nGridSizeY;ny++) for(nx=0;nx<g_vgSet.nGridSizeX;nx++)
	{
		if(g_frc[ny*g_vgSet.nGridSizeX+nx]>dfind)
		{
			dfind=g_frc[ny*g_vgSet.nGridSizeX+nx];
			nmax_x=nx; nmax_y=ny;
		}
	}

	//calculate the position of maxinum value in x direction
	dfxv=(double)nmax_x*g_frc[nmax_y*g_vgSet.nGridSizeX+nmax_x];
	dfind=g_frc[nmax_y*g_vgSet.nGridSizeX+nmax_x];
	if(nmax_x!=0)
	{
		dfxv+=(double)(nmax_x-1)*g_frc[nmax_y*g_vgSet.nGridSizeX+nmax_x-1];		
		dfind+=g_frc[nmax_y*g_vgSet.nGridSizeX+nmax_x-1];
	}
	else
	{
		dfxv+=(double)(nmax_x-1)*g_frc[nmax_y*g_vgSet.nGridSizeX+g_vgSet.nGridSizeX-1];
		dfind+=g_frc[nmax_y*g_vgSet.nGridSizeX+g_vgSet.nGridSizeX-1];
	}
	if(nmax_x!=g_vgSet.nGridSizeX-1)
	{
		dfxv+=(double)(nmax_x+1)*g_frc[nmax_y*g_vgSet.nGridSizeX+nmax_x+1];
		dfind+=g_frc[nmax_y*g_vgSet.nGridSizeX+nmax_x+1];
	}
	else
	{
		dfxv+=(double)(nmax_x+1)*g_frc[nmax_y*g_vgSet.nGridSizeX];
		dfind+=g_frc[nmax_y*g_vgSet.nGridSizeX];
	}
	dfxv=dfxv/dfind;
	if(dfxv>g_vgSet.nGridSizeX/2) dfxv=dfxv-g_vgSet.nGridSizeX;

	//calculate the position of maxinum value in y direction
	dfyv=(double)nmax_y*g_frc[nmax_y*g_vgSet.nGridSizeX+nmax_x];
	dfind=g_frc[nmax_y*g_vgSet.nGridSizeX+nmax_x];
	if(nmax_y!=0)
	{
		dfyv+=(double)(nmax_y-1)*g_frc[(nmax_y-1)*g_vgSet.nGridSizeX+nmax_x];		
		dfind+=g_frc[(nmax_y-1)*g_vgSet.nGridSizeX+nmax_x];
	}
	else
	{
		dfyv+=(double)(nmax_y-1)*g_frc[(g_vgSet.nGridSizeY-1)*g_vgSet.nGridSizeX+nmax_x];
		dfind+=g_frc[(g_vgSet.nGridSizeY-1)*g_vgSet.nGridSizeX+nmax_x];
	}
	if(nmax_y!=g_vgSet.nGridSizeY-1)
	{
		dfyv+=(double)(nmax_y+1)*g_frc[(nmax_y+1)*g_vgSet.nGridSizeX+nmax_x];
		dfind+=g_frc[(nmax_y+1)*g_vgSet.nGridSizeX+nmax_x];
	}
	else
	{
		dfyv+=(double)(nmax_y+1)*g_frc[nmax_x];
		dfind+=g_frc[nmax_x];
	}
	dfyv=dfyv/dfind;
	if(dfyv>g_vgSet.nGridSizeY/2) dfyv=dfyv-g_vgSet.nGridSizeY;

	//set the vector value
	vecdatum.npx=g_nVecXSeq; vecdatum.npy=g_nVecYSeq;
	vecdatum.dfvx=dfxv; vecdatum.dfvy=dfyv;
	vecdatum.nstat=DEAL_NORMAL;

	g_vect.SetVecDatum(vecdatum);
}

void CPivThread::DrawVector()
{
	int npx1,npy1,npx2,npy2,nxid,nyid,nxlen,nylen;

	CRect rect;
	m_pMainWnd->GetClientRect(&rect);
	int nox=(rect.Width()-g_bmp1.GetWidth())/2;
	int noy=(rect.Height()-g_bmp1.GetHeight())/2;
	if(nox<0) nox=0;
	if(noy<0) noy=0;

	//calculate the length of vector arrow after amplifying
	nxlen=(int)(g_vgSet.dfAmp*vecdatum.dfvx);
	nylen=(int)(g_vgSet.dfAmp*vecdatum.dfvy);

	npx1=nox+vecdatum.npx*g_vgSet.nGridStepX+g_vgSet.nGridSizeX/2;
	npy1=noy+vecdatum.npy*g_vgSet.nGridStepY+g_vgSet.nGridSizeY/2;
	npx2=npx1+nxlen; npy2=npy1+nylen;

	//draw the arrow here
	CDC *pCtrlDC=m_pMainWnd->GetDC();
	CPen* pOldPen;
	CPen* pPen1=new CPen;
	CPen* pPen2=new CPen;

	pPen1->CreatePen(PS_SOLID,0,RGB(0,0,255));
	pPen2->CreatePen(PS_SOLID,0,RGB(255,0,0));
	pOldPen=pCtrlDC->SelectObject(pPen1);

	pCtrlDC->MoveTo(npx1,npy1);
	pCtrlDC->LineTo(npx2,npy2);

	if((abs(npx1-npx2)<4)&&(abs(npy1-npy2)<4))
	{
		nxid=npx1;
		nyid=npy1;
	}
	else if((abs(npx1-npx2)<8)&&(abs(npy1-npy2)<8))
	{
		nxid=(npx1+npx2)/2;
		nyid=(npy1+npy2)/2;
	}
	else
	{
		nxid=(npx1+3*npx2)/4;
		nyid=(npy1+3*npy2)/4;
	}
	npx1=npx2; npy1=npy2;
	npx2=nxid+(nyid-npy1); npy2=nyid+(npx1-nxid);
	pCtrlDC->SelectObject(pPen2);
	pCtrlDC->LineTo(npx2,npy2);
	npx2=nxid-(nyid-npy1); npy2=nyid-(npx1-nxid);
	pCtrlDC->MoveTo(npx1,npy1);
	pCtrlDC->LineTo(npx2,npy2);

	pCtrlDC->SelectObject(pOldPen);
	m_pMainWnd->ReleaseDC(pCtrlDC);
	delete pPen1; delete pPen2;
}
