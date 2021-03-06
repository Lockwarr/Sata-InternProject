// AddAbsencesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddDepartmentTypes.h"

BEGIN_MESSAGE_MAP(CAddDepartmentTypes, CDialogEx)

	ON_BN_CLICKED(ID_ADD_DEPARTMENT_OK, &CAddDepartmentTypes::OnBnClickedOk)
	ON_BN_CLICKED(ID_ADD_DEPARTMENT_CANCEL, &CAddDepartmentTypes::OnCancel)

END_MESSAGE_MAP()

CAddDepartmentTypes::CAddDepartmentTypes(DEPARTMENT_TYPE& recDepartment, DialogMode eMode)
	: CDialogEx(IDD_ADD_DEPARTMENT),
	m_recDepartment(recDepartment)
{
	m_eMode = eMode;
}

CAddDepartmentTypes::~CAddDepartmentTypes()
{
}

void CAddDepartmentTypes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ADD_DEPARTMENT_TYPENAME, m_strDepartmentTypeName);
}

BOOL CAddDepartmentTypes::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if (m_eMode == eDialogMode_Edit)
	{
		m_strDepartmentTypeName = m_recDepartment.szDepartmentType;

		UpdateData(FALSE);

	}

	return TRUE;

}

void CAddDepartmentTypes::OnBnClickedOk()
{
	UpdateData();

	if (m_strDepartmentTypeName == "")
	{
		AfxMessageBox("Can't leave empty boxes!");
		return;
	}

	for (int i = 0; i < sizeof(m_strDepartmentTypeName); i++)
	{
		if (isdigit(m_strDepartmentTypeName[i]))
		{
			AfxMessageBox("Can't contain digits!");
			return;
		}
	}
	strncpy_s(m_recDepartment.szDepartmentType, m_strDepartmentTypeName, sizeof(m_recDepartment.szDepartmentType));

	__super::OnOK();
}

