#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <map>
#include <iomanip>
#include <sstream>
#include <string.h>

#define Export(index, name) __pragma(comment(linker, "/export:"#name"=Forward"#index))

// d3d9
Export(0, D3DPERF_BeginEvent)
Export(1, D3DPERF_EndEvent)
Export(2, D3DPERF_GetStatus)
Export(3, D3DPERF_QueryRepeatFrame)
Export(4, D3DPERF_SetMarker)
//Export(5, D3DPERF_SetOptions)
//Export(5, D3DPERF_SetRegion)
//Export(5, DebugSetLevel)
//Export(5, DebugSetMute)
//Export(5, Direct3D9EnableMaximizedWindowedModeShim)
//Export(5, Direct3DCreate9)
//Export(5, Direct3DCreate9Ex)
//Export(5, Direct3DCreate9On12)
//Export(5, Direct3DCreate9On12Ex)
//Export(5, Direct3DShaderValidatorCreate9)
//Export(5, PSGPError)
//Export(5, PSGPSampleTexture)
//Export(5, @16)
//Export(5, @17)
//Export(5, @17)

// dinput8
Export(0, DirectInput8Create)
Export(1, DllCanUnloadNow)
Export(2, DllGetClassObject)
Export(3, DllRegisterServer)
Export(4, DllUnregisterServer)
Export(5, GetdfDIJoystick)

namespace UPD
{
	#define GenerateForwardFunction(N) \
	extern "C" __declspec(dllexport) size_t Forward##N () { return(##N); } // Unique function result stops the functions from being optimized away
	GenerateForwardFunction(0);  GenerateForwardFunction(1);  GenerateForwardFunction(2);  GenerateForwardFunction(3);
	GenerateForwardFunction(4);  GenerateForwardFunction(5);  GenerateForwardFunction(6);  GenerateForwardFunction(7);
	GenerateForwardFunction(8);  GenerateForwardFunction(9);  GenerateForwardFunction(10); GenerateForwardFunction(11);
	GenerateForwardFunction(12); GenerateForwardFunction(13); GenerateForwardFunction(14); GenerateForwardFunction(15);
	GenerateForwardFunction(16); GenerateForwardFunction(17); GenerateForwardFunction(18); GenerateForwardFunction(19);
	GenerateForwardFunction(20); GenerateForwardFunction(21); GenerateForwardFunction(22); GenerateForwardFunction(23);
	GenerateForwardFunction(24); GenerateForwardFunction(25); GenerateForwardFunction(26); GenerateForwardFunction(27);
	GenerateForwardFunction(28); GenerateForwardFunction(29); GenerateForwardFunction(30); GenerateForwardFunction(31);
	GenerateForwardFunction(32); GenerateForwardFunction(33); GenerateForwardFunction(34); GenerateForwardFunction(35);
	GenerateForwardFunction(36); GenerateForwardFunction(37); GenerateForwardFunction(38); GenerateForwardFunction(39);
	GenerateForwardFunction(40); GenerateForwardFunction(41); GenerateForwardFunction(42); GenerateForwardFunction(43);
	GenerateForwardFunction(44); GenerateForwardFunction(45); GenerateForwardFunction(46); GenerateForwardFunction(47);
	GenerateForwardFunction(48); GenerateForwardFunction(49); GenerateForwardFunction(50); GenerateForwardFunction(51);
	GenerateForwardFunction(52); GenerateForwardFunction(53); GenerateForwardFunction(54); GenerateForwardFunction(55);
	GenerateForwardFunction(56); GenerateForwardFunction(57); GenerateForwardFunction(58); GenerateForwardFunction(59);
	GenerateForwardFunction(60); GenerateForwardFunction(61); GenerateForwardFunction(62); GenerateForwardFunction(63);
	GenerateForwardFunction(64); GenerateForwardFunction(65); GenerateForwardFunction(66); GenerateForwardFunction(67);
	GenerateForwardFunction(68); GenerateForwardFunction(69); GenerateForwardFunction(70); GenerateForwardFunction(71);
	GenerateForwardFunction(72); GenerateForwardFunction(73); GenerateForwardFunction(74); GenerateForwardFunction(75);
	GenerateForwardFunction(76); GenerateForwardFunction(77); GenerateForwardFunction(78); GenerateForwardFunction(79);
	GenerateForwardFunction(80); GenerateForwardFunction(81); GenerateForwardFunction(82); GenerateForwardFunction(83);
	GenerateForwardFunction(84); GenerateForwardFunction(85); GenerateForwardFunction(86); GenerateForwardFunction(87);
	GenerateForwardFunction(88); GenerateForwardFunction(89); GenerateForwardFunction(90); GenerateForwardFunction(91);
	GenerateForwardFunction(92); GenerateForwardFunction(93); GenerateForwardFunction(94); GenerateForwardFunction(95);
	GenerateForwardFunction(96); GenerateForwardFunction(97); GenerateForwardFunction(98); GenerateForwardFunction(99);
	std::vector<void*> forwardFunctionAddresses = {
		&Forward0,   &Forward1,   &Forward2,   &Forward3,   &Forward4,
		&Forward5,   &Forward6,   &Forward7,   &Forward8,   &Forward9,
		&Forward10,  &Forward11,  &Forward12,  &Forward13,  &Forward14,
		&Forward15,  &Forward16,  &Forward17,  &Forward18,  &Forward19,
		&Forward20,  &Forward21,  &Forward22,  &Forward23,  &Forward24,
		&Forward25,  &Forward26,  &Forward27,  &Forward28,  &Forward29,
		&Forward30,  &Forward31,  &Forward32,  &Forward33,  &Forward34,
		&Forward35,  &Forward36,  &Forward37,  &Forward38,  &Forward39,
		&Forward40,  &Forward41,  &Forward42,  &Forward43,  &Forward44,
		&Forward45,  &Forward46,  &Forward47,  &Forward48,  &Forward49,
		&Forward50,  &Forward51,  &Forward52,  &Forward53,  &Forward54,
		&Forward55,  &Forward56,  &Forward57,  &Forward58,  &Forward59,
		&Forward60,  &Forward61,  &Forward62,  &Forward63,  &Forward64,
		&Forward65,  &Forward66,  &Forward67,  &Forward68,  &Forward69,
		&Forward70,  &Forward71,  &Forward72,  &Forward73,  &Forward74,
		&Forward75,  &Forward76,  &Forward77,  &Forward78,  &Forward79,
		&Forward80,  &Forward81,  &Forward82,  &Forward83,  &Forward84,
		&Forward85,  &Forward86,  &Forward87,  &Forward88,  &Forward89,
		&Forward90,  &Forward91,  &Forward92,  &Forward93,  &Forward94,
		&Forward95,  &Forward96,  &Forward97,  &Forward98,  &Forward99
	};

	// Global variables
	std::ofstream logFile;
	std::vector<unsigned char> dllMemory;
	PIMAGE_SECTION_HEADER sectionHeadersBase = 0;
	DWORD numSections = 0;
	bool isProxyReady = false;
	std::vector<uintptr_t> relativeAddressesOfExportedFunctionsInOriginalDll;
	std::vector<uintptr_t> asmCodeAddresses;

	// Function prototypes
	void CreateProxy(HMODULE dllToProxy, std::string specificPathToSearch = "");
	std::string GetModuleFileNameFromModuleHandle(HMODULE handle);
	std::string FindOriginalDLL(std::string dllFileName, std::string specificPathToSearch = "");
	std::string SearchForDLLInSpecificPath(std::string dllFileName, std::string specificPath);
	std::string SearchForDLLUsingStandardSearchOrder(std::string dllFileName);
	std::string SearchForDLLInCurrentFolder(std::string dllFileName);
	std::string SearchForDLLInSystemFolder(std::string dllFileName);
	bool DoesFileExist(std::string filePath);
	std::vector<unsigned char> LoadFileToVectorOfBytes(std::string filePath);
	void GetRelativeAddressesOfExportedFunctionsForDLL(std::string dllFilePath);
	PIMAGE_DOS_HEADER GetDLLDosHeader(void* peHeaderBase);
	PIMAGE_NT_HEADERS GetDLLNtHeaders(PIMAGE_DOS_HEADER dosHeader);
	void SetSectionHeadersInfo(PIMAGE_FILE_HEADER fileHeader, PIMAGE_OPTIONAL_HEADER optionalHeader);
	PIMAGE_EXPORT_DIRECTORY GetExportDirectory(PIMAGE_OPTIONAL_HEADER optionalHeader);
	uintptr_t RvaToRawAddress(DWORD rva);
	void PrepareForwardFunctions();
	uintptr_t CreateMemoryWithAssemblyForwardingCode(size_t forwardIndex);
	void StartProxyCreationThread(std::string originalDllPath);
	DWORD WINAPI ThreadCreateProxy(LPVOID lpParam);
	void InjectExportAddresses(HMODULE module);
	void InjectExportAddressIntoAsmForwardingCode(uintptr_t exportAbsoluteAddress, uintptr_t asmForwardingCodeAddress);
	void ToggleMemoryProtection(bool enableProtection, uintptr_t address, size_t size);
	void MemCopy(uintptr_t destination, uintptr_t source, size_t numBytes);
	void Hook(uintptr_t address, uintptr_t destination, size_t extraClearance = 0);
	void LogAndThrow(std::string exceptionMessage);
	template<typename... Types> void Log(Types... args);
	template<typename T> std::string NumberToHexString(T number);

	void CreateProxy(HMODULE dllToProxy, std::string specificPathToSearch)
	{
		std::string dllToProxyFileName = GetModuleFileNameFromModuleHandle(dllToProxy);
		std::string dllFilePath = FindOriginalDLL(dllToProxyFileName, specificPathToSearch);
		dllMemory = LoadFileToVectorOfBytes(dllFilePath);
		GetRelativeAddressesOfExportedFunctionsForDLL(dllFilePath);
		PrepareForwardFunctions();
		StartProxyCreationThread(dllFilePath);
	}

	std::string GetModuleFileNameFromModuleHandle(HMODULE handle)
	{
		std::string moduleFileName = "";
		char lpFilename[MAX_PATH];
		GetModuleFileNameA(handle, lpFilename, sizeof(lpFilename));
		char* lastSlashPos = strrchr(lpFilename, '\\');
		if (lastSlashPos != nullptr)
		{
			moduleFileName = lastSlashPos;
			moduleFileName = moduleFileName.substr(1, moduleFileName.length());
		}
		Log("Module name: ", moduleFileName.c_str());

		if (moduleFileName == "")
		{
			LogAndThrow("Could not get module name from module handle");
		}
		return moduleFileName;
	}

	std::string FindOriginalDLL(std::string dllFileName, std::string specificPathToSearch)
	{
		std::string dllPath = "";
		if (specificPathToSearch != "")
		{
			dllPath = SearchForDLLInSpecificPath(dllFileName, specificPathToSearch);
		}
		
		if (dllPath == "")
		{
			dllPath = SearchForDLLUsingStandardSearchOrder(dllFileName);
		}

		if (dllPath == "")
		{
			LogAndThrow("Could not find DLL to proxy");
		}

		Log("DLL found: ", dllPath);
		return dllPath;
	}

	std::string SearchForDLLInSpecificPath(std::string dllFileName, std::string specificPath)
	{
		std::string dllPath = specificPath + "\\" + dllFileName;
		if (!DoesFileExist(dllPath))
		{
			return "";
		}
		return dllPath;
	}

	std::string SearchForDLLUsingStandardSearchOrder(std::string dllFileName)
	{
		std::string dllPath = SearchForDLLInCurrentFolder("_" + dllFileName);

		if (dllPath == "")
		{
			dllPath = SearchForDLLInSystemFolder(dllFileName);
		}

		return dllPath;
	}

	std::string SearchForDLLInCurrentFolder(std::string dllFileName)
	{
		std::string dllPath = ".\\" + dllFileName;
		if (!DoesFileExist(dllPath))
		{
			return "";
		}
		return dllPath;
	}

	std::string SearchForDLLInSystemFolder(std::string dllFileName)
	{
		char lpBuffer[MAX_PATH];
		UINT pathLength = GetSystemDirectoryA(lpBuffer, sizeof(lpBuffer));
		std::string systemFolderPath = lpBuffer;
		std::string dllPath = systemFolderPath + "\\" + dllFileName;

		if (!DoesFileExist(dllPath))
		{
			return "";
		}

		return dllPath;
	}

	bool DoesFileExist(std::string filePath)
	{
		std::ifstream file(filePath);
		if (file.is_open())
		{
			return true;
		}
		return false;
	}

	std::vector<unsigned char> LoadFileToVectorOfBytes(std::string filePath)
	{
		std::ifstream file;
		file.open(filePath, std::ios::in | std::ios::binary);
		if (!file.is_open())
		{
			LogAndThrow("Failed to read DLL: " + filePath);
		}

		return std::vector<unsigned char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	}

	void GetRelativeAddressesOfExportedFunctionsForDLL(std::string dllFilePath)
	{
		void* peHeaderBase = &dllMemory[0];
		PIMAGE_DOS_HEADER dosHeader = GetDLLDosHeader(peHeaderBase);
		PIMAGE_NT_HEADERS ntHeaders = GetDLLNtHeaders(dosHeader);
		PIMAGE_OPTIONAL_HEADER optionalHeader = &ntHeaders->OptionalHeader;
		PIMAGE_FILE_HEADER fileHeader = &ntHeaders->FileHeader;

		SetSectionHeadersInfo(fileHeader, optionalHeader);

		PIMAGE_EXPORT_DIRECTORY exportDirectory = GetExportDirectory(optionalHeader);
		DWORD numberOfExports = exportDirectory->NumberOfNames;
		Log("Number of exports: ", numberOfExports);

		uintptr_t tableOfRvaPointersToExportNames = RvaToRawAddress(exportDirectory->AddressOfNames);
		uintptr_t tableOfRvaPointersToExportAddresses = RvaToRawAddress(exportDirectory->AddressOfFunctions);
		for (DWORD i = 0; i < numberOfExports; i++)
		{
			std::string exportName = (char*)RvaToRawAddress(*((DWORD*)tableOfRvaPointersToExportNames + i));
			uintptr_t exportAddress = *((DWORD*)tableOfRvaPointersToExportAddresses + i);
			Log("Export name: ", exportName);
			Log("Export RVA: ", NumberToHexString(exportAddress));
			relativeAddressesOfExportedFunctionsInOriginalDll.push_back(exportAddress);
		}
	}

	PIMAGE_DOS_HEADER GetDLLDosHeader(void* peHeaderBase)
	{
		PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)peHeaderBase;
		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		{
			LogAndThrow("Incorrect DOS signature");
		}
		return dosHeader;
	}

	PIMAGE_NT_HEADERS GetDLLNtHeaders(PIMAGE_DOS_HEADER dosHeader)
	{
		PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((unsigned char*)dosHeader + dosHeader->e_lfanew);
		if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
		{
			LogAndThrow("Incorrect NT signature");
		}
		return ntHeaders;
	}

	void SetSectionHeadersInfo(PIMAGE_FILE_HEADER fileHeader, PIMAGE_OPTIONAL_HEADER optionalHeader)
	{
		DWORD sizeOfOptionalHeader = fileHeader->SizeOfOptionalHeader;
		sectionHeadersBase = (PIMAGE_SECTION_HEADER)((unsigned char*)optionalHeader + sizeOfOptionalHeader);
		numSections = fileHeader->NumberOfSections;
	}

	PIMAGE_EXPORT_DIRECTORY GetExportDirectory(PIMAGE_OPTIONAL_HEADER optionalHeader)
	{
		PIMAGE_DATA_DIRECTORY exportDataDirectory = &(optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]);
		PIMAGE_EXPORT_DIRECTORY exportDirectory = (PIMAGE_EXPORT_DIRECTORY)RvaToRawAddress(exportDataDirectory->VirtualAddress);
		return exportDirectory;
	}

	uintptr_t RvaToRawAddress(DWORD rva)
	{
		for (DWORD i = 0; i < numSections; i++)
		{
			PIMAGE_SECTION_HEADER section = sectionHeadersBase + i;
			DWORD sectionVirtualBegin = section->VirtualAddress;
			DWORD sectionVirtualEnd = section->VirtualAddress + section->Misc.VirtualSize;
			if (rva >= sectionVirtualBegin && rva <= sectionVirtualEnd)
			{
				uintptr_t moduleBaseAddress = (uintptr_t)&dllMemory[0];
				uintptr_t rawAddress = (uintptr_t)((section->PointerToRawData + (rva - section->VirtualAddress)) + moduleBaseAddress);
				return rawAddress;
			}
		}

		LogAndThrow("Could not convert RVA to raw address");
	}

	void PrepareForwardFunctions()
	{
		for (size_t i = 0; i < relativeAddressesOfExportedFunctionsInOriginalDll.size(); i++)
		{
			asmCodeAddresses.push_back(CreateMemoryWithAssemblyForwardingCode(i));
			Hook((uintptr_t)forwardFunctionAddresses[i], asmCodeAddresses[i]);
			Log("Prepared forward function ", NumberToHexString((uintptr_t)forwardFunctionAddresses[i]));
		}
	}

	uintptr_t CreateMemoryWithAssemblyForwardingCode(size_t forwardIndex)
	{
		const size_t offsetOfBoolAddress = 2;
		std::vector<unsigned char> asmBytes =
		{
			0x48, 0xa0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // mov al,abs
			0x3c, 0x01, // cmp al
			0x0f, 0x85, 0xee, 0xff, 0xff, 0xff, // jne
			0xff, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // jmp
		};

		void* pointerToBool = &isProxyReady;
		MemCopy((uintptr_t)&asmBytes[offsetOfBoolAddress], (uintptr_t)&pointerToBool, sizeof(uintptr_t));

		uintptr_t memoryAddress = (uintptr_t)VirtualAlloc(NULL, asmBytes.size(), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (memoryAddress == NULL)
		{
			LogAndThrow("Failed to allocate memory");
		}

		MemCopy(memoryAddress, (uintptr_t)&asmBytes[0], asmBytes.size());
		Log("Created assembly forwarding code at ", NumberToHexString(memoryAddress));

		return memoryAddress;
	}

	void StartProxyCreationThread(std::string originalDllPath)
	{
		// Thread will run only after DllMain is finished!
		// This is enforced by the loader.
		std::string* dllPath = new std::string(originalDllPath);
		CreateThread(0, 0, &ThreadCreateProxy, dllPath, 0, NULL);
	}
	
	DWORD WINAPI ThreadCreateProxy(LPVOID lpParam)
	{
		std::string dllPath = *(std::string*)lpParam;

		HMODULE module = LoadLibraryA(dllPath.c_str());
		if (!module)
		{
			LogAndThrow("LoadLibrary call for original DLL failed!");
		}

		Log("Module base address: ", NumberToHexString(module));
		InjectExportAddresses(module);

		delete (std::string*)lpParam;
		isProxyReady = true;
		return 0;
	}

	void InjectExportAddresses(HMODULE module)
	{
		for (size_t i = 0; i < relativeAddressesOfExportedFunctionsInOriginalDll.size(); i++)
		{
			uintptr_t exportAbsoluteAddress = (uintptr_t)module + relativeAddressesOfExportedFunctionsInOriginalDll[i];
			uintptr_t asmForwardingCodeAddress = asmCodeAddresses[i];
			Log("Export address: ", NumberToHexString(exportAbsoluteAddress));
			InjectExportAddressIntoAsmForwardingCode(exportAbsoluteAddress, asmForwardingCodeAddress);
		}
	}

	void InjectExportAddressIntoAsmForwardingCode(uintptr_t exportAbsoluteAddress, uintptr_t asmForwardingCodeAddress)
	{
		const size_t jmpAddrOffset = 24;
		MemCopy(asmForwardingCodeAddress + jmpAddrOffset, (uintptr_t)&exportAbsoluteAddress, sizeof(uintptr_t));
	}

	void ToggleMemoryProtection(bool enableProtection, uintptr_t address, size_t size)
	{
		static std::map<uintptr_t, DWORD> protectionHistory;
		if (enableProtection && protectionHistory.find(address) != protectionHistory.end())
		{
			VirtualProtect((void*)address, size, protectionHistory[address], &protectionHistory[address]);
			protectionHistory.erase(address);
		}
		else if (!enableProtection && protectionHistory.find(address) == protectionHistory.end())
		{
			DWORD oldProtection = 0;
			VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, &oldProtection);
			protectionHistory[address] = oldProtection;
		}
	}

	void MemCopy(uintptr_t destination, uintptr_t source, size_t numBytes)
	{
		ToggleMemoryProtection(false, destination, numBytes);
		ToggleMemoryProtection(false, source, numBytes);
		memcpy((void*)destination, (void*)source, numBytes);
		ToggleMemoryProtection(true, source, numBytes);
		ToggleMemoryProtection(true, destination, numBytes);
	}

	void MemSet(uintptr_t address, unsigned char byte, size_t numBytes)
	{
		ToggleMemoryProtection(false, address, numBytes);
		memset((void*)address, byte, numBytes);
		ToggleMemoryProtection(true, address, numBytes);
	}

	void Hook(uintptr_t address, uintptr_t destination, size_t extraClearance)
	{
		size_t clearance = 14 + extraClearance;
		MemSet(address, 0x90, clearance);
		std::vector<unsigned char> jumpBytes = { 0xff, 0x25, 0x00, 0x00, 0x00, 0x00 };
		MemCopy(address, (uintptr_t)&jumpBytes[0], jumpBytes.size());
		MemCopy((address + 6), (uintptr_t)&destination, 8);
		Log("Created jump from ", NumberToHexString(address), " to ", NumberToHexString(destination), " with a clearance of ", clearance);
	}

	void LogAndThrow(std::string exceptionMessage)
	{
		Log("UniversalProxyDLL > Exception thrown: ", exceptionMessage);
		throw std::runtime_error(exceptionMessage);
	}

	template<typename... Types>
	void Log(Types... args)
	{
		if (!logFile.is_open())
		{
			logFile.open("upd_log.txt");
		}

		std::stringstream stream;
		stream << "UniversalProxyDLL > ";
		(stream << ... << args) << std::endl;
		std::cout << stream.str();

		if (logFile.is_open())
		{
			logFile << stream.str();
			logFile.flush();
		}
	}

	template<typename T>
	std::string NumberToHexString(T number)
	{
		std::stringstream stream;
		stream
			<< std::setfill('0')
			<< std::setw(sizeof(T) * 2)
			<< std::hex
			<< number;
		return stream.str();
	}
}