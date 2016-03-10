// VWMFC.h : ������� ���� ��������� ��� ���������� VWMFC
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������

// CVWMFCApp:
// � ���������� ������� ������ ��. VWMFC.cpp

class CVWMFCApp : public CWinAppEx
{
public:
	CVWMFCApp();
	CStdioFile fIFile;
	CString sIFilePath;  // todo: ��������� ��� ��������������� ���������� � ����������, "� �������� ������ ����� ���� ���������������� ������ ����������� ����������� ������-����� ������ ����", ������ ������ ������?
	CStringList slFileContentList;
	void ReadFile();

// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������
public:
	BOOL m_bHiColorIcons;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()  // ����� ����� ������� ��� public ����������, ���������� ������������ public
	
};

extern CVWMFCApp theApp;