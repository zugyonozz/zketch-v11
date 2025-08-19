#pragma once

// standard header

#include <string>

// platform header

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
	#define NOMINMAX
#endif

#include <windows.h>

#ifdef __OBJC__
	#undef __OBJC__
#endif

#ifndef USE_ZKETCH_ALIAS
	#define USE_ZKETCH_ALIAS
#endif

#ifdef USE_ZKETCH_ALIAS

	using uchar		= unsigned char ;
	using ullong	= unsigned long long ;
	using cstr		= const char* ;
	using cwstr		= const wchar_t* ;
	using str		= std::string ;
	using wstr		= std::wstring ;

#endif

#ifdef WIN32_LEAN_AND_MEAN
	#undef WIN32_LEAN_AND_MEAN
#endif

#ifdef NOMINMAX
	#undef NOMINMAX
#endif

#ifdef USE_ZKETCH_ALIAS
	#undef USE_ZKETCH_ALIAS
#endif