#pragma once
#include "Structures.h"
#include <vector>

// CMissingEmployeesDlg dialog

class CMissingEmployeesDlg : public CDialogEx
{
	enum { IDD = IDD_MISSING_EMPLOYEES };

	enum ListCtrlColumns
	{
		eListCtrlColumns_first_name = 0,
		eListCtrlColumns_last_name = 1,
		eListCtrlColumns_type_of_absence = 2,
		eListCtrlColumns_start_date = 3,
		eListCtrlColumns_end_date = 4,
		eListCtrlColumns_days_restnig = 5,
		eListCtrlColumns_department = 6,
		eListCtrlColumns_position = 7,

	};

public:
	CMissingEmployeesDlg(std::vector<MISSING_EMPLOYEES>& arrMissingList);
	// standard constructor
	virtual ~CMissingEmployeesDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME

#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();

	BOOL LoadAll(const std::vector<MISSING_EMPLOYEES>& arrMissingEmplyoees);

private:
	CListCtrl m_lscMissingEmployees;

	std::vector<MISSING_EMPLOYEES> & m_arrMissingList;

	DECLARE_MESSAGE_MAP()

};
