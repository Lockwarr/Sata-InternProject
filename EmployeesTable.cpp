// employees.h : Implementation of the CEmployeesTable class

// CEmployeesTable implementation

// code generated on 26 ўыш 2018 у., 10:47

#include "stdafx.h"
#include "EmployeesTable.h"
#include "HumanResources.h"
#include "EmployeesOffTable.h"

IMPLEMENT_DYNAMIC(CEmployeesTable, CMyTables)

CEmployeesTable::CEmployeesTable(CDatabase* pdb)
	: CMyTables(pdb)
{
	m_id = 0;
	m_first_name = L"";
	m_surname = L"";
	m_last_name = L"";
	m_pin = L"";
	m_email = L"";
	m_phone_number = L"";
	m_date = L"";
	m_department = 0;
	m_position = 0;
	m_nFields = 10;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CEmployeesTable::GetDefaultConnect()
{
	return _T("DSN=TEST_SERVER;Description=DANGELOV;Trusted_Connection=No;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DT-VN00476;DATABASE=TEST_DB");
}

CString CEmployeesTable::GetDefaultSQL()
{
	return _T("[dbo].[employees]");
}

void CEmployeesTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[first_name]"), m_first_name);
	RFX_Text(pFX, _T("[surname]"), m_surname);
	RFX_Text(pFX, _T("[last_name]"), m_last_name);
	RFX_Text(pFX, _T("[pin]"), m_pin);
	RFX_Text(pFX, _T("[email]"), m_email);
	RFX_Text(pFX, _T("[phone_number]"), m_phone_number);
	RFX_Text(pFX, _T("[date]"), m_date);
	RFX_Long(pFX, _T("[department]"), m_department);
	RFX_Long(pFX, _T("[position]"), m_position);

	m_nDefaultType = dynaset;
}

#ifdef _DEBUG
void CEmployeesTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEmployeesTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}

/*virtual*/
void CEmployeesTable::DataToStruct(EMPLOYEE_DATA & recRecord)
{
	recRecord.nID = m_id;
	strncpy_s(recRecord.szFirstName, m_first_name, sizeof(recRecord.szFirstName));	// sizeof i na drugite
	strncpy_s(recRecord.szSurname, m_surname, sizeof(recRecord.szSurname));
	strncpy_s(recRecord.szLastName, m_last_name, sizeof(recRecord.szLastName));
	strncpy_s(recRecord.szPIN, m_pin, sizeof(recRecord.szPIN));
	strncpy_s(recRecord.szEmail, m_email, sizeof(recRecord.szEmail));
	strncpy_s(recRecord.szPhoneNumber, m_phone_number, sizeof(recRecord.szPhoneNumber));
	recRecord.dtDate = GetDateTimeFromSqlString(m_date);
	recRecord.nDepartment = m_department;
	recRecord.nPosition = m_position;
}

/*virtual*/
void CEmployeesTable::StructToData(const EMPLOYEE_DATA & recRecord)
{

	m_first_name = recRecord.szFirstName;
	m_surname = recRecord.szSurname;
	m_last_name = recRecord.szLastName;
	m_pin = recRecord.szPIN;
	m_email = recRecord.szEmail;
	m_phone_number = recRecord.szPhoneNumber;
	m_date = GetSqlDateTimeString(recRecord.dtDate);
	m_department = recRecord.nDepartment;
	m_position = recRecord.nPosition;
}

#endif //_DEBUG