// ChildView.h : ��������� ������ CChildView
#pragma once  // todo: ��������� ��������... -> done

// ���� CChildView
class CChildView : public CWnd
{
// ��������
public:
	CChildView();
// ��������
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

// ��������
public:
	BOOL RgnIsIntersect(CRgn& rRgn1, CRgn& rRgn2);

// ���������������
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����������
public:
	virtual ~CChildView();

// ��������� ������� ����� ���������
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

