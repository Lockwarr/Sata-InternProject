// ViMissingEmployeesTable.h : Declaration of the CViMissingEmployeesTable
#include "Structures.h"
#include <vector>
#include "HumanResources.h"
#pragma once

// code generated on 28 август 2018 г., 14:56

class CViMissingEmployeesTable : public CRecordset
{
public:
	CViMissingEmployeesTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CViMissingEmployeesTable)

	long	m_employee_id;
	CString	m_first_name;
	CString	m_last_name;
	CString	m_type_of_absence;
	CString	m_start_date;
	CString	m_end_date;
	long	m_days_count;
	CString	m_department;
	CString	m_position;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	BOOL LoadAll(std::vector<MISSING_EMPLOYEES>& arrMissingEmployees);
#endif

};


