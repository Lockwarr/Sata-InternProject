// EmployeesOffTable.h : Declaration of the CEmployeesOffTable

#pragma once
#include "Structures.h"
#include <vector>
#include "MyTables.h"

// code generated on 03 август 2018 г., 15:02

class CEmployeesOffTable : public CMyTables<EMPLOYEE_OFF_TIME>
{
public:
	CEmployeesOffTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEmployeesOffTable)


	long	m_id;
	long	m_employee_id;
	long	m_type_of_absence;
	CString	m_start_date;
	CString	m_end_date;
	long	m_days_resting;

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

	virtual void DataToStruct(EMPLOYEE_OFF_TIME & recRecord);
	virtual void StructToData(const EMPLOYEE_OFF_TIME & recRecord);
	BOOL DeleteAllByEmployeeID(int employeeID);

};


