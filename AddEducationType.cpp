// AddAbsencesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddEducationType.h"

BEGIN_MESSAGE_MAP(CAddEducationDlgType, CDialogEx)

	ON_BN_CLICKED(ID_ADD_EDUCATION_OK, &CAddEducationDlgType::OnBnClickedOk)
	ON_BN_CLICKED(ID_ADD_EDUCATION_CANCEL, &CAddEducationDlgType::OnCancel)

END_MESSAGE_MAP()

CAddEducationDlgType::CAddEducationDlgType(TYPE_OF_EDUCATION& recEducation, DialogMode eMode)
	: CDialogEx(IDD_ADD_EDUCATION),
	m_recEducation(recEducation)
{
	m_eMode = eMode;
}

CAddEducationDlgType::~CAddEducationDlgType()
{
}

void CAddEducationDlgType::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ADD_EDUCATION_TYPENAME, m_strEducationTypeName);
}

BOOL CAddEducationDlgType::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if (m_eMode == eDialogMode_Edit)
	{
		m_strEducationTypeName = m_recEducation.szEducationType;

		UpdateData(FALSE);

	}

	return TRUE;

}

void CAddEducationDlgType::OnBnClickedOk()
{
	UpdateData();

	if (m_strEducationTypeName == "")
	{
		AfxMessageBox("Can't leave empty boxes!");
		return;
	}

	for (int i = 0; i < sizeof(m_strEducationTypeName); i++)
	{
		if (isdigit(m_strEducationTypeName[i]))
		{
			AfxMessageBox("Can't contain digits!");
			return;
		}
	}
	strncpy_s(m_recEducation.szEducationType, m_strEducationTypeName, sizeof(m_recEducation.szEducationType));

	__super::OnOK();
}

