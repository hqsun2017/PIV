// Vector.h: interface for the CVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__340D12A2_50BD_11D4_A4E6_0060089C5332__INCLUDED_)
#define AFX_VECTOR_H__340D12A2_50BD_11D4_A4E6_0060089C5332__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DEAL_NORMAL 0
#define DEAL_REVISE 1
#define DEAL_REMOVE 2

#define  INRECT    0x00
#define  ONTOP     0x01
#define  ONLEFT    0x02
#define  ONRIGHT   0x04
#define  ONBOTTOM  0x08
#define  OUTOFRECT 0xff

typedef struct
{
	int nVecSize;
	int nVecWidth;
	int nVecHeight;
	int nBmpWidth;
	int nBmpHeight;
} InfoHead;
 
typedef struct
{
	int nGridSizeX;
	int nGridSizeY;
	int nGridStepX;
	int nGridStepY;
	double dfAmp;
} VectGrid;

typedef struct
{
	int    nstat;
	int    npx;
	int    npy;
	double dfvx;
	double dfvy;
} VecDatum;

class CVector
{
// Construction
public:
	CVector();
	CVector(const CVector& myvec);
	virtual ~CVector();

// Attributes
private:
	BOOL blflag;
	InfoHead  infohead;
	VectGrid  vectgrid;
	VecDatum* pVecData;

// Operations
private:
	void SetVectGrid(const VectGrid& vgind);
	void SetInfoHead(InfoHead& ihind);
	void SetInfoHead0();
	void CalcInfoHead(int nbmpwid, int nbmphit);
	void DeleteData();
	bool AllocData();
public:
	void GetVectGrid(VectGrid& vgind) const;
	void GetInfoHead(InfoHead& ihind) const;
	bool ImplementVec(const VectGrid& vgind, int nbmpwid, int nbmphit);
	void SetVecDatum(const VecDatum& vd);
	void GetVecDatum(int nseq, VecDatum& vd);
	char* GetVecPtr() const;
	CVector& operator =(const CVector &myvec);
	bool operator ==(const CVector &myvec);
	bool operator !=(const CVector &myvec);

	BOOL GetFlag() { return blflag; }
	void SetFlag(BOOL bltmp) { blflag=bltmp; }
	int GetVecSize() { return infohead.nVecSize ;}
	int GetVecWidth() { return infohead.nVecWidth ;}
	int GetVecHeight() { return infohead.nVecHeight ;}

	BYTE DetectPosition(int nPosX, int nPosY);
	void SetAmplifer(double dfamp);

// Overrides
public:
	// draw the vector at the specified location
	virtual void DrawVec(CDC * pDC);
	// draw the vector and stretch/compress it to the desired size
	virtual void DrawVec(CDC * pDC,int nw,int nh);
	// draw the vector and stretch/compress it to the desired size
	virtual void DrawVec(CDC * pDC,int nw,int nh,int nTot);
	// load a vector from disk
	virtual bool Load(CFile * pFile);
	virtual bool Load(const CString &);
	// save the vector to disk
	virtual bool Save(CFile * pFile);
	virtual bool Save(const CString &);
};

#endif // !defined(AFX_VECTOR_H__340D12A2_50BD_11D4_A4E6_0060089C5332__INCLUDED_)
