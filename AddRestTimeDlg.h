#pragma once
#include "MydateTimeCtrl.h"
#include "Structures.h"
#include "enumdialogmode.h"

class CAddRestTimeDlg : public CDialogEx
{

	enum { IDD = IDD_ADD_OFF_TIME };

public:
	CAddRestTimeDlg(EMPLOYEE_OFF_TIME & recEmployeeOffTime, DialogMode offTimeMode);
	~CAddRestTimeDlg();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

public:
	void OnBnClickedFromToOk();
	void FillDialog();

	BOOL LoadComboBox();

private:
	CString m_strDaysOff;

	CEdit m_edbDaysOff;	// m_edbDaysOff
	short m_sDaysOff;	// m_sDaysOff

	CComboBox m_cmbTimeOff;	

	CMydateTimeCtrl  m_dtcDateFrom;
	CMydateTimeCtrl  m_dtcDateTo;

	DialogMode m_eMode;

public:

	EMPLOYEE_OFF_TIME & m_oEmployeeOffTime;
	
	DECLARE_MESSAGE_MAP()

};
