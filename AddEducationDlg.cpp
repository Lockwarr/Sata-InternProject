// AddEducation.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResources.h"
#include "AddEducationDlg.h"
#include "afxdialogex.h"
#include "NmTypeOfEducationTable.h"

// CAddEducationDlg dialog



BEGIN_MESSAGE_MAP(CAddEducationDlg, CDialogEx)
	ON_BN_CLICKED(ID_ADD_EDUCATION_OK, &CAddEducationDlg::OnBnClickedOk)
	ON_BN_CLICKED(ID_ADD_EDUCATION_CANCEL, &CAddEducationDlg::OnCancel)
END_MESSAGE_MAP()


CAddEducationDlg::CAddEducationDlg(EMPLOYEE_EDUCATION & recEducation, DialogMode eMode)
	: CDialogEx(IDD_EMPLOYEE_EDUCATION),
	m_oEducation(recEducation)
{
	m_eMode = eMode;
}

CAddEducationDlg::~CAddEducationDlg()
{
}


void CAddEducationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDD_EMPLOYEE_EDUCATION_SPECIALTY, m_strSpecialty);
	DDX_Text(pDX, IDD_EMPLOYEE_EDUCATION_TOWN, m_strTown);
	DDX_Text(pDX, IDD_EMPLOYEE_EDUCATION_SCHOOL_NAME, m_strSchoolName);
	DDX_Text(pDX, IDD_EMPLOYEE_EDUCATION_ADDITIONAL_INFORMATION, m_strAdditionalInfo);


	DDX_Control(pDX, IDC_EMPLOYEE_EDUCATION_DATE_FROM, m_dtcDateFrom);
	DDX_Control(pDX, IDC_EMPLOYEE_EDUCATION_DATE_TO, m_dtcDateTo);
	DDX_Control(pDX, IDC_EDUCATION_COMBO, m_education_comboBox);
	DDX_Control(pDX, IDD_EMPLOYEE_EDUCATION_SPECIALTY, m_edbSpecialty);
	DDX_Control(pDX, IDD_EMPLOYEE_EDUCATION_TOWN, m_edbTown);
	DDX_Control(pDX, IDD_EMPLOYEE_EDUCATION_SCHOOL_NAME, m_edbSchoolName);
	DDX_Control(pDX, IDD_EMPLOYEE_EDUCATION_ADDITIONAL_INFORMATION, m_edbAdditionalInfo);

}

BOOL CAddEducationDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if (!LoadComboBox())
		return FALSE;



	//checking the mode of the Dialog
	if (m_eMode == eDialogMode_Edit)
	{
		SetWindowText(_T("Edit education"));
		FillDialog();

	}
	else if (m_eMode == eDialogMode_View)
	{
		SetWindowText(_T("View education"));
		FillDialog();

		m_dtcDateFrom.EnableWindow(FALSE);
		m_dtcDateTo.EnableWindow(FALSE);
		m_edbSpecialty.SetReadOnly();
		m_edbTown.SetReadOnly();
		m_edbSchoolName.SetReadOnly();
		m_edbAdditionalInfo.SetReadOnly();
		m_education_comboBox.EnableWindow(FALSE);

	}
	else
		SetWindowText(_T("Add education"));
	UpdateData(FALSE);

	return TRUE;
}

void CAddEducationDlg::OnBnClickedOk()
{
	UpdateData(TRUE);


	if (AreEmptyBoxesLeft())
	{
		AfxMessageBox(_T("Empty boxes in education tab!"));
		return;
	}

	DBTIMESTAMP dbDateFrom;
	DBTIMESTAMP dbDateTo;


	if (!m_dtcDateFrom.GetDate(dbDateFrom))
	{
		AfxMessageBox(_T("Couldn't retrieve date!"));
		return;
	}

	if (!m_dtcDateTo.GetDate(dbDateTo))
	{
		AfxMessageBox(_T("Couldn't retrieve date!"));
		return;
	}

	COleDateTime dateFrom(dbDateFrom);
	COleDateTime dateTo(dbDateTo);

	if (dateFrom > dateTo)
	{
		AfxMessageBox(_T("Starting date cannot be after end date!"));
		return;
	}


		strncpy_s(m_oEducation.szSpecialty, m_strSpecialty, sizeof(m_oEducation.szSpecialty));
	strncpy_s(m_oEducation.szTownCountry, m_strTown, sizeof(m_oEducation.szTownCountry));
	strncpy_s(m_oEducation.szSchoolName, m_strSchoolName, sizeof(m_oEducation.szSchoolName));
	strncpy_s(m_oEducation.szAdditionalInfo, m_strAdditionalInfo, sizeof(m_oEducation.szAdditionalInfo));
	m_oEducation.dtFrom = dbDateFrom;
	m_oEducation.dtTo = dbDateTo;

	int nCurSelItem = m_education_comboBox.GetCurSel();

	if (nCurSelItem != -1)
		m_oEducation.nEducationType = m_education_comboBox.GetItemData(nCurSelItem);

	__super::OnOK();
}

BOOL CAddEducationDlg::FillDialog()
{
	m_dtcDateFrom.SetDate(m_oEducation.dtFrom);
	m_dtcDateTo.SetDate(m_oEducation.dtTo);
	m_strSpecialty = m_oEducation.szSpecialty;
	m_strTown = m_oEducation.szTownCountry;
	m_strSchoolName = m_oEducation.szSchoolName;
	m_strAdditionalInfo = m_oEducation.szAdditionalInfo;

	CString strEducationType;
	CNmTypeOfEducationTable education(&theApp.m_database);
	std::vector<TYPE_OF_EDUCATION> typeOfEducation;

	if (!education.LoadAllFromTable(typeOfEducation, 0))
		return FALSE;

	for (int i = 0; i < typeOfEducation.size(); i++)
	{
		if (typeOfEducation[i].nID == m_oEducation.nEducationType)
		{
			strEducationType.Format("%s", typeOfEducation[i].szEducationType);
		}
	}

	m_education_comboBox.SelectString(0, strEducationType);
	return TRUE;
}

BOOL CAddEducationDlg::AreEmptyBoxesLeft()
{
	if (m_strSpecialty == "" || m_strTown == "" || m_strSchoolName == "" || m_strAdditionalInfo == "" || m_education_comboBox.GetCurSel() == -1)
		return TRUE;

	return FALSE;
}

BOOL CAddEducationDlg::LoadComboBox()
{
	int nItem;
	CNmTypeOfEducationTable educations(&theApp.m_database);
	std::vector<TYPE_OF_EDUCATION> educationTypes;

	if (!educations.LoadAllFromTable(educationTypes, 0))
		return FALSE;

	for (int i = 0; i < educationTypes.size(); i++)
	{
		int nIndex = m_education_comboBox.AddString(_T(educationTypes[i].szEducationType));

		m_education_comboBox.SetItemData(nIndex, educationTypes[i].nID);
	}
	return TRUE;
}

