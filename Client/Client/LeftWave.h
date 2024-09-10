#pragma once

#include "Obj.h"
class CLeftWave : public CObj
{
public:
	CLeftWave();
	virtual ~CLeftWave();
public:

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

