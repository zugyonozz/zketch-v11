#pragma once

// zketch header

#include "zunit.h"

#ifndef USE_ZKETCH_ALIAS
	#define USE_ZKETCH_ALIAS
#endif

namespace zketch {

	class Font {
	private :
		cwstr family_ ;
		float size_ ;
		int style_ ;

	public :
		constexpr Font(cwstr family, float size, FontStyle style) noexcept : family_(family), size_(size), style_(static_cast<int>(style)) {}
		constexpr Font(const Font& o) noexcept : family_(o.family_), size_(o.size_), style_(o.style_) {}

		constexpr cwstr family() const noexcept {
			return family_ ;
		}

		constexpr float size() const noexcept {
			return size_ ;
		}

		constexpr int style() const noexcept {
			return style_ ;
		}

	} ;

}

#ifdef USE_ZKETCH_ALIAS
	#undef USE_ZKETCH_ALIAS
#endif