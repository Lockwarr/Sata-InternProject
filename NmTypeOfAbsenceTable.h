// NmTypeOfAbsenceTable.h : Declaration of the CNmTypeOfAbsenceTable
#include <vector>
#include "Structures.h"
#include "MyTables.h"
#pragma once

// code generated on 06 август 2018 г., 9:58

class CNmTypeOfAbsenceTable : public CMyTables<TYPE_OF_ABSENCE>
{
public:
	CNmTypeOfAbsenceTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CNmTypeOfAbsenceTable)

	long	m_id;
	CString	m_name;
	
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

	virtual void DataToStruct(TYPE_OF_ABSENCE & recRecord);
	virtual void StructToData(const TYPE_OF_ABSENCE & recRecord);
	virtual BOOL OpenByEmployeeID() { return false; }

};


