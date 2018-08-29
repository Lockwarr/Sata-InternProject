#pragma once
#include <vector>

enum FilterMode
{
	eFilterMode_ByName,
	eFilterMode_ByDate
};

struct EMPLOYEE_DATA
{
	int nID;	// int
	char szFirstName[51];
	char szSurname[51];
	char szLastName[51];
	char szPIN[51];		// za kopirane strncpy()
	char szEmail[51];
	char szPhoneNumber[51];
	DBTIMESTAMP dtDate;	// DBTIMESTAMP
	int nDepartment;
	int nPosition;

	EMPLOYEE_DATA()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct DEPARTMENT_TYPE
{
	int nID;
	char szDepartmentType[51];

	DEPARTMENT_TYPE()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct POSITION_TYPE
{
	int nID;
	char szPositionType[51];

	POSITION_TYPE()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct MISSING_EMPLOYEES_STANDART
{
	DBTIMESTAMP edbStartDate;
	DBTIMESTAMP edbEndDate;
	int nDepartment;
	int nPosition;

	MISSING_EMPLOYEES_STANDART()
	{
		ZeroMemory(this, sizeof(*this));
	}	
};

struct MISSING_EMPLOYEES
{
	int nEmployeeID;
	char szFirstName[51];
	char szLastName[51];
	char szTypeAbsenceName[51];
	DBTIMESTAMP dtFrom;
	DBTIMESTAMP dtTo;
	int nDaysCount;
	int nPositionID;
	char szPosition[51];
	int nDepartmentID;
	char szDepartment[51];
	
	MISSING_EMPLOYEES()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct EMPLOYEE_OFF_TIME
{
	int nID;
	int nEmployeeID;
	int nTypeAbsence;
	DBTIMESTAMP dtFrom;
	DBTIMESTAMP dtTo;
	int nDaysCount;

	EMPLOYEE_OFF_TIME()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct TYPE_OF_ABSENCE
{
	int nID;
	char szAbsenceType[51];

	TYPE_OF_ABSENCE()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct TYPE_OF_EDUCATION
{
	int nID;
	char szEducationType[51];

	TYPE_OF_EDUCATION()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct TYPE_OF_EMPLOYMENT
{
	int nID;
	char szEmploymentType[51];

	TYPE_OF_EMPLOYMENT()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct EMPLOYEE_WORK
{
	int	nID;
	int nEmployeeID;
	DBTIMESTAMP	dtFrom;
	DBTIMESTAMP	dtTo;
	char szTownCountry[51];
	char szPosition[51];
	char szCompanyName[51];
	int nEmploymentType;
	char szAdditionalInfo[501];


	EMPLOYEE_WORK()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct EMPLOYEE_EDUCATION
{
	int	nID;
	int nEmployeeID;
	DBTIMESTAMP	dtFrom;
	DBTIMESTAMP	dtTo;
	int nEducationType;
	char szSpecialty[51];
	char szTownCountry[51];
	char szSchoolName[51];
	char szAdditionalInfo[501];

	EMPLOYEE_EDUCATION()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

class CEmployeeData
{
public:
	EMPLOYEE_DATA m_recEmployee;
	std::vector<EMPLOYEE_OFF_TIME> m_arrEmployeeOffTime;
	std::vector<EMPLOYEE_EDUCATION> m_arrEducation;
	std::vector<EMPLOYEE_WORK> m_arrWork;
};
