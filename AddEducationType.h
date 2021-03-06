#pragma once
#include <vector>
#include "HumanResources.h"
#include "Structures.h"
#include "EnumDialogMode.h"

// CAddEducationDlgType dialog

class CAddEducationDlgType : public CDialogEx
{
	enum { IDD = IDD_ADD_EDUCATION };

public:
	CAddEducationDlgType(TYPE_OF_EDUCATION& recEducation, DialogMode eMode);   // standard constructor
	virtual ~CAddEducationDlgType();

	


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();

private:
	afx_msg void OnBnClickedOk();

private:
	CString m_strEducationTypeName;
	TYPE_OF_EDUCATION & m_recEducation;	
	DialogMode m_eMode;
	DECLARE_MESSAGE_MAP()

};



