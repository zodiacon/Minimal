#include <Windows.h>

int mainCRTStartup() {
	char text[] = "Hello, World!\n";
	::WriteConsoleA(::GetStdHandle(STD_OUTPUT_HANDLE),
		text, (DWORD)strlen(text), nullptr, nullptr);

	return 0;
}
