#pragma once
#include <vector>
#include "HumanResources.h"
#include "Structures.h"
#include "EnumDialogMode.h"
// CAddAbsencesTypes dialog

class CAddAbsencesTypes : public CDialogEx
{
	enum { IDD = IDD_ADD_ABSENCES };

public:
	CAddAbsencesTypes(TYPE_OF_ABSENCE& recAbsence, DialogMode eMode);   // standard constructor
	virtual ~CAddAbsencesTypes();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedOk();

private:
	CString m_strAbsenceTypeName;
	TYPE_OF_ABSENCE & m_recAbsence;	
	DialogMode m_eMode;
	DECLARE_MESSAGE_MAP()
};
