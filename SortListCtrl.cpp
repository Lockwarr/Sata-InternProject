#include "stdafx.h"
#include "SortListCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


LPCTSTR g_pszSection = _T("ListCtrls");


CSortListCtrl::CSortListCtrl()
	: m_iSortColumn(-1)
	, m_bSortAscending(TRUE)
{
}


CSortListCtrl::~CSortListCtrl()
{
}


BEGIN_MESSAGE_MAP(CSortListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)

END_MESSAGE_MAP()



void CSortListCtrl::PreSubclassWindow()
{

	// the list control must have the report style.
}


int CALLBACK CSortListCtrl::CompareFunction(LPARAM lParam1, LPARAM lParam2, LPARAM lParamData)
{
	CSortListCtrl* pListCtrl = reinterpret_cast<CSortListCtrl*>(lParamData);
	ASSERT(pListCtrl->IsKindOf(RUNTIME_CLASS(CListCtrl)));

	EMPLOYEE_DATA* pid1 = reinterpret_cast<EMPLOYEE_DATA*>(lParam1);
	EMPLOYEE_DATA* pid2 = reinterpret_cast<EMPLOYEE_DATA*>(lParam2);

	ASSERT(pid1);
	ASSERT(pid2);
	int iSortColumn = pListCtrl->m_iSortColumn;
	CString pszText1;
	CString pszText2;
	switch (iSortColumn)
	{
	case 0:
		pszText1.Format("%s", pid1->szFirstName);
		pszText1.Format("%s", pid2->szFirstName);
		break;
	case 1:
		pszText1.Format("%s", pid1->szSurname);
		pszText1.Format("%s", pid2->szSurname);
		break;
	case 2:
		pszText1.Format("%s", pid1->szLastName);
		pszText1.Format("%s", pid2->szLastName);
		break;
	case 3:
		pszText1.Format("%s", pid1->szPIN);
		pszText1.Format("%s", pid2->szPIN);
		break;
	case 4:
		pszText1.Format("%s", pid1->szEmail);
		pszText1.Format("%s", pid2->szEmail);
		break;
	case 5:
		pszText1.Format("%s", pid1->szPhoneNumber);
		pszText1.Format("%s", pid2->szPhoneNumber);
		break;
	case 6:
		pszText1.Format("%d",pid1->dtDate);
		pszText2.Format("%d",pid2->dtDate);
		break;

	}
	return strcmp(pszText1, pszText2);

}


void CSortListCtrl::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	const int iColumn = pNMListView->iSubItem;

	// if it's a second click on the same column then reverse the sort order,
	// otherwise sort the new column in ascending order.
	Sort(iColumn, iColumn == m_iSortColumn ? !m_bSortAscending : TRUE);

	*pResult = 0;
}


void CSortListCtrl::Sort(int iColumn, BOOL bSortAscending)
{
	m_iSortColumn = iColumn;
	m_bSortAscending = bSortAscending;

	VERIFY(SortItems(CompareFunction, reinterpret_cast<DWORD>(this)));
}
void CSortListCtrl::Submenu(CMenu & m_Menu)
{
	CMenu submenu;
	submenu.CreatePopupMenu();
	submenu.AppendMenu(MF_STRING, IDC_ADD_EMPLOYEE, "&Add");
	submenu.AppendMenu(MF_STRING, IDC_EDIT_EMPLOYEE, "&Edit");
	submenu.AppendMenu(MF_STRING, IDC_HUMAN_RESOURCES_TIME_OFF, "&Add time off");
	submenu.AppendMenu(MF_SEPARATOR);
	submenu.AppendMenu(MF_STRING, IDC_DELETE_EMPLOYEE, "&Delete");

	m_Menu.AppendMenu(MF_POPUP, reinterpret_cast<UINT_PTR>(submenu.m_hMenu), "");
	submenu.Detach();
}
