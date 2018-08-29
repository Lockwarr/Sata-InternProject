// EmployeesEducationTable.h : Implementation of the CEmployeesEducationTable class



// CEmployeesEducationTable implementation

// code generated on 07 август 2018 г., 17:34

#include "stdafx.h"
#include "EmployeesEducationTable.h"
IMPLEMENT_DYNAMIC(CEmployeesEducationTable, CMyTables)

CEmployeesEducationTable::CEmployeesEducationTable(CDatabase* pdb)
	: CMyTables(pdb)
{
	m_id = 0;
	m_employee_id = 0;
	m_start_date = L"";
	m_end_date = L"";
	m_education_type = 0;
	m_specialty = L"";
	m_town_country = L"";
	m_school_name = L"";
	m_additional_information = L"";
	m_nFields = 9;
	m_nDefaultType = dynaset;
}

CString CEmployeesEducationTable::GetDefaultConnect()
{
	return _T("DSN=TEST_SERVER;Description=DANGELOV;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DT-VN00476;DATABASE=TEST_DB");
}

CString CEmployeesEducationTable::GetDefaultSQL()
{
	return _T("[dbo].[employees_education]");
}

void CEmployeesEducationTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Macros such as RFX_Text() and RFX_Int() are dependent on the
	// type of the member variable, not the type of the field in the database.
	// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Long(pFX, _T("[employee_id]"), m_employee_id);
	RFX_Text(pFX, _T("[start_date]"), m_start_date);
	RFX_Text(pFX, _T("[end_date]"), m_end_date);
	RFX_Long(pFX, _T("[education_type]"), m_education_type);
	RFX_Text(pFX, _T("[specialty]"), m_specialty);
	RFX_Text(pFX, _T("[town_country]"), m_town_country);
	RFX_Text(pFX, _T("[school_name]"), m_school_name);
	RFX_Text(pFX, _T("[additional_information]"), m_additional_information);

}
/////////////////////////////////////////////////////////////////////////////
// CEmployeesEducationTable diagnostics

#ifdef _DEBUG
void CEmployeesEducationTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEmployeesEducationTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}

/*virtual*/
void CEmployeesEducationTable::DataToStruct(EMPLOYEE_EDUCATION & recRecord)
{

	recRecord.nID = m_id;
	recRecord.nEmployeeID = m_employee_id;
	recRecord.dtFrom = GetDateTimeFromSqlString(m_start_date);
	recRecord.dtTo = GetDateTimeFromSqlString(m_end_date);
	recRecord.nEducationType = m_education_type;
	strncpy_s(recRecord.szSpecialty, m_specialty, sizeof(recRecord.szSpecialty));
	strncpy_s(recRecord.szTownCountry, m_town_country, sizeof(recRecord.szTownCountry));
	strncpy_s(recRecord.szSchoolName, m_school_name, sizeof(recRecord.szSchoolName));
	strncpy_s(recRecord.szAdditionalInfo, m_additional_information, sizeof(recRecord.szAdditionalInfo));

}

/*virtual*/
void CEmployeesEducationTable::StructToData(const EMPLOYEE_EDUCATION & recRecord)
{

	m_employee_id = recRecord.nEmployeeID;
	m_start_date = GetSqlDateTimeString(recRecord.dtFrom);
	m_end_date = GetSqlDateTimeString(recRecord.dtTo);
	m_education_type = recRecord.nEducationType;
	m_specialty = recRecord.szSpecialty;
	m_town_country = recRecord.szTownCountry;
	m_school_name = recRecord.szSchoolName;
	m_additional_information = recRecord.szAdditionalInfo;

}

/*virtual*/
BOOL CEmployeesEducationTable::DeleteAllByEmployeeID(int nEmployeeID)
{
	TRY
	{
		m_strFilter.Format("[employee_id] = %d", nEmployeeID);

	if (!Open())
		return FALSE;

	if (!CanAppend())
		return FALSE;

	while (GetRecordCount() != 0)
	{
		CRecordset::Delete();
		MoveNext();
	}

	}CATCH(CDBException, e)
	{
		// If a database exception occured, show error msg
		AfxMessageBox("Database error: " + e->m_strError);
		return FALSE;
	}
	END_CATCH;
	Close();
	return TRUE;
}
#endif //_DEBUG


