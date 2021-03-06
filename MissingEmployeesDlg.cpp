// MissingEmployeesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResources.h"
#include "MissingEmployeesDlg.h"
#include "afxdialogex.h"
#include "Structures.h"
#include "NmTypeOfAbsenceTable.h"

// CMissingEmployeesDlg dialog

BEGIN_MESSAGE_MAP(CMissingEmployeesDlg, CDialogEx)
END_MESSAGE_MAP()

CMissingEmployeesDlg::CMissingEmployeesDlg(std::vector<MISSING_EMPLOYEES> & arrMissingList)
	: CDialogEx(IDD)
	, m_arrMissingList(arrMissingList)
{

}

CMissingEmployeesDlg::~CMissingEmployeesDlg()
{
}

void CMissingEmployeesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MISSING_EMPLOYEES_LIST, m_lscMissingEmployees);

}

BOOL CMissingEmployeesDlg::OnInitDialog()
{

	if (!__super::OnInitDialog())
		return FALSE;

	m_lscMissingEmployees.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	CRect rect;
	m_lscMissingEmployees.GetClientRect(&rect);

	int nColInterval = rect.Width() / 8;

	m_lscMissingEmployees.InsertColumn(eListCtrlColumns_first_name, "First name", LVCFMT_LEFT, nColInterval);
	m_lscMissingEmployees.InsertColumn(eListCtrlColumns_last_name, "Surname", LVCFMT_LEFT, nColInterval);
	m_lscMissingEmployees.InsertColumn(eListCtrlColumns_type_of_absence, "Type of absence", LVCFMT_LEFT, nColInterval);
	m_lscMissingEmployees.InsertColumn(eListCtrlColumns_start_date, "Start date", LVCFMT_LEFT, nColInterval);
	m_lscMissingEmployees.InsertColumn(eListCtrlColumns_end_date, "End date", LVCFMT_LEFT, nColInterval);
	m_lscMissingEmployees.InsertColumn(eListCtrlColumns_days_restnig, "Days resting", LVCFMT_LEFT, nColInterval);
	m_lscMissingEmployees.InsertColumn(eListCtrlColumns_department, "Department", LVCFMT_LEFT, nColInterval);
	m_lscMissingEmployees.InsertColumn(eListCtrlColumns_position, "Position", LVCFMT_LEFT, nColInterval);

	if (!LoadAll(m_arrMissingList))
		return FALSE;

	return  TRUE;

}

BOOL CMissingEmployeesDlg::LoadAll(const std::vector<MISSING_EMPLOYEES>& arrMissingEmployees)
{

	m_lscMissingEmployees.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	for (int i = 0; i < arrMissingEmployees.size(); i++)
	{

		CString strDaysCount;
		strDaysCount.Format("%d", arrMissingEmployees[i].nDaysCount);

		lvi.iItem = i;
		lvi.iSubItem = 0;

		lvi.pszText = (LPTSTR)(LPCTSTR)(arrMissingEmployees[i].szFirstName);
		//inserting item in the first column
		m_lscMissingEmployees.InsertItem(&lvi);

		m_lscMissingEmployees.SetItemText(i, eListCtrlColumns_last_name, arrMissingEmployees[i].szLastName);
		m_lscMissingEmployees.SetItemText(i, eListCtrlColumns_type_of_absence, arrMissingEmployees[i].szTypeAbsenceName);
		m_lscMissingEmployees.SetItemText(i, eListCtrlColumns_start_date, GetSqlDateTimeString(arrMissingEmployees[i].dtFrom));
		m_lscMissingEmployees.SetItemText(i, eListCtrlColumns_end_date, GetSqlDateTimeString(arrMissingEmployees[i].dtTo));
		m_lscMissingEmployees.SetItemText(i, eListCtrlColumns_days_restnig, strDaysCount);
		m_lscMissingEmployees.SetItemText(i, eListCtrlColumns_department, arrMissingEmployees[i].szDepartment);
		m_lscMissingEmployees.SetItemText(i, eListCtrlColumns_position, arrMissingEmployees[i].szDepartment);


		m_lscMissingEmployees.SetItemData(i, i);


	}
	return TRUE;
}



// CMissingEmployeesDlg message handlers
