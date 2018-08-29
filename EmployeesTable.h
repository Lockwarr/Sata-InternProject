// employees.h : Declaration of the CEmployeesTable

#pragma once
#include "Structures.h"
#include <vector>
#include "MyTables.h"

// code generated on 26 ўыш 2018 у., 10:47

class CEmployeesTable : public CMyTables<EMPLOYEE_DATA>
{
public:
	CEmployeesTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEmployeesTable)

	long	m_id;
	CString	m_first_name;
	CString	m_surname;
	CString	m_last_name;
	CString	m_pin;
	CString	m_email;
	CString	m_phone_number;
	CString	m_date;
	long m_department;
	long m_position;

public:
	virtual CString GetDefaultConnect();	

	virtual CString GetDefaultSQL(); 	
	virtual void DoFieldExchange(CFieldExchange* pFX);	


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public: 

	virtual void DataToStruct(EMPLOYEE_DATA & recRecord);
	virtual void StructToData(const EMPLOYEE_DATA & recRecord);
	virtual BOOL OpenByEmployeeID() { return false; }

};


