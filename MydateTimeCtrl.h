#pragma once

class CMydateTimeCtrl : public CDateTimeCtrl
{
public:
	CMydateTimeCtrl() {}
	virtual ~CMydateTimeCtrl() {}

public:

	BOOL GetDate(DBTIMESTAMP& dtDate);

	void SetDate(const DBTIMESTAMP& dtDate);
};