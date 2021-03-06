#pragma once
#include "SortListCtrl.h"
#include <vector>

// CEmploymentDlg dialog

class CEmploymentDlg : public CDialogEx
{

	enum { IDD = IDD_EMPLOYMENT };
	
public:
	CEmploymentDlg(std::vector<TYPE_OF_EMPLOYMENT>& arrEmploymentType);   // standard constructor
	virtual ~CEmploymentDlg();

// Dialog Data

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	BOOL OnInitDialog();

private:
	CListCtrl m_Employment_ListCtrl;

public:
	afx_msg void OnBnClickedEmploymentAdd();
	afx_msg void OnBnClickedEmploymentEdit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEmploymentDelete();

	BOOL LoadAllToListCtrl();

public:

	std::vector<TYPE_OF_EMPLOYMENT>& m_arrEmploymentType;

};


