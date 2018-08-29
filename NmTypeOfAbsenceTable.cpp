// NmTypeOfAbsenceTable.h : Implementation of the CNmTypeOfAbsenceTable class



// CNmTypeOfAbsenceTable implementation

// code generated on 06 август 2018 г., 9:58

#include "stdafx.h"
#include "NmTypeOfAbsenceTable.h"

IMPLEMENT_DYNAMIC(CNmTypeOfAbsenceTable, CMyTables)

CNmTypeOfAbsenceTable::CNmTypeOfAbsenceTable(CDatabase* pdb)
	: CMyTables(pdb)
{
	m_id = 0;
	m_name = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

CString CNmTypeOfAbsenceTable::GetDefaultConnect()
{
	return _T("DSN=TEST_SERVER;Description=DANGELOV;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DT-VN00476;DATABASE=TEST_DB");
}

CString CNmTypeOfAbsenceTable::GetDefaultSQL()
{
	return _T("[dbo].[nm_type_of_absence]");
}

void CNmTypeOfAbsenceTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[name]"), m_name);

}

#ifdef _DEBUG
void CNmTypeOfAbsenceTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CNmTypeOfAbsenceTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}

/*virtual*/ 
void CNmTypeOfAbsenceTable::DataToStruct(TYPE_OF_ABSENCE & recRecord)
{
	recRecord.nID = m_id;
	strncpy_s(recRecord.szAbsenceType, m_name, sizeof(recRecord.szAbsenceType));
}

/*virtual*/
void CNmTypeOfAbsenceTable::StructToData(const TYPE_OF_ABSENCE & recRecord)
{
	m_id = recRecord.nID;
	m_name = recRecord.szAbsenceType;
}

#endif //_DEBUG

