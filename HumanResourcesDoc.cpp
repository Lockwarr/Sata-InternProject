
// HumanResourcesDoc.cpp : implementation of the CHumanResourcesDoc class
//
#include "stdafx.h"
#include "MyTables.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#endif

#include "odbcinst.h"
#include "afxdb.h"

#include "EmployeesOffTable.h"
#include "EmployeesViewOffTimeDlg.h"
#include "HumanResourcesDoc.h"
#include "EmployeesTable.h"
#include "NmTypeOfAbsenceTable.h"
#include "EmployeesEducationTable.h"
#include "EmployeesWorkTable.h"
#include "NmTypeOfEducationTable.h"
#include "NmTypeOfEmploymentTable.h"
#include "ViMissingEmployeesTable.h"
#include "NmTypeOfDepartment.h"
#include "NmTypeOfPosition.h"

int i = 0;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHumanResourcesDoc

IMPLEMENT_DYNCREATE(CHumanResourcesDoc, CDocument)

BEGIN_MESSAGE_MAP(CHumanResourcesDoc, CDocument)
END_MESSAGE_MAP()


// CHumanResourcesDoc construction/destruction

CHumanResourcesDoc::CHumanResourcesDoc()
{
	// TODO: add one-time construction code here
}

CHumanResourcesDoc::~CHumanResourcesDoc()
{
}

BOOL CHumanResourcesDoc::AddEmployee(CEmployeeData& oEmployeeData)
{
	CEmployeesTable employeesTable(&theApp.m_database);
	CEmployeesOffTable writeToOffTime(&theApp.m_database);
	CEmployeesEducationTable writeToEducationTable(&theApp.m_database);
	CEmployeesWorkTable writeToWorkTable(&theApp.m_database);

	EMPLOYEE_DATA currentEmployeeInfo;

	if (!theApp.m_database.BeginTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	if (!employeesTable.AddToTable(oEmployeeData.m_recEmployee))
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	for each(auto offTime in oEmployeeData.m_arrEmployeeOffTime)
	{
		offTime.nEmployeeID = oEmployeeData.m_recEmployee.nID;

		if (!writeToOffTime.AddToTable(offTime))
		{
			theApp.m_database.Rollback();
			AfxMessageBox(_T("Failed to add into Times off table!"));
			return FALSE;
		}
	}

	for each(auto educ in oEmployeeData.m_arrEducation)
	{
		educ.nEmployeeID = oEmployeeData.m_recEmployee.nID;

		if (!writeToEducationTable.AddToTable(educ))
		{
			theApp.m_database.Rollback();
			AfxMessageBox(_T("Failed to add into Education table!"));
			return FALSE;
		}
	}

	for each(auto job in oEmployeeData.m_arrWork)
	{
		job.nEmployeeID = oEmployeeData.m_recEmployee.nID;

		if (!writeToWorkTable.AddToTable(job))
		{
			theApp.m_database.Rollback();
			AfxMessageBox(_T("Failed to add into Work table!"));
			return FALSE;
		}
	}

	if (!theApp.m_database.CommitTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	return TRUE;
}

BOOL CHumanResourcesDoc::MissingEmployees(std::vector<MISSING_EMPLOYEES> & filteredEmployees, const MISSING_EMPLOYEES_STANDART& recFilter)
{
	CViMissingEmployeesTable getMissing(&theApp.m_database);

	getMissing.m_strFilter.Format("[start_date] >= '%s' AND [end_date] <= '%s'",
		GetSqlDateTimeString(recFilter.edbStartDate),
		GetSqlDateTimeString(recFilter.edbEndDate));

	if (recFilter.nDepartment > 0)
	{
		getMissing.m_strFilter.AppendFormat(" AND [department_id] = %d ", recFilter.nDepartment);
	}
	
	if (recFilter.nPosition > 0)
	{
		getMissing.m_strFilter.AppendFormat(" AND [position_id] = %d ", recFilter.nPosition);
	}

	if (!getMissing.LoadAll(filteredEmployees))
		return FALSE;

	return TRUE;
}

BOOL CHumanResourcesDoc::FilterBy(std::vector<EMPLOYEE_DATA> & filteredEmployees, CString strFilter, FilterMode eMode)
{
	CEmployeesTable oEmployeesTable(&theApp.m_database);

	if (eMode == eFilterMode_ByName)
	{
		oEmployeesTable.m_strFilter.Format("[first_name] = '%s' ", strFilter);

	}
	else if (eMode == eFilterMode_ByDate)
	{
		oEmployeesTable.m_strFilter.Format("[date] = '%s' ", strFilter);

	}

	return TRUE;
}

BOOL CHumanResourcesDoc::EditEmployee(CEmployeeData& oEmployeeData)
{
	CEmployeesTable writeToEmployees(&theApp.m_database);

	if (!theApp.m_database.BeginTrans())
		return FALSE;

	if (!writeToEmployees.EditTable(oEmployeeData.m_recEmployee, oEmployeeData.m_recEmployee.nID))
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	if (!EditAddDeleteOffTime(oEmployeeData.m_arrEmployeeOffTime, oEmployeeData.m_recEmployee.nID))
	{
		theApp.m_database.Rollback();
		return FALSE;
	}

	if (!EditAddDeleteEducation(oEmployeeData.m_arrEducation, oEmployeeData.m_recEmployee.nID))
	{
		theApp.m_database.Rollback();
		return FALSE;
	}

	if (!EditAddDeleteWork(oEmployeeData.m_arrWork, oEmployeeData.m_recEmployee.nID))
	{
		theApp.m_database.Rollback();
		return FALSE;
	}

	if (!theApp.m_database.CommitTrans())
	{
		theApp.m_database.Rollback();
		return FALSE;
	}

	return TRUE;
}

BOOL CHumanResourcesDoc::EditAddDeleteEducation(std::vector<EMPLOYEE_EDUCATION> &oEducation, int nEmployeeID)
{
	CEmployeesEducationTable editEducation(&theApp.m_database);
	if (oEducation.size() > 0)
	{
		std::vector<EMPLOYEE_EDUCATION> oEmployeeEducation_NotUpdated;
		editEducation.LoadAllFromTable(oEmployeeEducation_NotUpdated, nEmployeeID);

		for each (auto educ in oEducation)
		{
			educ.nEmployeeID = nEmployeeID;
			BOOL isThisNewRecord = TRUE;
			for each (auto educNotUpdated in oEmployeeEducation_NotUpdated)
			{
				if (educ.nID == educNotUpdated.nID)
				{
					COleDateTime dtDateFromCheck(educNotUpdated.dtFrom);
					COleDateTime dtDateFrom(educ.dtFrom);

					COleDateTime dtDateToCheck(educNotUpdated.dtTo);
					COleDateTime dtDateTo(educ.dtTo);

					if (educNotUpdated.nEmployeeID != educ.nEmployeeID ||
						(strcmp(educNotUpdated.szAdditionalInfo, educ.szAdditionalInfo) != 0) ||
						educNotUpdated.nEducationType != educ.nEducationType ||
						(strcmp(educNotUpdated.szSchoolName, educ.szSchoolName) != 0) ||
						(strcmp(educNotUpdated.szSpecialty, educ.szSpecialty) != 0) ||
						(strcmp(educNotUpdated.szTownCountry, educ.szTownCountry) != 0) ||
						dtDateFromCheck != dtDateFrom ||
						dtDateToCheck != dtDateTo)
					{
						if (!editEducation.EditTable(educ, educ.nID))
							return FALSE;

					}
					isThisNewRecord = FALSE;
					break;
				}

			}

			if (isThisNewRecord)
			{
				educ.nEmployeeID = nEmployeeID;
				if (!editEducation.AddToTable(educ))
					return FALSE;
			}

		}

		for (int i = 0; i < oEmployeeEducation_NotUpdated.size(); i++)
		{
			BOOL isDeleted = TRUE;

			for (int z = 0; z < oEducation.size(); z++)
			{
				if (oEmployeeEducation_NotUpdated[i].nID == oEducation[z].nID)
				{
					isDeleted = FALSE;
					break;
				}
			}

			if (isDeleted)
			{
				if (!editEducation.DeleteFromTable(oEmployeeEducation_NotUpdated[i].nID))
					return FALSE;
			}
		}
	}
	else if (oEducation.size() == 0)
	{
		if (!editEducation.DeleteAllByEmployeeID(nEmployeeID))
			return FALSE;
	}
	return TRUE;
}

BOOL CHumanResourcesDoc::EditAddDeleteOffTime(std::vector<EMPLOYEE_OFF_TIME> & oEmployeeOffTime, int nEmployeeID)
{
	CEmployeesOffTable editOffTime(&theApp.m_database);
	if (oEmployeeOffTime.size() > 0)
	{
		std::vector<EMPLOYEE_OFF_TIME> oEmployeeOffTime_NotUpdated;
		editOffTime.LoadAllFromTable(oEmployeeOffTime_NotUpdated, nEmployeeID);

		for (int i = 0; i < oEmployeeOffTime.size(); i++)
		{
			oEmployeeOffTime[i].nEmployeeID = nEmployeeID;
			BOOL isThisNewRecord = TRUE;

			for (int z = 0; z < oEmployeeOffTime_NotUpdated.size(); z++)
			{
				if (oEmployeeOffTime[i].nID == oEmployeeOffTime_NotUpdated[z].nID)
				{
					COleDateTime dtDateFromCheck(oEmployeeOffTime_NotUpdated[z].dtFrom);
					COleDateTime dtDateFrom(oEmployeeOffTime[i].dtFrom);

					COleDateTime dtDateToCheck(oEmployeeOffTime_NotUpdated[z].dtTo);
					COleDateTime dtDateTo(oEmployeeOffTime[i].dtTo);

					if (oEmployeeOffTime_NotUpdated[z].nEmployeeID != oEmployeeOffTime[i].nEmployeeID ||
						oEmployeeOffTime_NotUpdated[z].nDaysCount != oEmployeeOffTime[i].nDaysCount ||
						oEmployeeOffTime_NotUpdated[z].nTypeAbsence != oEmployeeOffTime[i].nTypeAbsence ||
						dtDateFromCheck != dtDateFrom ||
						dtDateToCheck != dtDateTo)
					{
						if (!editOffTime.EditTable(oEmployeeOffTime[i], oEmployeeOffTime[i].nID))
							return FALSE;
					}
					isThisNewRecord = FALSE;
					break;
				}
			}

			if (isThisNewRecord)
			{
				if (!editOffTime.AddToTable(oEmployeeOffTime[i]))
					return FALSE;

			}

		}

		for (int i = 0; i < oEmployeeOffTime_NotUpdated.size(); i++)
		{
			BOOL isDeleted = TRUE;

			for (int z = 0; z < oEmployeeOffTime.size(); z++)
			{
				if (oEmployeeOffTime_NotUpdated[i].nID == oEmployeeOffTime[z].nID)
				{
					isDeleted = FALSE;
					break;
				}
			}

			if (isDeleted)
			{
				if (!editOffTime.DeleteFromTable(oEmployeeOffTime_NotUpdated[i].nID))
					return FALSE;

			}
		}

	}
	else if (oEmployeeOffTime.size() == 0)
	{
		if (!editOffTime.DeleteAllByEmployeeID(nEmployeeID))
			return FALSE;
	}
	return TRUE;
}

BOOL CHumanResourcesDoc::EditAddDeleteWork(std::vector<EMPLOYEE_WORK> & arrEmployeeWork, int nEmployeeID)
{
	CEmployeesWorkTable editWork(&theApp.m_database);
	if (arrEmployeeWork.size() > 0)
	{
		std::vector<EMPLOYEE_WORK> arrEmployeeWork_NotUpdated;
		editWork.LoadAllFromTable(arrEmployeeWork_NotUpdated, nEmployeeID);

		for each (auto job in arrEmployeeWork)
		{
			job.nEmployeeID = nEmployeeID;
			BOOL isThisNewRecord = TRUE;
			for each (auto jobNotUpdated in arrEmployeeWork_NotUpdated)
			{
				if (job.nID == jobNotUpdated.nID)
				{
					COleDateTime dtDateFromCheck(jobNotUpdated.dtFrom);
					COleDateTime dtDateFrom(job.dtFrom);

					COleDateTime dtDateToCheck(jobNotUpdated.dtTo);
					COleDateTime dtDateTo(job.dtTo);

					if (jobNotUpdated.nEmployeeID != job.nEmployeeID ||
						(strcmp(jobNotUpdated.szAdditionalInfo, job.szAdditionalInfo) != 0) ||
						(strcmp(jobNotUpdated.szPosition, job.szPosition) != 0) ||
						(strcmp(jobNotUpdated.szCompanyName, job.szCompanyName) != 0) ||
						(strcmp(jobNotUpdated.szTownCountry, job.szTownCountry) != 0) ||
						jobNotUpdated.nEmploymentType != job.nEmploymentType ||
						dtDateFromCheck != dtDateFrom ||
						dtDateToCheck != dtDateTo)
					{
						if (!editWork.EditTable(job, job.nID))
							return FALSE;
					}
					isThisNewRecord = FALSE;
					break;
				}

			}

			if (isThisNewRecord)
			{
				job.nEmployeeID = nEmployeeID;

				if (!editWork.AddToTable(job))
					return FALSE;

			}

		}

		for (int i = 0; i < arrEmployeeWork_NotUpdated.size(); i++)
		{
			BOOL isDeleted = TRUE;

			for (int z = 0; z < arrEmployeeWork.size(); z++)
			{
				if (arrEmployeeWork_NotUpdated[i].nID == arrEmployeeWork[z].nID)
				{
					isDeleted = FALSE;
					break;
				}
			}

			if (isDeleted)
			{
				if (!editWork.DeleteFromTable(arrEmployeeWork_NotUpdated[i].nID))
					return FALSE;

			}
		}
	}
	else if (arrEmployeeWork.size() == 0)
	{
		if (!editWork.DeleteAllByEmployeeID(nEmployeeID))
			return FALSE;
	}
	return TRUE;
}

BOOL CHumanResourcesDoc::ModifyAbsenceTypeTable(std::vector<TYPE_OF_ABSENCE>& arrAbsences)
{
	CEmployeesTable employeesAll(&theApp.m_database);
	std::vector<EMPLOYEE_DATA> employees;

	CNmTypeOfAbsenceTable absencesTable(&theApp.m_database);
	std::vector<TYPE_OF_ABSENCE> current_Absences;

	absencesTable.LoadAllFromTable(current_Absences, 0);
	employeesAll.LoadAllFromTable(employees, 0);

	TYPE_OF_ABSENCE absence;

	if (!theApp.m_database.BeginTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	//Delete
	for (int z = 0; z < current_Absences.size(); z++)
	{
		BOOL isDeleted = TRUE;

		for (int i = 0; i < arrAbsences.size(); i++)
		{
			if (current_Absences[z].nID == arrAbsences[i].nID)
			{
				isDeleted = FALSE;
				break;
			}
		}

		if (isDeleted)
		{
			for each(auto employee in employees)
			{
				int nEmployeeID = employee.nID;
				std::vector<EMPLOYEE_OFF_TIME> arrCurrentOffTime;
				LoadEmployeeOffTime(arrCurrentOffTime, nEmployeeID);

				for each(auto offTime in arrCurrentOffTime)
				{
					if (offTime.nTypeAbsence == current_Absences[z].nID)
					{
						AfxMessageBox("Can't delete this absence while it is in use!");

						theApp.m_database.Rollback();

						return FALSE;
					}
				}
			}
			if (!absencesTable.DeleteFromTable(current_Absences[z].nID))
			{
				theApp.m_database.Rollback();
				return FALSE;
			}
			current_Absences.erase(current_Absences.begin() + z);
			z--;
		}

	}

	for (int i = 0; i < arrAbsences.size(); i++)
	{
		//Add
		if (arrAbsences[i].nID == 0)
		{
			if (!absencesTable.AddToTable(arrAbsences[i]))
			{
				theApp.m_database.Rollback();
				AfxMessageBox(_T("Failed to add into Times off table!"));
				return FALSE;
			}
		}
		else
		{
			//Edit
			for (int z = 0; z < current_Absences.size(); z++)
			{
				if (arrAbsences[i].nID == current_Absences[z].nID && strcmp(arrAbsences[i].szAbsenceType, current_Absences[z].szAbsenceType))
				{
					if (!absencesTable.EditTable(arrAbsences[i], 0))
					{
						theApp.m_database.Rollback();
						return FALSE;
					}

				}

				for (int y = 0; y < arrAbsences.size(); y++)
				{
					if (arrAbsences[y].nID != current_Absences[z].nID && !strcmp(arrAbsences[y].szAbsenceType, current_Absences[z].szAbsenceType))
					{

						theApp.m_database.Rollback();

						AfxMessageBox("Some absences are repeated twice or more!");

						return FALSE;
					}
				}
			}
		}

	}


	if (!theApp.m_database.CommitTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	return TRUE;
}

BOOL CHumanResourcesDoc::ModifyEmploymentTypeTable(std::vector<TYPE_OF_EMPLOYMENT>& arrEmploymentTypes)
{
	CEmployeesTable employeesAll(&theApp.m_database);
	std::vector<EMPLOYEE_DATA> employees;

	CNmTypeOfEmploymentTable employmentTable(&theApp.m_database);
	std::vector<TYPE_OF_EMPLOYMENT> current_Employment;

	employeesAll.LoadAllFromTable(employees, 0);
	employmentTable.LoadAllFromTable(current_Employment, 0);

	TYPE_OF_EMPLOYMENT employment;

	if (!theApp.m_database.BeginTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	//Delete
	for (int z = 0; z < current_Employment.size(); z++)
	{
		BOOL isDeleted = TRUE;

		for (int i = 0; i < arrEmploymentTypes.size(); i++)
		{
			if (current_Employment[z].nID == arrEmploymentTypes[i].nID)
			{
				isDeleted = FALSE;
				break;
			}
		}

		if (isDeleted)
		{
			for each(auto employee in employees)
			{
				int nEmployeeID = employee.nID;
				std::vector<EMPLOYEE_WORK> arrCurrentWork;
				LoadAllFromTableWork(arrCurrentWork, nEmployeeID);

				for each(auto job in arrCurrentWork)
				{
					if (job.nEmploymentType == current_Employment[z].nID)
					{
						theApp.m_database.Rollback();

						AfxMessageBox("Can't delete this employment type while it is in use!");

						return FALSE;
					}
				}
			}
			if (!employmentTable.DeleteFromTable(current_Employment[z].nID))
			{
				theApp.m_database.Rollback();
				return FALSE;
			}
			current_Employment.erase(current_Employment.begin() + z);
			z--;
		}

	}

	for (int i = 0; i < arrEmploymentTypes.size(); i++)
	{
		//Add
		if (arrEmploymentTypes[i].nID == 0)
		{
			if (!employmentTable.AddToTable(arrEmploymentTypes[i]))
			{
				theApp.m_database.Rollback();
				AfxMessageBox(_T("Failed to add into Times off table!"));
				return FALSE;
			}
		}
		else
		{
			//Edit
			for (int z = 0; z < current_Employment.size(); z++)
			{
				if (arrEmploymentTypes[i].nID == current_Employment[z].nID && strcmp(arrEmploymentTypes[i].szEmploymentType, current_Employment[z].szEmploymentType))
				{
					if (!employmentTable.EditTable(arrEmploymentTypes[i], 0))
					{
						theApp.m_database.Rollback();
						return FALSE;
					}

				}

				for (int y = 0; y < arrEmploymentTypes.size(); y++)
				{
					if (arrEmploymentTypes[y].nID != current_Employment[z].nID && !strcmp(arrEmploymentTypes[y].szEmploymentType, current_Employment[z].szEmploymentType))
					{
						theApp.m_database.Rollback();

						AfxMessageBox("Some absences are repeated twice or more!");

						return FALSE;
					}
				}
			}
		}

	}

	if (!theApp.m_database.CommitTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	return TRUE;
}

BOOL CHumanResourcesDoc::ModifyEducationTypeTable(std::vector<TYPE_OF_EDUCATION>& arrEducationTypes)
{
	CEmployeesTable employeesAll(&theApp.m_database);
	std::vector<EMPLOYEE_DATA> employees;

	CNmTypeOfEducationTable educationTable(&theApp.m_database);
	std::vector<TYPE_OF_EDUCATION> current_Education;

	employeesAll.LoadAllFromTable(employees, 0);
	educationTable.LoadAllFromTable(current_Education, 0);

	TYPE_OF_EDUCATION education;

	if (!theApp.m_database.BeginTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	//Delete
	for (int z = 0; z < current_Education.size(); z++)
	{
		BOOL isDeleted = TRUE;

		for (int i = 0; i < arrEducationTypes.size(); i++)
		{
			if (current_Education[z].nID == arrEducationTypes[i].nID)
			{
				isDeleted = FALSE;
				break;
			}
		}

		if (isDeleted)
		{
			for each(auto employee in employees)
			{
				int nEmployeeID = employee.nID;
				std::vector<EMPLOYEE_EDUCATION> arrCurrentEducation;
				LoadAllFromTableEducations(arrCurrentEducation, nEmployeeID);

				for each(auto educ in arrCurrentEducation)
				{
					if (educ.nEducationType == current_Education[z].nID)
					{
						theApp.m_database.Rollback();

						AfxMessageBox("Can't delete this education type while it is in use!");

						return FALSE;
					}
				}
			}
			if (!educationTable.DeleteFromTable(current_Education[z].nID))
			{
				theApp.m_database.Rollback();
				return FALSE;
			}
			current_Education.erase(current_Education.begin() + z);
			z--;
		}

	}

	for (int i = 0; i < arrEducationTypes.size(); i++)
	{
		//Add
		if (arrEducationTypes[i].nID == 0)
		{
			if (!educationTable.AddToTable(arrEducationTypes[i]))
			{
				theApp.m_database.Rollback();
				AfxMessageBox(_T("Failed to add into education table!"));
				return FALSE;
			}
		}
		else
		{

			//Edit
			for (int z = 0; z < current_Education.size(); z++)
			{
				if (arrEducationTypes[i].nID == current_Education[z].nID && strcmp(arrEducationTypes[i].szEducationType, current_Education[z].szEducationType))
				{
					if (!educationTable.EditTable(arrEducationTypes[i], 0))
					{
						theApp.m_database.Rollback();
						return FALSE;
					}

				}

				for (int y = 0; y < arrEducationTypes.size(); y++)
				{
					if (arrEducationTypes[y].nID != current_Education[z].nID && !strcmp(arrEducationTypes[y].szEducationType, current_Education[z].szEducationType))
					{
						theApp.m_database.Rollback();

						AfxMessageBox("Some education types are repeated twice or more!");

						return FALSE;
					}
				}
			}
		}

	}

	if (!theApp.m_database.CommitTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	return TRUE;
}

BOOL CHumanResourcesDoc::ModifyDepartmentTypeTable(std::vector<DEPARTMENT_TYPE>& arrDepartmentTypes)
{
	CEmployeesTable employeesAll(&theApp.m_database);
	std::vector<EMPLOYEE_DATA> employees;

	CNmTypeOfDepartment departmentTable(&theApp.m_database);
	std::vector<DEPARTMENT_TYPE> current_Department;

	employeesAll.LoadAllFromTable(employees, 0);
	departmentTable.LoadAllFromTable(current_Department, 0);

	DEPARTMENT_TYPE department;

	if (!theApp.m_database.BeginTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	//Delete
	for (int z = 0; z < current_Department.size(); z++)
	{
		BOOL isDeleted = TRUE;

		for (int i = 0; i < arrDepartmentTypes.size(); i++)
		{
			if (current_Department[z].nID == arrDepartmentTypes[i].nID)
			{
				isDeleted = FALSE;
				break;
			}
		}

		if (isDeleted)
		{
			for each(auto employee in employees)
			{

				if (employee.nDepartment == current_Department[z].nID)
				{
					theApp.m_database.Rollback();

					AfxMessageBox("Can't delete this department type while it is in use!");

					return FALSE;
				}
			}
			if (!departmentTable.DeleteFromTable(current_Department[z].nID))
			{
				theApp.m_database.Rollback();
				return FALSE;
			}
		}

		current_Department.erase(current_Department.begin() + z);
		z--;
	}

	for (int i = 0; i < arrDepartmentTypes.size(); i++)
	{
		//Add
		if (arrDepartmentTypes[i].nID == 0)
		{
			if (!departmentTable.AddToTable(arrDepartmentTypes[i]))
			{
				theApp.m_database.Rollback();
				AfxMessageBox(_T("Failed to add into department table!"));
				return FALSE;
			}
		}
		else
		{

			//Edit
			for (int z = 0; z < current_Department.size(); z++)
			{
				if (arrDepartmentTypes[i].nID == current_Department[z].nID && strcmp(arrDepartmentTypes[i].szDepartmentType, current_Department[z].szDepartmentType))
				{
					if (!departmentTable.EditTable(arrDepartmentTypes[i], 0))
					{
						theApp.m_database.Rollback();
						return FALSE;
					}

				}

				for (int y = 0; y < arrDepartmentTypes.size(); y++)
				{
					if (arrDepartmentTypes[y].nID != current_Department[z].nID && !strcmp(arrDepartmentTypes[y].szDepartmentType, current_Department[z].szDepartmentType))
					{
						theApp.m_database.Rollback();

						AfxMessageBox("Some departments types are repeated twice or more!");

						return FALSE;
					}
				}
			}
		}

	}

	if (!theApp.m_database.CommitTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	return TRUE;
}

BOOL CHumanResourcesDoc::ModifyPositionTypeTable(std::vector<POSITION_TYPE>& arrPositionTypes)
{
	CEmployeesTable employeesAll(&theApp.m_database);
	std::vector<EMPLOYEE_DATA> employees;

	CNmTypeOfPosition positionTable(&theApp.m_database);
	std::vector<POSITION_TYPE> current_Position;

	employeesAll.LoadAllFromTable(employees, 0);
	positionTable.LoadAllFromTable(current_Position, 0);

	POSITION_TYPE position;

	if (!theApp.m_database.BeginTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	//Delete
	for (int z = 0; z < current_Position.size(); z++)
	{
		BOOL isDeleted = TRUE;

		for (int i = 0; i < arrPositionTypes.size(); i++)
		{
			if (current_Position[z].nID == arrPositionTypes[i].nID)
			{
				isDeleted = FALSE;
				break;
			}
		}

		if (isDeleted)
		{
			for each(auto employee in employees)
			{

				if (employee.nDepartment == current_Position[z].nID)
				{
					theApp.m_database.Rollback();

					AfxMessageBox("Can't delete this position type while it is in use!");

					return FALSE;
				}
			}

			if (!positionTable.DeleteFromTable(current_Position[z].nID))
			{
				theApp.m_database.Rollback();
				return FALSE;
			}
		}


		current_Position.erase(current_Position.begin() + z);
		z--;
	}

	for (int i = 0; i < arrPositionTypes.size(); i++)
	{
		//Add
		if (arrPositionTypes[i].nID == 0)
		{
			if (!positionTable.AddToTable(arrPositionTypes[i]))
			{
				theApp.m_database.Rollback();
				AfxMessageBox(_T("Failed to add into positions table!"));
				return FALSE;
			}
		}
		else
		{

			//Edit
			for (int z = 0; z < current_Position.size(); z++)
			{
				if (arrPositionTypes[i].nID == current_Position[z].nID && strcmp(arrPositionTypes[i].szPositionType, current_Position[z].szPositionType))
				{
					if (!positionTable.EditTable(arrPositionTypes[i], 0))
					{
						theApp.m_database.Rollback();
						return FALSE;
					}

				}

				for (int y = 0; y < arrPositionTypes.size(); y++)
				{
					if (arrPositionTypes[y].nID != current_Position[z].nID && !strcmp(arrPositionTypes[y].szPositionType, current_Position[z].szPositionType))
					{
						theApp.m_database.Rollback();

						AfxMessageBox("Some position types are repeated twice or more!");

						return FALSE;
					}
				}
			}
		}

	}

	if (!theApp.m_database.CommitTrans())
	{
		theApp.m_database.Rollback();

		return FALSE;
	}

	return TRUE;
}

BOOL CHumanResourcesDoc::AddToEmployeesOffTimesTable(EMPLOYEE_OFF_TIME& employeeOffTime)
{
	if (!theApp.m_database.BeginTrans())
		return FALSE;

	CEmployeesOffTable write(&theApp.m_database);

	if (!write.AddToTable(employeeOffTime))
	{
		theApp.m_database.Rollback();
		return FALSE;
	}

	if (!theApp.m_database.CommitTrans())
	{
		theApp.m_database.Rollback();
		return FALSE;
	}


	return TRUE;
}

BOOL CHumanResourcesDoc::LoadEmployee(EMPLOYEE_DATA & oEmployee, int nID)
{

	CEmployeesTable read(&theApp.m_database);
	if (!read.LoadFromTable(oEmployee, nID))
		return FALSE;

	return TRUE;
}


BOOL CHumanResourcesDoc::LoadAllFromTableEmployees(std::vector<EMPLOYEE_DATA> & arrEmployeesData)
{
	CEmployeesTable read(&theApp.m_database);
	if (!read.LoadAllFromTable(arrEmployeesData, 0))
		return FALSE;

	return TRUE;
}
BOOL CHumanResourcesDoc::LoadAllFromTableEducations(std::vector<EMPLOYEE_EDUCATION>& arrMultipleEducations, int nEmployeeID)
{
	CEmployeesEducationTable read(&theApp.m_database);
	if (!read.LoadAllFromTable(arrMultipleEducations, nEmployeeID))
		return FALSE;

	return TRUE;
}

BOOL CHumanResourcesDoc::LoadAllFromTableWork(std::vector<EMPLOYEE_WORK>& arrWork, int nEmployeeID)
{
	CEmployeesWorkTable read(&theApp.m_database);
	if (!read.LoadAllFromTable(arrWork, nEmployeeID))
		return FALSE;

	return TRUE;
}

BOOL CHumanResourcesDoc::LoadEmployeeOffTime(std::vector<EMPLOYEE_OFF_TIME> & arrEmployeesOffTime, int nEmployeeID)
{
	CEmployeesOffTable read(&theApp.m_database);
	if (!read.LoadAllFromTable(arrEmployeesOffTime, nEmployeeID))
		return FALSE;

	return TRUE;
}

BOOL CHumanResourcesDoc::LoadAbsences(std::vector<TYPE_OF_ABSENCE>& oAbsenceType)
{

	CNmTypeOfAbsenceTable read(&theApp.m_database);
	if (!read.LoadAllFromTable(oAbsenceType, 0))
		return FALSE;

	return TRUE;
}

BOOL CHumanResourcesDoc::LoadEmployment(std::vector<TYPE_OF_EMPLOYMENT>& employmentTypes)
{
	CNmTypeOfEmploymentTable read(&theApp.m_database);
	if (!read.LoadAllFromTable(employmentTypes, 0))
		return FALSE;

	return TRUE;
}
BOOL CHumanResourcesDoc::LoadEducation(std::vector<TYPE_OF_EDUCATION>& educationTypes)
{
	CNmTypeOfEducationTable read(&theApp.m_database);
	if (!read.LoadAllFromTable(educationTypes, 0))
		return FALSE;

	return TRUE;
}

BOOL CHumanResourcesDoc::LoadDepartments(std::vector<DEPARTMENT_TYPE>& departmentTypes)
{
	CNmTypeOfDepartment read(&theApp.m_database);
	if (!read.LoadAllFromTable(departmentTypes, 0))
		return FALSE;

	return TRUE;
}


BOOL CHumanResourcesDoc::LoadPositions(std::vector<POSITION_TYPE>& positionTypes)
{
	CNmTypeOfPosition read(&theApp.m_database);
	if (!read.LoadAllFromTable(positionTypes, 0))
		return FALSE;

	return TRUE;
}


BOOL CHumanResourcesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

BOOL CHumanResourcesDoc::DeleteEmployee(int nEmployeeID)
{
	CEmployeesTable deleteEmployee(&theApp.m_database);
	std::vector<EMPLOYEE_DATA> employeeData;

	CEmployeesOffTable deleteOffTime(&theApp.m_database);

	CEmployeesEducationTable deleteEducation(&theApp.m_database);

	CEmployeesWorkTable deleteWork(&theApp.m_database);

	if (!deleteOffTime.DeleteAllByEmployeeID(nEmployeeID))
		return FALSE;

	if (!deleteEducation.DeleteAllByEmployeeID(nEmployeeID))
		return FALSE;

	if (!deleteWork.DeleteAllByEmployeeID(nEmployeeID))
		return FALSE;

	if (!deleteEmployee.DeleteFromTable(nEmployeeID))
		return FALSE;


	return TRUE;
}

// CHumanResourcesDoc serialization

void CHumanResourcesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CHumanResourcesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CHumanResourcesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CHumanResourcesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CHumanResourcesDoc diagnostics

#ifdef _DEBUG
void CHumanResourcesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHumanResourcesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CHumanResourcesDoc commands
