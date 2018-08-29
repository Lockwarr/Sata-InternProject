// EmployeesEducationTable.h : Declaration of the CEmployeesEducationTable

#pragma once

#include "Structures.h"
#include "HumanResources.h"
#include <vector>
#include "MydateTimeCtrl.h"
#include "MyTables.h"

// code generated on 07 август 2018 г., 17:34

class CEmployeesEducationTable : public CMyTables<EMPLOYEE_EDUCATION>
{
public:
	CEmployeesEducationTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEmployeesEducationTable)

	long	m_id;
	long	m_employee_id;
	CString	m_start_date;
	CString	m_end_date;
	long	m_education_type;
	CString	m_specialty;
	CString	m_town_country;
	CString	m_school_name;
	CString	m_additional_information;

public:

	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:

	virtual void DataToStruct(EMPLOYEE_EDUCATION & recRecord);
	virtual void StructToData(const EMPLOYEE_EDUCATION & recRecord);
	BOOL DeleteAllByEmployeeID(int nEmployeeID);
};


