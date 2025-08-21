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

public :
	zlog() noexcept = delete ;
	zlog(const zlog&) noexcept = delete ;
	zlog(zlog&&) noexcept = delete ;
	zlog& operator=(const zlog&) noexcept = delete ;
	zlog& operator=(zlog&&) noexcept = delete ;


	static inline void info(const str& msg) noexcept {
		printf("[") ; 
		apply_color("INFO", 0) ;
		printf("]\t%s\n", msg.c_str()) ;
	}

	static inline void warning(const str& msg) noexcept {
		printf("[") ; 
		apply_color("WARN", 1) ;
		printf("]\t%s\n", msg.c_str()) ;
	}

	static inline void error(const str& msg) noexcept {
		printf("[") ; 
		apply_color("ERROR", 2) ;
		printf("]\t%s\n", msg.c_str()) ;
	}
} ;