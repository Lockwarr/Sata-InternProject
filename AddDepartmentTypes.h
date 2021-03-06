#pragma once
#include <vector>
#include "HumanResources.h"
#include "Structures.h"
#include "EnumDialogMode.h"

// CAddDepartmentTypes dialog

class CAddDepartmentTypes : public CDialogEx
{

	enum { IDD = IDD_ADD_DEPARTMENT };

public:
	CAddDepartmentTypes(DEPARTMENT_TYPE & recDepartment, DialogMode eMode);
	// standard constructor
	virtual ~CAddDepartmentTypes();

// Dialog Data


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();

private:
	afx_msg void OnBnClickedOk();

private:
	CString m_strDepartmentTypeName;
	DEPARTMENT_TYPE & m_recDepartment;
	DialogMode m_eMode;
	DECLARE_MESSAGE_MAP()

};




