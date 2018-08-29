
#pragma once

#include "Structures.h"
#include "FilterDialog.h"

class CSortListCtrl : public CListCtrl
{
	// Construction
public:
	CSortListCtrl();
	virtual ~CSortListCtrl();

	// Attributes
public:

	// Operations
public:
	void Sort(int iColumn, BOOL bAscending);
	void Submenu(CMenu & m_Menu);
	void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	static int CALLBACK CompareFunction(LPARAM lParam1, LPARAM lParam2, LPARAM lParamData);

	// Overrides
protected:
	virtual void PreSubclassWindow();

protected:

	int m_iSortColumn;
	BOOL m_bSortAscending;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
