// VWMFC.cpp : ���������� ��������� ������� ��� ����������.
#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "VWMFC.h"
#include "MainFrm.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVWMFCApp
BEGIN_MESSAGE_MAP(CVWMFCApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CVWMFCApp::OnAppAbout)
END_MESSAGE_MAP()

// �������� CVWMFCApp
CVWMFCApp::CVWMFCApp()
{
	m_bHiColorIcons = TRUE;
	// TODO: �������� ���� ������ �������������� ���������� ������� ����������� ��������������; �������������
	// ������ ��� ������: �����������.�����������.����������.���������������
	SetAppID(_T("kit500.development.demo.app.1.v0.1.alpha"));

	// TODO: �������� ��� ��������,
	// ��������� ���� ������ ��� ������������� � InitInstance

	// ���������� ���������� ��� ������ � ����. ������������� �����������, ������������� �� ����������.
	// �� ��������� �������� CString ������ ������ ������ (?), ��� ���������� ������ � CP1251, ������ ��������� � CP1252
	setlocale(LC_ALL, "");
	//_tsetlocale(LC_ALL, _T("cp1251"));

	sIFilePath = _T("file.txt");
	ReadFile();
}

// ������������ ������ CVWMFCApp
CVWMFCApp theApp;

// ������������� CVWMFCApp
BOOL CVWMFCApp::InitInstance()
{
	// InitCommonControlsEx() ��������� ��� Windows XP, ���� ��������
	// ���������� ���������� ComCtl32.dll ������ 6 ��� ����� ������� ������ ��� ���������
	// ������ �����������. � ��������� ������ ����� ��������� ���� ��� �������� ������ ����.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �������� ���� �������� ��� ��������� ���� ����� ������� ����������, ������� ���������� ������������
	// � ����� ����������.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinAppEx::InitInstance();
	EnableTaskbarInteraction(FALSE);
	// ��� ������������� �������� ���������� RichEdit ��������� ����� AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ����������� �������������
	// ���� ��� ����������� �� ������������ � ���������� ��������� ������
	// ��������� ������������ �����, ���������� ������� �� ����������
	// ���������� ��������� �������������, ������� �� ���������
	// �������� ������ �������, � ������� �������� ���������

	// TODO: ������� �������� ��� ������ �� ���-������ ����������,
	// �������� �� �������� �����������
	// + ��������� � �������
	//SetRegistryKey(_T("��������� ����������, ��������� � ������� ������� ����������"));
	SetRegistryKey(_T("kit500.development"));
	InitContextMenuManager();
	InitKeyboardManager();
	//InitTooltipManager();
	//CMFCToolTipInfo ttParams;
	//ttParams.m_bVislManagerTheme = TRUE;
	//theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
	//	RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ����� ������� ������� ����, ���� ��� ������� ����� ������ ����
	// �����, � ����� ������ ��� ��� ������ ��������� ���� ����������
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// �������� � ��������� ����� � ��� ���������
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE, NULL,
		NULL);
	// ���� � ������ ���� ���� ���� ����������������, ������� ���������� � �������� ���
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	// ����� DragAcceptFiles ������ ��� ������� ��������
	// � ���������� SDI ��� ������ ��������� ����� ProcessShellCommand


	/*
	// ������������ � CWindowDC...
	CWindowDC dc1(pFrame);
	BOOL r;
	r = dc1.TextOutW(200, 200, _T("CVWMFCApp::InitInstance Text Output..."));
	if (!r) {TRACE("CVWMFCApp::InitInstance TextOut error");}
	dc1.Ellipse(100,100,200,200); */

	return TRUE;
}

int CVWMFCApp::ExitInstance()
{
	//TODO: ����������� �������������� �������, ������� ����� ���� ���������
	return CWinAppEx::ExitInstance();
}

// ����������� ��������� CVWMFCApp
// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// ������ ����������� ����
	enum {IDD = IDD_ABOUTBOX};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV
// ����������
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// ������� ���������� ��� ������� �������
void CVWMFCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CVWMFCApp ��������� ������� �������� � ����������
// + �������� ����?

void CVWMFCApp::PreLoadState()  // todo: ���������� ��� ��� ��� �������.
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CVWMFCApp::LoadCustomState()
{
}

void CVWMFCApp::SaveCustomState()
{
}

// ����������� ��������� CVWMFCApp
//...


void CVWMFCApp::ReadFile()
{
	CFileException eFE;
	TCHAR szCause[255];
	TCHAR szCurrentPath[255];
	CString sTraceMsg = _wgetcwd(szCurrentPath, 255);  // _wgetcwd - Get current work dir (Unicode)  // todo: �����������, ��� ����� ����������� ��� �������.
	sTraceMsg = _T("Current Dir: ") + sTraceMsg + _T("\n");
	TRACE(sTraceMsg);  // ���������� ����������

	fIFile.Open(sIFilePath, CFile::modeRead, &eFE);
	if (eFE.m_cause)
	{
		eFE.GetErrorMessage(szCause, 255);
		//AfxMessageBox(szCause);
		eFE.ReportError();
		eFE.Delete();
	}

	//CString iostr, iostr1;
	//CString tracestr;
	ULONGLONG iFL = fIFile.GetLength();
	//char* szFLb = new char[iFL + 1];
	TCHAR* szFLc = new TCHAR[static_cast<UINT>(iFL) / sizeof(TCHAR) + 1];  // File length in chars
	TRACE(_T("CVWMFCApp::ReadFile: FILE LENGTH: %d\n"), iFL);
	CString sB;  // Buffer string
	CString sFileContent;
	//file1.Read(iostr.GetBuffer(200 / sizeof(TCHAR)), 200);
	//iostr.ReleaseBuffer(200 / sizeof(TCHAR));
	//file1.Read(iostr2, fl);
	//file1.SeekToBegin();
	//file1.Read(iostr3, fl);
	//file1.ReadString(iostr1.GetBuffer(60 / sizeof(TCHAR)), 60 / sizeof(TCHAR));
	//iostr1.ReleaseBuffer(60 / sizeof(TCHAR));
	while (fIFile.ReadString(sB))
	{
		sFileContent += sB;
	}
	
	int iCurPos = 0;
	CString sResToken = sFileContent.Tokenize(_T("% #"), iCurPos);
	// todo: ������������ ~~ArrayObject ->> CStringList
	while(!sResToken.IsEmpty())
	{
		slFileContentList.AddTail(sResToken);
		//OutputDebugString(sResToken);  // todo: ���������� OutputDebugString.
		sResToken = sFileContent.Tokenize(_T("% #"), iCurPos);
	}
	//TRACE(iostr);
	
	delete szFLc;
	fIFile.Close();
}
