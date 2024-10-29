#include <Windows.h>
#include <iostream>

#include "UniversalProxyDLL.h"

DWORD WINAPI NewThread(LPVOID lpParam)
{
	std::ifstream chainloadFile;
	chainloadFile.open("upd_chainload.txt");
	if (chainloadFile.is_open())
	{
		std::string line;
		while (getline(chainloadFile, line))
		{
			line.erase(line.find_last_not_of(' ') + 1);
			line.erase(0, line.find_first_not_of(' '));
			UPD::Log("Loading: ", line);
			LoadLibraryA(line.c_str());
		}
		chainloadFile.close();
		return 1;
	}
	UPD::Log("upd_chainload.txt not found.");
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);
		try
		{	
			UPD::MuteLogging();
			UPD::CreateProxy(hinstDLL);
			CreateThread(0, 0, &NewThread, NULL, 0, NULL);
		}
		catch (std::runtime_error e)
		{
			std::cout << e.what() << std::endl;
			return FALSE;
		}
	}
	return TRUE;
}