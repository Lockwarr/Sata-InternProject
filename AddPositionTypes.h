#pragma once
#include <vector>
#include "HumanResources.h"
#include "Structures.h"
#include "EnumDialogMode.h"

// CAddPositionTypes dialog

class CAddPositionTypes : public CDialogEx
{

	enum { IDD = IDD_ADD_POSITION };

public:
	CAddPositionTypes(POSITION_TYPE & recPosition, DialogMode eMode);
	// standard constructor
	virtual ~CAddPositionTypes();

	// Dialog Data


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();

private:
	afx_msg void OnBnClickedOk();

private:
	CString m_strPositionTypeName;
	POSITION_TYPE & m_recPosition;
	DialogMode m_eMode;
	DECLARE_MESSAGE_MAP()

};




