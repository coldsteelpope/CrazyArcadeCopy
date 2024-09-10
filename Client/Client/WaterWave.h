#pragma once

#include "Obj.h"
class CWaterWave : public CObj
{
public:
	CWaterWave();
	virtual ~CWaterWave();
public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Set_Bomb_Radius(int _iBombRadius) { m_iBombRadius = _iBombRadius; }
	
private:
	void Set_vTiles();
	void Add_Water_Up_Waves();
	void Add_Water_Down_Waves();
	void Add_Water_Left_Waves();
	void Add_Water_Right_Waves();

public:
	void Motion_Change();
	void Manage_Status();

private:
	int m_iBombRadius;

	int m_iValidLeftNumber;
	int m_iValidUpNumber;
	int m_iValidRightNumber;
	int m_iValidDownNumber;

	int m_iPivotIdx;
	vector<CObj*> vTiles;
};

