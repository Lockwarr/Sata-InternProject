// NmTypeOfPosition.h : Implementation of the CNmTypeOfPosition class



// CNmTypeOfPosition implementation

// code generated on 28 август 2018 г., 17:05

#include "stdafx.h"
#include "NmTypeOfPosition.h"
IMPLEMENT_DYNAMIC(CNmTypeOfPosition, CMyTables)

CNmTypeOfPosition::CNmTypeOfPosition(CDatabase* pdb)
	: CMyTables(pdb)
{
	m_id = 0;
	m_name = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

CString CNmTypeOfPosition::GetDefaultConnect()
{
	return _T("DSN=TEST_SERVER;Description=DANGELOV;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DT-VN00476;DATABASE=TEST_DB");
}

CString CNmTypeOfPosition::GetDefaultSQL()
{
	return _T("[dbo].[nm_type_of_position]");
}

void CNmTypeOfPosition::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[name]"), m_name);

}
/////////////////////////////////////////////////////////////////////////////
// CNmTypeOfPosition diagnostics

#ifdef _DEBUG
void CNmTypeOfPosition::AssertValid() const
{
	CRecordset::AssertValid();
}

void CNmTypeOfPosition::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
void CNmTypeOfPosition::DataToStruct(POSITION_TYPE & recRecord)
{
	recRecord.nID = m_id;
	strncpy_s(recRecord.szPositionType, m_name, sizeof(recRecord.szPositionType));
}
void CNmTypeOfPosition::StructToData(const POSITION_TYPE & recRecord)
{
	m_id = recRecord.nID;
	m_name = recRecord.szPositionType;
}
#endif //_DEBUG


