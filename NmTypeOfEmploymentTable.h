// NmTypeOfEducation.h : Declaration of the CNmTypeOfEmploymentTable
#include <vector>
#include "Structures.h"
#include "MyTables.h"
#pragma once

// code generated on 21 август 2018 г., 14:31

class CNmTypeOfEmploymentTable : public CMyTables<TYPE_OF_EMPLOYMENT>
{
public:
	CNmTypeOfEmploymentTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CNmTypeOfEmploymentTable)

	long	m_id;
	CString	m_education_type;


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

	virtual void DataToStruct(TYPE_OF_EMPLOYMENT & recRecord);
	virtual void StructToData(const TYPE_OF_EMPLOYMENT & recRecord);
	virtual BOOL OpenByEmployeeID() { return false; }
};


