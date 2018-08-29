
#include "stdafx.h"
#include "MydateTimectrl.h"



BOOL CMydateTimeCtrl::GetDate(DBTIMESTAMP& dtDate)
{
	COleDateTime oDateTimeFrom;

	if (!GetTime(oDateTimeFrom))
		return FALSE;

	if (!oDateTimeFrom.GetAsDBTIMESTAMP(dtDate))
		return FALSE;

	return TRUE;
}

void CMydateTimeCtrl::SetDate(const DBTIMESTAMP & dtDate)
{

	COleDateTime oDateTime;
	SetTime(dtDate);
	
}
