#pragma once

#include <windows.h>
#include <string>

#define USE_Z_ALIAS

#ifdef USE_Z_ALIAS

using uchar		= unsigned char ;
using schar		= signed char ;
using ushort	= unsigned short ;
using sshort	= signed short ;
using uint		= unsigned ;
using sint		= signed ;
using ulong		= unsigned long ;
using slong		= signed long ;
using ullong	= unsigned long long ;
using sllong	= long long ;
using cstr		= const char* ;
using str		= std::string ;

#endif

struct WinFg {
	enum : uint {
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

#undef USE_Z_ALIAS