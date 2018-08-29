// ViViMissingEmployeesTable.h : Implementation of the CViMissingEmployeesTable class



// CViMissingEmployeesTable implementation

// code generated on 29 август 2018 г., 15:35

#include "stdafx.h"
#include "ViMissingEmployeesTable.h"
IMPLEMENT_DYNAMIC(CViMissingEmployeesTable, CRecordset)

CViMissingEmployeesTable::CViMissingEmployeesTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_empl_id = 0;
	m_first_name = L"";
	m_last_name = L"";
	m_type_of_absence_id = 0;
	m_type_of_absence = L"";
	m_start_date = L"";
	m_end_date = L"";
	m_days_count = 0;
	m_position_id = 0;
	m_position_name = L"";
	m_department_id = 0;
	m_department_name = L"";
	m_nFields = 12;
	m_nDefaultType = dynaset;
}

CString CViMissingEmployeesTable::GetDefaultConnect()
{
	return _T("DSN=TEST_SERVER;Description=DANGELOV;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DT-VN00476;DATABASE=TEST_DB");
}

CString CViMissingEmployeesTable::GetDefaultSQL()
{
	return _T("[dbo].[vi_missing_employees]");
}

void CViMissingEmployeesTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, _T("[empl_id]"), m_empl_id);
	RFX_Text(pFX, _T("[first_name]"), m_first_name);
	RFX_Text(pFX, _T("[last_name]"), m_last_name);
	RFX_Long(pFX, _T("[type_of_absence_id]"), m_type_of_absence_id);
	RFX_Text(pFX, _T("[type_of_absence]"), m_type_of_absence);
	RFX_Text(pFX, _T("[start_date]"), m_start_date);
	RFX_Text(pFX, _T("[end_date]"), m_end_date);
	RFX_Long(pFX, _T("[days_count]"), m_days_count);
	RFX_Long(pFX, _T("[position_id]"), m_position_id);
	RFX_Text(pFX, _T("[position_name]"), m_position_name);
	RFX_Long(pFX, _T("[department_id]"), m_department_id);
	RFX_Text(pFX, _T("[department_name]"), m_department_name);

}

#ifdef _DEBUG
void CViMissingEmployeesTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CViMissingEmployeesTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}

BOOL CViMissingEmployeesTable::LoadAll(std::vector<MISSING_EMPLOYEES>& arrMissingEmployees)
{

	TRY
	{

		if (!Open())
		return FALSE;

	while (!IsEOF())
	{
		MISSING_EMPLOYEES currentMissingEmployee;

		currentMissingEmployee.nEmployeeID = m_empl_id;
		strncpy_s(currentMissingEmployee.szFirstName, m_first_name, sizeof(currentMissingEmployee.szFirstName));
		strncpy_s(currentMissingEmployee.szLastName, m_last_name, sizeof(currentMissingEmployee.szLastName));
		currentMissingEmployee.dtFrom = GetDateTimeFromSqlString(m_start_date);
		currentMissingEmployee.dtTo = GetDateTimeFromSqlString(m_end_date);
		strncpy_s(currentMissingEmployee.szTypeAbsenceName, m_type_of_absence, sizeof(currentMissingEmployee.szTypeAbsenceName));
		currentMissingEmployee.nDaysCount = m_days_count;
		currentMissingEmployee.nPositionID = m_position_id;
		strncpy_s(currentMissingEmployee.szPosition, m_position_name, sizeof(currentMissingEmployee.szPosition));
		currentMissingEmployee.nDepartmentID = m_department_id;
		strncpy_s(currentMissingEmployee.szDepartment, m_department_name, sizeof(currentMissingEmployee.szDepartment));

		arrMissingEmployees.push_back(currentMissingEmployee);

		MoveNext();
	}
	}CATCH(CDBException, e)
	{
		// If a database exception occured, show error msg
		AfxMessageBox("Database error: " + e->m_strError);
		return FALSE;
	}
	END_CATCH;


	return TRUE;
}
#endif //_DEBUG


