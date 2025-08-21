#pragma once

// platform header

#include <objidl.h>
#include <gdiplus.h>

namespace zketch {

	namespace error_handler {

		struct failed_init_gdiplussession {
			const char* what() const noexcept {
				return "Failed to initialize GDI+" ;
			}
		} ;

	}
}

class GDIplusSession {
private :
	ULONG_PTR token {} ;

public :
	GDIplusSession() {
		Gdiplus::GdiplusStartupInput in ;
		if (Gdiplus::GdiplusStartup(&token, &in, nullptr) != Gdiplus::Ok)
            throw zketch::error_handler::failed_init_gdiplussession() ;
	}
	~GDIplusSession() {
        Gdiplus::GdiplusShutdown(token);
    }
} ;

static GDIplusSession gdiplusinit ;