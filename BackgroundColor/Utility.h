//////////////////////////////////////////////////////////////////////////
// Utility.h
//
#pragma once
//#define Diagnostics 1

#include <stdio.h>
#include <windows.h>

#define LOG(fmt, ...)			LogInfo(__FUNCTIONW__ L": " fmt L"\r\n", __VA_ARGS__)
#define LOG_ERROR(fmt, ...)		LogError(L"ERROR: " __FUNCTIONW__ L": " fmt L"\r\n", __VA_ARGS__)
#define LOG_ERROR32(fmt, ...)	LogWin32Error(__FUNCTIONW__ L": " fmt L"\r\n", __VA_ARGS__)
#define LOG_MSGBOX(fmt, ...)	LogMsgBox(__FUNCTIONW__ L": " fmt L"\r\n", __VA_ARGS__)
#if Diagnostics
#define DBG_MSGBOX(fmt, ...)	LogMsgBox(__FUNCTIONW__ L": " fmt L"\r\n", __VA_ARGS__)
#else
#define DBG_MSGBOX(fmt, ...)
#endif
void LogInfo(wchar_t* fmt, ...);
void LogError(wchar_t* fmt, ...);
void LogWin32Error(wchar_t* fmt, ...);
void LogMsgBox(wchar_t* fmt, ...);

int		GetParentPID();
void	GetWindowsErrorMessage(DWORD error, wchar_t* szError, size_t cchError);
HWND	GetWindowFromProcessId(int ProcessId);
int		WaitForParentToFinish();

inline wchar_t* ToWide(const char* ValueA)
{
	const char *valueA = ValueA;
	size_t size = strlen(valueA) + 1;
	wchar_t* valueW = new wchar_t[size];

	size_t outSize;
	mbstowcs_s(&outSize, valueW, size, valueA, size - 1);

	return valueW;
}

//////////////////////////////////////////////////////////////////////////
// IsNumeric
inline bool IsNumeric(const char* Value)
{
	if (!Value || !*Value)
		return false;

	const char* psz = Value;

	while (*psz)
	{
		if (!isdigit(*psz))
			return false;
		psz++;
	}

	return true;
}

inline bool IsNumeric(const wchar_t* Value)
{
	if (!Value || !*Value)
		return false;

	const wchar_t* psz = Value;

	while (*psz)
	{
		if (!isdigit(*psz))
			return false;
		psz++;
	}

	return true;
}

