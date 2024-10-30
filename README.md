# Universal Proxy DLL
A header-only library for proxying DLLs with one function call:

```cpp
UPD::CreateProxy(dll);
```

### Features:
* No .masm or other assembly files required
* No module definition files (.def) files required
* No project configuration required
* Built DLL can dynamically proxy any [supported DLL](#supported-dlls) without rebuilding (just rename the DLL)
* Easily create [callbacks](#adding-a-callback) for exported functions
* No race conditions (exported functions will wait for proxy creation)
* No [LoadLibrary calls](https://learn.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-best-practices) within DllMain
* Works for 32-bit and 64-bit games (32-bit has limited support!)

## Usage
A simple DllMain is all that is needed:

```cpp
#include <Windows.h>

#include "UniversalProxyDLL.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        UPD::OpenDebugTerminal();
        UPD::CreateProxy(hinstDLL);
    }
    return TRUE;
}
```

That's it! The DLL will then be proxied properly.

In the following example, Elden Ring was proxied with a dxgi.dll proxy:

![Proxy example pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/proxy_example.png)

**Note: The debug terminal is optional.**

From there you can create a new thread and do the usual proxy DLL stuff:

```cpp
#include <Windows.h>

#include "UniversalProxyDLL.h"

DWORD WINAPI NewThread(LPVOID lpParam)
{
    printf("Doing some very naughty stuff\n");
    char* p = nullptr;
    char c = *p;
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        UPD::OpenDebugTerminal();
        UPD::CreateProxy(hinstDLL);
        CreateThread(0, 0, &NewThread, NULL, 0, NULL);
    }
    return TRUE;
}
```

## Adding a callback
You may add callbacks back to your own code for when an exported function is called:

```cpp
#include <Windows.h>

#include "UniversalProxyDLL.h"

using FpDirectInput8Create = HRESULT (*)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
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
        UPD::OpenDebugTerminal();
        fpDirectInput8Create = UPD::RegisterCallback("DirectInput8Create", &CallbackDirectInput8Create);
        UPD::CreateProxy(hinstDLL);
    }
    return TRUE;
}
```

Dinput8.dll was proxied in this example. 

Your callback will be called directly prior to the exported function being executed.

**Note: It's crucial that the function signature for the callback exactly matches the function signature of the exported function. For instance, the function signature for "DirectInput8Create" used in the example was found [here](https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ee416756(v=vs.85)).**

**As for the** `return` **with a call to the original exported function - in some cases you might get away with omitting it, but I wouldn't recommend it.**

## Supported DLLs
Yes, in practice this project is not truly *universal*, only in theory. See section [Adding support for a DLL](#adding-support-for-a-dll). 

**The most common proxy DLLs are supported out of the box:**
* dxgi
* d3d10
* d3d11
* ~~d3d12~~ (see issue [#1](https://github.com/techiew/UniversalProxyDLL/issues/1))
* dinput8
* XInput1_3
* XInput1_4
* steam_api64
* steam_api
* opengl32
* winhttp
* bink2w64
* vcruntime140
* vcruntime140_1
* msvcp140 (Needs explicit definition in [UniversalProxyDLL.h](https://github.com/techiew/UniversalProxyDLL/blob/master/UniversalProxyDLL.h#L13))
* msvcp140_1
* msvcp140_2


**Note: I do not guarantee that all supported DLLs will work for 32-bit games. Trial and error is required in this case.**

## Adding support for a DLL
Adding support for a DLL is simple. In the "scripts" folder you will find some Python scripts. 

Use the `create_export_list.py` script by running `python create_export_list.py <path_to_dll>`. This will create a "&lt;dll&gt;_export_list.txt" file in the script folder:

![create_export_list pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/create_export_list.png)

Copy the contents of the generated file to somewhere at the bottom of "UniversalProxyDLL.h" and build:

![New exports pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/new_exports.png)

The DLL should now be proxied correctly. 

**Note: If your DLL has a higher number of exports than the current amount of Forward and ForwardOrdinal functions, you must also use the scripts `create_export_ordinals.py` and `create_forward_functions.py` to generate an amount of functions equal to or higher than the number of exports of your DLL.**

**Also note: Some system DLLs such as user32 may refuse to be proxied!**

## Checking which DLLs a game loads
To check which DLLs you can use to create proxies for specific games, you may for example use the `dumpbin` tool provided with Visual Studio:

![Dumpbin pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/dumpbin.png)

## Precompiled DLL for chainloading
I have provided a [precompiled DLL](https://github.com/techiew/UniversalProxyDLL/releases/tag/precompiled-dll) to be used for simple chainloading.

The precompiled proxy DLL "dxgi.dll" will read the file "upd_chainload.txt" in the working directory and go through the file line by line, calling LoadLibrary on each DLL name it reads.

As many DLLs as you wish can be entered into the file. Each DLL name must be separated with a newline and end with ".dll". Example entry: ```test.dll```. The precompiled DLL can be renamed to any of the supported DLLs.

The DLL is built on this commit: [164580d090f7c0625b37fe71d7f52c819df7368a](https://github.com/techiew/UniversalProxyDLL/commit/164580d090f7c0625b37fe71d7f52c819df7368a)

## Used in...
Some of my other projects, such as [DirectXHook](https://github.com/techiew/DirectXHook) and [Elden Mod Loader](https://github.com/techiew/EldenRingModLoader).

## Contributions
If you find that a DLL is not supported and you've added the exports yourself, I'd appreciate if you'd create a PR so the exports can be made available to others. Thank you.

## License
[LICENSE.md](https://github.com/techiew/UniversalProxyDLL/blob/master/LICENSE.md)
