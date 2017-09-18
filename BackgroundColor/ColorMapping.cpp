//////////////////////////////////////////////////////////////////////////
// ColorMapping.cpp
//
#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <wincon.h>
#include "ColorMapping.h"
#include "Utility.h"

//////////////////////////////////////////////////////////////////////////
// GetColorMapping
const ColorMapping GetColorMapping(const wchar_t* name)
{
	if (name && *name)
	{
		for (int idx = 0; idx < _countof(ColorMappings); idx++)
		{
			ColorMapping mapping = ColorMappings[idx];
			if (0 == _wcsicmp(name, mapping.Name))
			{
				return ColorMappings[idx];
			}
		}
	}

	LOG_ERROR("Unknown color: %s", name);
	return ColorMappings[0];
}

const ColorMapping GetColorMapping(WORD mask)
{
	for (int idx = 0; idx < _countof(ColorMappings); idx++)
	{
		if (ColorMappings[idx].Color == mask)
			return ColorMappings[idx];
	}

	LOG_ERROR("Unknown color: %X", mask);
	return ColorMappings[0];
}

const char* ColorUsage = R"V0G0N(
Black
Gray
DarkBlue
Blue      LightBlue    Light Blue     BrightBlue      Bright Blue
Green     LightGreen   Light Green    BrightGreen     Bright Green
Aqua      LightAqua    Light Aqua     BrightAqua      Bright Aqua
Red       LightRed     Light Red      BrightRed       Bright Red
Purple    LightPurple  Light Purple   BrightPurple    Bright Purple
Yellow    LightYellow  Light Yellow   BrightYellow    Bright Yellow
White     LightWhite   Light White    BrightWhite     Bright White
)V0G0N";
