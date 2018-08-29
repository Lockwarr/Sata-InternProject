#pragma once
#include "resource.h"
#include "Structures.h"
#include <vector>
#include "EnumDialogMode.h"
#include "MydateTimeCtrl.h"
#include "MyTabDialog.h"

class CEmployeeDialog : public CMyTabDialog
{

	enum { IDD = IDD_EMPLOYEE_SEARCH};

public:
	CEmployeeDialog(EMPLOYEE_DATA & oEmployee, DialogMode eMode);
	~CEmployeeDialog();

public:


private:
	virtual void DoDataExchange(CDataExchange* pDX);    
	virtual BOOL OnInitDialog();

	BOOL FillComboBoxes();
	BOOL LoadComboBoxes();
	BOOL AreEmptyBoxesLeft();
	BOOL ValidatePIN();


private:
	CString m_strFirstName;
	CString m_strSurName;
	CString m_strLastName;
	CString m_strPhoneNumber;
	CString m_strEmail;
	CString m_strPIN;
	CMydateTimeCtrl m_edbDate;
	CString m_strCaption;

	CComboBox m_cmbDepartment;
	CComboBox m_cmbPosition;

	CEdit m_EdbFirstName;
	CEdit m_EdbSurName;
	CEdit m_EdbLastName;
	CEdit m_EdbPhoneNumber;
	CEdit m_EdbEmail;
	CEdit m_EdbPIN;
	CEdit m_EdbDate;
	CEdit m_EdbID;

	DialogMode m_eMode;

	EMPLOYEE_DATA& m_recEmployee;

public:

	virtual void AddElement() {}
	virtual void EditElement() {}
	virtual void DeleteElement() {}
	virtual bool ShowButtons() { return false; }
public:


	BOOL onBnClickedOK();

	DECLARE_MESSAGE_MAP()

};

