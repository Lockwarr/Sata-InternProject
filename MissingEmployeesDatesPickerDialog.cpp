// MissingEmployeesDatesPicker.cpp : implementation file
//

#include "stdafx.h"
#include "HumanResources.h"
#include "MissingEmployeesDatesPickerDialog.h"
#include "afxdialogex.h"
#include "NmTypeOfDepartment.h"
#include "NmTypeOfPosition.h"

// CMissingEmployeesDatesPickerDialog dialog

BEGIN_MESSAGE_MAP(CMissingEmployeesDatesPickerDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMissingEmployeesDatesPickerDialog::OnBnClickedOk)
END_MESSAGE_MAP()


CMissingEmployeesDatesPickerDialog::CMissingEmployeesDatesPickerDialog(MISSING_EMPLOYEES_STANDART & missingStandart)
	: CDialogEx(IDD)
	, m_missingStandart(missingStandart)
{
}

CMissingEmployeesDatesPickerDialog::~CMissingEmployeesDatesPickerDialog()
{
}

void CMissingEmployeesDatesPickerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EMPLOYEES_MISSING_FROM_DATEPICKER, m_edbStartDate);
	DDX_Control(pDX, IDC_EMPLOYEES_MISSING_TO_DATEPICKER, m_edbEndDate);
	DDX_Control(pDX, IDC_EMPLOYEES_MISSING_DEPARTMENT, m_cmbDepartment);
	DDX_Control(pDX, IDC_EMPLOYEES_MISSING_POSITION, m_cmbPosition);
}


// CMissingEmployeesDatesPickerDialog message handlers
BOOL CMissingEmployeesDatesPickerDialog::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if (!LoadComboBoxes())
		return FALSE;

	return TRUE;
}

BOOL CMissingEmployeesDatesPickerDialog::LoadComboBoxes()
{
	CNmTypeOfDepartment departments(&theApp.m_database);
	std::vector<DEPARTMENT_TYPE> departmentTypes;

	if (!departments.LoadAllFromTable(departmentTypes, 0))
		return FALSE;

	for (int i = 0; i < departmentTypes.size(); i++)
	{
		int nIndex = m_cmbDepartment.AddString(_T(departmentTypes[i].szDepartmentType));

		m_cmbDepartment.SetItemData(nIndex, departmentTypes[i].nID);
	}
	
	CNmTypeOfPosition positions(&theApp.m_database);
	std::vector<POSITION_TYPE> positionTypes;

	if (!positions.LoadAllFromTable(positionTypes, 0))
		return FALSE;

	for (int i = 0; i < positionTypes.size(); i++)
	{
		int nIndex = m_cmbPosition.AddString(_T(positionTypes[i].szPositionType));

		m_cmbPosition.SetItemData(nIndex, positionTypes[i].nID);
	}
	return TRUE;
}

void CMissingEmployeesDatesPickerDialog::OnBnClickedOk()
{
	UpdateData();

	DBTIMESTAMP dbStartDate;
	DBTIMESTAMP dbEndDate;

	if (!m_edbStartDate.GetDate(dbStartDate))
	{
		AfxMessageBox(_T("Couldn't retrieve start date!"));
		return;
	}

	if (!m_edbEndDate.GetDate(dbEndDate))
	{
		AfxMessageBox(_T("Couldn't retrieve end date!"));
		return;
	}

	COleDateTime startDate(dbStartDate);
	COleDateTime endDate(dbEndDate);

	if (startDate > endDate)
	{
		AfxMessageBox(_T("Starting date can't be after end date!"));
		return;
	}
	dbStartDate.hour = 0;
	dbStartDate.minute = 0;
	dbStartDate.fraction = 0;
	dbStartDate.second = 0;

	dbEndDate.hour = 0;
	dbEndDate.minute = 0;
	dbEndDate.fraction = 0;
	dbEndDate.second = 0;

	m_missingStandart.edbStartDate = dbStartDate;
	m_missingStandart.edbEndDate = dbEndDate;

	int nCurSelItem = m_cmbDepartment.GetCurSel();

	if (nCurSelItem == -1)
	{
		AfxMessageBox("Please select department! ");
		return;
	}

	m_missingStandart.nDepartment = m_cmbDepartment.GetItemData(nCurSelItem);
	
	nCurSelItem = m_cmbPosition.GetCurSel();

	if (nCurSelItem == -1)
	{
		AfxMessageBox("Please select position! ");
		return;
	}

	m_missingStandart.nPosition = m_cmbPosition.GetItemData(nCurSelItem);

	CDialogEx::OnOK();
}
