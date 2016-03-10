// VWMFC.h : главный файл заголовка для приложения VWMFC
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы

// CVWMFCApp:
// О реализации данного класса см. VWMFC.cpp

class CVWMFCApp : public CWinAppEx
{
public:
	CVWMFCApp();
	CStdioFile fIFile;
	CString sIFilePath;  // todo: Проверить как инициализровать переменные в объявлении, "в пределах класса могут быть инициализированы только статические константные данные-члены целого типа", почему только целого?
	CStringList slFileContentList;
	void ReadFile();

// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
public:
	BOOL m_bHiColorIcons;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()  // После этого макроса для public переменных, обязателен спецификатор public
	
};

extern CVWMFCApp theApp;