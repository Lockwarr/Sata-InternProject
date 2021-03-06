// EmployeeEducationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResources.h"
#include "EducationDlg.h"
#include "afxdialogex.h"
#include "EmployeesEducationTable.h"
#include "NmTypeOfEducationTable.h"
#include "AddEducationDlg.h"

BEGIN_MESSAGE_MAP(CEducationDlg, CMyTabDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_EMPLOYEE_EDUCATION_LIST, &CEducationDlg::OnDblClicked)
END_MESSAGE_MAP()
// CEmployeeEducationDlg dialog

CEducationDlg::CEducationDlg(std::vector<EMPLOYEE_EDUCATION>& arrEmployeeEducation, DialogMode eDialogMode)
	: CMyTabDialog(IDD_EDUCATION)
	, m_arrEmployeeEducation(arrEmployeeEducation)
{
	m_eDialogMode = eDialogMode;
}

CEducationDlg::~CEducationDlg()
{
}

void CEducationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EMPLOYEE_EDUCATION_LIST, m_lscEmployeeEducation);

}

BOOL CEducationDlg::OnInitDialog()
{

	if (!__super::OnInitDialog())
		return FALSE;

	m_lscEmployeeEducation.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	CRect rect;
	m_lscEmployeeEducation.GetClientRect(&rect);

	int nColInterval = rect.Width() / 7;

	m_lscEmployeeEducation.InsertColumn(eListCtrlColumns_startDate, "From", LVCFMT_LEFT, nColInterval);
	m_lscEmployeeEducation.InsertColumn(eListCtrlColumns_endDate, "To", LVCFMT_LEFT, nColInterval);
	m_lscEmployeeEducation.InsertColumn(eListCtrlColumns_educationType, "Education Type", LVCFMT_LEFT, nColInterval);
	m_lscEmployeeEducation.InsertColumn(eListCtrlColumns_specialty, "Specialty", LVCFMT_LEFT, nColInterval);
	m_lscEmployeeEducation.InsertColumn(eListCtrlColumns_town, "Town", LVCFMT_LEFT, nColInterval);
	m_lscEmployeeEducation.InsertColumn(eListCtrlColumns_schoolName, "School name", LVCFMT_LEFT, nColInterval);
	m_lscEmployeeEducation.InsertColumn(eListCtrlColumns_additionalInfo, "Additional info", LVCFMT_LEFT, nColInterval);

	if (!LoadAll(m_arrEmployeeEducation))
		return FALSE;

	return  TRUE;

}

BOOL CEducationDlg::LoadAll(const std::vector<EMPLOYEE_EDUCATION>& oEmployeeEducation)
{
	m_lscEmployeeEducation.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	for (int i = 0; i < oEmployeeEducation.size(); i++)
	{
		CString strEducationType;

		CNmTypeOfEducationTable educations(&theApp.m_database);
		std::vector<TYPE_OF_EDUCATION> typeOfEducation;

		if (!educations.LoadAllFromTable(typeOfEducation, 0))
			return FALSE;

		for (int z = 0; z < typeOfEducation.size(); z++)
		{
			if (typeOfEducation[z].nID == oEmployeeEducation[i].nEducationType)
			{
				strEducationType.Format("%s", typeOfEducation[z].szEducationType);
				break;
			}
		}


		lvi.iItem = i;
		lvi.iSubItem = 0;

		lvi.pszText = (LPTSTR)(LPCTSTR)(GetSqlDateTimeString(oEmployeeEducation[i].dtFrom));
		//inserting item in the first column
		m_lscEmployeeEducation.InsertItem(&lvi);

		m_lscEmployeeEducation.SetItemText(i, eListCtrlColumns_startDate, GetSqlDateTimeString(oEmployeeEducation[i].dtFrom));
		m_lscEmployeeEducation.SetItemText(i, eListCtrlColumns_endDate, GetSqlDateTimeString(oEmployeeEducation[i].dtTo));
		m_lscEmployeeEducation.SetItemText(i, eListCtrlColumns_educationType, strEducationType);
		m_lscEmployeeEducation.SetItemText(i, eListCtrlColumns_specialty, oEmployeeEducation[i].szSpecialty);
		m_lscEmployeeEducation.SetItemText(i, eListCtrlColumns_town, oEmployeeEducation[i].szTownCountry);
		m_lscEmployeeEducation.SetItemText(i, eListCtrlColumns_schoolName, oEmployeeEducation[i].szSchoolName);
		m_lscEmployeeEducation.SetItemText(i, eListCtrlColumns_additionalInfo, oEmployeeEducation[i].szAdditionalInfo);
		m_lscEmployeeEducation.SetItemText(i, eListCtrlColumns_additionalInfo, oEmployeeEducation[i].szAdditionalInfo);


		m_lscEmployeeEducation.SetItemData(i, i);

	}
	return TRUE;
}

void CEducationDlg::OnDblClicked(NMHDR * pNMHDR, LRESULT * pResult)
{
	EMPLOYEE_EDUCATION education;
	EMPLOYEE_EDUCATION* pEmployeeEducation = NULL;

	if ((GetSelectedRow()) == NULL)
		return;

	education = *GetSelectedRow();

	CAddEducationDlg viewEducation(education, eDialogMode_View);

	if (viewEducation.DoModal() != IDOK)
		return;

}

void CEducationDlg::DeleteElement()
{
	//delete
	int selectedData = m_lscEmployeeEducation.GetSelectionMark();
	m_lscEmployeeEducation.GetItemData(selectedData);

	m_arrEmployeeEducation.erase(m_arrEmployeeEducation.begin() + selectedData);

	if (!LoadAll(m_arrEmployeeEducation))
		return;
}

void CEducationDlg::EditElement()
{
	EMPLOYEE_EDUCATION* education;

	if ((GetSelectedRow()) == NULL)
		return;

	education = GetSelectedRow();

	CAddEducationDlg addEducation(*education, eDialogMode_Edit); 

	if (addEducation.DoModal() == IDOK)	
	{
		int selectedData = m_lscEmployeeEducation.GetSelectionMark();
		m_lscEmployeeEducation.GetItemData(selectedData);

		m_arrEmployeeEducation[selectedData] = *education;
	}

	if (!LoadAll(m_arrEmployeeEducation))
		return;

}


void CEducationDlg::AddElement()
{
	EMPLOYEE_EDUCATION education;

	CAddEducationDlg addEducation(education, eDialogMode_Add);

	if (addEducation.DoModal() != IDOK)
		return;

	m_arrEmployeeEducation.push_back(education);

	if (!LoadAll(m_arrEmployeeEducation))
		return;
}

EMPLOYEE_EDUCATION* CEducationDlg::GetSelectedRow()
{
	EMPLOYEE_EDUCATION* pEmployeeEducation = NULL;

	int selectedRow = m_lscEmployeeEducation.GetSelectionMark();

	if (selectedRow == -1)
	{
		AfxMessageBox("You haven't selected any row!");
		return NULL;
	}

	if (m_arrEmployeeEducation.size() < m_lscEmployeeEducation.GetItemData(selectedRow))
		return NULL;

	pEmployeeEducation = &m_arrEmployeeEducation[m_lscEmployeeEducation.GetItemData(selectedRow)];
	return pEmployeeEducation;

}
