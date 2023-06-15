#include <Windows.h>
#include <iostream>

#include "UniversalProxyDLL.h"

void OpenDebugTerminal()
{
	if (AllocConsole())
	{
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
		SetWindowText(GetConsoleWindow(), "UPD");
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);
		try
		{
			OpenDebugTerminal();
			UPD::CreateProxy(hinstDLL);
		}
		catch (std::runtime_error e)
		{
			std::cout << e.what() << std::endl;
			return FALSE;
		}
	}
    return TRUE;
}