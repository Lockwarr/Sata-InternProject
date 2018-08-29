// EmployeesWorkTable.h : Declaration of the CEmployeesWorkTable

#pragma once
#include "Structures.h"
#include <vector>
#include "HumanResources.h"
#include "MyTables.h"

// code generated on 07 август 2018 г., 17:34

class CEmployeesWorkTable : public CMyTables<EMPLOYEE_WORK>
{
public:
	CEmployeesWorkTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEmployeesWorkTable)

	long	m_id;
	long	m_employee_id;
	CString	m_start_date;
	CString	m_end_date;
	CString	m_town_country;
	CString	m_position;
	CString	m_company_name;
	CString	m_additional_information;
	long	m_employment_type;

	
public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:

	virtual void DataToStruct(EMPLOYEE_WORK& recRecord);
	virtual void StructToData(const EMPLOYEE_WORK & recRecord);
	BOOL DeleteAllByEmployeeID(int nEmployeeID);
};


