#pragma once
#include "EmployeesViewOffTimeDlg.h"
#include "EmployeeDialog.h"
#include "HumanResourcesView.h"
#include "EducationDlg.h"
#include "WorkDlg.h"

// CTabsDlgForm dialog

class CTabsDlg : public CDialogEx 
{

	enum { IDD = IDD_TABS };

	enum TabIndex
	{
		eEmployeeDialog = 0,
		eOffTimeDialog = 1,
		eEducationDialog = 2,
		eWorkDialog = 3 
	};

public:
	CTabsDlg(CEmployeeData& oEmployeeData, DialogMode eDialogMode);  // standard constructor
	virtual ~CTabsDlg();

	// Dialog Data

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

protected:

	void OnTcnSelchangeTabsTab(NMHDR *pNMHDR, LRESULT *pResult);

	CMyTabDialog* GetDlgByTabIndex(const TabIndex eIndex);

protected:
	CEmployeeData& m_oEmployeeData;

	CEmployeeDialog * m_EmployeeDialog;

	CEmployeesViewOffTimeDlg* m_OffTimeDialog;

	CEducationDlg *m_EducationDialog;

	CWorkDlg *m_WorkDialog;

	DialogMode m_eDialogMode;
	
	CTabCtrl m_tabCtrl;

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedEmployeesofftimeEditEmployee();
	afx_msg void OnBnClickedEmployeesofftimeDeleteEmployee();
	afx_msg void OnBnClickedEmployeesofftimeAddEmployee();
};

