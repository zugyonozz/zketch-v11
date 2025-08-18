// #include "zunit.h"

// constexpr Point::Point() noexcept : x(0.0f), y(0.0f) {}

// constexpr Point::Point(float v) noexcept : x(v), y(v) {}

// constexpr Point::Point(float x, float y) noexcept : x(x), y(y) {}

// constexpr Point::Point(const Point& o) noexcept : x(o.x), y(o.y) {}

// constexpr Point& Point::operator=(float v) noexcept { 
// 	x = y = v ;
// 	return *this ; 
// }

// constexpr Point& Point::operator=(const Point& o) noexcept {
// 	x = o.x ;
// 	y = o.y ;
// 	return *this ;
// }

// constexpr Point Point::operator+() const noexcept { 
// 	return *this ; 
// }

// constexpr Point Point::operator-() const noexcept { 
// 	return {-x, -y} ; 
// }

// constexpr Point& Point::operator+=(const Point& o) noexcept { 
// 	x += o.x ; 
// 	y += o.y ; 
// 	return *this ; 
// }

// constexpr Point& Point::operator-=(const Point& o) noexcept { 
// 	x -= o.x ; 
// 	y -= o.y ; 
// 	return *this ; 
// }

// constexpr Point& Point::operator*=(const Point& o) noexcept { 
// 	x *= o.x ; 
// 	y *= o.y ; 
// 	return *this ; 
// }

// constexpr Point& Point::operator/=(const Point& o) noexcept { 
// 	x /= o.x ; 
// 	y /= o.y ; 
// 	return *this ; 
// }

// constexpr Point& Point::operator+=(int v) noexcept { 
// 	x += v ; 
// 	y += v ; 
// 	return *this ; 
// }

// constexpr Point& Point::operator-=(int v) noexcept { 
// 	x -= v ; 
// 	y -= v ; 
// 	return *this ; 
// }

// constexpr Point& Point::operator*=(int v) noexcept { 
// 	x *= v ; 
// 	y *= v ; 
// 	return *this ; 
// }

// constexpr Point& Point::operator/=(int v) noexcept { 
// 	x /= v ; 
// 	y /= v ; 
// 	return *this ; 
// }

// constexpr bool Point::operator==(const Point& o) const noexcept { 
// 	return x == o.x && y == o.y ; 
// }

// constexpr bool Point::operator!=(const Point& o) const noexcept { 
// 	return !(*this == o) ; 
// }

// constexpr Point::operator tagPOINT() const noexcept { 
// 	return {
// 		static_cast<long>(x), 
// 		static_cast<long>(y)
// 	} ; 
// }

// constexpr Point::operator _POINTL() const noexcept { 
// 	return {
// 		static_cast<long>(x), 
// 		static_cast<long>(y)
// 	} ; 
// }

// constexpr Point::operator tagSIZE() const noexcept { 
// 	return {
// 		static_cast<long>(x), 
// 		static_cast<long>(y)
// 	} ; 
// }

// constexpr Point::operator tagPOINTS() const noexcept { 
// 	return {
// 		static_cast<short>(x), 
// 		static_cast<short>(y)
// 	} ; 
// }

// Point::operator GDIPLUS_BOUNDARY::Gdiplus::PointF() const noexcept {
// 	return {x, y} ;
// }

// Point::operator GDIPLUS_BOUNDARY::Gdiplus::SizeF() const noexcept {
// 	return {x, y} ;
// }

// Point::operator GDIPLUS_BOUNDARY::Gdiplus::Point() const noexcept {
// 	return {static_cast<int>(x), static_cast<int>(y)} ;
// }

// Point::operator GDIPLUS_BOUNDARY::Gdiplus::Size() const noexcept {
// 	return {static_cast<int>(x), static_cast<int>(y)} ;
// }

// constexpr Point operator+(const Point& a, const Point& b) noexcept  { 
// 	return {
// 		a.x + b.x, 
// 		a.y + b.y
// 	} ; 
// }

// constexpr Point operator-(const Point& a, const Point& b) noexcept  { 
// 	return {
// 		a.x - b.x, 
// 		a.y - b.y
// 	} ; 
// }

// constexpr Point operator*(const Point& a, const Point& b) noexcept  { 
// 	return {
// 		a.x * b.x, 
// 		a.y * b.y
// 	} ; 
// }

// constexpr Point operator/(const Point& a, const Point& b) noexcept  { 
// 	return {
// 		a.x / b.x, 
// 		a.y / b.y
// 	} ; 
// }

// constexpr Point operator+(const Point& a, int v) noexcept { 
// 	return {
// 		a.x + v, 
// 		a.y + v
// 	} ; 
// }

// constexpr Point operator-(const Point& a, int v) noexcept { 
// 	return {
// 		a.x - v, 
// 		a.y - v
// 	} ; 
// }

// constexpr Point operator*(const Point& a, int v) noexcept { 
// 	return {
// 		a.x * v, 
// 		a.y * v
// 	} ; 
// }

// constexpr Point operator/(const Point& a, int v) noexcept { 
// 	return {
// 		a.x / v, 
// 		a.y / v
// 	} ; 
// }

// constexpr Point operator+(int v, const Point& a) noexcept { 
// 	return a + v ; 
// }

// constexpr Point operator*(int v, const Point& a) noexcept { 
// 	return a * v ; 
// }

// constexpr Point operator-(int v, const Point& a) noexcept { 
// 	return {
// 		v - a.x, 
// 		v - a.y
// 	} ; 
// }

// constexpr Point operator/(int v, const Point& a) noexcept { 
// 	return {
// 		v / a.x, 
// 		v / a.y
// 	} ; 
// }

// std::ostream& operator<<(std::ostream& os, const Point& pt) noexcept {
// 	return os << "{" << pt.x << ", " << pt.y << "}" ;
// }

// constexpr Quad::Quad() noexcept : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}

// constexpr Quad::Quad(float v) noexcept : x(v), y(v), w(v), h(v) {}

// constexpr Quad::Quad(float x, float y, float w, float h) noexcept : x(x), y(y), w(w), h(h) {}

// constexpr Quad::Quad(const Quad& o) noexcept : x(o.x), y(o.y), w(o.w), h(o.h) {}

// constexpr Quad::Quad(const Point& p, const Point& s) noexcept : x(p.x), y(p.y), w(s.x), h(s.y) {}

// constexpr Quad& Quad::operator=(float v) noexcept { 
// 	x = y = w = h = v ; 
// 	return *this ; 
// }

// constexpr Quad& Quad::operator=(const Quad& o) noexcept { 
// 	x = o.x ; 
// 	y = o.y ; 
// 	w = o.w ; 
// 	h = o.h ; 
// 	return *this ; 
// }

// constexpr Quad Quad::operator+() const noexcept { 
// 	return *this ; 
// }

// constexpr Quad Quad::operator-() const noexcept { 
// 	return {-x, -y, w, h} ; 
// }

// constexpr Quad& Quad::operator+=(const Quad& o) noexcept { 
// 	x += o.x ; 
// 	y += o.y ; 
// 	w += o.w ; 
// 	h += o.h ; 
// 	return *this ; 
// }

// constexpr Quad& Quad::operator-=(const Quad& o) noexcept { 
// 	x -= o.x ; 
// 	y -= o.y ; 
// 	w -= o.w ; 
// 	h -= o.h ; 
// 	return *this ; 
// }

// constexpr Quad& Quad::operator*=(const Quad& o) noexcept { 
// 	x *= o.x ; 
// 	y *= o.y ; 
// 	w *= o.w ; 
// 	h *= o.h ; 
// 	return *this ; 
// }

// constexpr Quad& Quad::operator/=(const Quad& o) noexcept { 
// 	x /= o.x ; 
// 	y /= o.y ; 
// 	w /= o.w ; 
// 	h /= o.h ; 
// 	return *this ; 
// }

// constexpr Quad& Quad::operator+=(float v) noexcept { 
// 	x += v ; 
// 	y += v ; 
// 	w += v ; 
// 	h += v ; 
// 	return *this ; 
// }

// constexpr Quad& Quad::operator-=(float v) noexcept { 
// 	x -= v ; 
// 	y -= v ; 
// 	w -= v ; 
// 	h -= v ; 
// 	return *this ; 
// }

// constexpr Quad& Quad::operator*=(float v) noexcept { 
// 	x *= v ; 
// 	y *= v ; 
// 	w *= v ; 
// 	h *= v ; 
// 	return *this ; 
// }

// constexpr Quad& Quad::operator/=(float v) noexcept { 
// 	x /= v ; 
// 	y /= v ; 
// 	w /= v ; 
// 	h /= v ; 
// 	return *this ; 
// }

// constexpr bool Quad::operator==(const Quad& o) const noexcept { 
// 	return x == o.x && y == o.x && w == o.x && h == o.x ; 
// }

// constexpr bool Quad::operator!=(const Quad& o) const noexcept { 
// 	return !(*this == o) ; 
// }

// constexpr Quad::operator tagRECT() const noexcept { 
// 	return {
// 		static_cast<long>(x), 
// 		static_cast<long>(y), 
// 		static_cast<long>(w) + static_cast<long>(x), 
// 		static_cast<long>(h) +  static_cast<long>(y) 
// 	} ; 
// }

// constexpr Quad::operator _RECTL() const noexcept { 
// 	return {
// 		static_cast<long>(x), 
// 		static_cast<long>(y), 
// 		static_cast<long>(w) + static_cast<long>(x), 
// 		static_cast<long>(h) +  static_cast<long>(y) 
// 	} ; 
// }

// Quad::operator GDIPLUS_BOUNDARY::Gdiplus::Rect() const noexcept {
// 	return {static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h)} ;
// }

// Quad::operator GDIPLUS_BOUNDARY::Gdiplus::RectF() const noexcept {
// 	return {x, y, w, h} ;
// }

// constexpr const Point Quad::getPos() const noexcept { 
// 	return {x, y} ; 
// }

// constexpr Point Quad::getPos() noexcept { 
// 	return {x, y} ; 
// }

// constexpr const Point Quad::getSize() const noexcept { 
// 	return {w, h} ; 
// }

// constexpr Point Quad::getSize() noexcept { 
// 	return {w, h} ; 
// }

// constexpr Quad& Quad::setPos(float x, float y) noexcept { 
// 	x = x ; 
// 	y = y ; 
// 	return *this ;
// }

// constexpr Quad& Quad::setPos(const Point& pos) noexcept { 
// 	x = pos.x ; 
// 	y = pos.y ; 
// 	return *this ;
// }

// constexpr Quad& Quad::setSize(float w, float h) noexcept { 
// 	w = w ; 
// 	h = h ; 
// 	return *this ;
// }

// constexpr Quad& Quad::setSize(const Point& size) noexcept { 
// 	w = size.x ; 
// 	h = size.y ; 
// 	return *this ;
// }

// constexpr Quad operator+(const Quad& a, const Quad& b) noexcept { 
// 	return {
// 		a.x + b.x, 
// 		a.y + b.y, 
// 		a.w + b.w, 
// 		a.h + b.h
// 	} ; 
// }

// constexpr Quad operator-(const Quad& a, const Quad& b) noexcept { 
// 	return {
// 		a.x - b.x, 
// 		a.y - b.y, 
// 		a.w - b.w, 
// 		a.h - b.h
// 	} ; 
// }

// constexpr Quad operator*(const Quad& a, const Quad& b) noexcept { 
// 	return {
// 		a.x * b.x, 
// 		a.y * b.y, 
// 		a.w * b.w, 
// 		a.h * b.h
// 	} ; 
// }

// constexpr Quad operator/(const Quad& a, const Quad& b) noexcept { 
// 	return {
// 		a.x / b.x, 
// 		a.y / b.y, 
// 		a.w / b.w, 
// 		a.h / b.h
// 	} ; 
// }

// constexpr Quad operator+(const Quad& a, float v) noexcept { 
// 	return {
// 		a.x + v, 
// 		a.y + v, 
// 		a.w + v, 
// 		a.h + v
// 	} ; 
// }

// constexpr Quad operator-(const Quad& a, float v) noexcept { 
// 	return {
// 		a.x - v, 
// 		a.y - v, 
// 		a.w - v, 
// 		a.h - v
// 	} ; 
// }

// constexpr Quad operator*(const Quad& a, float v) noexcept { 
// 	return {
// 		a.x * v, 
// 		a.y * v, 
// 		a.w * v, 
// 		a.h * v
// 	} ; 
// }

// constexpr Quad operator/(const Quad& a, float v) noexcept { 
// 	return {
// 		a.x / v, 
// 		a.y / v, 
// 		a.w / v, 
// 		a.h / v
// 	} ; 
// }

// constexpr Quad operator+(float v, const Quad& a) noexcept { 
// 	return a + v ; 
// }

// constexpr Quad operator-(float v, const Quad& a) noexcept { 
// 	return {
// 		v - a.x, 
// 		v - a.y, 
// 		v - a.w, 
// 		v - a.h
// 	} ; 
// }

// constexpr Quad operator*(float v, const Quad& a) noexcept { 
// 	return a * v ; 
// }

// constexpr Quad operator/(float v, const Quad& a) noexcept { 
// 	return {
// 		v / a.x, 
// 		v / a.y, 
// 		v / a.w, 
// 		v / a.h
// 	} ; 
// }

// std::ostream& operator<<(std::ostream& os, const Quad& q) noexcept {
// 	return os << "{" << q.x << ", " << q.y << ", " << q.w << ", " << q.h << "}" ;
// }

// const char* error_handler::color_access_out_of_bound::what() const noexcept {
// 	return "error\t:Color access out of range!\nhelp\t:color access must be 0 ~ 3" ;
// }

// constexpr Color::Color() noexcept : color_(0, 0, 0, 255) {}

// constexpr Color::Color(uint8 r, uint8 g, uint8 b, uint8 a) noexcept : color_(r, g, b, a) {}

// constexpr Color::Color(const Color& o) noexcept : color_(o.color_) {}

// constexpr Color& Color::operator=(const Color& o) noexcept {
// 	if (this != &o)
// 		color_ = o.color_ ;
// 	return *this ;
// }

// constexpr const uint8& Color::operator[](RGBA channel) const noexcept {
// 	return color_.bytes[static_cast<uint8>(channel)] ;
// }

// constexpr uint8& Color::operator[](RGBA channel) noexcept {
// 	return color_.bytes[static_cast<uint8>(channel)] ;
// }

// const uint8& Color::operator[](uint8 channel) const {
// 	if (channel > 3)
// 		throw error_handler::color_access_out_of_bound() ;
// 	return color_.bytes[channel] ;
// }

// uint8& Color::operator[](uint8 channel) {
// 	if (channel > 3)
// 		throw error_handler::color_access_out_of_bound() ;
// 	return color_.bytes[channel] ;
// }

// constexpr const uint8* Color::begin() const noexcept {
// 	return color_.bytes ;
// }

// constexpr uint8* Color::begin() noexcept {
// 	return color_.bytes ;
// }

// constexpr const uint8* Color::end() const noexcept {
// 	return color_.bytes + sizeof(unsigned) ;
// }

// constexpr uint8* Color::end() noexcept {
// 	return color_.bytes + sizeof(unsigned) ;
// }

// constexpr Color::operator COLORREF() const noexcept {
// 	return color_.bytes[0] << 16 | color_.bytes[1] << 8 | color_.bytes[2] ;
// }

// Color::operator GDIPLUS_BOUNDARY::Gdiplus::Color() const noexcept {
// 	return color_.bytes[3] << 24 | color_.bytes[2] << 16 | color_.bytes[1] << 8 | color_.bytes[0] ;
// }

// std::ostream& operator<<(std::ostream& os, const Color& c) noexcept  {
// 	return os << "{" << static_cast<int>(c[3]) << ", " << static_cast<int>(c[2]) << ", " << static_cast<int>(c[1]) << ", " << static_cast<int>(c[0])  << "{\n" ;
// }