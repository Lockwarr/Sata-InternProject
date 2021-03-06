#pragma once


// CMissingEmployeesDatesPickerDialog dialog
#include "MydateTimeCtrl.h"
#include "Structures.h"

class CMissingEmployeesDatesPickerDialog : public CDialogEx
{
	enum { IDD = IDD_EMPLOYEES_MISSING };

public:
	CMissingEmployeesDatesPickerDialog(MISSING_EMPLOYEES_STANDART & missingStandart);   // standard constructor
	virtual ~CMissingEmployeesDatesPickerDialog();

	// Dialog Data

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support	

public:
	BOOL OnInitDialog();
	BOOL LoadComboBoxes();
	void OnBnClickedOk();

private:
	CMydateTimeCtrl m_edbStartDate;
	CMydateTimeCtrl m_edbEndDate;

	CComboBox m_cmbDepartment;
	CComboBox m_cmbPosition;

	MISSING_EMPLOYEES_STANDART & m_missingStandart;

	DECLARE_MESSAGE_MAP()

};
