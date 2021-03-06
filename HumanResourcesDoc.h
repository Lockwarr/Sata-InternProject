
// HumanResourcesDoc.h : interface of the CHumanResourcesDoc class
//


#pragma once

#include "Structures.h"
#include "EnumDialogMode.h"
#include "EmployeesTable.h"
#include "HumanResources.h"
#include "EmployeesWorkTable.h"
#include "EmployeesTable.h"
#include "EmployeesOffTable.h"
#include "EmployeesEducationTable.h"


#include <propkey.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


#include <vector>

class CHumanResourcesDoc : public CDocument
{
protected: // create from serialization only
	CHumanResourcesDoc();
	DECLARE_DYNCREATE(CHumanResourcesDoc)

public:

	BOOL AddEmployee(CEmployeeData& oEmployeeData);
	BOOL MissingEmployees(std::vector<MISSING_EMPLOYEES>& filteredEmployees, const MISSING_EMPLOYEES_STANDART& missingStandart);
	BOOL AddToEmployeesOffTimesTable(EMPLOYEE_OFF_TIME& arrEmployeeOffTime);
	BOOL LoadEmployee(EMPLOYEE_DATA & oEmployee, int nID);
	BOOL FilterBy(std::vector<EMPLOYEE_DATA> & arrEmployeesData, CString filter, FilterMode eMode);
	BOOL EditEmployee(CEmployeeData& oEmployeeData);
	BOOL EditAddDeleteEducation(std::vector<EMPLOYEE_EDUCATION>& oEducation, int nID);
	BOOL EditAddDeleteOffTime(std::vector<EMPLOYEE_OFF_TIME>& oEmployeeOffTime, int nID);
	BOOL EditAddDeleteWork(std::vector<EMPLOYEE_WORK>& arrEmployeeWork, int nID);
	BOOL ModifyAbsenceTypeTable(std::vector<TYPE_OF_ABSENCE>& oAbsences);
	BOOL ModifyEmploymentTypeTable(std::vector<TYPE_OF_EMPLOYMENT>& arrEmploymentTypes);
	BOOL ModifyDepartmentTypeTable(std::vector<DEPARTMENT_TYPE>& arrDepartmentTypes);
	BOOL ModifyPositionTypeTable(std::vector<POSITION_TYPE>& arrPositionTypes);
	BOOL ModifyEducationTypeTable(std::vector<TYPE_OF_EDUCATION>& arrEducationTypes);
	BOOL LoadAllFromTableEmployees(std::vector<EMPLOYEE_DATA>& arrEmployeesData);
	BOOL LoadAllFromTableEducations(std::vector<EMPLOYEE_EDUCATION>& arrMultipleEducations, int nEmployeeID);
	BOOL LoadAllFromTableWork(std::vector<EMPLOYEE_WORK>& arrWork, int nEmployeeID);
	BOOL LoadEmployeeOffTime(std::vector<EMPLOYEE_OFF_TIME>& arrEmployeesOffTime, int nEmployeeID);
	BOOL LoadAbsences(std::vector<TYPE_OF_ABSENCE>& arrAbsenceType);
	BOOL LoadEmployment(std::vector<TYPE_OF_EMPLOYMENT>& employmentTypes);
	BOOL LoadEducation(std::vector<TYPE_OF_EDUCATION>& educationTypes);
	BOOL LoadDepartments(std::vector<DEPARTMENT_TYPE>& departmentTypes);
	BOOL LoadPositions(std::vector<POSITION_TYPE>& positionTypes);
	BOOL DeleteEmployee(int nEmployeeID);


public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

public:
#ifdef _DEBUG

	virtual ~CHumanResourcesDoc();
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

#endif
protected:

	DECLARE_MESSAGE_MAP()


#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};








