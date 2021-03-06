// EmployeesViewOffTimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResourcesView.h"
#include "EmployeesViewOffTimeDlg.h"
#include "afxdialogex.h"
#include "Structures.h"
#include "EmployeesOffTable.h"
#include "NmTypeOfAbsenceTable.h"
#include "MyTabDialog.h"

// CEmployeesViewOffTimeDlg dialog

BEGIN_MESSAGE_MAP(CEmployeesViewOffTimeDlg, CMyTabDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_EmployeesOffTime_LIST1, &CEmployeesViewOffTimeDlg::OnDblClicked)

	ON_BN_CLICKED(IDC_EmployeesOffTime_OK, &CEmployeesViewOffTimeDlg::OnOK)
	ON_BN_CLICKED(IDC_EmployeesOffTime_CANCEL, &CEmployeesViewOffTimeDlg::OnCancel)
END_MESSAGE_MAP()


CEmployeesViewOffTimeDlg::CEmployeesViewOffTimeDlg(std::vector<EMPLOYEE_OFF_TIME>& arrEmployeeOffTime, DialogMode eDialogMode)
	: CMyTabDialog(IDD_EMPLOYEE_OFF_TIME)
	, m_arrEmployeeOffTime(arrEmployeeOffTime)
{
	m_eDialogMode = eDialogMode;
}

CEmployeesViewOffTimeDlg::~CEmployeesViewOffTimeDlg()
{
}

void CEmployeesViewOffTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EmployeesOffTime_LIST1, m_lscEmployeeOffTime);

}

BOOL CEmployeesViewOffTimeDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	m_lscEmployeeOffTime.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	CRect rect;
	m_lscEmployeeOffTime.GetClientRect(&rect);

	int nColInterval = rect.Width() / 4;

	m_lscEmployeeOffTime.InsertColumn(eListCtrlColumns_typeOfAbsence, "Type of Absence", LVCFMT_LEFT, nColInterval);
	m_lscEmployeeOffTime.InsertColumn(eListCtrlColumns_startDate, "From", LVCFMT_LEFT, nColInterval);
	m_lscEmployeeOffTime.InsertColumn(eListCtrlColumns_endDate, "To", LVCFMT_LEFT, nColInterval);
	m_lscEmployeeOffTime.InsertColumn(eListCtrlColumns_daysResting, "Days count", LVCFMT_LEFT, nColInterval);


	if (!LoadAllFromTable(m_arrEmployeeOffTime))
		return FALSE;

	return  TRUE;
}


BOOL CEmployeesViewOffTimeDlg::LoadAllFromTable(const std::vector<EMPLOYEE_OFF_TIME>& oEmployeeOffTime)
{
	m_lscEmployeeOffTime.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	for (int i = 0; i < oEmployeeOffTime.size(); i++)
	{
		CString strAbsenceType;

		CNmTypeOfAbsenceTable absences(&theApp.m_database);
		std::vector<TYPE_OF_ABSENCE> typeOfAbsence;

		if (!absences.LoadAllFromTable(typeOfAbsence, oEmployeeOffTime[i].nEmployeeID))
			return FALSE;

		for (int z = 0; z < typeOfAbsence.size(); z++)
		{
			if (typeOfAbsence[z].nID == oEmployeeOffTime[i].nTypeAbsence)
			{
				strAbsenceType.Format("%s", typeOfAbsence[z].szAbsenceType);
				break;
			}
		}


		lvi.iItem = i;
		lvi.iSubItem = 0;

		lvi.pszText = (LPTSTR)(LPCTSTR)(strAbsenceType);
		//inserting item in the first column
		m_lscEmployeeOffTime.InsertItem(&lvi);

		CString strDaysCount;
		strDaysCount.Format("%d", oEmployeeOffTime[i].nDaysCount);

		m_lscEmployeeOffTime.SetItemText(i, eListCtrlColumns_startDate, GetSqlDateTimeString(oEmployeeOffTime[i].dtFrom));
		m_lscEmployeeOffTime.SetItemText(i, eListCtrlColumns_endDate, GetSqlDateTimeString(oEmployeeOffTime[i].dtTo));
		m_lscEmployeeOffTime.SetItemText(i, eListCtrlColumns_daysResting, strDaysCount);

		m_lscEmployeeOffTime.SetItemData(i, i);

	}
	return TRUE;

}


void CEmployeesViewOffTimeDlg::OnDblClicked(NMHDR * pNMHDR, LRESULT * pResult)
{

	EMPLOYEE_OFF_TIME offTime;

	if ((GetSelectedRow()) == NULL)
		return;

	offTime = *GetSelectedRow();

	CAddRestTimeDlg datePicks(offTime, eDialogMode_View);

	if (datePicks.DoModal() != IDOK)
		return;

}


void CEmployeesViewOffTimeDlg::AddElement()
{
	EMPLOYEE_OFF_TIME employeeOffTime;

	CAddRestTimeDlg viewOffTime(employeeOffTime, eDialogMode_Add);

	if (viewOffTime.DoModal() != IDOK)
		return;

	m_arrEmployeeOffTime.push_back(employeeOffTime);

	if (!LoadAllFromTable(m_arrEmployeeOffTime))
		return;
}


void CEmployeesViewOffTimeDlg::EditElement()
{
	EMPLOYEE_OFF_TIME* offTime;

	if (GetSelectedRow() == NULL)
		return;

	offTime = GetSelectedRow();

	CAddRestTimeDlg addRestTime(*offTime, eDialogMode_Edit);

	if (addRestTime.DoModal() == IDOK)
	{
		int selectedData = m_lscEmployeeOffTime.GetSelectionMark();
		m_lscEmployeeOffTime.GetItemData(selectedData);

		m_arrEmployeeOffTime[selectedData] = *offTime;
	}

	if (!LoadAllFromTable(m_arrEmployeeOffTime))
		return;

}

void CEmployeesViewOffTimeDlg::DeleteElement()
{
	EMPLOYEE_OFF_TIME offTime;

	if (GetSelectedRow() == NULL)
		return;

	offTime = *GetSelectedRow();



	//delete
	int selectedData = m_lscEmployeeOffTime.GetSelectionMark();
	m_lscEmployeeOffTime.GetItemData(selectedData);

	m_arrEmployeeOffTime.erase(m_arrEmployeeOffTime.begin() + selectedData);


	if (!LoadAllFromTable(m_arrEmployeeOffTime))
		return;
}

EMPLOYEE_OFF_TIME* CEmployeesViewOffTimeDlg::GetSelectedRow()
{
	EMPLOYEE_OFF_TIME* pEmployeeOffTime = NULL;
	int selectedRow = m_lscEmployeeOffTime.GetSelectionMark();

	if (selectedRow == -1)
	{
		AfxMessageBox("You haven't selected any row!");
		return NULL;
	}

	if (m_arrEmployeeOffTime.size() < m_lscEmployeeOffTime.GetItemData(selectedRow))
		return NULL;

	pEmployeeOffTime = &m_arrEmployeeOffTime[m_lscEmployeeOffTime.GetItemData(selectedRow)];

	return pEmployeeOffTime;

}
