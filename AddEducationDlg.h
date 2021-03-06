#pragma once

#include <vector>
#include "Structures.h"
#include "EnumDialogMode.h"
#include "MydateTimeCtrl.h"

// CAddEducationDlg dialog

class CAddEducationDlg : public CDialogEx
{

	enum { IDD = IDD_EMPLOYEE_EDUCATION };

public:
	CAddEducationDlg(EMPLOYEE_EDUCATION & recEducation, DialogMode eMode);
	virtual ~CAddEducationDlg();

	// Dialog Data

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//	virtual void PreSubclassWindow();

private:

	virtual BOOL OnInitDialog();
	BOOL FillDialog();
	BOOL AreEmptyBoxesLeft();
	BOOL LoadComboBox();
	void OnBnClickedOk();


private:

	CComboBox m_education_comboBox;

	CString m_strSpecialty;
	CString m_strTown;
	CString m_strSchoolName;
	CString m_strAdditionalInfo;

	CEdit m_edbID;
	CMydateTimeCtrl m_dtcDateFrom;
	CMydateTimeCtrl m_dtcDateTo;
	CEdit m_edbEducationType;
	CEdit m_edbSpecialty;
	CEdit m_edbTown;
	CEdit m_edbSchoolName;
	CEdit m_edbAdditionalInfo;

	DialogMode m_eMode;

	EMPLOYEE_EDUCATION& m_oEducation;

	DECLARE_MESSAGE_MAP()

};
