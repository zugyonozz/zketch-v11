#pragma once

#include "zdef.h"

namespace zketch {

	struct nanoseconds_ {
		static constexpr double val = 1000000000.0 ;
	} ;

	struct microseconds_ {
		static constexpr double val = 1000000.0 ;
	} ;

	struct milliseconds_ {
		static constexpr double val = 1000.0 ;
	} ;

	struct seconds_ {
		static constexpr double val = 1.0 ;
	} ;

	struct minutes_ {
		static constexpr double val = 1.0 / 60.0 ;
	} ;

	struct hours_ {
		static constexpr double val = 1.0 / 3600.0;
	} ;

	template <typename T>
	struct _is_timestamp {
		static constexpr bool val = false ;
	} ;

	template <> struct _is_timestamp<nanoseconds_> {
		static constexpr bool val = true ;
	} ;

	template <> struct _is_timestamp<microseconds_> {
		static constexpr bool val = true ;
	} ;

	template <> struct _is_timestamp<milliseconds_> {
		static constexpr bool val = true ;
	} ;

	template <> struct _is_timestamp<seconds_> {
		static constexpr bool val = true ;
	} ;

	template <> struct _is_timestamp<minutes_> {
		static constexpr bool val = true ;
	} ;

	template <> struct _is_timestamp<hours_> {
		static constexpr bool val = true ;
	} ;

	template <typename T> constexpr bool is_timestamp = _is_timestamp<T>::val ;
	
	template <typename T> constexpr double get_frequency = T::val ;

	class Timer {
	private :
		LARGE_INTEGER m_f, m_t0, m_t1 ;

	public :
		Timer() noexcept {
			QueryPerformanceFrequency(&m_f) ;
			start() ;
		}

		void start() noexcept {
			QueryPerformanceCounter(&m_t0) ;
			m_t1 = m_t0 ;
		}

		void delay(ullong ms) noexcept {
			Sleep(ms) ;
		}

		template <typename T> requires is_timestamp<T>
		double duration() noexcept {
			QueryPerformanceCounter(&m_t1) ;
			return static_cast<double>(m_t1.QuadPart - m_t0.QuadPart) * get_frequency<T> / m_f.QuadPart ;
		}

		void reset() {
			QueryPerformanceFrequency(&m_f) ;
			QueryPerformanceCounter(&m_t0) ;
		}
	} ;

}