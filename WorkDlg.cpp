// EmployeeEducationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResources.h"
#include "WorkDlg.h"
#include "afxdialogex.h"
#include "EmployeesWorkTable.h"
#include "AddWork.h"
#include "NmTypeOfEmploymentTable.h"

BEGIN_MESSAGE_MAP(CWorkDlg, CMyTabDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_EMPLOYEE_WORK_LIST, &CWorkDlg::OnDblClicked)
END_MESSAGE_MAP()

// CEmployeeEducationDlg dialog

CWorkDlg::CWorkDlg(std::vector<EMPLOYEE_WORK>& oEmployeeWork, DialogMode eDialogMode)
	: CMyTabDialog(IDD_WORK)
	, m_arrEmployeeWork(oEmployeeWork)
{
	m_eDialogMode = eDialogMode;
}

CWorkDlg::~CWorkDlg()
{
}

void CWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EMPLOYEE_WORK_LIST, m_lcsEmployeeWork);

}

BOOL CWorkDlg::OnInitDialog()
{

	if (!__super::OnInitDialog())
		return FALSE;

	m_lcsEmployeeWork.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	CRect rect;
	m_lcsEmployeeWork.GetClientRect(&rect);

	int nColInterval = rect.Width() / 7;

	m_lcsEmployeeWork.InsertColumn(eListCtrlColumns_startDate, "From", LVCFMT_LEFT, nColInterval);
	m_lcsEmployeeWork.InsertColumn(eListCtrlColumns_endDate, "To", LVCFMT_LEFT, nColInterval);
	m_lcsEmployeeWork.InsertColumn(eListCtrlColumns_town, "Town", LVCFMT_LEFT, nColInterval);
	m_lcsEmployeeWork.InsertColumn(eListCtrlColumns_position, "Position", LVCFMT_LEFT, nColInterval);
	m_lcsEmployeeWork.InsertColumn(eListCtrlColumns_companyName, "Company Name", LVCFMT_LEFT, nColInterval);
	m_lcsEmployeeWork.InsertColumn(eListCtrlColumns_employmentType, "Employment type", LVCFMT_LEFT, nColInterval);
	m_lcsEmployeeWork.InsertColumn(eListCtrlColumns_additionalInfo, "Additional info", LVCFMT_LEFT, nColInterval);

	if (!LoadAllFromTable(m_arrEmployeeWork))
		return FALSE;

	return  TRUE;

}


BOOL CWorkDlg::LoadAllFromTable(const std::vector<EMPLOYEE_WORK>& oEmployeeWork)
{
	m_lcsEmployeeWork.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	for (int i = 0; i < oEmployeeWork.size(); i++)
	{

		lvi.iItem = i;
		lvi.iSubItem = 0;
		
		CString strEmploymentType;

		CNmTypeOfEmploymentTable employment(&theApp.m_database);
		std::vector<TYPE_OF_EMPLOYMENT> typeOfEmployment;

		if (!employment.LoadAllFromTable(typeOfEmployment, 0))
			return FALSE;

		for (int z = 0; z < typeOfEmployment.size(); z++)
		{
			if (typeOfEmployment[z].nID == oEmployeeWork[i].nEmploymentType)
			{
				strEmploymentType.Format("%s", typeOfEmployment[z].szEmploymentType);
				break;
			}
		}

		lvi.pszText = (LPTSTR)(LPCTSTR)(GetSqlDateTimeString(oEmployeeWork[i].dtFrom));
		//inserting item in the first column
		m_lcsEmployeeWork.InsertItem(&lvi);

		m_lcsEmployeeWork.SetItemText(i, eListCtrlColumns_startDate, GetSqlDateTimeString(oEmployeeWork[i].dtFrom));
		m_lcsEmployeeWork.SetItemText(i, eListCtrlColumns_endDate, GetSqlDateTimeString(oEmployeeWork[i].dtTo));
		m_lcsEmployeeWork.SetItemText(i, eListCtrlColumns_town, oEmployeeWork[i].szTownCountry);
		m_lcsEmployeeWork.SetItemText(i, eListCtrlColumns_position, oEmployeeWork[i].szPosition);
		m_lcsEmployeeWork.SetItemText(i, eListCtrlColumns_companyName, oEmployeeWork[i].szCompanyName);
		m_lcsEmployeeWork.SetItemText(i, eListCtrlColumns_employmentType, strEmploymentType);
		m_lcsEmployeeWork.SetItemText(i, eListCtrlColumns_additionalInfo, oEmployeeWork[i].szAdditionalInfo);

		m_lcsEmployeeWork.SetItemData(i, i); 

	}
	return TRUE;
}

void CWorkDlg::OnDblClicked(NMHDR * pNMHDR, LRESULT * pResult)
{
	EMPLOYEE_WORK work;

	if ((GetSelectedRow()) == NULL)
		return;

	work = *GetSelectedRow();

	CAddWork viewWork(work, eDialogMode_View);

	if (viewWork.DoModal() != IDOK)
		return;

}

void CWorkDlg::DeleteElement()
{

	int selectedData = m_lcsEmployeeWork.GetSelectionMark();
	m_lcsEmployeeWork.GetItemData(selectedData);

	m_arrEmployeeWork.erase(m_arrEmployeeWork.begin() + selectedData);

	if (!LoadAllFromTable(m_arrEmployeeWork))
		return;
}


void CWorkDlg::EditElement()
{
	EMPLOYEE_WORK* work;

	if ((GetSelectedRow()) == NULL)
		return;

	work = GetSelectedRow();

	CAddWork addWork(*work, eDialogMode_Edit);

	if (addWork.DoModal() == IDOK)
	{
		int selectedData = m_lcsEmployeeWork.GetSelectionMark();
		m_lcsEmployeeWork.GetItemData(selectedData);

		m_arrEmployeeWork[selectedData] = *work;
	}

	if (!LoadAllFromTable(m_arrEmployeeWork))
		return;

}

void CWorkDlg::AddElement()
{
	EMPLOYEE_WORK work;

	CAddWork addWork(work, eDialogMode_Add);

	if (addWork.DoModal() != IDOK)
		return;

	m_arrEmployeeWork.push_back(work);

	if (!LoadAllFromTable(m_arrEmployeeWork))
		return;
}


EMPLOYEE_WORK* CWorkDlg::GetSelectedRow()
{
	EMPLOYEE_WORK* pEmployeeWork = NULL;

	int selectedRow = m_lcsEmployeeWork.GetSelectionMark();

	if (selectedRow == -1)
	{
		AfxMessageBox("You haven't selected any row!");
		return NULL;
	}

	if (m_arrEmployeeWork.size() < m_lcsEmployeeWork.GetItemData(selectedRow))
		return NULL;
	
	pEmployeeWork = &m_arrEmployeeWork[m_lcsEmployeeWork.GetItemData(selectedRow)];

	return pEmployeeWork;

}