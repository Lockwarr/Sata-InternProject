// HumanResourcesView.h : interface of the CHumanResourcesView class
//

#pragma once
#include "HumanResourcesDoc.h"
#include "SortListCtrl.h"
#include "EnumDialogMode.h"
#include "Structures.h"
#include "EmployeeDialog.h"
#include "EmployeesTable.h"
#include "FilterDialog.h"
#include "AddRestTimeDlg.h"
#include "HumanResources.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

enum RefreshMode
{
	eFileMode_filtered,
	eFileMode_showAll
};

class CHumanResourcesView : public CFormView
{
	DECLARE_DYNCREATE(CHumanResourcesView)

	enum ListCtrlColumns
	{
		eListCtrlColumns_FirstName = 0,
		eListCtrlColumns_SurName = 1,
		eListCtrlColumns_LastName = 2,
		eListCtrlColumns_PIN = 3,
		eListCtrlColumns_Email = 4,
		eListCtrlColumns_PhoneNumber = 5,
		eListCtrlColumns_Date = 6,
		eListCtrlColumns_Department = 7,
		eListCtrlColumns_Position = 8,
	};

public:
	CHumanResourcesView();
	virtual ~CHumanResourcesView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HUMANRESOURCES_FORM };
#endif

	// Attributes
public:
	CHumanResourcesDoc * GetDocument() const;

	// Operations
public:

	void LoadEmployees(std::vector<EMPLOYEE_DATA> employeesData);
	void OnFilterByDate();
	void OnFilterMissingBetween();
	void LoadEmployee(NMHDR * pNMHDR, LRESULT * pResult);
	void OnFilterByFirstName();
	void LoadListCtrl();

	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

#endif

	// Generated message map functions
protected:
	
	DECLARE_MESSAGE_MAP()


public:
	void OnBnClickedAddEmployee();
	void OnBnClickedEditEmployee();
	void OnFilePrintPreview();
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnContextMenu(CWnd* pWnd, CPoint point);
	void OnBnClickedDeleteEmployee();
	void OnLvnDeleteKeyPress(NMHDR *pNMHDR, LRESULT *pResult);
	void OnEditAbsenceTypes();
	void OnEditEmploymentTypes();
	void OnEditDepartmentTypes();
	void OnEditPositionTypes();
	void OnEditEducationTypes();

private:

	CMenu m_Menu;

	BOOL m_bSortAscending = TRUE;
	
	CSortListCtrl m_lcsEmployees;

	std::vector<EMPLOYEE_DATA> m_arrEmployeesData;


};

#ifndef _DEBUG  // debug version in HumanResourcesView.cpp
inline CHumanResourcesDoc* CHumanResourcesView::GetDocument() const
{
	return reinterpret_cast<CHumanResourcesDoc*>(m_pDocument);
}
#endif

