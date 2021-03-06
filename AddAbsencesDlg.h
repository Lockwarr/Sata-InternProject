#pragma once
#include "SortListCtrl.h"
#include <vector>
// CAddAbsencesDlg dialog

class CAddAbsencesDlg : public CDialogEx
{
	enum { IDD = IDD_ABSENCES_TYPES};

public:
	CAddAbsencesDlg(std::vector<TYPE_OF_ABSENCE>& arrAbsenceType);   // standard constructor
	virtual ~CAddAbsencesDlg();

// Dialog Data


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


public:
	BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedAbsencesAdd();
	afx_msg void OnBnClickedAbsencesEdit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAbsencesDelete();

	BOOL LoadAllFromTableToListCtrl();

	DECLARE_MESSAGE_MAP()

private:

	CListCtrl m_lscAbsences_ListCtrl;

	std::vector<TYPE_OF_ABSENCE>& m_arrAbsenceType;

};
