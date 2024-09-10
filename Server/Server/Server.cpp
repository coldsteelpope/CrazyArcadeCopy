#include "pch.h"
#include "MainServer.h"

int _tmain(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CMainServer mainServer;
	
	if (mainServer.Initialize())
	{
		while (true)
		{
			mainServer.Update();
			mainServer.Late_Update();
		}
	}
	mainServer.Release();
}