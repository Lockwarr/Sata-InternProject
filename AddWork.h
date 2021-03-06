#pragma once

#include <vector>
#include "Structures.h"
#include "EnumDialogMode.h"
#include "MydateTimeCtrl.h"

// CAddEducationDlg dialog

class CAddWork : public CDialogEx
{

	enum { IDD = IDD_EMPLOYEE_WORK };

public:
	CAddWork(EMPLOYEE_WORK & recWork, DialogMode eMode);
	virtual ~CAddWork();

	// Dialog Data

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														//	virtual void PreSubclassWindow();

private:

	virtual BOOL OnInitDialog();
	BOOL FillDialog();
	BOOL LoadComboBox();
	BOOL AreEmptyBoxesLeft();
	void OnBnClickedOk();

private:
	
	CString m_strTown;
	CString m_strPosition;
	CString m_strCompanyName;
	CString m_strAdditionalInfo;

	CEdit m_edbID;
	CMydateTimeCtrl m_dtcDateFrom;
	CMydateTimeCtrl m_dtcDateTo;
	CEdit m_edbTown;
	CEdit m_edbPosition;
	CEdit m_edbCompanyName;
	CComboBox m_cmbEmploymentType;
	CEdit m_edbAdditionalInfo;

	DialogMode m_eMode;

	EMPLOYEE_WORK& m_recWork;

	DECLARE_MESSAGE_MAP()
};
