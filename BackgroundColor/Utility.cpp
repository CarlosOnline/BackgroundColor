//////////////////////////////////////////////////////////////////////////
// Utility.cpp
//
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <Psapi.h>
#include <tlhelp32.h>
#include <vdmdbg.h>
#include <conio.h>
#include "Utility.h"

void LogInfo(wchar_t* fmt, ...)
{
	static wchar_t szDebug[2048];

	va_list args;
	va_start(args, fmt);
	vswprintf_s(szDebug, fmt, args);
	va_end(args);

	OutputDebugStringW(szDebug);
	wprintf(szDebug);
}

void LogMsgBox(wchar_t* fmt, ...)
{
	static wchar_t szDebug[2048];

	va_list args;
	va_start(args, fmt);
	vswprintf_s(szDebug, fmt, args);
	va_end(args);

	OutputDebugStringW(szDebug);
	wprintf(szDebug);
	wprintf(szDebug);
	MessageBoxW(NULL, szDebug, L"Background Color Worker", MB_OK);
}

void LogError(wchar_t* fmt, ...)
{
	static wchar_t szDebug[2048];

	va_list args;
	va_start(args, fmt);
	vswprintf_s(szDebug, fmt, args);
	va_end(args);

	OutputDebugStringW(szDebug);
	wprintf(szDebug);
	wprintf(szDebug);
	//MessageBoxW(NULL, szDebug, L"Background Color Worker Error", MB_OK);
}

void LogWin32Error(wchar_t* fmt, ...)
{
	static wchar_t szDebug[2048];
	static wchar_t szDebug2[2048];

	int error = GetLastError();

	va_list args;
	va_start(args, fmt);
	vswprintf_s(szDebug, fmt, args);
	va_end(args);

	wsprintfW(szDebug2, L"ERROR: (%d) %s", error, szDebug);

	OutputDebugStringW(szDebug2);
	wprintf(szDebug2);
	//MessageBoxW(NULL, szDebug2, L"Background Color Worker Error", MB_OK);
}
