#pragma once
class CMainServer
{
public:
	CMainServer();
	virtual ~CMainServer();

public:
	bool Initialize();
	void Update();
	void Late_Update();
	void Release();

private:
	bool Initialize_WinSocket();
};

