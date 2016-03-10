// ChildView.h : интерфейс класса CChildView
#pragma once  // todo: Помотреть значение... -> done

// окно CChildView
class CChildView : public CWnd
{
// Создание
public:
	CChildView();
// Атрибуты
public:
	int iYPos, iXPos;
//	bool bTimerFlag;
	int iWI, iWC;  // word index/counter
	POSITION pos;
	CString sP;
	int iXPosS, iYPosS;  // x/y position step
	static const int iXPosSA = 1;  // x position step absolute
	CRgn rA, rTCRgn;  // region all, region text current
	int iCTW, iCTH;  // current text width/heght

// Операции
public:
	BOOL RgnIsIntersect(CRgn& rRgn1, CRgn& rRgn2);

// Переопределение
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Реализация
public:
	virtual ~CChildView();

// Созданные функции схемы сообщений
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

