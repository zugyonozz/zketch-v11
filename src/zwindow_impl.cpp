#include "zwindow.h"

namespace zketch {

	namespace error_handler {

		cstr register_class_failed::what() const noexcept {
			return "Failed to register window class" ;
		}

		cstr create_window_failed::what() const noexcept {
			return "Failed to create window" ;
		}

	}

}