#pragma once

#define WIN32_LEAN_AND_MEAN

#ifndef NOMINMAX
#define NOMINMAX
#endif

#undef __OBJC__

#include <windows.h>

using uchar		= unsigned char ;
using ullong	= unsigned long long ;
using cstr		= const char* ;

struct WinFg {
	enum : uchar {
		HIDE = SW_HIDE,
		NORMAL = SW_NORMAL,
		SHOWMINIMIZE = SW_SHOWMINIMIZED,
		MAXIMIZE = SW_MAXIMIZE,
		SHOWNOFOCUS = SW_SHOWNOACTIVATE,
		SHOW = SW_SHOW,
		MINIMIZE = SW_MINIMIZE,
		SHOWMINIZENOFOCUS = SW_SHOWMINNOACTIVE,
		SHOWRECENTNOFOCUS = SW_SHOWNA,
		RESTORE = SW_RESTORE,
		DEFAULT = SW_SHOWDEFAULT ,
		FORCEMINIMIZE = SW_FORCEMINIMIZE ,
	} fg ;

	constexpr operator int() const noexcept { 
		return static_cast<int>(fg) ; 
	}
} ;