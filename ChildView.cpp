// ChildView.cpp : реализация класса CChildView
#include "stdafx.h"
#include "VWMFC.h"
#include "ChildView.h"
#include "MainFrm.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView
CChildView::CChildView()
{
	iYPos = 0;
	iXPos = 0;
	iXPosS = 1;
	iYPosS = 1;
//	bTimerFlag = false;
	iWI = 0;
	iCTH = 0;
	CStringList* pslFileContentList = &(theApp.slFileContentList);
	iWC = pslFileContentList->GetSize();
	pos = pslFileContentList->GetHeadPosition();
	sP = pslFileContentList->GetAt(pos);

	int res = rA.CreateRectRgn(0, 0, 0, 0);
	ASSERT(res == TRUE);
	res = rTCRgn.CreateRectRgn(0, 0, 0, 0);
	ASSERT(res == TRUE);
}

CChildView::~CChildView()
{
	rA.DeleteObject();
	rTCRgn.DeleteObject();
	//file1.Close();
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// обработчики сообщений CChildView
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // контекст устройства для рисования
	// TODO: Добавьте код обработки сообщений
	// Через такой объект можно только вызывать методы класса CWinApp(Ex) (даже если выполнить приведение, приравнять можно, но смысла нет)
	CVWMFCApp* pApp = static_cast<CVWMFCApp*>(AfxGetApp());
	CStringList* pslFileContentList = &(theApp.slFileContentList);
	//CString sTraceMsg;
	//static int iStrCntr;

	//dc.TextOutW(10, iYPos++, iostr);
	//AfxMessageBox(iostr);
	rA.DeleteObject();
	int res = rA.CreateRectRgn(0, 0, 0, 0);
	ASSERT(res == TRUE);
	
	// Не вызывайте CWnd::OnPaint() для сообщений рисования
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания
	// Почему не получается рисовать в этой функции:
	// The CWnd object receives this call after the window is created but _before_ it becomes visible. OnCreate is called before the Create or CreateEx member function returns.
	// Поэтому следующий тестовый код ничего не выводит:
	/*CClientDC dc(this);
	BOOL br;
	br = dc.TextOutW(100, 160, _T("CChildView::OnCreate Text Output..."));
	if (!br) TRACE("CChildView::OnCreate TextOut error");*/
	UINT iTimerID;
	iTimerID = SetTimer(5, 20, NULL);
	TRACE(_T("CChildView::OnCreate Timer 1 id: %d\n"), iTimerID);
	ASSERT(iTimerID == 5);
	//iTimerID = SetTimer(5, 600, NULL);
	//TRACE(_T("CChildView::OnCreate Timer 2 id: %d\n"), iTimerID);
	return 0;
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	/*if (bTimerFlag) {
		bTimerFlag = false;
		return 0;
	}
	else return CWnd::OnEraseBkgnd(pDC);*/
	return CWnd::OnEraseBkgnd(pDC);
}


BOOL CChildView::RgnIsIntersect(CRgn& rRgn1, CRgn& rRgn2) {
	CRgn rRRgn;  // result region
	rRRgn.CreateRectRgn(0, 0, 0, 0);
	int res = rRRgn.CombineRgn(&rRgn1, &rRgn2, RGN_AND);
	rRRgn.DeleteObject();
	ASSERT(res != ERROR);
	if (res == NULLREGION) return FALSE;
	else return TRUE;
}


void CChildView::OnTimer(UINT_PTR nIDEvent) {

	//bTimerFlag = true;
	//OnPaint();

	// Объявления и инициализация переменных
	bool bXE = false;
	CClientDC dc(this);
	CRgn rTRgn, rRgn1;
	CRect rRect1, rCR;
	CBrush br2;
	CFont fF1; 
	fF1.CreatePointFont(380, _T("Times New Roman"));
	CFont* pfFO = dc.SelectObject(&fF1);
	//CException* e1;
	
	GetClientRect(rCR);
	//TRACE(_T("CChildView::OnTimer Client Rect Height: %d\n"), rCR.Height());
	if ((iYPos >= (rCR.Height() - iCTH))||(iWI == 0)||(RgnIsIntersect(rA, rTCRgn))) {
		if (iWI == iWC) {
			KillTimer(5);
			CWnd::OnTimer(nIDEvent);
			return;
		}
		// Получение элемента для отображения
		CStringList* pslFileContentList = &(theApp.slFileContentList);
		sP = pslFileContentList->GetNext(pos);
		iYPos = 0;
		iWI++;
		CString sSBText;
		sSBText.Format(_T("%d/%d"), iWI, iWC);
		CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		pFrame->SetSBText(0, sSBText);
		CSize szTS = dc.GetTextExtent(sP);
		iCTW = szTS.cx;
		iCTH = szTS.cy;
		int res = rA.CombineRgn(&rA, &rTCRgn, RGN_OR);
		ASSERT(res != ERROR);
	}
	int iXPosSP = iXPosS;
	if (iXPos >= (rCR.Width() - iCTW)) {
		iXPosS = -iXPosSA;
	}
	if (iXPos < 0) {
		iXPosS = iXPosSA;
	}
	if (iXPosSP != iXPosS) bXE = true;


	COLORREF crBGC = dc.GetBkColor();
	//COLORREF crOTC = dc.SetTextColor(crBGC);
	//dc.MoveTo(100, iYPos);
	//dc.TextOutW(10, iYPos++, sP);
	//dc.SetTextColor(crOTC);
	dc.BeginPath(); // Define a path 
	dc.TextOutW(iXPos, iYPos, sP);
	iXPos += iXPosS;
	iYPos += iYPosS;
	// Пока работает без этого, нужно ли делать вообще - неизвестно
	/*if (!dc.CloseFigure()) {
		TRACE(_T("CChildView::OnTimer CDC::CloseFigure error\n"));
		throw;
	}*/
	dc.EndPath();
	if (!rTRgn.CreateFromPath(&dc)) {
		TRACE(_T("CChildView::OnTimer rTRgn.CreateFromPath error\n"));
		throw;
	}
	// Преобразовать обрамляющий регион в регион текста
	rTRgn.GetRgnBox(&rRect1);
	rRgn1.CreateRectRgnIndirect(&rRect1); 
	rTRgn.CombineRgn(&rRgn1, &rTRgn, RGN_DIFF);
	rTCRgn.CopyRgn(&rTRgn);

	/*try {
		rTRgn.OffsetRgn(0, 0);
	}
	catch (CException* e1) {
		e1->ReportError();
		e1->Delete();
	}*/

	rTRgn.OffsetRgn(bXE ? iXPosS : (-iXPosS), -iYPosS);
	br2.CreateSolidBrush(crBGC);
	dc.FrameRgn(&rTRgn, &br2, 1, 1);
	br2.DeleteObject();
	rTRgn.OffsetRgn(bXE ? -iXPosS : iXPosS, iYPosS);
	br2.CreateSolidBrush(RGB(0, 155, 20));
	//dc.FrameRgn(&rTRgn, &br2, 1, 1);
	dc.FillRgn(&rTRgn, &br2);
	br2.DeleteObject();

	dc.SelectObject(pfFO);
	CWnd::OnTimer(nIDEvent);
}
