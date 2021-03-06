#pragma once

#include "stdafx.h"

#include <vector>
#include "Structures.h"
#include "EnumDialogMode.h"
#include "MyTabDialog.h"

class CWorkDlg : public CMyTabDialog
{

	enum { IDD = IDD_WORK };

	enum ListCtrlColumns
	{
		eListCtrlColumns_startDate = 0,
		eListCtrlColumns_endDate = 1,
		eListCtrlColumns_town = 2,
		eListCtrlColumns_position = 3,
		eListCtrlColumns_companyName = 4,
		eListCtrlColumns_employmentType = 5,
		eListCtrlColumns_additionalInfo = 6,
	};



public:
	CWorkDlg(std::vector<EMPLOYEE_WORK>& arrEmployeeWork, DialogMode eDialogMode);   // standard constructor
	virtual ~CWorkDlg();

	// Dialog Data

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	BOOL LoadAllFromTable(const std::vector<EMPLOYEE_WORK>& oEmployeeWork);

public:
	void AddElement();
	void EditElement();
	void DeleteElement();

	EMPLOYEE_WORK * GetSelectedRow();
	void OnDblClicked(NMHDR * pNMHDR, LRESULT * pResult); 

private:
	DialogMode m_eDialogMode;

	CListCtrl m_lcsEmployeeWork;

	std::vector<EMPLOYEE_WORK>& m_arrEmployeeWork;

	DECLARE_MESSAGE_MAP()

};
