#pragma once
#include <vector>
#include "HumanResources.h"
#include "Structures.h"
#include "EnumDialogMode.h"

// CAddEmploymentType dialog

class CAddEmploymentType : public CDialogEx
{

	enum { IDD = IDD_ADD_EMPLOYMENT };


public:
	CAddEmploymentType(TYPE_OF_EMPLOYMENT& recEmploymentType, DialogMode eMode);   // standard constructor
	virtual ~CAddEmploymentType();

// Dialog Data


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();

private:
	afx_msg void OnBnClickedOk();

private:
	CString m_strEmploymentTypeName;
	TYPE_OF_EMPLOYMENT & m_recEmployment;
	DialogMode m_eMode;
	DECLARE_MESSAGE_MAP()
};



