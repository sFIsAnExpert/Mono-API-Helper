#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include "minhook/include/MinHook.h"

class MonoMemory {
public:
	MODULEENTRY32W GetModule(const wchar_t* modName) {
		uintptr_t modBaseAddr = 0;
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetCurrentProcessId());
		if (hSnap != INVALID_HANDLE_VALUE)
		{
			MODULEENTRY32W modEntry;
			modEntry.dwSize = sizeof(modEntry);
			if (Module32FirstW(hSnap, &modEntry))
			{
				do
				{
					if (!_wcsicmp(modEntry.szModule, modName))
					{
						return modEntry;
					}
				} while (Module32NextW(hSnap, &modEntry));
			}
		}
		CloseHandle(hSnap);
		return MODULEENTRY32W();
	}
	uintptr_t GetExport(const wchar_t* wAPIName) {
		unsigned char* lpBase = reinterpret_cast<unsigned char*>(this->Mono.hModule);
		IMAGE_DOS_HEADER* idhDosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(lpBase);
		if (idhDosHeader->e_magic == 0x5A4D)
		{
			IMAGE_NT_HEADERS64* inhNtHeader = reinterpret_cast<IMAGE_NT_HEADERS64*>(lpBase + idhDosHeader->e_lfanew);
			if (inhNtHeader->Signature == 0x4550)
			{
				IMAGE_EXPORT_DIRECTORY* iedExportDirectory = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(lpBase + inhNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
				for (register unsigned int uiIter = 0; uiIter < iedExportDirectory->NumberOfNames; ++uiIter)
				{
					char* szNames = reinterpret_cast<char*>(lpBase + reinterpret_cast<unsigned long*>(lpBase + iedExportDirectory->AddressOfNames)[uiIter]);
					if (this->isEqual(szNames, wAPIName))
					{
						unsigned short usOrdinal = reinterpret_cast<unsigned short*>(lpBase + iedExportDirectory->AddressOfNameOrdinals)[uiIter];
						return reinterpret_cast<uintptr_t>(lpBase + reinterpret_cast<unsigned long*>(lpBase + iedExportDirectory->AddressOfFunctions)[usOrdinal]);
					}
				}
			}
		}
		return 0;
	}

	void Initialize() {
		this->Mono = this->GetModule(L"mono-2.0-bdwgc.dll");
	}
private:
	bool isEqual(char* names, const wchar_t* API) {
		std::wstring wc(API);
		std::string tmp(names);
		std::wstring wc2(tmp.begin(), tmp.end());

		return wc.compare(wc2) == 0;
	}
	MODULEENTRY32W Mono;
}inline _MonoMemory;