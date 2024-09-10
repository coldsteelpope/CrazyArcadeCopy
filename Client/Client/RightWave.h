#pragma once

#include "Obj.h"
class CRightWave : public CObj
{
public:
	CRightWave();
	virtual ~CRightWave();

public:

	// CObj��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Set_Wave_Type(WAVE_TYPE _eWaveType) { m_eWaveType = _eWaveType; }
	void Motion_Change();
	void Manage_Status();
private:
	WAVE_TYPE m_eWaveType = WAVE_TYPE::WAVE_TYPE_END;

};

