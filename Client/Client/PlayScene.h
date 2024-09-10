#pragma once

#include "Scene.h"
class CPlayScene : public CScene
{
public:
	CPlayScene();
	virtual ~CPlayScene();
	
public:
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

