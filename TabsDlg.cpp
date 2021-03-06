// WorkEducationForm.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResources.h"
#include "TabsDlg.h"
#include "afxdialogex.h"
#include "EducationDlg.h"
#include "MyTabDialog.h"

// CTabsDlgForm dialog

BEGIN_MESSAGE_MAP(CTabsDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABS_TAB, &CTabsDlg::OnTcnSelchangeTabsTab)
	ON_BN_CLICKED(IDOK, &CTabsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTabsDlg::OnCancel)
	ON_BN_CLICKED(IDC_TABS_EDIT_EMPLOYEE, &CTabsDlg::OnBnClickedEmployeesofftimeEditEmployee)
	ON_BN_CLICKED(IDC_TABS_DELETE_EMPLOYEE, &CTabsDlg::OnBnClickedEmployeesofftimeDeleteEmployee)
	ON_BN_CLICKED(IDC_TABS_ADD_EMPLOYEE, &CTabsDlg::OnBnClickedEmployeesofftimeAddEmployee)
END_MESSAGE_MAP()


CTabsDlg::CTabsDlg(CEmployeeData& oEmployeeData, DialogMode eDialogMode)
	: CDialogEx(IDD_TABS)
	, m_oEmployeeData(oEmployeeData)
	
{
	m_eDialogMode = eDialogMode;

	//m_EmployeeDialog = NULL;
	m_OffTimeDialog = NULL;
	m_EducationDialog = NULL;
	m_WorkDialog = NULL;
}

CTabsDlg::~CTabsDlg()
{
	if(m_EmployeeDialog != NULL)
		delete m_EmployeeDialog;

	if (m_OffTimeDialog != NULL)
		delete m_OffTimeDialog;

	if (m_EducationDialog != NULL)
		delete m_EducationDialog;

	if (m_WorkDialog != NULL)
		delete m_WorkDialog;
}


void CTabsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TABS_TAB, m_tabCtrl);
}


BOOL CTabsDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	m_EmployeeDialog = new CEmployeeDialog(m_oEmployeeData.m_recEmployee, m_eDialogMode);
	m_EmployeeDialog->Create(IDD_EMPLOYEE_SEARCH, this);

	m_OffTimeDialog = new CEmployeesViewOffTimeDlg(m_oEmployeeData.m_arrEmployeeOffTime, m_eDialogMode);
	m_OffTimeDialog->Create(IDD_EMPLOYEE_OFF_TIME, this);
	
	m_EducationDialog = new CEducationDlg(m_oEmployeeData.m_arrEducation, m_eDialogMode);
	m_EducationDialog->Create(IDD_EDUCATION, this); 

	m_WorkDialog = new CWorkDlg(m_oEmployeeData.m_arrWork, m_eDialogMode);
	m_WorkDialog->Create(IDD_WORK, this);

	/* set the child dialogs to be positioned inside tabCtrl*/

	m_tabCtrl.InsertItem(eEmployeeDialog, "Employee data");
	m_tabCtrl.InsertItem(eOffTimeDialog, "Off time");
	m_tabCtrl.InsertItem(eEducationDialog, "Education");
	m_tabCtrl.InsertItem(eWorkDialog, "Work");

	CRect rcClient, rcWindow;

	m_tabCtrl.GetClientRect(&rcClient);
	m_tabCtrl.AdjustRect(FALSE, &rcClient);

	m_tabCtrl.GetWindowRect(&rcWindow);
	ScreenToClient(rcWindow);

	rcClient.OffsetRect(rcWindow.left, rcWindow.top);

	m_OffTimeDialog->MoveWindow(&rcClient);
	m_EducationDialog->MoveWindow(&rcClient);
	m_EmployeeDialog->MoveWindow(&rcClient);
	m_WorkDialog->MoveWindow(&rcClient);

	GetDlgItem(IDC_TABS_EDIT_EMPLOYEE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TABS_DELETE_EMPLOYEE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TABS_ADD_EMPLOYEE)->ShowWindow(SW_HIDE);

	m_EmployeeDialog->ShowWindow(SW_SHOW);
	m_OffTimeDialog->ShowWindow(SW_HIDE);
	m_EducationDialog->ShowWindow(SW_HIDE);
	m_WorkDialog->ShowWindow(SW_HIDE);

	UpdateData(FALSE);

	return TRUE;

}

CMyTabDialog* CTabsDlg::GetDlgByTabIndex(const TabIndex eIndex)
{
	switch (eIndex)
	{
	case eEmployeeDialog:
		return m_EmployeeDialog;
	case eOffTimeDialog:
		return m_OffTimeDialog;
	case eEducationDialog:
		return m_EducationDialog;
	case eWorkDialog:
		return m_WorkDialog;
	default:
		return NULL;
	}

	return NULL;
}

void CTabsDlg::OnTcnSelchangeTabsTab(NMHDR * pNMHDR, LRESULT * pResult)
{

	int selected = m_tabCtrl.GetCurSel();


	if (GetDlgByTabIndex((TabIndex)selected)->ShowButtons()
		&& m_eDialogMode != eDialogMode_View)
	{
		GetDlgItem(IDC_TABS_EDIT_EMPLOYEE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TABS_DELETE_EMPLOYEE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TABS_ADD_EMPLOYEE)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_TABS_EDIT_EMPLOYEE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TABS_DELETE_EMPLOYEE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TABS_ADD_EMPLOYEE)->ShowWindow(SW_HIDE);
	}

	switch (selected)
	{
	case eEmployeeDialog:

		
		m_EmployeeDialog->ShowWindow(SW_SHOW);
		m_OffTimeDialog->ShowWindow(SW_HIDE);
		m_EducationDialog->ShowWindow(SW_HIDE);
		m_WorkDialog->ShowWindow(SW_HIDE);
		break;

	case eOffTimeDialog:

		m_EmployeeDialog->ShowWindow(SW_HIDE);
		m_OffTimeDialog->ShowWindow(SW_SHOW);
		m_EducationDialog->ShowWindow(SW_HIDE);
		m_WorkDialog->ShowWindow(SW_HIDE);
		break;

	case eEducationDialog:

		m_EmployeeDialog->ShowWindow(SW_HIDE);
		m_OffTimeDialog->ShowWindow(SW_HIDE);
		m_EducationDialog->ShowWindow(SW_SHOW);
		m_WorkDialog->ShowWindow(SW_HIDE);
		break;
	case eWorkDialog:

		m_EmployeeDialog->ShowWindow(SW_HIDE);
		m_OffTimeDialog->ShowWindow(SW_HIDE);
		m_EducationDialog->ShowWindow(SW_HIDE);
		m_WorkDialog->ShowWindow(SW_SHOW);
		break;
	}
}

void CTabsDlg::OnBnClickedOk()
{
	if(!m_EmployeeDialog->onBnClickedOK())
		return;

	CDialogEx::OnOK();
}



void CTabsDlg::OnBnClickedEmployeesofftimeEditEmployee()
{
	int selected = m_tabCtrl.GetCurSel();

	CMyTabDialog* pTab = GetDlgByTabIndex((TabIndex)selected);

	if(pTab)
		pTab->EditElement();
}


void CTabsDlg::OnBnClickedEmployeesofftimeDeleteEmployee()
{
	int selected = m_tabCtrl.GetCurSel();

	CMyTabDialog* pTab = GetDlgByTabIndex((TabIndex)selected);

	if (pTab)
		pTab->DeleteElement();

}

void CTabsDlg::OnBnClickedEmployeesofftimeAddEmployee()
{
	int selected = m_tabCtrl.GetCurSel();

	CMyTabDialog* pTab = GetDlgByTabIndex((TabIndex)selected);

	if (pTab)
		pTab->AddElement();

}
