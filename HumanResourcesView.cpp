
// HumanResourcesView.cpp : implementation of the CHumanResourcesView class
//
#include "stdafx.h"

#include "odbcinst.h"
#include "afxdb.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.

#include "HumanResourcesView.h"
#include "EmployeesOffTable.h"
#include "AddAbsencesDlg.h"
#include "TabsDlg.h"
#include "EmploymentDlg.h"
#include "EducationTypes.h"
#include "MissingEmployeesDatesPickerDialog.h"
#include "MissingEmployeesDlg.h"
#include "NmTypeOfDepartment.h"
#include "NmTypeOfPosition.h"
#include "DepartmentDlg.h"
#include "PositionDlg.h"


int employeesCounter = 0;



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHumanResourcesView

IMPLEMENT_DYNCREATE(CHumanResourcesView, CFormView)

BEGIN_MESSAGE_MAP(CHumanResourcesView, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHumanResourcesView::OnFilePrintPreview)
	ON_COMMAND(ID_FILTER_BYFIRSTNAME, &CHumanResourcesView::OnFilterByFirstName)
	ON_COMMAND(ID_FILTER_BYDATE, &CHumanResourcesView::OnFilterByDate)
	ON_COMMAND(ID_FILTER_SHOWALL, &CHumanResourcesView::LoadListCtrl)
	ON_COMMAND(ID_FILTER_MISSINGBETWEEN, &CHumanResourcesView::OnFilterMissingBetween)


	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_BN_CLICKED(IDC_ADD_EMPLOYEE, &CHumanResourcesView::OnBnClickedAddEmployee)
	ON_BN_CLICKED(IDC_EDIT_EMPLOYEE, &CHumanResourcesView::OnBnClickedEditEmployee)
	ON_BN_CLICKED(IDC_DELETE_EMPLOYEE, &CHumanResourcesView::OnBnClickedDeleteEmployee)

	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, &CHumanResourcesView::OnLvnDeleteKeyPress)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CHumanResourcesView::LoadEmployee)

	ON_COMMAND(ID_EDIT_ADDABSENCE, &CHumanResourcesView::OnEditAbsenceTypes)
	ON_COMMAND(ID_EDIT_EMPLOYMENTTYPES, &CHumanResourcesView::OnEditEmploymentTypes)
	ON_COMMAND(ID_EDIT_EDUCATIONTYPES, &CHumanResourcesView::OnEditEducationTypes)
	ON_COMMAND(ID_EDIT_DEPARTMENTTYPES, &CHumanResourcesView::OnEditDepartmentTypes)
	ON_COMMAND(ID_EDIT_POSITIONTYPES, &CHumanResourcesView::OnEditPositionTypes)

END_MESSAGE_MAP()

// CHumanResourcesView construction/destruction

CHumanResourcesView::CHumanResourcesView()
	: CFormView(IDD_HUMANRESOURCES_FORM)
{
}

CHumanResourcesView::~CHumanResourcesView()
{
}

void CHumanResourcesView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_lcsEmployees);
}

BOOL CHumanResourcesView::PreCreateWindow(CREATESTRUCT& cs)
{
	m_Menu.CreateMenu(); //Call this once only (I do it in PreSubclassWindow)

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}


void CHumanResourcesView::OnInitialUpdate()
{

	CFormView::OnInitialUpdate();

	m_lcsEmployees.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	ResizeParentToFit(FALSE);

	CRect rect;
	m_lcsEmployees.GetClientRect(&rect);

	int nColInterval = rect.Width() / 9;

	m_lcsEmployees.InsertColumn(eListCtrlColumns_FirstName, "First name", LVCFMT_LEFT, nColInterval);
	m_lcsEmployees.InsertColumn(eListCtrlColumns_SurName, "Surname", LVCFMT_LEFT, nColInterval);
	m_lcsEmployees.InsertColumn(eListCtrlColumns_LastName, "Last name", LVCFMT_LEFT, nColInterval);
	m_lcsEmployees.InsertColumn(eListCtrlColumns_PIN, "PIN", LVCFMT_LEFT, nColInterval);
	m_lcsEmployees.InsertColumn(eListCtrlColumns_Email, "Email", LVCFMT_LEFT, nColInterval);
	m_lcsEmployees.InsertColumn(eListCtrlColumns_PhoneNumber, "Phone number", LVCFMT_LEFT, nColInterval);
	m_lcsEmployees.InsertColumn(eListCtrlColumns_Date, "Date", LVCFMT_LEFT, nColInterval);
	m_lcsEmployees.InsertColumn(eListCtrlColumns_Department, "Departmnet", LVCFMT_LEFT, nColInterval);
	m_lcsEmployees.InsertColumn(eListCtrlColumns_Position, "Position", LVCFMT_LEFT, nColInterval);

	m_lcsEmployees.Submenu(m_Menu);

	LoadListCtrl();
}


// CHumanResourcesView printing


void CHumanResourcesView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHumanResourcesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CHumanResourcesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHumanResourcesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CHumanResourcesView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

void CHumanResourcesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}


void CHumanResourcesView::OnContextMenu(CWnd *pWnd, CPoint ptMousePos)
{
	CPoint hitPoint = ptMousePos;
	ScreenToClient(&hitPoint);

	//Fix header pop-up bug
	CHeaderCtrl *pHeader = m_lcsEmployees.GetHeaderCtrl();
	HDHITTESTINFO hitTestHeader = { 0 };
	hitTestHeader.pt = hitPoint;

	//The header doesn't need a context-menu, the item does
	if (pHeader->HitTest(&hitTestHeader) != -1)
		return;

	UINT uFlags = 0;
	int nItemIndex = m_lcsEmployees.HitTest(hitPoint, &uFlags);

	if (uFlags & LVHT_NOWHERE)
		return;

	//Get the previously created menu
	CMenu *pPopUp = nullptr;
	pPopUp = m_Menu.GetSubMenu(0);

	if (pPopUp)
		pPopUp->TrackPopupMenu(TPM_LEFTALIGN, ptMousePos.x, ptMousePos.y, this);
#ifndef SHARED_HANDLERS
	//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, ptMousePos.x, ptMousePos.y, this, TRUE);
#endif
}


// CHumanResourcesView diagnostics

#ifdef _DEBUG
void CHumanResourcesView::AssertValid() const
{
	CFormView::AssertValid();
}

void CHumanResourcesView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CHumanResourcesDoc* CHumanResourcesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHumanResourcesDoc)));
	return (CHumanResourcesDoc*)m_pDocument;
}
#endif //_DEBUG


// CHumanResourcesView message handlers

void CHumanResourcesView::OnBnClickedDeleteEmployee()
{
	//get the index of currently selected row
	int selectedRow = m_lcsEmployees.GetSelectionMark();

	//0 is the position of the id in the structure



	if (selectedRow == -1)
	{
		AfxMessageBox(_T("You haven't clicked on any employee!"));

		return;
	}

	EMPLOYEE_DATA* pEmployeeData = (EMPLOYEE_DATA*)m_lcsEmployees.GetItemData(selectedRow);

	if (!pEmployeeData)
		return;

	if (!GetDocument()->DeleteEmployee(pEmployeeData->nID))
		AfxMessageBox(_T("Failed to delete employee!"));

	LoadListCtrl();


}
void CHumanResourcesView::OnBnClickedAddEmployee()
{

	UpdateData();

	CEmployeeData oEmployeeData;

	CTabsDlg addEmployee(oEmployeeData, eDialogMode_Add);

	if (addEmployee.DoModal() != IDOK)
		return;

	if (!GetDocument()->AddEmployee(oEmployeeData))
		return;

	LoadListCtrl();
}


void CHumanResourcesView::OnBnClickedEditEmployee()
{

	UpdateData();

	int selectedRow = m_lcsEmployees.GetSelectionMark();

	if (selectedRow == -1)
	{
		AfxMessageBox(_T("Please select edit choice!"));
		return;
	}

	EMPLOYEE_DATA* pEmployeeData = (EMPLOYEE_DATA*)m_lcsEmployees.GetItemData(selectedRow);

	CEmployeeData oEmployeeData;

	if (!pEmployeeData)
		return;

	if (!GetDocument()->LoadEmployee(oEmployeeData.m_recEmployee, pEmployeeData->nID))
		return;

	if (!GetDocument()->LoadEmployeeOffTime(oEmployeeData.m_arrEmployeeOffTime, oEmployeeData.m_recEmployee.nID))
		return;

	if (!GetDocument()->LoadAllFromTableEducations(oEmployeeData.m_arrEducation, oEmployeeData.m_recEmployee.nID))
		return;

	if (!GetDocument()->LoadAllFromTableWork(oEmployeeData.m_arrWork, oEmployeeData.m_recEmployee.nID))
		return;

	CTabsDlg editEmployee(oEmployeeData, eDialogMode_Edit);

	if (editEmployee.DoModal() != IDOK)
		return;

	if (!GetDocument()->EditEmployee(oEmployeeData))
		return;

	LoadListCtrl();
}

void CHumanResourcesView::LoadEmployees(std::vector<EMPLOYEE_DATA> employeesData)
{
	m_lcsEmployees.DeleteAllItems();
	m_arrEmployeesData.clear(); //clearing the list everytime before we get new data (if we have just deleted the last item ,
	// GetEmployees won't fill m_arrEmployeesData because the file will be empty and fill method wont be invoked )
	m_arrEmployeesData = employeesData;

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	for (UINT i = 0; i < m_arrEmployeesData.size(); i++)
	{

		CString strDepartmentType;

		CNmTypeOfDepartment departments(&theApp.m_database);
		std::vector<DEPARTMENT_TYPE> departmentType;

		if (!departments.LoadAllFromTable(departmentType, employeesData[i].nID))
			return;

		for (int z = 0; z < departmentType.size(); z++)
		{
			if (departmentType[z].nID == employeesData[i].nDepartment)
			{
				strDepartmentType.Format("%s", departmentType[z].szDepartmentType);
				break;
			}
		}

		CString strPosition;

		CNmTypeOfPosition positions(&theApp.m_database);
		std::vector<POSITION_TYPE> positionType;

		if (!positions.LoadAllFromTable(positionType, employeesData[i].nID))
			return;

		for (int z = 0; z < positionType.size(); z++)
		{
			if (positionType[z].nID == employeesData[i].nPosition)
			{
				strPosition.Format("%s", positionType[z].szPositionType);
				break;
			}
		}



		lvi.iItem = i;
		lvi.iSubItem = 0;
		CString strFirstName;
		strFirstName.Format("%s", m_arrEmployeesData[i].szFirstName);
		lvi.pszText = (LPTSTR)(LPCTSTR)(strFirstName);
		//inserting item in the first column
		m_lcsEmployees.InsertItem(&lvi);

		m_lcsEmployees.SetItemText(i, eListCtrlColumns_SurName, m_arrEmployeesData[i].szSurname);
		m_lcsEmployees.SetItemText(i, eListCtrlColumns_LastName, m_arrEmployeesData[i].szLastName);
		m_lcsEmployees.SetItemText(i, eListCtrlColumns_PIN, m_arrEmployeesData[i].szPIN);
		m_lcsEmployees.SetItemText(i, eListCtrlColumns_Email, m_arrEmployeesData[i].szEmail);
		m_lcsEmployees.SetItemText(i, eListCtrlColumns_PhoneNumber, m_arrEmployeesData[i].szPhoneNumber);
		m_lcsEmployees.SetItemText(i, eListCtrlColumns_Date, GetSqlDateTimeString(m_arrEmployeesData[i].dtDate));
		m_lcsEmployees.SetItemText(i, eListCtrlColumns_Department , strDepartmentType);
		m_lcsEmployees.SetItemText(i, eListCtrlColumns_Position, strPosition);

		m_lcsEmployees.SetItemData(i, (DWORD_PTR)&m_arrEmployeesData[i]); //the data of each item will be equal to it's ID

	}
}

void CHumanResourcesView::LoadEmployee(NMHDR * pNMHDR, LRESULT * pResult)
{

	//get the index of currently selected row
	int selectedRow = m_lcsEmployees.GetSelectionMark();

	if (selectedRow == -1)
	{
		AfxMessageBox(_T("You didn't click on any employee!"));
		return;
	}

	EMPLOYEE_DATA* pEmployeeData = (EMPLOYEE_DATA*)m_lcsEmployees.GetItemData(selectedRow);

	CEmployeeData oEmployeeData;

	if (!pEmployeeData)
		return;

	if (!GetDocument()->LoadEmployee(oEmployeeData.m_recEmployee, pEmployeeData->nID))
		return;

	if (!GetDocument()->LoadEmployeeOffTime(oEmployeeData.m_arrEmployeeOffTime, oEmployeeData.m_recEmployee.nID))
		return;

	if (!GetDocument()->LoadAllFromTableEducations(oEmployeeData.m_arrEducation, oEmployeeData.m_recEmployee.nID))
		return;

	if (!GetDocument()->LoadAllFromTableWork(oEmployeeData.m_arrWork, oEmployeeData.m_recEmployee.nID))
		return;


	CTabsDlg editEmployee(oEmployeeData, eDialogMode_View);

	if (!editEmployee.DoModal())
		return;

	LoadListCtrl();

}

void CHumanResourcesView::OnFilterByFirstName()
{
	UpdateData();

	EMPLOYEE_DATA employee;

	CString filter;

	std::vector<EMPLOYEE_DATA> filteredEmployees;

	CString firstName;
	firstName.Format("%s", employee.szFirstName);
	CFilterDialog filterName(firstName, eFilterMode_ByName);

	if (filterName.DoModal() == IDOK)
	{
		if (!GetDocument()->FilterBy(filteredEmployees, firstName, eFilterMode_ByName))
			return;

		LoadEmployees(filteredEmployees);

	}
}

void CHumanResourcesView::OnFilterByDate()
{
	UpdateData();

	EMPLOYEE_DATA employee;

	CString filter;

	std::vector<EMPLOYEE_DATA> filteredEmployees;
	CString date;
	CFilterDialog filterName(date, eFilterMode_ByDate);

	if (filterName.DoModal() == IDOK)
	{
		if (!GetDocument()->FilterBy(filteredEmployees, date, eFilterMode_ByDate))
		{
			AfxMessageBox(_T("Failed to load employee by filter!"));
			return;
		}

		LoadEmployees(filteredEmployees);

	}

}

void CHumanResourcesView::OnFilterMissingBetween()
{
	UpdateData();

	MISSING_EMPLOYEES_STANDART missingStandart;

	std::vector<MISSING_EMPLOYEES> arrFilteredEmplyoees;

	CMissingEmployeesDatesPickerDialog oMissingDates(missingStandart);

	if (oMissingDates.DoModal() != IDOK)
		return;

	if (!GetDocument()->MissingEmployees(arrFilteredEmplyoees, missingStandart))
	{
		AfxMessageBox(_T("Failed to load missing Employees!"));
		return;
	}

	CMissingEmployeesDlg missingList(arrFilteredEmplyoees);
	if (missingList.DoModal() != IDOK)
		return;

}

void CHumanResourcesView::OnLvnDeleteKeyPress(NMHDR *pNMHDR, LRESULT *pResult)
{

	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;

	if (pLVKeyDown->wVKey == 46) //Virtual key code for Delete is 46 -> checking if the user has pressed Delete key
		OnBnClickedDeleteEmployee();

	*pResult = 0;
}

void CHumanResourcesView::LoadListCtrl()
{
	std::vector<EMPLOYEE_DATA> employeesData;

	if (!GetDocument()->LoadAllFromTableEmployees(employeesData))
		AfxMessageBox(_T("Failed to load all employees!"));

	LoadEmployees(employeesData);
}

void CHumanResourcesView::OnEditAbsenceTypes()
{
	std::vector<TYPE_OF_ABSENCE> absenceTypes;
	if (!GetDocument()->LoadAbsences(absenceTypes))
		return;

	CAddAbsencesDlg absences(absenceTypes);
	if (absences.DoModal() == IDOK)
	{
		if (!GetDocument()->ModifyAbsenceTypeTable(absenceTypes))
			return;
	}
}

void CHumanResourcesView::OnEditEmploymentTypes()
{
	std::vector<TYPE_OF_EMPLOYMENT> employmentTypes;
	if (!GetDocument()->LoadEmployment(employmentTypes))
		return;

	CEmploymentDlg employment(employmentTypes);
	if (employment.DoModal() == IDOK)
	{
		if (!GetDocument()->ModifyEmploymentTypeTable(employmentTypes))
			return;
	}
}

void CHumanResourcesView::OnEditDepartmentTypes()
{
	std::vector<DEPARTMENT_TYPE> departmentTypes;
	if (!GetDocument()->LoadDepartments(departmentTypes))
		return;

	CDepartmentDlg department(departmentTypes);
	if (department.DoModal() == IDOK)
	{
		if (!GetDocument()->ModifyDepartmentTypeTable(departmentTypes))
			return;
	}
}

void CHumanResourcesView::OnEditPositionTypes()
{
	std::vector<POSITION_TYPE> positionTypes;
	if (!GetDocument()->LoadPositions(positionTypes))
		return;

	CPositionDlg employment(positionTypes);
	if (employment.DoModal() == IDOK)
	{
		if (!GetDocument()->ModifyPositionTypeTable(positionTypes))
			return;
	}
}

void CHumanResourcesView::OnEditEducationTypes()
{
	std::vector<TYPE_OF_EDUCATION> educationTypes;
	if (!GetDocument()->LoadEducation(educationTypes))
		return;

	CEducationTypes education(educationTypes);
	if (education.DoModal() == IDOK)
	{
		if (!GetDocument()->ModifyEducationTypeTable(educationTypes))
			return;
	}
}



