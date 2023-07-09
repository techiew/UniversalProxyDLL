#include <Windows.h>
#include <iostream>

#include "UniversalProxyDLL.h"

typedef HRESULT(*FpDirectInput8Create)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
void* fpDirectInput8Create = nullptr;
HRESULT CallbackDirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
	printf("Callback called!\n");
	return (*(FpDirectInput8Create*)fpDirectInput8Create)(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);
		try
		{
			UPD::OpenDebugTerminal();
			fpDirectInput8Create = UPD::RegisterCallback("DirectInput8Create", &CallbackDirectInput8Create);
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
