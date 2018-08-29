// NmTypeOfDepartment.h : Implementation of the CNmTypeOfDepartment class



// CNmTypeOfDepartment implementation

// code generated on 28 август 2018 г., 17:04

#include "stdafx.h"
#include "NmTypeOfDepartment.h"
IMPLEMENT_DYNAMIC(CNmTypeOfDepartment, CMyTables)

CNmTypeOfDepartment::CNmTypeOfDepartment(CDatabase* pdb)
	: CMyTables(pdb)
{
	m_id = 0;
	m_name = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

CString CNmTypeOfDepartment::GetDefaultConnect()
{
	return _T("DSN=TEST_SERVER;Description=DANGELOV;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DT-VN00476;DATABASE=TEST_DB");
}

CString CNmTypeOfDepartment::GetDefaultSQL()
{
	return _T("[dbo].[nm_type_of_department]");
}

void CNmTypeOfDepartment::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[name]"), m_name);

}

#ifdef _DEBUG
void CNmTypeOfDepartment::AssertValid() const
{
	CRecordset::AssertValid();
}

void CNmTypeOfDepartment::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
void CNmTypeOfDepartment::DataToStruct(DEPARTMENT_TYPE & recRecord)
{
	recRecord.nID = m_id;
	strncpy_s(recRecord.szDepartmentType, m_name, sizeof(recRecord.szDepartmentType));

}
void CNmTypeOfDepartment::StructToData(const DEPARTMENT_TYPE & recRecord)
{
	m_id = recRecord.nID;
	m_name = recRecord.szDepartmentType;
}
#endif //_DEBUG


