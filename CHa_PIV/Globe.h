#ifndef _GLOBE_H_
#define _GLOBE_H_

#include "stdafx.h"
#include "DibMap.h"
#include "PivThread.h"
#include "xFHT2D.h"
#include "xCorr2D.h"
#include "xPhase2D.h"

#define SHOWNONE  0x00
#define SHOWBMP1  0x01
#define SHOWBMP2  0x02
#define SHOWVEC   0x04

#define PNTCOUNT  100

#define WM_POLYSELCHG WM_USER+100
#define WM_FINISHED   WM_USER+101

extern CPivThread* g_pThread;
extern int g_nStateRun,g_nKernel;
extern CDIBitmap g_bmp1,g_bmp2;
extern double *g_fr0,*g_fr1,*g_frc;
extern double *g_fHanningX,*g_fHanningY;
extern BYTE g_bShowCtrl;
extern BOOL g_bPicOk1,g_bPicOk2,g_bWindowed;

extern int g_nVecXSeq,g_nVecYSeq,g_nVecTot;
extern VectGrid g_vgSet;
extern InfoHead g_vecinfo;
extern CVector g_vect;

extern CxCorr2D g_corr2d;
extern CxPhase2D g_phase2d;
extern CxFHT2D g_fht2d;

#endif