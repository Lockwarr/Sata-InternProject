// AbsencesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResources.h"
#include "DepartmentDlg.h"
#include "afxdialogex.h"
#include "Structures.h"
#include "NmTypeOfAbsenceTable.h"
#include "AddDepartmentTypes.h"

// CDepartmentDlg dialog

BEGIN_MESSAGE_MAP(CDepartmentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DEPARTMENT_ADD, &CDepartmentDlg::OnBnClickedDepartmentAdd)
	ON_BN_CLICKED(IDC_DEPARTMENT_DELETE, &CDepartmentDlg::OnBnClickedDepartmentDelete)
	ON_BN_CLICKED(ID_DEPARTMENT_OK, &CDepartmentDlg::OnOK)
	ON_BN_CLICKED(ID_DEPARTMENT_CANCEL, &CDepartmentDlg::OnCancel)

	ON_NOTIFY(NM_DBLCLK, IDC_DEPARTMENT_LIST, &CDepartmentDlg::OnBnClickedDepartmentEdit)
END_MESSAGE_MAP()

CDepartmentDlg::CDepartmentDlg(std::vector<DEPARTMENT_TYPE>& arrDepartmentType)
	: CDialogEx(IDD_DEPARTMENT),
	m_arrDepartmentType(arrDepartmentType)
{

}

CDepartmentDlg::~CDepartmentDlg()
{
}

void CDepartmentDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DEPARTMENT_LIST, m_lscDepartments_ListCtrl);

}

BOOL CDepartmentDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	m_lscDepartments_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	CRect rect;
	m_lscDepartments_ListCtrl.GetClientRect(&rect);

	int nColInterval = rect.Width();

	m_lscDepartments_ListCtrl.InsertColumn(1, "Departments type", LVCFMT_LEFT, nColInterval);

	if (!LoadAllFromTableToListCtrl())
		return FALSE;

	return  TRUE;
}



// CDepartmentDlg message handlers

BOOL CDepartmentDlg::LoadAllFromTableToListCtrl()
{
	m_lscDepartments_ListCtrl.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;

	for (int i = 0; i < m_arrDepartmentType.size(); i++)
	{
		CString departmentTypeName;
		departmentTypeName.Format("%s", m_arrDepartmentType[i].szDepartmentType);
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(departmentTypeName);

		m_lscDepartments_ListCtrl.InsertItem(&lvi);

		m_lscDepartments_ListCtrl.SetItemData(i, (DWORD_PTR)m_arrDepartmentType[i].nID); //the data of each item will be equal to it's ID

	}

	return TRUE;
}

void CDepartmentDlg::OnBnClickedDepartmentAdd()
{
	DEPARTMENT_TYPE departmentType;

	CAddDepartmentTypes newDepartment(departmentType, eDialogMode_Add);
	if (newDepartment.DoModal() != IDOK)
		return;

	m_arrDepartmentType.push_back(departmentType);

	if (!LoadAllFromTableToListCtrl())
		return;
}


void CDepartmentDlg::OnBnClickedDepartmentEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	DEPARTMENT_TYPE departmentType;

	int selectedRow = m_lscDepartments_ListCtrl.GetSelectionMark();

	if (selectedRow == -1)
	{
		AfxMessageBox("You haven't selected any row!");
		return;
	}

	int nID = m_lscDepartments_ListCtrl.GetItemData(selectedRow);

	for (int i = 0; i < m_arrDepartmentType.size(); i++)
	{
		if (m_arrDepartmentType[i].nID == nID)
		{
			departmentType = m_arrDepartmentType[i];
			break;
		}
	}

	CAddDepartmentTypes absence(departmentType, eDialogMode_Edit);

	if (absence.DoModal() == IDOK)
	{

		for (int i = 0; i < m_arrDepartmentType.size(); i++)
		{
			if (m_arrDepartmentType[i].nID == nID)
			{
				m_arrDepartmentType[i] = departmentType;
				break;
			}
		}

	}

	if (!LoadAllFromTableToListCtrl())
		return;
}


void CDepartmentDlg::OnBnClickedDepartmentDelete()
{
	int selectedRow = m_lscDepartments_ListCtrl.GetSelectionMark();

	if (selectedRow == -1)
		return;

	int nID = m_lscDepartments_ListCtrl.GetItemData(selectedRow);

	for (int i = 0; i < m_arrDepartmentType.size(); i++)
	{
		if (m_arrDepartmentType[i].nID == nID)
		{
			m_arrDepartmentType.erase(m_arrDepartmentType.begin() + i);
			break;
		}
	}

	if (!LoadAllFromTableToListCtrl())
		return;
}