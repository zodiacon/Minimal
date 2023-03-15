#include <Windows.h>
#include <winternl.h>

int __cdecl sprintf_s_f(
	char* buffer,
	size_t sizeOfBuffer,
	const char* format,	...);

#pragma comment(lib, "ntdll")

int mainCRTStartup(PPEB peb) {
	auto sprintf_s = (decltype(sprintf_s_f)*)::GetProcAddress(::GetModuleHandle(L"ntdll"), "sprintf_s");
	if (sprintf_s) {
		char text[128];
		sprintf_s(text, _countof(text), "PEB: 0x%p\n", peb);
		::WriteConsoleA(::GetStdHandle(STD_OUTPUT_HANDLE),
			text, (DWORD)strlen(text), nullptr, nullptr);

		sprintf_s(text, _countof(text), "Executable: %wZ\n", peb->ProcessParameters->ImagePathName);
		::WriteConsoleA(::GetStdHandle(STD_OUTPUT_HANDLE),
			text, (DWORD)strlen(text), nullptr, nullptr);

		sprintf_s(text, _countof(text), "Commandline: %wZ\n", peb->ProcessParameters->CommandLine);
		::WriteConsoleA(::GetStdHandle(STD_OUTPUT_HANDLE),
			text, (DWORD)strlen(text), nullptr, nullptr);

		sprintf_s(text, _countof(text), "Hello, world from process %u\n", ::GetCurrentProcessId());
		::WriteConsoleA(::GetStdHandle(STD_OUTPUT_HANDLE),
			text, (DWORD)strlen(text), nullptr, nullptr);
	}

	return 0;
}
