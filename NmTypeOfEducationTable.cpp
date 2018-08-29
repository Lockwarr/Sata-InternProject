// NmTypeOfEducation.h : Implementation of the CNmTypeOfEducationTable class



// CNmTypeOfEducationTable implementation

// code generated on 21 август 2018 г., 14:31

#include "stdafx.h"
#include "NmTypeOfEducationTable.h"

IMPLEMENT_DYNAMIC(CNmTypeOfEducationTable, CMyTables)

CNmTypeOfEducationTable::CNmTypeOfEducationTable(CDatabase* pdb)
	: CMyTables(pdb)
{
	m_id = 0;
	m_education_type = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}

CString CNmTypeOfEducationTable::GetDefaultConnect()
{
	return _T("DSN=TEST_SERVER;Description=DANGELOV;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DT-VN00476;DATABASE=TEST_DB");
}

CString CNmTypeOfEducationTable::GetDefaultSQL()
{
	return _T("[dbo].[nm_type_of_education]");
}

void CNmTypeOfEducationTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[education_type]"), m_education_type);

}

#ifdef _DEBUG
void CNmTypeOfEducationTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CNmTypeOfEducationTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}

/*virtual*/
void CNmTypeOfEducationTable::DataToStruct(TYPE_OF_EDUCATION & recRecord)
{
	recRecord.nID = m_id;
	strncpy_s(recRecord.szEducationType, m_education_type, sizeof(recRecord.szEducationType));
}

/*virtual*/
void CNmTypeOfEducationTable::StructToData(const TYPE_OF_EDUCATION & recRecord)
{
	m_id = recRecord.nID;
	m_education_type = recRecord.szEducationType;
}

#endif //_DEBUG


