// VWMFC.cpp : Определяет поведение классов для приложения.
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

// создание CVWMFCApp
CVWMFCApp::CVWMFCApp()
{
	m_bHiColorIcons = TRUE;
	// TODO: замените ниже строку идентификатора приложения строкой уникального идентификатора; рекомендуемый
	// формат для строки: ИмяКомпании.ИмяПродукта.СубПродукт.СведенияОВерсии
	SetAppID(_T("kit500.development.demo.app.1.v0.1.alpha"));

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance

	// Исправляет крякозябры при выводе в окно. Устанавливает локализацию, установленную на компьютере.
	// По умолчанию объъекты CString видимо хранят юникод (?), при считывании текста в CP1251, видимо переводят в CP1252
	setlocale(LC_ALL, "");
	//_tsetlocale(LC_ALL, _T("cp1251"));

	sIFilePath = _T("file.txt");
	ReadFile();
}

// Единственный объект CVWMFCApp
CVWMFCApp theApp;

// инициализация CVWMFCApp
BOOL CVWMFCApp::InitInstance()
{
	// InitCommonControlsEx() требуются для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения. В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinAppEx::InitInstance();
	EnableTaskbarInteraction(FALSE);
	// Для использования элемента управления RichEdit требуется метод AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующего
	// конкретные процедуры инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры

	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	// + проверено в реестре
	//SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));
	SetRegistryKey(_T("kit500.development"));
	InitContextMenuManager();
	InitKeyboardManager();
	//InitTooltipManager();
	//CMFCToolTipInfo ttParams;
	//ttParams.m_bVislManagerTheme = TRUE;
	//theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
	//	RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Чтобы создать главное окно, этот код создает новый объект окна
	// рамки, а затем задает его как объект основного окна приложения
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// создайте и загрузите рамку с его ресурсами
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE, NULL,
		NULL);
	// Одно и только одно окно было инициализировано, поэтому отобразите и обновите его
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	// вызов DragAcceptFiles только при наличии суффикса
	// В приложении SDI это должно произойти после ProcessShellCommand


	/*
	// Эксперименты с CWindowDC...
	CWindowDC dc1(pFrame);
	BOOL r;
	r = dc1.TextOutW(200, 200, _T("CVWMFCApp::InitInstance Text Output..."));
	if (!r) {TRACE("CVWMFCApp::InitInstance TextOut error");}
	dc1.Ellipse(100,100,200,200); */

	return TRUE;
}

int CVWMFCApp::ExitInstance()
{
	//TODO: обработайте дополнительные ресурсы, которые могли быть добавлены
	return CWinAppEx::ExitInstance();
}

// обработчики сообщений CVWMFCApp
// Диалоговое окно CAboutDlg используется для описания сведений о приложении
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// Данные диалогового окна
	enum {IDD = IDD_ABOUTBOX};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
// Реализация
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

// Команда приложения для запуска диалога
void CVWMFCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CVWMFCApp настройка методов загрузки и сохранения
// + загрузка меню?

void CVWMFCApp::PreLoadState()  // todo: Посмотреть про эти три функции.
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

// обработчики сообщений CVWMFCApp
//...


void CVWMFCApp::ReadFile()
{
	CFileException eFE;
	TCHAR szCause[255];
	TCHAR szCurrentPath[255];
	CString sTraceMsg = _wgetcwd(szCurrentPath, 255);  // _wgetcwd - Get current work dir (Unicode)  // todo: Помсмотреть, как можно реализовать без буффера.
	sTraceMsg = _T("Current Dir: ") + sTraceMsg + _T("\n");
	TRACE(sTraceMsg);  // Достаточно неграмотно

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
	// todo: Использовать ~~ArrayObject ->> CStringList
	while(!sResToken.IsEmpty())
	{
		slFileContentList.AddTail(sResToken);
		//OutputDebugString(sResToken);  // todo: Посмотреть OutputDebugString.
		sResToken = sFileContent.Tokenize(_T("% #"), iCurPos);
	}
	//TRACE(iostr);
	
	delete szFLc;
	fIFile.Close();
}
