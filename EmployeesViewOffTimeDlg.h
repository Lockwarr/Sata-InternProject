#pragma once
#include "SortListCtrl.h"
#include <vector>
#include "MyTabDialog.h"

// CEmployeesViewOffTimeDlg dialog

class CEmployeesViewOffTimeDlg : public CMyTabDialog
{
	enum { IDD = IDD_EMPLOYEE_OFF_TIME };

	enum ListCtrlColumns
	{
		eListCtrlColumns_typeOfAbsence =0,
		eListCtrlColumns_startDate = 1,
		eListCtrlColumns_endDate = 2,
		eListCtrlColumns_daysResting = 3,
	};

public:

	CEmployeesViewOffTimeDlg(std::vector<EMPLOYEE_OFF_TIME>& arrEmployeeOffTime, DialogMode eDialogMode);
	virtual ~CEmployeesViewOffTimeDlg();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:

	BOOL OnInitDialog();
	BOOL LoadAllFromTable(const std::vector<EMPLOYEE_OFF_TIME>& oEmployeeOffTime);

private:
	DialogMode m_eDialogMode;

	CListCtrl m_lscEmployeeOffTime;	

	std::vector<EMPLOYEE_OFF_TIME>& m_arrEmployeeOffTime;

public:
	void AddElement() override;
	void EditElement();
	void DeleteElement();


	EMPLOYEE_OFF_TIME * GetSelectedRow();
	void OnDblClicked(NMHDR * pNMHDR, LRESULT * pResult);


	DECLARE_MESSAGE_MAP()
};
