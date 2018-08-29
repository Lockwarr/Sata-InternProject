// ViViMissingEmployeesTable.h : Declaration of the CViViMissingEmployeesTable

#pragma once
#include <vector>
#include "Structures.h"
#include "HumanResources.h"

// code generated on 29 август 2018 г., 15:35

class CViMissingEmployeesTable : public CRecordset
{
public:
	CViMissingEmployeesTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CViMissingEmployeesTable)

	long	m_empl_id;
	CString	m_first_name;
	CString	m_last_name;
	long	m_type_of_absence_id;
	CString	m_type_of_absence;
	CString	m_start_date;
	CString	m_end_date;
	long	m_days_count;
	long	m_position_id;
	CString	m_position_name;
	long	m_department_id;
	CString	m_department_name;

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


