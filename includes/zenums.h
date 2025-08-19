#pragma once

// checking endianess

static_assert(sizeof(unsigned) == 4, "Color assumes 32-bit unsigned") ;

#ifndef IS_LITTLE_ENDIAN
	#ifdef _MSC_VER
		#define IS_LITTLE_ENDIAN 1
	#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		#define IS_LITTLE_ENDIAN 1
	#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		#define IS_LITTLE_ENDIAN 0
	#else
		#error "Cannot determine endianness"
	#endif
#endif

// zketch header

#include "zdef.h"

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
	#define NOMINMAX
#endif

#ifdef __OBJC__
	#undef __OBJC__
#endif

#include "zgdiplusinit.h"

namespace zketch {

	// enum for window flags

	enum class WindowFlags {
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
	} ;

	// enum for font styles

	enum class FontStyle {
		Regular = Gdiplus::FontStyleRegular,
		Bold = Gdiplus::FontStyleBold,
		Italic = Gdiplus::FontStyleItalic,
		BoldItalic = Bold | Italic,
		Underline = Gdiplus::FontStyleUnderline,
		Strikeout = Gdiplus::FontStyleStrikeout
	} ;

	// enum for event types

	enum class EventType {
		None,
		Quit,
		KeyDown,
		KeyUp,
		MouseMove,
		MouseDown,
		MouseUp,
		Resize,
		Close
	} ;

	// enum for mouse button flags

	enum class MouseButton {
		Left,
		Right,
		Middle,
		Unknown
	} ;

	// enum for color accessor

	#ifdef IS_LITTLE_ENDIAN

		enum class RGBA {
			RED		= 3,
			GREEN	= 2,
			BLUE	= 1,
			ALPHA	= 0,
			R		= RED,
			G		= GREEN,
			B		= BLUE,
			A		= ALPHA
		} ;

	#else

		enum class RGBA {
			RED		= 0,
			GREEN	= 1,
			BLUE	= 2,
			ALPHA	= 3,
			R		= RED,
			G		= GREEN,
			B		= BLUE,
			A		= ALPHA
		} ;

	#endif

	static_assert(static_cast<int>(RGBA::R) == 3 || static_cast<int>(RGBA::R) == 0, "Unexpected RGBA channel layout") ;

	enum class Unit {
		World = Gdiplus::UnitWorld,
		Display = Gdiplus::UnitDisplay,
		Pixel = Gdiplus::UnitPixel,
		Point = Gdiplus::UnitPoint,
		Inch = Gdiplus::UnitInch,
		Document = Gdiplus::UnitDocument,
		Millimeter = Gdiplus::UnitMillimeter
	} ;
}

#ifdef WIN32_LEAN_AND_MEAN
	#undef WIN32_LEAN_AND_MEAN
#endif

#ifdef NOMINMAX
	#undef NOMINMAX
#endif

#ifdef IS_LITTLE_ENDIAN
    #undef IS_LITTLE_ENDIAN
#endif