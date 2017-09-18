//////////////////////////////////////////////////////////////////////////
// ColorMapping.h
//
#pragma once
#include <iostream>
#include <windows.h>
#include <wincon.h>

//////////////////////////////////////////////////////////////////////////
// Structures
struct ColorMapping
{
	const wchar_t* Name;
	const WORD  Color;
};

//////////////////////////////////////////////////////////////////////////
// ColorMappings
static const ColorMapping ColorMappings[] = {
	{ L"Black"              , ((WORD)0 ) },
	{ L"Blue"               , ((WORD)1 ) },
	{ L"Green"              , ((WORD)2 ) },
	{ L"Aqua"               , ((WORD)3 ) },
	{ L"Red"                , ((WORD)4 ) },
	{ L"Purple"             , ((WORD)5 ) },
	{ L"Yellow"             , ((WORD)6 ) },
	{ L"White"              , ((WORD)7 ) },
	{ L"Gray"               , ((WORD)8 ) },
	{ L"DarkBlue"           , ((WORD)1)  },

	{ L"LightBlue"          , ((WORD)9 ) },
	{ L"LightGreen"         , ((WORD)10) },
	{ L"LightAqua"          , ((WORD)11) },
	{ L"LightRed"           , ((WORD)12) },
	{ L"LightPurple"        , ((WORD)13) },
	{ L"LightYellow"        , ((WORD)14) },
	{ L"LightWhite"         , ((WORD)15) },

	{ L"Light Blue"         , ((WORD)9 ) },
	{ L"Light Green"        , ((WORD)10) },
	{ L"Light Aqua"         , ((WORD)11) },
	{ L"Light Red"          , ((WORD)12) },
	{ L"Light Purple"       , ((WORD)13) },
	{ L"Light Yellow"       , ((WORD)14) },
	{ L"Light White"        , ((WORD)15) },

	{ L"BrightBlue"          , ((WORD)9 ) },
	{ L"BrightGreen"         , ((WORD)10) },
	{ L"BrightAqua"          , ((WORD)11) },
	{ L"BrightRed"           , ((WORD)12) },
	{ L"BrightPurple"        , ((WORD)13) },
	{ L"BrightYellow"        , ((WORD)14) },
	{ L"BrightWhite"         , ((WORD)15) },

	{ L"Bright Blue"         , ((WORD)9 ) },
	{ L"Bright Green"        , ((WORD)10) },
	{ L"Bright Aqua"         , ((WORD)11) },
	{ L"Bright Red"          , ((WORD)12) },
	{ L"Bright Purple"       , ((WORD)13) },
	{ L"Bright Yellow"       , ((WORD)14) },
	{ L"Bright White"        , ((WORD)15) },
};

const ColorMapping GetColorMapping(const wchar_t* name);
const ColorMapping GetColorMapping(WORD mask);

extern const char* ColorUsage;