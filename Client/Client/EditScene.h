#pragma once

#include "Scene.h"
class CEditScene : public CScene
{
public:
	CEditScene();
	virtual ~CEditScene();

private:
	

	// CScene을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

