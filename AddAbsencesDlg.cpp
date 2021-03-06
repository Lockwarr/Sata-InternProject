// AbsencesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResources.h"
#include "AddAbsencesDlg.h"
#include "afxdialogex.h"
#include "Structures.h"
#include "NmTypeOfAbsenceTable.h"
#include "AddAbsencesTypes.h"

// CAddAbsencesDlg dialog

BEGIN_MESSAGE_MAP(CAddAbsencesDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ABSENCES_TYPES_ADD, &CAddAbsencesDlg::OnBnClickedAbsencesAdd)
	ON_BN_CLICKED(IDC_ABSENCES_TYPES_DELETE, &CAddAbsencesDlg::OnBnClickedAbsencesDelete)
	ON_BN_CLICKED(ID_ABSENCES_TYPES_OK, &CAddAbsencesDlg::OnOK)
	ON_BN_CLICKED(ID_ABSENCES_TYPES_CANCEL, &CAddAbsencesDlg::OnCancel)

	ON_NOTIFY(NM_DBLCLK, IDC_ABSENCES_TYPES_LIST, &CAddAbsencesDlg::OnBnClickedAbsencesEdit)
END_MESSAGE_MAP() 

CAddAbsencesDlg::CAddAbsencesDlg(std::vector<TYPE_OF_ABSENCE>& arrAbsenceType)
 	: CDialogEx(IDD_ABSENCES_TYPES),
	m_arrAbsenceType(arrAbsenceType)
{

}

CAddAbsencesDlg::~CAddAbsencesDlg()
{
}

void CAddAbsencesDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ABSENCES_LIST, m_lscAbsences_ListCtrl);

}

BOOL CAddAbsencesDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	m_lscAbsences_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	CRect rect;
	m_lscAbsences_ListCtrl.GetClientRect(&rect);

	int nColInterval = rect.Width();

	m_lscAbsences_ListCtrl.InsertColumn(1, "Absence type", LVCFMT_LEFT, nColInterval);

	if (!LoadAllFromTableToListCtrl())
		return FALSE;

	return  TRUE;
}



// CAddAbsencesDlg message handlers

BOOL CAddAbsencesDlg::LoadAllFromTableToListCtrl()
{
	m_lscAbsences_ListCtrl.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;

	for (int i = 0; i < m_arrAbsenceType.size(); i++)
	{
		CString absenceTypeName;
		absenceTypeName.Format("%s", m_arrAbsenceType[i].szAbsenceType);
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(absenceTypeName);

		m_lscAbsences_ListCtrl.InsertItem(&lvi);

		m_lscAbsences_ListCtrl.SetItemData(i, (DWORD_PTR)m_arrAbsenceType[i].nID); //the data of each item will be equal to it's ID

	}

	return TRUE;
}

void CAddAbsencesDlg::OnBnClickedAbsencesAdd()
{
	TYPE_OF_ABSENCE absenceType;

	CAddAbsencesTypes newAbsence(absenceType, eDialogMode_Add);
	if (newAbsence.DoModal() != IDOK)
		return;

	m_arrAbsenceType.push_back(absenceType);

	if (!LoadAllFromTableToListCtrl())
		return;
}


void CAddAbsencesDlg::OnBnClickedAbsencesEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	TYPE_OF_ABSENCE absenceType;

	int selectedRow = m_lscAbsences_ListCtrl.GetSelectionMark();

	if (selectedRow == -1)
	{
		AfxMessageBox("You haven't selected any row!");
		return;
	}

	int nID = m_lscAbsences_ListCtrl.GetItemData(selectedRow);

	for (int i = 0; i < m_arrAbsenceType.size(); i++)
	{
		if (m_arrAbsenceType[i].nID == nID)
		{
			absenceType = m_arrAbsenceType[i];
			break;
		}
	}

	CAddAbsencesTypes absence(absenceType, eDialogMode_Edit);

	if (absence.DoModal() == IDOK)
	{

		for (int i = 0; i < m_arrAbsenceType.size(); i++)
		{
			if (m_arrAbsenceType[i].nID == nID)
			{
				m_arrAbsenceType[i] = absenceType;
				break;
			}
		}

	}

	if (!LoadAllFromTableToListCtrl())
		return;
}


void CAddAbsencesDlg::OnBnClickedAbsencesDelete()
{
	int selectedRow = m_lscAbsences_ListCtrl.GetSelectionMark();

	if (selectedRow == -1)
		return;

	int nID = m_lscAbsences_ListCtrl.GetItemData(selectedRow);

	for (int i = 0; i < m_arrAbsenceType.size(); i++)
	{
		if (m_arrAbsenceType[i].nID == nID)
		{
			m_arrAbsenceType.erase(m_arrAbsenceType.begin() + i);
			break;
		}
	}

	if (!LoadAllFromTableToListCtrl())
		return;
}