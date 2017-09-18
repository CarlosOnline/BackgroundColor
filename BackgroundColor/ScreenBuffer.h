//////////////////////////////////////////////////////////////////////////
// ScreenBuffer.h
//
#pragma once
#include <iostream>
#include <windows.h>
#include <wincon.h>

//////////////////////////////////////////////////////////////////////////
// ScreenBuffer
class ScreenBuffer
{
	enum ColorMode {
		Foreground,
		Background,
	};

public:
	int		ProcessId;
	HANDLE	ConsoleHandle;
	CONSOLE_SCREEN_BUFFER_INFO BufferInfo;

	int Width() const { return BufferInfo.dwSize.X; }
	int Height() const { return BufferInfo.dwSize.Y; }

	ScreenBuffer()
	{
		ProcessId = 0;
		ConsoleHandle = INVALID_HANDLE_VALUE;
		memset(&BufferInfo, 0, sizeof(BufferInfo));
	}

	~ScreenBuffer()
	{
		ConsoleHandle = INVALID_HANDLE_VALUE;
	}

	bool ConnectToConsole();
	bool ConnectToConsole(int ProcessId);
	bool ConnectToConsole(HANDLE hConsole);

	WORD GetForegroundColor() { return GetColor(ColorMode::Foreground); }
	WORD GetBackgroundColor() { return GetColor(ColorMode::Background); }

	bool SetColorFullScreen(WORD ForegroundColor, WORD BackgroundColor)
	{ 
		SetForegroundColorFullScreen(ForegroundColor);
		SetBackgroundColorFullScreen(BackgroundColor);
	}

	bool SetNewColor(WORD ForegroundColor, WORD BackgroundColor)
	{
		SetForegroundColor(ForegroundColor);
		SetBackgroundColor(BackgroundColor);
	}

	bool SetForegroundColor(WORD Color)				{ return SetNewColor(Color, ColorMode::Foreground); }
	bool SetBackgroundColor(WORD Color)				{ return SetNewColor(Color, ColorMode::Background); }
	bool SetForegroundColorFullScreen(WORD Color)	{ return SetColorFullScreen(Color, ColorMode::Foreground); }
	bool SetBackgroundColorFullScreen(WORD Color)	{ return SetColorFullScreen(Color, ColorMode::Background); }

	void LogColorInfo();

private:
	WORD GetColor(ColorMode Mode);
	bool SetNewColor(WORD Color, ColorMode Mode);
	bool SetColorFullScreen(WORD Color, ColorMode Mode);
};
