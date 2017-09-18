//////////////////////////////////////////////////////////////////////////
// ScreenBuffer.cpp
//
#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <wincon.h>
#include <string>
#include "ScreenBuffer.h"
#include "Utility.h"
#include "ColorMapping.h"

//////////////////////////////////////////////////////////////////////////
// Constants
const int BatchRowSize = 1000;

bool ScreenBuffer::ConnectToConsole(int PID)
{
	if (!PID)
	{
		LOG_ERROR(L"Mising PID");
		return false;
	}

	ProcessId = PID;

	FreeConsole();
	if (!AttachConsole(ProcessId))
	{
		LOG_ERROR32(L"AttachConsole");
		return false;
	}

	return ConnectToConsole();
}

bool ScreenBuffer::ConnectToConsole()
{
	return ConnectToConsole(GetStdHandle(STD_OUTPUT_HANDLE));
}

bool ScreenBuffer::ConnectToConsole(HANDLE hConsole)
{
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		LogError(L"INVALID_HANDLE_VALUE");
		return false;
	}

	ConsoleHandle = hConsole;

	memset(&BufferInfo, 0, sizeof(BufferInfo));
	if (!GetConsoleScreenBufferInfo(ConsoleHandle, &BufferInfo))
	{
		LOG_ERROR32(L": GetConsoleScreenBufferInfo Failed\n");
		return false;
	}
	return true;
}

WORD ScreenBuffer::GetColor(ColorMode Mode)
{
	bool foreground = Mode == ColorMode::Foreground;

	if (!GetConsoleScreenBufferInfo(ConsoleHandle, &BufferInfo))
	{
		LOG_ERROR32(L": GetConsoleScreenBufferInfo Failed\n");
		return 0;
	}

	if (foreground)
		return BufferInfo.wAttributes & ~0xFFF0;
	else
		return (BufferInfo.wAttributes & ~0xFF0F) >> 4;
}

/// <summary>
/// Sets color mask for new lines only
/// </summary>
bool ScreenBuffer::SetNewColor(WORD Color, ColorMode Mode)
{
	bool foreground = Mode == ColorMode::Foreground;
	WORD mask = foreground ? Color : Color << 4;

	if (!GetConsoleScreenBufferInfo(ConsoleHandle, &BufferInfo))
	{
		LOG_ERROR32(L": GetConsoleScreenBufferInfo Failed\n");
		goto Error;
	}

	BufferInfo.wAttributes &= foreground ? 0xFFF0 : 0xFF0F;  // zero the color
	BufferInfo.wAttributes |= foreground ? Color : Color << 4; // change the color
	if (foreground)
	{
		BufferInfo.wAttributes &= 0xFFF0; // zero the color
		BufferInfo.wAttributes |= mask;  // change the color
	}
	else
	{
		BufferInfo.wAttributes &= 0xFF0F;  // zero the background color
		BufferInfo.wAttributes |= mask;    // change the background color to red
	}

	if (!SetConsoleTextAttribute(ConsoleHandle, BufferInfo.wAttributes))
	{
		LOG_ERROR32(L": SetConsoleTextAttribute");
		goto Error;
	}

	DBG_MSGBOX(L"%d", (int)Color);

	return true;

Error:
	return false;
}

bool ScreenBuffer::SetColorFullScreen(WORD Color, ColorMode Mode)
{
	bool foreground = Mode == ColorMode::Foreground;
	WORD mask = foreground ? Color : Color << 4;

	int curRow = 0;
	DWORD dwWritten = 0;

	WORD* screenBuffer = new WORD[Width() * BatchRowSize];

	while (curRow < Height())
	{
		int batchRowCount = __min(BatchRowSize, Height());
		DWORD dwDesired = __min(BatchRowSize, (Height() - curRow)) * Width();
		DWORD dwRead = 0;
		COORD coord = { 0, (SHORT)curRow };

		if (!ReadConsoleOutputAttribute(ConsoleHandle, screenBuffer, dwDesired, coord, &dwRead))
		{
			LOG_ERROR32(L": ReadConsoleOutputAttribute");
			goto Error;
		}

		// Apply new color mask
		{
			WORD* buffer = screenBuffer;

			for (int y = 0; y < batchRowCount; y++)     // rows
			{
				buffer = &screenBuffer[y * Width()];
				for (int x = 0; x < Width(); x++)  // columns
				{
					WORD* attribute = &buffer[x];
					if (foreground)
					{
						*attribute &= 0xFFF0; // zero the color
						*attribute |= mask;  // change the color
					}
					else
					{
						*attribute &= 0xFF0F;  // zero the background color
						*attribute |= mask;    // change the background color to red
					}
					WORD result = *attribute;
				}
			}
		}

		// Change console screen buffer
		if (!WriteConsoleOutputAttribute(ConsoleHandle, screenBuffer, dwRead, coord, &dwWritten))
		{
			LOG_ERROR32(L": WriteConsoleOutputAttribute");
			goto Error;
		}

		curRow = __min(curRow + batchRowCount, Height());
	}

	SetNewColor(Color, Mode);

	DBG_MSGBOX(L"%d", (int)Color);

	return true;

Error:
	delete[]screenBuffer;
	return false;
}

void ScreenBuffer::LogColorInfo()
{
	ColorMapping foreMask = GetColorMapping(GetForegroundColor());
	ColorMapping backMask = GetColorMapping(GetBackgroundColor());

	LogInfo(L"color %X%X %s %s\n", (int)GetBackgroundColor(), (int)GetForegroundColor(), backMask.Name, foreMask.Name);
}

