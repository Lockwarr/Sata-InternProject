#pragma once
#include "SortListCtrl.h"
#include <vector>

class CEducationTypes : public CDialogEx
{

	enum { IDD = IDD_EDUCATION_TYPES };

public:
	CEducationTypes(std::vector<TYPE_OF_EDUCATION>& arrEducationType);   // standard constructor
	virtual ~CEducationTypes();

// Dialog Data


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


public:
	BOOL OnInitDialog();

private:
	CListCtrl m_lscEducation;	

public:
	afx_msg void OnBnClickedEducationAdd();
	afx_msg void OnBnClickedEducationEdit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEducationDelete();

	BOOL LoadAllFromTableToListCtrl();

public:

	std::vector<TYPE_OF_EDUCATION>& m_arrEducationType;

	DECLARE_MESSAGE_MAP()
};


