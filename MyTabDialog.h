#pragma once
#include "stdafx.h"

class CMyTabDialog : public CDialogEx
{
public:
	CMyTabDialog() {}
	CMyTabDialog(UINT nIDTemplate, CWnd *pParent = NULL) : CDialogEx(nIDTemplate, pParent) {}
	CMyTabDialog(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL) : CDialogEx(lpszTemplateName, pParentWnd) {}

public:
	virtual void AddElement() = 0;
	virtual void EditElement() = 0;
	virtual void DeleteElement() = 0;
	virtual bool ShowButtons() { return true; }
}; 
