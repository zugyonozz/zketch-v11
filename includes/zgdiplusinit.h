#pragma once

#ifdef __OBJC__
#undef __OBJC__
#endif

#include <objidl.h>
#include <gdiplus.h>

namespace error_handler {
	struct failed_init_gdiplussession {
		const char* what() {
			return "Failed to initialize GDI+" ;
		}
	} ;
}

class GDIplusSession {
private :
	ULONG_PTR token {} ;

public :
	GDIplusSession() {
		Gdiplus::GdiplusStartupInput in ;
		if (Gdiplus::GdiplusStartup(&token, &in, nullptr) != Gdiplus::Ok)
            throw error_handler::failed_init_gdiplussession() ;
	}
	~GDIplusSession() {
        Gdiplus::GdiplusShutdown(token);
    }
} ;

inline GDIplusSession g ;