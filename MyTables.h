#pragma once
#include "stdafx.h"
#include "Structures.h"

//class CMyTables : public CRecordset
//{
//public:
//	CMyTables() {}
//	CMyTables(CDatabase* test) {}
//
//public:
//	virtual BOOL AddToTable() = 0;
//	virtual BOOL LoadAllFromTable() = 0;
//	virtual BOOL LoadFromTable() = 0;
//	virtual BOOL EditTable() = 0;
//	virtual BOOL DeleteTable() = 0;
//};



template<class T>
class CMyTables : public CRecordset
{
public:
	CMyTables(CDatabase* pDatabase = NULL) : CRecordset(pDatabase)
	{
	}

protected:

	virtual void DataToStruct(T & recRecord) = 0;
	virtual void StructToData(const T & recRecord) = 0;
	virtual BOOL OpenByEmployeeID() { return true; }

public:
	BOOL AddToTable(T & recRecord)
	{
		TRY
		{

		if (!Open())
			return FALSE;

		if (!CanAppend())
			return FALSE;

		AddNew();

		StructToData(recRecord);

		if (!Update())
			return FALSE;

		//if(SQLExecDirect(m_hstmt, (SQLCHAR*)"select @@identity", SQL_NTS) == SQL_ERROR)
		//	return FALSE;
		//
		//if(SQLGetData(m_hstmt, 1, SQL_C_NUMERIC, &recRecord.nID, sizeof(recRecord.nID), NULL) == SQL_ERROR)
		//	return FALSE;

		CRecordset oRecordset(m_pDatabase);
		oRecordset.Open(CRecordset::forwardOnly, _T("SELECT @@Identity"));
		CString currentData;

		if (!oRecordset.IsEOF())
		{
			oRecordset.GetFieldValue((short)0, currentData);
		}

		oRecordset.Close();

		recRecord.nID = atoi(currentData);

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

	BOOL LoadAllFromTable(std::vector<T>& recRecord, int nID)
	{
		TRY
		{
			if (OpenByEmployeeID())
			{
				m_strFilter.Format("[employee_id] = %d", nID);
			}

				if (!Open())
				return FALSE;

			while (!IsEOF())
			{
				T currentRecRecord;

				DataToStruct(currentRecRecord);

				recRecord.push_back(currentRecRecord);

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

	BOOL LoadFromTable(T& recRecord, int nID)
	{
		TRY
		{

		m_strFilter.Format("[id] = %d", nID);

		if (!Open())
			return FALSE;

		DataToStruct(recRecord);

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

	BOOL EditTable(T & recRecord, int nID)
	{

		TRY
		{
			m_strFilter.Format("[id] = %d", nID);

		if (!Open())
			return FALSE;

		if (!CanAppend())
			return FALSE;

		while (!IsEOF())
		{

			Edit();

			StructToData(recRecord);

			//Update
			Update();

			//if (!CanUpdate())
			//	return FALSE;
			//
			//if (!Update())
			//	return FALSE;

			break;

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

	BOOL DeleteFromTable(int nID)
	{
		TRY
		{

			m_strFilter.Format("[id] = %d", nID);

		if (!Open())
			return FALSE;

		if (!CanAppend())
			return FALSE;

		if (!IsEOF())
			Delete();

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

};

