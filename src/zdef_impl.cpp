#include "zdef.h"

constexpr WinFg::operator int() const noexcept { 
	return static_cast<int>(fg) ; 
}