//Globe.cpp

#include "stdafx.h"
#include "Globe.h"

CPivThread* g_pThread=NULL;
int g_nStateRun=0,g_nKernel=0;
CDIBitmap g_bmp1,g_bmp2;
double *g_fr0=NULL,*g_fr1=NULL,*g_frc=NULL;
double *g_fHanningX=NULL,*g_fHanningY=NULL;
BYTE g_bShowCtrl=SHOWNONE;
BOOL g_bPicOk1=FALSE,g_bPicOk2=FALSE,g_bWindowed=FALSE;

int g_nVecXSeq,g_nVecYSeq,g_nVecTot;
VectGrid g_vgSet={64,64,16,16,1.0};
InfoHead g_vecinfo;
CVector g_vect;

CxCorr2D g_corr2d;
CxPhase2D g_phase2d;
CxFHT2D g_fht2d;

