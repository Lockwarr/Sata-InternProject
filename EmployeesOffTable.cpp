// EmployeesOffTable.h : Implementation of the CEmployeesOffTable class



// CEmployeesOffTable implementation

// code generated on 03 август 2018 г., 15:02

#include "stdafx.h"
#include "EmployeesOffTable.h"
#include "HumanResources.h"

IMPLEMENT_DYNAMIC(CEmployeesOffTable, CMyTables)

CEmployeesOffTable::CEmployeesOffTable(CDatabase* pdb)
	: CMyTables(pdb)
{
	m_id = 0;
	m_employee_id = 0;
	m_type_of_absence = 0;
	m_start_date = L"";
	m_end_date = L"";
	m_days_resting = 0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}

CString CEmployeesOffTable::GetDefaultConnect()
{
	return _T("DSN=TEST_SERVER;Description=DANGELOV;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DT-VN00476;DATABASE=TEST_DB");
}

CString CEmployeesOffTable::GetDefaultSQL()
{
	return _T("[dbo].[employees_off_time]");
}

void CEmployeesOffTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Long(pFX, _T("[employee_id]"), m_employee_id);
	RFX_Long(pFX, _T("[type_of_absence]"), m_type_of_absence);
	RFX_Text(pFX, _T("[start_date]"), m_start_date);
	RFX_Text(pFX, _T("[end_date]"), m_end_date);
	RFX_Long(pFX, _T("[days_resting]"), m_days_resting);

}

#ifdef _DEBUG
void CEmployeesOffTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEmployeesOffTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}

/*virtual*/
void CEmployeesOffTable::DataToStruct(EMPLOYEE_OFF_TIME & recRecord)
{
	recRecord.nID = m_id;
	recRecord.nEmployeeID = m_employee_id;
	recRecord.nTypeAbsence = m_type_of_absence;
	recRecord.dtFrom = GetDateTimeFromSqlString(m_start_date);
	recRecord.dtTo = GetDateTimeFromSqlString(m_end_date);
	recRecord.nDaysCount = m_days_resting;
}

/*virtual*/
void CEmployeesOffTable::StructToData(const EMPLOYEE_OFF_TIME & recRecord)
{
	m_employee_id = recRecord.nEmployeeID;
	m_type_of_absence = recRecord.nTypeAbsence;
	m_start_date = GetSqlDateTimeString(recRecord.dtFrom);
	m_end_date = GetSqlDateTimeString(recRecord.dtTo);
	m_days_resting = recRecord.nDaysCount;
}

/*virtual*/
BOOL CEmployeesOffTable::DeleteAllByEmployeeID(int employeeID)
{
	TRY
	{
		m_strFilter.Format("[employee_id] = %d", employeeID);

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


