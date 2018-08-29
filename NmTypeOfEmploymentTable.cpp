// nm_type_of_employment.h : Implementation of the Cnm_type_of_employment class



// Cnm_type_of_employment implementation

// code generated on 21 август 2018 г., 15:59

#include "stdafx.h"
#include "NmTypeOfEmploymentTable.h"

IMPLEMENT_DYNAMIC(CNmTypeOfEmploymentTable, CMyTables)

CNmTypeOfEmploymentTable::CNmTypeOfEmploymentTable(CDatabase* pdb)
	: CMyTables(pdb)
{
	m_id = 0;
	m_type = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

CString CNmTypeOfEmploymentTable::GetDefaultConnect()
{
	return _T("DSN=TEST_SERVER;Description=DANGELOV;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DT-VN00476;DATABASE=TEST_DB");
}

CString CNmTypeOfEmploymentTable::GetDefaultSQL()
{
	return _T("[dbo].[nm_type_of_employment]");
}

void CNmTypeOfEmploymentTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[type]"), m_type);

}

#ifdef _DEBUG
void CNmTypeOfEmploymentTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CNmTypeOfEmploymentTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}

/*virtual*/
void CNmTypeOfEmploymentTable::DataToStruct(TYPE_OF_EMPLOYMENT & recRecord)
{
	recRecord.nID = m_id;
	strncpy_s(recRecord.szEmploymentType, m_type, sizeof(recRecord.szEmploymentType));

}

/*virtual*/
void CNmTypeOfEmploymentTable::StructToData(const TYPE_OF_EMPLOYMENT & recRecord)
{
	m_id = recRecord.nID;
	m_type = recRecord.szEmploymentType;
}

#endif //_DEBUG