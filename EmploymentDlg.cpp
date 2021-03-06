// AbsencesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResources.h"
#include "EmploymentDlg.h"
#include "afxdialogex.h"
#include "Structures.h"
#include "NmTypeOfAbsenceTable.h"
#include "AddEmploymentType.h"

// CAddAbsencesType dialog

BEGIN_MESSAGE_MAP(CEmploymentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_EMPLOYMENT_ADD, &CEmploymentDlg::OnBnClickedEmploymentAdd)
	ON_BN_CLICKED(IDC_EMPLOYMENT_DELETE, &CEmploymentDlg::OnBnClickedEmploymentDelete)
	ON_BN_CLICKED(ID_EMPLOYMENT_OK, &CEmploymentDlg::OnOK)
	ON_BN_CLICKED(ID_EMPLOYMENT_CANCEL, &CEmploymentDlg::OnCancel)

	ON_NOTIFY(NM_DBLCLK, IDC_EMPLOYMENT_LIST, &CEmploymentDlg::OnBnClickedEmploymentEdit)
END_MESSAGE_MAP()

CEmploymentDlg::CEmploymentDlg(std::vector<TYPE_OF_EMPLOYMENT>& arrEmploymentType)
	: CDialogEx(IDD_EMPLOYMENT),
	m_arrEmploymentType(arrEmploymentType)
{

}

CEmploymentDlg::~CEmploymentDlg()
{
}

void CEmploymentDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EMPLOYMENT_LIST, m_Employment_ListCtrl);

}

BOOL CEmploymentDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	m_Employment_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	CRect rect;
	m_Employment_ListCtrl.GetClientRect(&rect);

	int nColInterval = rect.Width();

	m_Employment_ListCtrl.InsertColumn(0, "Employment type", LVCFMT_LEFT, nColInterval);

	if (!LoadAllToListCtrl())
		return FALSE;

	return  TRUE;
}



// CAddAbsencesType message handlers

BOOL CEmploymentDlg::LoadAllToListCtrl()
{
	m_Employment_ListCtrl.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;

	for (int i = 0; i < m_arrEmploymentType.size(); i++)
	{
		CString employmentTypeName;
		employmentTypeName.Format("%s", m_arrEmploymentType[i].szEmploymentType);
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(employmentTypeName);

		m_Employment_ListCtrl.InsertItem(&lvi);

		m_Employment_ListCtrl.SetItemData(i, (DWORD_PTR)m_arrEmploymentType[i].nID); //the data of each item will be equal to it's ID

	}

	return TRUE;
}

void CEmploymentDlg::OnBnClickedEmploymentAdd()
{
	TYPE_OF_EMPLOYMENT employmentType;

	CAddEmploymentType newEmployment(employmentType, eDialogMode_Add);
	if (newEmployment.DoModal() != IDOK)
		return;

	m_arrEmploymentType.push_back(employmentType);

	if (!LoadAllToListCtrl())
		return;
}


void CEmploymentDlg::OnBnClickedEmploymentEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	TYPE_OF_EMPLOYMENT employmentType;

	int selectedRow = m_Employment_ListCtrl.GetSelectionMark();

	if (selectedRow == -1)
	{
		AfxMessageBox("You haven't selected any row!");
		return;
	}

	int nID = m_Employment_ListCtrl.GetItemData(selectedRow);

	for (int i = 0; i < m_arrEmploymentType.size(); i++)
	{
		if (m_arrEmploymentType[i].nID == nID)
		{
			employmentType = m_arrEmploymentType[i];
			break;
		}
	}

	CAddEmploymentType employment(employmentType, eDialogMode_Edit);

	if (employment.DoModal() == IDOK)
	{

		for (int i = 0; i < m_arrEmploymentType.size(); i++)
		{
			if (m_arrEmploymentType[i].nID == nID)
			{
				m_arrEmploymentType[i] = employmentType;
				break;
			}
		}

	}

	if (!LoadAllToListCtrl())
		return;
}


void CEmploymentDlg::OnBnClickedEmploymentDelete()
{
	int selectedRow = m_Employment_ListCtrl.GetSelectionMark();

	if (selectedRow == -1)
		return;

	int nID = m_Employment_ListCtrl.GetItemData(selectedRow);

	for (int i = 0; i < m_arrEmploymentType.size(); i++)
	{
		if (m_arrEmploymentType[i].nID == nID)
		{
			m_arrEmploymentType.erase(m_arrEmploymentType.begin() + i);
			break;
		}
	}

	if (!LoadAllToListCtrl())
		return;
}