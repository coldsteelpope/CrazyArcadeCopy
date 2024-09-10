#pragma once

#include "Obj.h"
class CWaterBomb : public CObj
{
public:
	CWaterBomb();
	virtual ~CWaterBomb();
public:
	void	Initialize()		override;
	int		Update()			override;
	void	Late_Update()		override;
	void	Render(HDC _hDC)	override;
	void	Release()			override;

public:
	inline const bool Get_Can_Not_Step() { return m_bCanNotStep; }

public:
	void Motion_Change();
	void Manage_Status();

private:
	DWORD	m_dwLimitTime;
	DWORD	m_dwSurviveTime;
	DWORD	m_dwCanNotStepTime;
	int		m_iBombRadius;
	bool	m_bCanNotStep = false;
};

