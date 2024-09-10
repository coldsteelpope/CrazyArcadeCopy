#pragma once

#include "Obj.h"
class CEnemy : public CObj
{
public:
	CEnemy();
	virtual ~CEnemy();
public:
	

	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;


public:
	void Motion_Change();
	void Manage_Status();
	void Set_Frame_Key();

};

