// NmTypeOfDepartment.h : Declaration of the CNmTypeOfDepartment

#pragma once
#include "Structures.h"
#include <vector>
#include "MyTables.h"

// code generated on 28 август 2018 г., 17:04

class CNmTypeOfDepartment : public CMyTables<DEPARTMENT_TYPE>
{
public:
	CNmTypeOfDepartment(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CNmTypeOfDepartment)

	long	m_id;
	CString		m_name;

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
#endif

	virtual void DataToStruct(DEPARTMENT_TYPE & recRecord);
	virtual void StructToData(const DEPARTMENT_TYPE & recRecord);
	virtual BOOL OpenByEmployeeID() { return false; }

};


