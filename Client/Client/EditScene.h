#pragma once

#include "Scene.h"
class CEditScene : public CScene
{
public:
	CEditScene();
	virtual ~CEditScene();

private:
	

	// CScene��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

