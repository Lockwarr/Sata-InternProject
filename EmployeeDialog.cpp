#include "stdafx.h"
#include "EmployeeDialog.h"
#include <string>
#include "MydateTimeCtrl.h"
#include "EmployeesViewOffTimeDlg.h"
#include "AddRestTimeDlg.h"
#include "EmployeesOffTable.h"
#include "NmTypeOfDepartment.h"
#include "NmTypeOfPosition.h"
#include "HumanResources.h"

BEGIN_MESSAGE_MAP(CEmployeeDialog, CMyTabDialog)

	ON_BN_CLICKED(IDC_EMPLOYEE_SEARCH_OK, &CEmployeeDialog::OnOK)
	ON_BN_CLICKED(IDC_CANCEL, &CEmployeeDialog::OnCancel)
END_MESSAGE_MAP()

CEmployeeDialog::CEmployeeDialog(EMPLOYEE_DATA & recEmployee, DialogMode eDialogMode)
	: CMyTabDialog(IDD)
	, m_recEmployee(recEmployee)

{

	m_eMode = eDialogMode;

}


CEmployeeDialog::~CEmployeeDialog()
{
}

void CEmployeeDialog::DoDataExchange(CDataExchange* pDX)    // DDX/DDV support
{
	__super::DoDataExchange(pDX);

	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_FIRSTNAME, m_strFirstName);
	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_SURNAME, m_strSurName);
	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_LASTNAME, m_strLastName);
	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_PIN, m_strPIN);
	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_EMAIL, m_strEmail);
	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_PHONENUMBER, m_strPhoneNumber);

	DDX_Control(pDX, IDC_EMPLOYEE_SEARCH_DEPARTMNET, m_cmbDepartment);
	DDX_Control(pDX, IDC_EMPLOYEE_SEARCH_POSITION, m_cmbPosition);
	DDX_Control(pDX, IDC_EMPLOYEE_SEARCH_DATEPICKER, m_edbDate);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_FIRSTNAME, m_EdbFirstName);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_SURNAME, m_EdbSurName);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_LASTNAME, m_EdbLastName);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_PIN, m_EdbPIN);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_PHONENUMBER, m_EdbPhoneNumber);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_EMAIL, m_EdbEmail);
//	DDX_Control(pDX, IDC_EMPLOYEE_SEARCH_ID, m_EdbID);

}

BOOL CEmployeeDialog::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if (!LoadComboBoxes())
		return FALSE;

	if (m_eMode == eDialogMode_Edit)
	{
		FillComboBoxes();

		m_strCaption = m_recEmployee.szPIN;
		CString strID;
		strID.Format("%d", m_recEmployee.nID);

		//setting dialog's caption
		SetWindowText(_T("Edit employee with PIN " + m_strCaption));

		m_strFirstName = m_recEmployee.szFirstName;
		m_strSurName = m_recEmployee.szSurname;
		m_strLastName = m_recEmployee.szLastName;
		m_strPIN = m_recEmployee.szPIN;
		m_strEmail = m_recEmployee.szEmail;
		m_strPhoneNumber = m_recEmployee.szPhoneNumber;
		m_edbDate.SetDate(m_recEmployee.dtDate);

		m_EdbPIN.SetReadOnly();

	}
	else if (m_eMode == eDialogMode_View)
	{
		FillComboBoxes();

		CString strID;
		strID.Format("%d", m_recEmployee.nID);
		m_strCaption = m_recEmployee.szPIN;

		//setting dialog's caption
		SetWindowText(_T("View employee with PIN " + m_strCaption));

		m_strFirstName = m_recEmployee.szFirstName;
		m_strSurName = m_recEmployee.szSurname;
		m_strLastName = m_recEmployee.szLastName;
		m_strPIN = m_recEmployee.szPIN;
		m_strEmail = m_recEmployee.szEmail;
		m_strPhoneNumber = m_recEmployee.szPhoneNumber;
		m_edbDate.SetDate(m_recEmployee.dtDate);

		m_EdbFirstName.SetReadOnly();
		m_EdbSurName.SetReadOnly();
		m_EdbLastName.SetReadOnly();
		m_EdbPIN.SetReadOnly();
		m_EdbPhoneNumber.SetReadOnly();
		m_EdbEmail.SetReadOnly();
		m_edbDate.EnableWindow(FALSE);
		m_cmbDepartment.EnableWindow(FALSE);
		m_cmbPosition.EnableWindow(FALSE);

	}

	UpdateData(FALSE);

	return TRUE;

}

BOOL CEmployeeDialog::LoadComboBoxes() 
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

BOOL CEmployeeDialog::FillComboBoxes()
{
	CString departmentType;
	CNmTypeOfDepartment department(&theApp.m_database);
	std::vector<DEPARTMENT_TYPE> typeOfDepartment;

	if (!department.LoadAllFromTable(typeOfDepartment, 0))
		return FALSE;

	for (int i = 0; i < typeOfDepartment.size(); i++)
	{
		if (typeOfDepartment[i].nID == m_recEmployee.nDepartment)
		{
			departmentType.Format("%s", typeOfDepartment[i].szDepartmentType);
		}
	}

	m_cmbDepartment.SelectString(0, departmentType);

	CString positionType;
	CNmTypeOfPosition position(&theApp.m_database);
	std::vector<POSITION_TYPE> typeOfPosition;

	if (!position.LoadAllFromTable(typeOfPosition, 0))
		return FALSE;

	for (int i = 0; i < typeOfPosition.size(); i++)
	{
		if (typeOfPosition[i].nID == m_recEmployee.nPosition)
		{
			positionType.Format("%s", typeOfPosition[i].szPositionType);
		}
	}

	m_cmbPosition.SelectString(0, positionType);
	
	return TRUE;
}

BOOL CEmployeeDialog::onBnClickedOK()
{
	UpdateData();

//	if (!ValidatePIN())
//	{
//		AfxMessageBox(_T("Invalid PIN!"));
//		return FALSE;
//	}
//
//	if (AreEmptyBoxesLeft())
//	{
//		AfxMessageBox(_T("Empty boxes in employee data tab!"));
//		return FALSE;
//	}

	DBTIMESTAMP dbDate;

	if (!m_edbDate.GetDate(dbDate))
	{
		AfxMessageBox(_T("Couldn't retrieve date!"));
		return FALSE;
	}

	strncpy_s(m_recEmployee.szFirstName, m_strFirstName, sizeof(m_recEmployee.szFirstName));
	strncpy_s(m_recEmployee.szSurname, m_strSurName, sizeof(m_recEmployee.szSurname));
	strncpy_s(m_recEmployee.szLastName, m_strLastName, sizeof(m_recEmployee.szLastName));
	strncpy_s(m_recEmployee.szPIN, m_strPIN, sizeof(m_recEmployee.szPIN));
	strncpy_s(m_recEmployee.szEmail, m_strEmail, sizeof(m_recEmployee.szEmail));
	strncpy_s(m_recEmployee.szPhoneNumber, m_strPhoneNumber, sizeof(m_recEmployee.szPhoneNumber));
	m_recEmployee.dtDate = dbDate;

	int nCurSelItem = m_cmbDepartment.GetCurSel();

	if (nCurSelItem != -1)
		m_recEmployee.nDepartment= m_cmbDepartment.GetItemData(nCurSelItem);

	nCurSelItem = m_cmbPosition.GetCurSel();

	if (nCurSelItem != -1)
		m_recEmployee.nPosition = m_cmbPosition.GetItemData(nCurSelItem);

	return TRUE;
}


BOOL CEmployeeDialog::AreEmptyBoxesLeft()
{

	if (m_strFirstName == "" || m_strSurName == "" || m_strLastName == "" || m_strPIN == "" ||
		m_strEmail == "" || m_strPhoneNumber == "")
	{
		return TRUE;

	}
	return FALSE;
}

BOOL CEmployeeDialog::ValidatePIN()
{
	for (int i = 0; i < strlen(m_strPIN); i++)
	{
		if (!isdigit(m_strPIN[i]))
			return FALSE;
	}

	int lengthOfPIN = strlen(m_strPIN);

	if (lengthOfPIN != 10)
	{
		return FALSE;
	}

	std::string firstNum;
	firstNum.push_back(m_strPIN[0]);

	std::string monthNums;
	monthNums.push_back(m_strPIN[2]);
	monthNums.push_back(m_strPIN[3]);

	std::string yearNums;
	yearNums.push_back(m_strPIN[0]);
	yearNums.push_back(m_strPIN[1]);


	if (stoi(firstNum) == 0)
	{
		if (!((stoi(monthNums) > 20 && stoi(monthNums) <= 32)
			|| (stoi(monthNums) > 40 && stoi(monthNums) <= 52)))
		{
			return FALSE;
		}
	}
	else
	{
		if (!((stoi(monthNums) >= 0 && stoi(monthNums) <= 12)
			|| (stoi(monthNums) > 20 && stoi(monthNums) <= 32)
			|| (stoi(monthNums) > 40 && stoi(monthNums) <= 52)))
		{
			return FALSE;
		}
	}

	std::string dayNums;//5th and 6th numbers
	dayNums.push_back(m_strPIN[4]);
	dayNums.push_back(m_strPIN[5]);


	if (stoi(monthNums) == 1 || stoi(monthNums) == 3 || stoi(monthNums) == 5 || stoi(monthNums) == 7
		|| stoi(monthNums) == 8 || stoi(monthNums) == 10 || stoi(monthNums) == 12

		|| stoi(monthNums) == 21 || stoi(monthNums) == 23 || stoi(monthNums) == 25 || stoi(monthNums) == 27
		|| stoi(monthNums) == 28 || stoi(monthNums) == 30 || stoi(monthNums) == 32

		|| stoi(monthNums) == 41 || stoi(monthNums) == 43 || stoi(monthNums) == 45 || stoi(monthNums) == 47
		|| stoi(monthNums) == 48 || stoi(monthNums) == 50 || stoi(monthNums) == 52)
	{
		if (stoi(dayNums) < 0 || stoi(dayNums) > 31)
		{
			return FALSE;
		}
	}
	else if (stoi(monthNums) == 2 || stoi(monthNums) == 22 || stoi(monthNums) == 42)
	{
		if (stoi(yearNums) % 4 == 0)
		{
			if (stoi(dayNums) < 0 || stoi(dayNums) > 29)
			{
				return FALSE;
			}
		}
		else
		{
			if (stoi(dayNums) < 0 || stoi(dayNums) > 28)
			{
				return FALSE;
			}
		}
	}
	else
	{
		if (stoi(dayNums) < 0 || stoi(dayNums) > 30)
		{
			return FALSE;
		}
	}

	return TRUE;
}
