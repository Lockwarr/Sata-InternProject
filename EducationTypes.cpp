// AbsencesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResources.h"
#include "EducationTypes.h"
#include "afxdialogex.h"
#include "Structures.h"
#include "NmTypeOfAbsenceTable.h"
#include "AddEducationType.h"

// CAddAbsencesType dialog

BEGIN_MESSAGE_MAP(CEducationTypes, CDialogEx)
	ON_BN_CLICKED(IDC_EDUCATION_TYPES_ADD, &CEducationTypes::OnBnClickedEducationAdd)
	ON_BN_CLICKED(IDC_EDUCATION_TYPES_DELETE, &CEducationTypes::OnBnClickedEducationDelete)
	ON_BN_CLICKED(ID_EDUCATION_TYPES_OK, &CEducationTypes::OnOK)
	ON_BN_CLICKED(ID_EDUCATION_TYPES_CANCEL, &CEducationTypes::OnCancel)

	ON_NOTIFY(NM_DBLCLK, IDC_EDUCATION_TYPES_LIST, &CEducationTypes::OnBnClickedEducationEdit)
END_MESSAGE_MAP()

CEducationTypes::CEducationTypes(std::vector<TYPE_OF_EDUCATION>& arrEducationType)
	: CDialogEx(IDD_EDUCATION_TYPES),
	m_arrEducationType(arrEducationType)
{

}

CEducationTypes::~CEducationTypes()
{
}

void CEducationTypes::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDUCATION_TYPES_LIST, m_lscEducation);

}

BOOL CEducationTypes::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	m_lscEducation.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	CRect rect;
	m_lscEducation.GetClientRect(&rect);

	int nColInterval = rect.Width();

	m_lscEducation.InsertColumn(0, "Education type", LVCFMT_LEFT, nColInterval);

	if (!LoadAllFromTableToListCtrl())
		return FALSE;

	return  TRUE;
}



// CAddAbsencesType message handlers

BOOL CEducationTypes::LoadAllFromTableToListCtrl()
{
	m_lscEducation.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;

	for (int i = 0; i < m_arrEducationType.size(); i++)
	{
		CString educationTypeName;
		educationTypeName.Format("%s", m_arrEducationType[i].szEducationType);
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(educationTypeName);

		m_lscEducation.InsertItem(&lvi);

		m_lscEducation.SetItemData(i, (DWORD_PTR)m_arrEducationType[i].nID); //the data of each item will be equal to it's ID

	}

	return TRUE;
}

void CEducationTypes::OnBnClickedEducationAdd()
{
	TYPE_OF_EDUCATION educationType;

	CAddEducationDlgType newEducation(educationType, eDialogMode_Add);
	if (newEducation.DoModal() != IDOK)
		return;

	m_arrEducationType.push_back(educationType);

	if (!LoadAllFromTableToListCtrl())
		return;
}


void CEducationTypes::OnBnClickedEducationEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	TYPE_OF_EDUCATION educationType;

	int selectedRow = m_lscEducation.GetSelectionMark();

	if (selectedRow == -1)
	{
		AfxMessageBox("You haven't selected any row!");
		return;
	}

	int nID = m_lscEducation.GetItemData(selectedRow);

	for (int i = 0; i < m_arrEducationType.size(); i++)
	{
		if (m_arrEducationType[i].nID == nID)
		{
			educationType = m_arrEducationType[i];
			break;
		}
	}

	CAddEducationDlgType newEducation(educationType, eDialogMode_Edit);

	if (newEducation.DoModal() == IDOK)
	{

		for (int i = 0; i < m_arrEducationType.size(); i++)
		{
			if (m_arrEducationType[i].nID == nID)
			{
				m_arrEducationType[i] = educationType;
				break;
			}
		}

	}

	if (!LoadAllFromTableToListCtrl())
		return;
}


void CEducationTypes::OnBnClickedEducationDelete()
{
	int selectedRow = m_lscEducation.GetSelectionMark();

	if (selectedRow == -1)
		return;

	int nID = m_lscEducation.GetItemData(selectedRow);

	for (int i = 0; i < m_arrEducationType.size(); i++)
	{
		if (m_arrEducationType[i].nID == nID)
		{
			m_arrEducationType.erase(m_arrEducationType.begin() + i);
			break;
		}
	}

	if (!LoadAllFromTableToListCtrl())
		return;
}