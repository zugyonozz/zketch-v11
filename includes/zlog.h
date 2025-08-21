#pragma once
#include "zdef.h"

struct zlog {
private :
	static inline void apply_color(const char* tx, int lv) noexcept {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE) ;
		CONSOLE_SCREEN_BUFFER_INFO info ;
		GetConsoleScreenBufferInfo(hConsole, &info) ;
		WORD oldColor = info.wAttributes ;

		switch (lv) {
			case 0 :
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY) ; break ;
			case 1 :
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY) ; break ;
			case 2 :
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY) ; break ;
			default : break ;
		}

		printf("%s", tx) ;
		SetConsoleTextAttribute(hConsole, oldColor) ;
	}

	template <typename T>
	static void print(const T& val) noexcept {
		if constexpr (std::is_same_v<T, std::string>)
			printf("%s", val.c_str()) ;
		else if constexpr (std::is_same_v<T, const char*>)
			printf("%s", val) ;
		else if constexpr (std::is_arithmetic_v<T>)
			std::cout << val ; // atau printf dengan format berbeda
		else
			std::cout << val ; // fallback
	}

public :
	zlog() noexcept = delete ;
	zlog(const zlog&) noexcept = delete ;
	zlog(zlog&&) noexcept = delete ;
	zlog& operator=(const zlog&) noexcept = delete ;
	zlog& operator=(zlog&&) noexcept = delete ;


	template <typename... Args>
	static inline void info(Args&&... args) noexcept {
		printf("[") ;
		apply_color("INFO", 0) ;
		printf("]\t") ;
		(print(std::forward<Args>(args)), ...) ;
		printf("\n") ;
	}

	template <typename... Args>
	static inline void warning(Args&&... args) noexcept {
		printf("[") ;
		apply_color("WARN", 1) ;
		printf("]\t") ;
		(print(std::forward<Args>(args)), ...) ;
		printf("\n") ;
	}

	template <typename... Args>
	static inline void error(Args&&... args) noexcept {
		printf("[") ;
		apply_color("ERROR", 2) ;
		printf("]\t") ;
		(print(std::forward<Args>(args)), ...) ;
		printf("\n") ;
	}
} ;