#pragma once

#include "Structures.h"
#include <vector>

// CPositionDlg dialog

class CPositionDlg : public CDialogEx
{

	enum { IDD = IDD_POSITION };

public:
	CPositionDlg(std::vector<POSITION_TYPE>& arrPositionType);   // standard constructor
	virtual ~CPositionDlg();

	// Dialog Data
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


public:
	BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedPositionAdd();
	afx_msg void OnBnClickedPositionEdit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedPositionDelete();

	BOOL LoadAllFromTableToListCtrl();

	DECLARE_MESSAGE_MAP()

private:

	CListCtrl m_lscPositions_ListCtrl;

	std::vector<POSITION_TYPE>& m_arrPositionType;

};

