// AddAbsencesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddEmploymentType.h"

BEGIN_MESSAGE_MAP(CAddEmploymentType, CDialogEx)

	ON_BN_CLICKED(ID_ADD_EMPLOYMENT_OK, &CAddEmploymentType::OnBnClickedOk)
	ON_BN_CLICKED(ID_ADD_EMPLOYMENT_CANCEL, &CAddEmploymentType::OnCancel)

END_MESSAGE_MAP()

CAddEmploymentType::CAddEmploymentType(TYPE_OF_EMPLOYMENT& recEmployment, DialogMode eMode)
	: CDialogEx(IDD_ADD_EMPLOYMENT),
	m_recEmployment(recEmployment)
{
	m_eMode = eMode;
}

CAddEmploymentType::~CAddEmploymentType()
{
}

void CAddEmploymentType::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ADD_EMPLOYMENT_TYPENAME, m_strEmploymentTypeName);
}

BOOL CAddEmploymentType::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if (m_eMode == eDialogMode_Edit)
	{
		m_strEmploymentTypeName = m_recEmployment.szEmploymentType;

		UpdateData(FALSE);

	}

	return TRUE;

}

void CAddEmploymentType::OnBnClickedOk()
{
	UpdateData();

	if (m_strEmploymentTypeName == "")
	{
		AfxMessageBox("Can't leave empty boxes!");
		return;
	}

	for (int i = 0; i < sizeof(m_strEmploymentTypeName); i++)
	{
		if (isdigit(m_strEmploymentTypeName[i]))
		{
			AfxMessageBox("Can't contain digits!");
			return;
		}
	}
	strncpy_s(m_recEmployment.szEmploymentType, m_strEmploymentTypeName, sizeof(m_recEmployment.szEmploymentType));

	__super::OnOK();
}

