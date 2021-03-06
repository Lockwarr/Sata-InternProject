
// HumanResources.h : main header file for the HumanResources application
//
#pragma once

#include "odbcinst.h"
#include "afxdb.h"
#include "resource.h"       // main symbols

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

class CHumanResourcesApp : public CWinAppEx
{
public:
	CHumanResourcesApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	void OnAppAbout();

	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	DECLARE_MESSAGE_MAP()

public:

	CDatabase m_database;

	CString sDriver = "ODBC Driver 13 for SQL Server";
	CString sServer = "DT-VN00316\\DANGELOV";
	CString DB = "TEST_DB";

};

CString GetSqlDateTimeString(const DBTIMESTAMP& dtDate);
DBTIMESTAMP GetDateTimeFromSqlString(const CString& strDate);

extern CHumanResourcesApp theApp;
