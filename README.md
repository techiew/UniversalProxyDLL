# Universal Proxy DLL
A header-only library for proxying DLLs with one function call:

![One function call pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/one_function_call.png)

### Features:
* No .masm or .def files required
* No project configuration required
* Built DLL can dynamically proxy any supported DLL without rebuilding (just rename the DLL)
* Set callbacks for exported functions
* No race conditions (exported functions will wait for proxy creation)
* No [LoadLibrary calls](https://learn.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-best-practices) within DllMain
* Works for 32-bit and 64-bit games (32-bit has limited support!)

## Example
A simple DLL with a DllMain looking like this:

![DllMain example pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/dllmain_example.png)

Is all that is needed, the DLL is then proxied properly (dxgi.dll was used in this example):

![Proxy example pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/proxy_example.png)

**Note: The debug terminal is optional of course.**

You can then create a new thread and do the usual proxy DLL stuff:

![Usual proxy stuff pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/usual_proxy_stuff.png)

## Callback example
Adding a callback for one of the exported functions:

![Callback example pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/callback_example.png)

Your function will be called when the exported function is called **(directly prior to it)**.

You'll have to know and specify the correct function signature in the same manner as shown in the example. The function signature for "DirectInput8Create" used in the example was found [here](https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ee416756(v=vs.85)).

## Supported DLLs
Yes, technically this is not *universal*, only on paper. See section "Add support for a DLL". 

The most common proxy DLLs are supported out of the box:
* dxgi
* d3d10
* d3d11
* ~~d3d12~~ (see issue #1)
* dinput8
* XInput1_3
* XInput1_4
* steam_api64
* steam_api
* opengl32
* winhttp
* bink2w64

I do not guarantee that all supported DLLs will work for 32-bit games. Trial and error is required in this case.

## Adding support for a DLL
Adding support for a DLL is simple. In the "scripts" folder you will find some Python scripts. 

Use the "create_export_list.py" script by running `python create_export_list.py <path_to_dll>`. This will generate a "&lt;dll&gt;_export_list.txt" file in the script folder:

![create_export_list pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/create_export_list.png)

Copy the contents of the generated file to the bottom of "UniversalProxyDLL.h" and build:

![New exports pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/new_exports.png)

The DLL should now be proxied correctly. 

**Note: some system DLLs such as user32 may refuse to be proxied!**

## Checking which DLLs a game loads
To check which DLLs you can use to create proxies for specific games, you may for example use the "dumpbin" tool provided with Visual Studio:

![Dumpbin pic](https://github.com/techiew/UniversalProxyDLL/blob/master/pictures/dumpbin.png)

## Used in...
Some of my other projects, such as [DirectXHook](https://github.com/techiew/DirectXHook) and [Elden Mod Loader](https://github.com/techiew/EldenRingModLoader).

## Contributions
If you find that a DLL is not supported and you've added the exports yourself, I'd appreciate if you'd create a PR so the exports can be made available to others. Thank you.

## License
[LICENSE.md](https://github.com/techiew/UniversalProxyDLL/blob/master/LICENSE.md)
