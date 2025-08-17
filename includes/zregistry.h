#pragma once

#ifndef USE_Z_ALIAS
#define USE_Z_ALIAS
#endif

#ifndef USE_ZREGISTRY_HELPER
#define USE_ZREGISTRY_HELPER
#endif

#include <string>
#include <unordered_map>
#include "zdef.h"

#ifdef USE_ZREGISTRY_HELPER

struct inc {
	int operator()(int n = 1) const noexcept {
		static int internal_inc_v = 0 ;
		return (internal_inc_v += n) ;
	}
} ;

struct dec {
	int operator()(int n = 1) const noexcept {
		static int internal_dec_v = ~0U & static_cast<unsigned>(1 << 31) ;
		return (internal_dec_v -= n) ;
	}
} ;

#endif

template <typename Fn>
constexpr std::string_view make_id(cstr prefix, Fn&& fn = inc{}) noexcept {
	return prefix + std::to_string(std::forward<Fn>(fn())) ;
}

#ifdef USE_Z_ALIAS

template <typename Key, typename Data>
using umap = std::unordered_map<Key, Data> ;

#endif

template <typename T>
class window_registry {
private :
	static umap<HWND, Window>

public :
	template <typename Fn> 
	constexpr component_registry(const char* prefix, Fn&& fn = zid_ops::inc{}) noexcept : id(prefix + std::to_string(fn())) {}

	constexpr cstr getId() const noexcept { return id.data() ; }
} ;

#ifdef USE_ZREGISTRY_HELPER
#undef USE_ZREGISTRY_HELPER
#endif

#ifdef USE_Z_ALIAS
#undef USE_Z_ALIAS
#endif