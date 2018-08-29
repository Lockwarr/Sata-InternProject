// EmployeesWorkTable.h : Implementation of the CEmployeesWorkTable class



// CEmployeesWorkTable implementation

// code generated on 07 август 2018 г., 17:34

#include "stdafx.h"
#include "EmployeesWorkTable.h"

IMPLEMENT_DYNAMIC(CEmployeesWorkTable, CMyTables)

CEmployeesWorkTable::CEmployeesWorkTable(CDatabase* pdb)
	: CMyTables(pdb)
{
	m_id = 0;
	m_employee_id = 0;
	m_start_date = L"";
	m_end_date = L"";
	m_town_country = L"";
	m_position = L"";
	m_company_name = L"";
	m_additional_information = L"";
	m_employment_type = 0;
	m_nFields = 9;
	m_nDefaultType = dynaset;
}

CString CEmployeesWorkTable::GetDefaultConnect()
{
	return _T("DSN=TEST_SERVER;Description=DANGELOV;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DT-VN00476;DATABASE=TEST_DB");
}

CString CEmployeesWorkTable::GetDefaultSQL()
{
	return _T("[dbo].[employees_work]");
}

void CEmployeesWorkTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Long(pFX, _T("[employee_id]"), m_employee_id);
	RFX_Text(pFX, _T("[start_date]"), m_start_date);
	RFX_Text(pFX, _T("[end_date]"), m_end_date);
	RFX_Text(pFX, _T("[town_country]"), m_town_country);
	RFX_Text(pFX, _T("[position]"), m_position);
	RFX_Text(pFX, _T("[company_name]"), m_company_name);
	RFX_Text(pFX, _T("[additional_information]"), m_additional_information);
	RFX_Long(pFX, _T("[employment_type]"), m_employment_type);

}


#ifdef _DEBUG
void CEmployeesWorkTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEmployeesWorkTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}

/*virtual*/
void CEmployeesWorkTable::DataToStruct(EMPLOYEE_WORK & recRecord)
{
	recRecord.nID = m_id;
	recRecord.nEmployeeID = m_employee_id;
	recRecord.dtFrom = GetDateTimeFromSqlString(m_start_date);
	recRecord.dtTo = GetDateTimeFromSqlString(m_end_date);
	strncpy_s(recRecord.szTownCountry, m_town_country, sizeof(recRecord.szTownCountry));
	strncpy_s(recRecord.szPosition, m_position, sizeof(recRecord.szPosition));
	strncpy_s(recRecord.szCompanyName, m_company_name, sizeof(recRecord.szCompanyName));
	strncpy_s(recRecord.szAdditionalInfo, m_additional_information, sizeof(recRecord.szAdditionalInfo));
	recRecord.nEmploymentType = m_employment_type;
}

/*virtual*/
void CEmployeesWorkTable::StructToData(const EMPLOYEE_WORK & recRecord)
{
	m_employee_id = recRecord.nEmployeeID;
	m_start_date = GetSqlDateTimeString(recRecord.dtFrom);
	m_end_date = GetSqlDateTimeString(recRecord.dtTo);
	m_town_country = recRecord.szTownCountry;
	m_position = recRecord.szPosition;
	m_company_name = recRecord.szCompanyName;
	m_additional_information = recRecord.szAdditionalInfo;
	m_employment_type = recRecord.nEmploymentType;
}

/*virtual*/
BOOL CEmployeesWorkTable::DeleteAllByEmployeeID(int nEmployeeID)
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


