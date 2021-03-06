#pragma once

#include "Structures.h"
#include <vector>

// CDepartmentDlg dialog

class CDepartmentDlg : public CDialogEx
{

	enum { IDD = IDD_DEPARTMENT };

public:
	CDepartmentDlg(std::vector<DEPARTMENT_TYPE>& arrAbsenceType);   // standard constructor
	virtual ~CDepartmentDlg();

	// Dialog Data
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


public:
	BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedDepartmentAdd();
	afx_msg void OnBnClickedDepartmentEdit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDepartmentDelete();

	BOOL LoadAllFromTableToListCtrl();

	DECLARE_MESSAGE_MAP()

private:

	CListCtrl m_lscDepartments_ListCtrl;

	std::vector<DEPARTMENT_TYPE>& m_arrDepartmentType;

};

