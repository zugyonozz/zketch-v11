#pragma once

#include "zunit.h"

struct Font {
	const wchar_t* name ;
	float size ;
	GDIPLUS_BOUNDARY::Gdiplus::FontStyle style ;

	constexpr Font(const wchar_t* name, float size, GDIPLUS_BOUNDARY::Gdiplus::FontStyle style) noexcept : name(name), size(size), style(style) {}
} ;