
#include "stdafx.h"
#include "VWMFC.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
IMPLEMENT_DYNAMIC(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	//ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	//ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ��������� ������ ���������
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// ��������/����������� CMainFrame
CMainFrame::CMainFrame()
{
	// TODO: �������� ��� ������������� �����
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	// ���������� ��������� ���������, ��������������� ��� ��������� ���� ��������� ���������� ������������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("�� ������� ������� ������ ����\n");
		return -1;      // �� ������� �������
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// �������������� ����������� ������ ���� �� ��������� 
	// ?
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	// ������� ������������� ��� ���������� ������� ������� �����
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("�� ������� ������� ���� �������������\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC)||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons? IDR_MAINFRAME_256:IDR_MAINFRAME))
	{
		TRACE0("�� ������� ������� ������ ������������\n");
		return -1;      // �� ������� �������
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// ��������� �������� � ����������������� �������� ������������:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("�� ������� ������� ������ ���������\n");
		return -1;      // �� ������� �������
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: ������� ��� ���� �����, ���� ������ ������������ � ������ ���� �� ������ ���� �������������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// �������� ����� ������ ������������ ���� ������ Visual Studio 2005
	CDockingManager::SetDockingMode(DT_SMART);
	// �������� ����� ������ ��������������� ������� ������������ ���� ������ Visual Studio 2005
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ������� ��������� ����:
	// ��� �� ������ ���������, ��� ������ ������, ��������������� ��� ������� �����������.
	/*if (!CreateCaptionBar())
	{
		TRACE0("�� ������� ������� ��������� ����\n");
		return -1;      // �� ������� �������
	}*/

	// �������� ������� ������ ���� ������� ������������ � ������������ ���� 
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// �������� ������� (Alt+��������������) ��������� ������� ������������
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// ��������� ����������� ���������������� ������� ������������
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// ������� �������� � MainFrame, ������ ��� ������ �� �������, ������, ������ ��� ��� ������� ������������� �������, ������� � ������ ������ ����� ������������� ����������������.
	// �����, ��������� ���� � toolbar - ��� ��������� ����, � ����� � �� ������� ��������, � �� � MainFrame.
	/*CDC* dc = GetDC();
	ASSERT(dc);
	BOOL br;
	br = dc->TextOutW(190, 230, _T("CMainFrame::OnCreate Text Output..."));
	if (!br) {TRACE("CMainFrame::OnCreate TextOut error");}
	//dc->Ellipse(100,100,300,600);*/

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �������� ����� Window ��� ����� ����������� ��������� CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/*BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("�� ������� ������� ��������� ����\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
	//bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	//ASSERT(bNameValid);
	//m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	//bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	//ASSERT(bNameValid);
	//m_wndCaptionBar.SetButtonToolTip(strTemp);

	//bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	//ASSERT(bNameValid);
	//m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}*/

// ����������� CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// ����������� ��������� CMainFrame

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// �������� ������ ���� �������������
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ��������� ������ � ������������� ��� ���������� �������
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// � ��������� ������ ����������� ��������� �� ���������
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ����������� ����*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

/*void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}*/

/*void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}*/

void CMainFrame::OnOptions()
{
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// ������� ����� �� ��������
	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}
	
	// �������� ������ ��������� ��� ���� ���������������� ������� ������������
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}

void CMainFrame::SetSBText(int Pane, LPCTSTR Text1)
{
	m_wndStatusBar.SetPaneText(Pane, Text1);
}
