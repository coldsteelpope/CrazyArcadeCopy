#pragma once

#include "Obj.h"
class CUpWave : public CObj
{
public:
	CUpWave();
	virtual ~CUpWave();
public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Set_Wave_Type(WAVE_TYPE _eWaveType) { m_eWaveType = _eWaveType; }
	void Manage_Status();
	void Motion_Change();
private:
	WAVE_TYPE m_eWaveType = WAVE_TYPE::WAVE_TYPE_END;
	
};

