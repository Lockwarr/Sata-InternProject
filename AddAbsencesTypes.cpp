// AddAbsencesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddAbsencesTypes.h"

BEGIN_MESSAGE_MAP(CAddAbsencesTypes, CDialogEx)

	ON_BN_CLICKED(ID_ADD_ABSENCES_OK, &CAddAbsencesTypes::OnBnClickedOk)
	ON_BN_CLICKED(ID_ADD_ABSENCES_CANCEL, &CAddAbsencesTypes::OnCancel)

END_MESSAGE_MAP()

CAddAbsencesTypes::CAddAbsencesTypes(TYPE_OF_ABSENCE& recAbsence, DialogMode eMode)
	: CDialogEx(IDD_ADD_ABSENCES),
	m_recAbsence(recAbsence)
{
	m_eMode = eMode;
}

CAddAbsencesTypes::~CAddAbsencesTypes()
{
}

void CAddAbsencesTypes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ADD_ABSENCES_TYPENAME, m_strAbsenceTypeName);
}

BOOL CAddAbsencesTypes::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if (m_eMode == eDialogMode_Edit)
	{
		m_strAbsenceTypeName = m_recAbsence.szAbsenceType;

		UpdateData(FALSE);

	}

	return TRUE;

}

void CAddAbsencesTypes::OnBnClickedOk()
{
	UpdateData();

	if (m_strAbsenceTypeName == "")
	{
		AfxMessageBox("Can't leave empty boxes!");
		return;
	}

	for (int i = 0; i < sizeof(m_strAbsenceTypeName); i++)
	{
		if (isdigit(m_strAbsenceTypeName[i]))
		{
			AfxMessageBox("Can't contain digits!");
			return;
		}
	}
	strncpy_s(m_recAbsence.szAbsenceType, m_strAbsenceTypeName, sizeof(m_recAbsence.szAbsenceType));

	__super::OnOK();
}

