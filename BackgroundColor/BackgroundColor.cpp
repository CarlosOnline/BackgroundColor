// BackgroundColor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <wincon.h>
#include <string>
#include "Utility.h"
#include "ColorMapping.h"
#include "ScreenBuffer.h"

//////////////////////////////////////////////////////////////////////////
// Constants
const int BatchRowSize = 1000;

//////////////////////////////////////////////////////////////////////////
// Globals

wchar_t* ForegroundColorName = nullptr;
wchar_t* BackgroundColorName = nullptr;
int      PidOverride = 0;
bool     g_Verbose = false;
bool     g_NewLinesOnly = false;

//////////////////////////////////////////////////////////////////////////
// Functions
int DumpColors(HANDLE hStdOut, CONSOLE_SCREEN_BUFFER_INFO& bufInfo);
bool ParseArgs(int argc, char *argv[]);

ScreenBuffer g_ScreenBuffer;

//////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char *argv[])
{
	if (!ParseArgs(argc, argv))
		return -1;

	if (0 == _wcsicmp(BackgroundColorName, L"none"))
		BackgroundColorName = nullptr;

	ColorMapping foreColorMapping = ForegroundColorName ? GetColorMapping(ForegroundColorName) : ColorMappings[0];
	ColorMapping backColorMapping = BackgroundColorName ? GetColorMapping(BackgroundColorName) : ColorMappings[0];

	//LOG(L"Fore: %s Back: %s", ForegroundColorName, BackgroundColorName);

	if (PidOverride)
	{
		FreeConsole();
		if (!g_ScreenBuffer.ConnectToConsole(PidOverride))
		{
			LOG_ERROR(L"ConnectToConsole");
			return -1;
		}
	}
	else
	{
		g_ScreenBuffer.ConnectToConsole();
	}

	if (g_Verbose)
		g_ScreenBuffer.LogColorInfo();

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!g_NewLinesOnly)
	{
		if (BackgroundColorName)
			g_ScreenBuffer.SetBackgroundColorFullScreen(backColorMapping.Color);

		if (ForegroundColorName)
			g_ScreenBuffer.SetForegroundColorFullScreen(foreColorMapping.Color);
	}
	else
	{
		if (BackgroundColorName)
			g_ScreenBuffer.SetBackgroundColor(backColorMapping.Color);

		if (ForegroundColorName)
			g_ScreenBuffer.SetForegroundColor(foreColorMapping.Color);
	}
	FreeConsole();

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// DumpColors
int DumpColors(HANDLE hStdOut, CONSOLE_SCREEN_BUFFER_INFO& bufInfo)
{
	for (int idx = 0; idx < 16; idx++)
	{
		bufInfo.wAttributes &= 0xFF0F;  // zero the background color
		bufInfo.wAttributes |= ((WORD)idx) << 4; // change the background color to red

		if (!SetConsoleTextAttribute(hStdOut, bufInfo.wAttributes))
		{
			wchar_t szDebug[256];
			wsprintf(szDebug, __FUNCTIONW__ L": ERROR: SetConsoleTextAttribute Failed\n");
			OutputDebugString(szDebug);
			wprintf(szDebug);
			return -1;
		}

		memset(&bufInfo, 0, sizeof(bufInfo));
		if (!GetConsoleScreenBufferInfo(hStdOut, &bufInfo))
		{
			wchar_t szDebug[256];
			wsprintf(szDebug, __FUNCTIONW__ L": ERROR: GetConsoleScreenBufferInfo Failed\n");
			OutputDebugString(szDebug);
			wprintf(szDebug);
			return -1;
		}
		printf("Press any key to continue");
		getchar();
	}
	return 0;
}

wchar_t* to_wcs(const char* value)
{
	size_t size = strlen(value) + 1;
	size_t outSize;

	wchar_t* result = new wchar_t[size];
	mbstowcs_s(&outSize, result, size, value, size - 1);
	return result;
}

//////////////////////////////////////////////////////////////////////////
// ParseArgs
bool ParseArgs(int argc, char *argv[])
{
	for (int idx = 1; idx < argc; idx++)
	{
		char* value = argv[idx];

		if (0 == _stricmp(value, "-newlines"))
		{
			g_NewLinesOnly = true;
			continue;
		}

		if (value[0] == '-')
		{
			printf("\r\nError unknown argument: %s\r\n", value);
			goto Usage;
		}

		if (!BackgroundColorName)
		{
			if (!IsNumeric(value))
			{
				BackgroundColorName = to_wcs(value);
				continue;
			}
		}

		if (!ForegroundColorName)
		{
			if (!IsNumeric(value))
			{
				ForegroundColorName = to_wcs(value);
				continue;
			}
		}

		if (!PidOverride)
		{
			if (IsNumeric(value))
			{
				PidOverride = atoi(value);
				continue;
			}
		}
	}

	if (BackgroundColorName && BackgroundColorName[0])
		return true;

Usage:
	const char * usage = R"V0G0N(
BackgroundColor Utility
Created by Carlos Gomes <cgomes@iinet.com>

Arguments:
        background     - specifies background color name. Use none to keep current background color.
        foreground     - (optional) specifies foreground color name. If not specified then not changed.
        process id     - (optional) attach to console application for testing.
                          Defaults to current console.
        -newlines      - changes the colors for new lines only, previous lines are untouched.

Examples:
	BackgroundColor.exe blue
			Changes background color only to blue on all lines.

	BackgroundColor.exe red white
			Changes background & foreground color on all lines.

	BackgroundColor.exe blue -newlines
			Changes background color only to blue on new lines only.  Existing lines are not changed.

	BackgroundColor.exe red white
			Changes background & foreground color on new lines only.  Existing lines are not changed.

	BackgroundColor.exe none red
			Changes foreground color only on all lines.
)V0G0N";

	printf(usage);
	printf("Color Names:\r\n");
	printf("   Any of the variations below can be used.\r\n");
	printf(ColorUsage);
	return false;
}

