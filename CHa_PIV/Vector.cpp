// Vector.cpp: implementation of the CVector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CHa_PIV.h"
#include "Vector.h"

#include <memory.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector::CVector()
{
	blflag=FALSE;
	infohead.nBmpWidth=0;
	infohead.nBmpHeight=0;
	infohead.nVecWidth=0;
	infohead.nVecHeight=0;
	infohead.nVecSize=0;
	vectgrid.nGridSizeX=64;
	vectgrid.nGridSizeY=64;
	vectgrid.nGridStepX=16;
	vectgrid.nGridStepY=16;
	vectgrid.dfAmp=1.0;

	pVecData=0;
}

CVector::CVector(const CVector& myvec)
{
	VectGrid vgind;
	myvec.GetVectGrid(vgind);
	SetVectGrid(vgind);
	InfoHead ihind;
	myvec.GetInfoHead(ihind);
	SetInfoHead(ihind);
	AllocData();
	memcpy((char*)pVecData,myvec.GetVecPtr(),ihind.nVecSize);
}

CVector::~CVector()
{
	DeleteData();
}

void CVector::SetVectGrid(const VectGrid& vgind)
{
	vectgrid.nGridSizeX=vgind.nGridSizeX;
	vectgrid.nGridSizeY=vgind.nGridSizeY;
	vectgrid.nGridStepX=vgind.nGridStepX;
	vectgrid.nGridStepY=vgind.nGridStepY;
	vectgrid.dfAmp=vgind.dfAmp;
}

void CVector::SetInfoHead(InfoHead& ihind)
{
	infohead.nBmpHeight=ihind.nBmpHeight;
	infohead.nBmpWidth=ihind.nBmpWidth;
	infohead.nVecHeight=ihind.nVecHeight;
	infohead.nVecWidth=ihind.nVecWidth;
	infohead.nVecSize=infohead.nVecHeight*infohead.nVecWidth;
}

void CVector::SetInfoHead0()
{
	infohead.nVecHeight=0;
	infohead.nVecWidth=0;
	infohead.nVecSize=infohead.nVecHeight*infohead.nVecWidth;
}

void CVector::CalcInfoHead(int nbmpwid,int nbmphit)
{
	//call this function after calling SetVectGrid()
	infohead.nBmpWidth=nbmpwid;
	infohead.nBmpHeight=nbmphit;
	infohead.nVecHeight=(nbmphit-vectgrid.nGridSizeY+vectgrid.nGridStepY)/vectgrid.nGridStepY;
	if(infohead.nVecHeight<0) infohead.nVecHeight=0;
	infohead.nVecWidth=(nbmpwid-vectgrid.nGridSizeX+vectgrid.nGridStepX)/vectgrid.nGridStepX;
	if(infohead.nVecWidth<0) infohead.nVecWidth=0;
	infohead.nVecSize=infohead.nVecHeight*infohead.nVecWidth;
}

void CVector::DeleteData()
{
	delete [infohead.nVecSize]pVecData;
	pVecData=0;
}

bool CVector::AllocData()
{
	bool blret;

	pVecData=new VecDatum[infohead.nVecSize];
	if(pVecData==0) blret=false;
	else
	{
		blret=true;
		memset((char*)pVecData,0,sizeof(VecDatum)*infohead.nVecSize);
	}

	return blret;
}

void CVector::GetVectGrid(VectGrid& vgind) const
{
	vgind.nGridSizeX=vectgrid.nGridSizeX;
	vgind.nGridSizeY=vectgrid.nGridSizeY;
	vgind.nGridStepX=vectgrid.nGridStepX;
	vgind.nGridStepY=vectgrid.nGridStepY;
	vgind.dfAmp=vectgrid.dfAmp;
}

void CVector::GetInfoHead(InfoHead& ihind) const
{
	ihind.nBmpWidth=infohead.nBmpWidth;
	ihind.nBmpHeight=infohead.nBmpHeight;
	ihind.nVecWidth=infohead.nVecWidth;
	ihind.nVecHeight=infohead.nVecHeight;
	ihind.nVecSize=infohead.nVecSize;
}

bool CVector::ImplementVec(const VectGrid& vgind,int nbmpwid,int nbmphit)
{
	bool blret;

	//note: the sequence of functions
	SetVectGrid(vgind);//1
	DeleteData();//2
	CalcInfoHead(nbmpwid,nbmphit);//3
	blret=AllocData();//4
	if(blret==false) SetInfoHead0();

	return blret;
}

void CVector::SetVecDatum(const VecDatum& vd)
{
	if((vd.npx<0)||(vd.npx>=infohead.nVecWidth)) return;
	if((vd.npy<0)||(vd.npy>=infohead.nVecHeight)) return;
	pVecData[vd.npy*infohead.nVecWidth+vd.npx].nstat=vd.nstat;
	pVecData[vd.npy*infohead.nVecWidth+vd.npx].npx=vd.npx;
	pVecData[vd.npy*infohead.nVecWidth+vd.npx].npy=vd.npy;
	pVecData[vd.npy*infohead.nVecWidth+vd.npx].dfvx=vd.dfvx;
	pVecData[vd.npy*infohead.nVecWidth+vd.npx].dfvy=vd.dfvy;
	//memcpy(&(pVecData[vd.npy*infohead.nVecWidth+vd.npx]),&vd,sizeof(VecDatum));
}

void CVector::GetVecDatum(int nseq,VecDatum& vd)
{
	memset(&vd,0,sizeof(VecDatum));

	if((nseq<0)||(nseq>infohead.nVecSize)) return;
	vd.nstat=pVecData[nseq].nstat;
	vd.npx=pVecData[nseq].npx;
	vd.npy=pVecData[nseq].npy;
	vd.dfvx=pVecData[nseq].dfvx;
	vd.dfvy=pVecData[nseq].dfvy;
	//memcpy(&vd,&(pVecData[nseq]),sizeof(VecDatum));
}

char* CVector::GetVecPtr() const
{
	return (char*)pVecData;
}

CVector& CVector::operator =(const CVector &myvec)
{
	DeleteData();
	VectGrid vgind;
	myvec.GetVectGrid(vgind);
	SetVectGrid(vgind);
	InfoHead ihind;
	myvec.GetInfoHead(ihind);
	SetInfoHead(ihind);
	AllocData();
	memcpy((char*)pVecData,myvec.GetVecPtr(),ihind.nVecSize);

	return *this;
}

bool CVector::operator ==(const CVector &myvec)
{
	VectGrid vgind;
	myvec.GetVectGrid(vgind);
	if(memcmp((char*)(&vectgrid),(char*)(&vgind),sizeof(VectGrid))!=0) return false;
	InfoHead ihind;
	myvec.GetInfoHead(ihind);
	if(memcmp((char*)(&infohead),(char*)(&ihind),sizeof(InfoHead))!=0) return false;
	if(memcmp((char*)pVecData,myvec.GetVecPtr(),infohead.nVecSize)!=0) return false;

	return true;
}

bool CVector::operator !=(const CVector &myvec)
{
	if(*this==myvec) return true;
	else return false;
}

void CVector::DrawVec(CDC* pDC)
{
	DrawVec(pDC,infohead.nBmpWidth,infohead.nBmpHeight);
}

//Display the vector.
void CVector::DrawVec(CDC* pDC,int nw,int nh)
{
	DrawVec(pDC,nw,nh,infohead.nVecSize);
}

//Display the vector.
void CVector::DrawVec(CDC* pDC,int nw,int nh,int nTot)
{
	if(nTot>infohead.nVecSize) return;

	ASSERT(pDC);

	int i,npx1,npy1,npx2,npy2,nxid,nyid,nxlen,nylen;
	VecDatum vecind;

	int nox=(nw-infohead.nBmpWidth)/2;
	if(nox<0) nox=0;
	int noy=(nh-infohead.nBmpHeight)/2;
	if(noy<0) noy=0;

	CPen* pPen1=new CPen;
	CPen* pPen2=new CPen;
	pPen1->CreatePen(PS_SOLID,0,RGB(0,0,255));
	pPen2->CreatePen(PS_SOLID,0,RGB(255,0,0));
	CPen* pOldPen=pDC->SelectObject(pPen1);

	for(i=0;i<nTot;i++)
	{
		GetVecDatum(i,vecind);
		//calculate the length of vector arrow after amplifying
		nxlen=(int)(vectgrid.dfAmp*vecind.dfvx);
		nylen=(int)(vectgrid.dfAmp*vecind.dfvy);

		npx1=nox+vecind.npx*vectgrid.nGridStepX+vectgrid.nGridSizeX/2;
		npy1=noy+vecind.npy*vectgrid.nGridStepY+vectgrid.nGridSizeY/2;
		npx2=npx1+nxlen; npy2=npy1+nylen;

		//draw the arrow here
		pDC->SelectObject(pPen1);

		pDC->MoveTo(npx1,npy1);
		pDC->LineTo(npx2,npy2);

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
		npx2=nxid+(nyid-npy1);
		npy2=nyid+(npx1-nxid);
		pDC->SelectObject(pPen2);
		pDC->LineTo(npx2,npy2);
		npx2=nxid-(nyid-npy1);
		npy2=nyid-(npx1-nxid);
		pDC->MoveTo(npx1,npy1);
		pDC->LineTo(npx2,npy2);
	}

	pDC->SelectObject(pOldPen);
	delete pPen1; delete pPen2;
}

bool CVector::Load(CFile* pFile)
{
	ASSERT(pFile);
	bool fReturn=true;
	blflag=TRUE;
	try
	{
		DeleteData();

		//Check to make sure we have a vector.
		char pTxtHeader[4]; //occupy 4 buffers
		char pTxType[4]={'v','e','c','t'};
		pFile->Read(pTxtHeader,4);
		if(memcmp(pTxtHeader,pTxType,4)!=0) throw TEXT("错误:文件格式出错,不是一个速度文件\n");
			//throw TEXT("Error:Unexpected file type,not a VEC\n");

		pFile->Read((char*)&infohead,sizeof(InfoHead));
		pFile->Read((char*)&vectgrid,sizeof(VectGrid));
		AllocData();
		pFile->ReadHuge((char*)pVecData,infohead.nVecSize*sizeof(VecDatum));
#ifdef _DEBUG
    }
	catch(TCHAR *psz)
	{
		TRACE(psz);
#else
    }
	catch(TCHAR *)
	{
#endif
        fReturn=false;
		blflag=FALSE;
    }
    return fReturn;
}

bool CVector::Load(const CString& strFilename)
{
	CFile file;
	if(file.Open(strFilename,CFile::modeRead)) return Load(&file);
	return false;
}

//Does not open or close pFile. Assumes caller will do it.
bool CVector::Save(CFile *pFile)
{
	ASSERT(pVecData);

	//Make sure we have a vector.
	char pTxType[4]={'v','e','c','t'};
	pFile->Write(pTxType,4);

	pFile->Write((char*)&infohead,sizeof(InfoHead));
	pFile->Write((char*)&vectgrid,sizeof(VectGrid));
	pFile->WriteHuge((char*)pVecData,infohead.nVecSize*sizeof(VecDatum));

	return true;
}

bool CVector::Save(const CString& strFileName)
{
	ASSERT(!strFileName.IsEmpty());

	CFile File;

	if(!File.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
	{
		TRACE1("CVector::Save():Failed to open file %s for writing.\n",LPCSTR(strFileName));
		return FALSE;
	}

	return Save(&File);
}

BYTE CVector::DetectPosition(int nPosX,int nPosY)
{
	BYTE bRet;

	bRet=INRECT;

	if((nPosX>=infohead.nVecWidth)||(nPosY>=infohead.nVecHeight)) bRet=bRet|OUTOFRECT;

	if(nPosY==0) bRet=bRet|ONTOP;
	if(nPosX==0) bRet=bRet|ONLEFT;
	if(nPosY==infohead.nVecHeight-1) bRet=bRet|ONBOTTOM;
	if(nPosX==infohead.nVecWidth-1) bRet=bRet|ONRIGHT;

	return bRet;
}

void CVector::SetAmplifer(double dfamp)
{
	vectgrid.dfAmp=dfamp;
}
