// AbsencesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResources.h"
#include "PositionDlg.h"
#include "afxdialogex.h"
#include "Structures.h"
#include "NmTypeOfAbsenceTable.h"
#include "AddPositionTypes.h"

// CPositionDlg dialog

BEGIN_MESSAGE_MAP(CPositionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_POSITION_ADD, &CPositionDlg::OnBnClickedPositionAdd)
	ON_BN_CLICKED(IDC_POSITION_DELETE, &CPositionDlg::OnBnClickedPositionDelete)
	ON_BN_CLICKED(ID_POSITION_OK, &CPositionDlg::OnOK)
	ON_BN_CLICKED(ID_POSITION_CANCEL, &CPositionDlg::OnCancel)

	ON_NOTIFY(NM_DBLCLK, IDC_POSITION_LIST, &CPositionDlg::OnBnClickedPositionEdit)
END_MESSAGE_MAP()

CPositionDlg::CPositionDlg(std::vector<POSITION_TYPE>& arrPositionType)
	: CDialogEx(IDD_POSITION),
	m_arrPositionType(arrPositionType)
{

}

CPositionDlg::~CPositionDlg()
{
}

void CPositionDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_POSITION_LIST, m_lscPositions_ListCtrl);

}

BOOL CPositionDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	m_lscPositions_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	CRect rect;
	m_lscPositions_ListCtrl.GetClientRect(&rect);

	int nColInterval = rect.Width();

	m_lscPositions_ListCtrl.InsertColumn(1, "Positions type", LVCFMT_LEFT, nColInterval);

	if (!LoadAllFromTableToListCtrl())
		return FALSE;

	return  TRUE;
}



// CPositionDlg message handlers

BOOL CPositionDlg::LoadAllFromTableToListCtrl()
{
	m_lscPositions_ListCtrl.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;

	for (int i = 0; i < m_arrPositionType.size(); i++)
	{
		CString departmentTypeName;
		departmentTypeName.Format("%s", m_arrPositionType[i].szPositionType);
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(departmentTypeName);

		m_lscPositions_ListCtrl.InsertItem(&lvi);

		m_lscPositions_ListCtrl.SetItemData(i, (DWORD_PTR)m_arrPositionType[i].nID); //the data of each item will be equal to it's ID

	}

	return TRUE;
}

void CPositionDlg::OnBnClickedPositionAdd()
{
	POSITION_TYPE positionType;

	CAddPositionTypes newPosition(positionType, eDialogMode_Add);
	if (newPosition.DoModal() != IDOK)
		return;

	m_arrPositionType.push_back(positionType);

	if (!LoadAllFromTableToListCtrl())
		return;
}


void CPositionDlg::OnBnClickedPositionEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION_TYPE positionType;

	int selectedRow = m_lscPositions_ListCtrl.GetSelectionMark();

	if (selectedRow == -1)
	{
		AfxMessageBox("You haven't selected any row!");
		return;
	}

	int nID = m_lscPositions_ListCtrl.GetItemData(selectedRow);

	for (int i = 0; i < m_arrPositionType.size(); i++)
	{
		if (m_arrPositionType[i].nID == nID)
		{
			positionType = m_arrPositionType[i];
			break;
		}
	}

	CAddPositionTypes position(positionType, eDialogMode_Edit);

	if (position.DoModal() == IDOK)
	{

		for (int i = 0; i < m_arrPositionType.size(); i++)
		{
			if (m_arrPositionType[i].nID == nID)
			{
				m_arrPositionType[i] = positionType;
				break;
			}
		}

	}

	if (!LoadAllFromTableToListCtrl())
		return;
}


void CPositionDlg::OnBnClickedPositionDelete()
{
	int selectedRow = m_lscPositions_ListCtrl.GetSelectionMark();

	if (selectedRow == -1)
		return;

	int nID = m_lscPositions_ListCtrl.GetItemData(selectedRow);

	for (int i = 0; i < m_arrPositionType.size(); i++)
	{
		if (m_arrPositionType[i].nID == nID)
		{
			m_arrPositionType.erase(m_arrPositionType.begin() + i);
			break;
		}
	}

	if (!LoadAllFromTableToListCtrl())
		return;
}