// AddAbsencesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddPositionTypes.h"

BEGIN_MESSAGE_MAP(CAddPositionTypes, CDialogEx)

	ON_BN_CLICKED(ID_ADD_POSITION_OK, &CAddPositionTypes::OnBnClickedOk)
	ON_BN_CLICKED(ID_ADD_ABSENCES_CANCEL, &CAddPositionTypes::OnCancel)

END_MESSAGE_MAP()

CAddPositionTypes::CAddPositionTypes(POSITION_TYPE& recPosition, DialogMode eMode)
	: CDialogEx(IDD_ADD_POSITION),
	m_recPosition(recPosition)
{
	m_eMode = eMode;
}

CAddPositionTypes::~CAddPositionTypes()
{
}

void CAddPositionTypes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ADD_POSITION_TYPENAME, m_strPositionTypeName);
}

BOOL CAddPositionTypes::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if (m_eMode == eDialogMode_Edit)
	{
		m_strPositionTypeName = m_recPosition.szPositionType;

		UpdateData(FALSE);

	}

	return TRUE;

}

void CAddPositionTypes::OnBnClickedOk()
{
	UpdateData();

	if (m_strPositionTypeName == "")
	{
		AfxMessageBox("Can't leave empty boxes!");
		return;
	}

	for (int i = 0; i < sizeof(m_strPositionTypeName); i++)
	{
		if (isdigit(m_strPositionTypeName[i]))
		{
			AfxMessageBox("Can't contain digits!");
			return;
		}
	}
	strncpy_s(m_recPosition.szPositionType, m_strPositionTypeName, sizeof(m_recPosition.szPositionType));

	__super::OnOK();
}

