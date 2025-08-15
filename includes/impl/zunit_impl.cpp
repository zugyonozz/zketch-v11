#include "../zunit.h"

PT::PT() noexcept : Base() {}

PT::PT(int v) noexcept : Base(v, v) {}

PT::PT(int x, int y) noexcept : Base(x, y) {}

PT::PT(const PT& o) noexcept : Base(o) {}

PT::PT(const PTF& o) noexcept : Base(static_cast<PT>(o)) {}

PT::PT(const SZ& o) noexcept : Base(o) {}

PT::PT(const SZF& o) noexcept : Base(static_cast<PT>(o)) {}

PT::PT(const tagPOINT& o) noexcept : Base(static_cast<int>(o.x), static_cast<int>(o.y)) {}

PT::PT(const POINTL& o) noexcept : Base(static_cast<int>(o.x), static_cast<int>(o.y)) {}

PT::PT(const tagSIZE& o) noexcept : Base(static_cast<int>(o.cx), static_cast<int>(o.cy)) {}

PT::PT(const tagPOINTS& o) noexcept : Base(static_cast<short>(o.x), static_cast<short>(o.y)) {}

constexpr PT& PT::operator=(int v) noexcept { 
	X = Y = v ;
	return *this ; 
}

constexpr PT& PT::operator=(const PT& o) noexcept {
	X = o.X ;
	Y = o.Y ;
	return *this ;
}

constexpr PT& PT::operator=(const PTF& o) noexcept {
	X = static_cast<float>(o.X) ;
	Y = static_cast<float>(o.Y) ;
	return *this ;
}

constexpr PT& PT::operator=(const SZ& o) noexcept {
	X = o.Width ;
	Y = o.Height ;
	return *this ;
}

constexpr PT& PT::operator=(const SZF& o) noexcept {
	X = static_cast<float>(o.Width) ;
	Y = static_cast<float>(o.Height) ;
	return *this ;
}

PT PT::operator+() const noexcept { 
	return *this ; 
}

PT PT::operator-() const noexcept { 
	return {-X, -Y} ; 
}

constexpr PT& PT::operator+=(const PT& o) noexcept { 
	X += o.X ; 
	Y += o.Y ; 
	return *this ; 
}

constexpr PT& PT::operator-=(const PT& o) noexcept { 
	X -= o.X ; 
	Y -= o.Y ; 
	return *this ; 
}

constexpr PT& PT::operator*=(const PT& o) noexcept { 
	X *= o.X ; 
	Y *= o.Y ; 
	return *this ; 
}

constexpr PT& PT::operator/=(const PT& o) noexcept { 
	X /= o.X ; 
	Y /= o.Y ; 
	return *this ; 
}

constexpr PT& PT::operator+=(int v) noexcept { 
	X += v ; 
	Y += v ; 
	return *this ; 
}

constexpr PT& PT::operator-=(int v) noexcept { 
	X -= v ; 
	Y -= v ; 
	return *this ; 
}

constexpr PT& PT::operator*=(int v) noexcept { 
	X *= v ; 
	Y *= v ; 
	return *this ; 
}

constexpr PT& PT::operator/=(int v) noexcept { 
	X /= v ; 
	Y /= v ; 
	return *this ; 
}

bool PT::operator==(const PT& o) const noexcept { 
	return Equals(o) ; 
}

bool PT::operator!=(const PT& o) const noexcept { 
	return !Equals(o) ; 
}

PT::operator tagPOINT() const noexcept { 
	return {
		static_cast<long>(X), 
		static_cast<long>(Y)
	} ; 
}

PT::operator _POINTL() const noexcept { 
	return {
		static_cast<long>(X), 
		static_cast<long>(Y)
	} ; 
}

PT::operator tagSIZE() const noexcept { 
	return {
		static_cast<long>(X), 
		static_cast<long>(Y)
	} ; 
}

PT::operator tagPOINTS() const noexcept { 
	return {
		static_cast<short>(X), 
		static_cast<short>(Y)
	} ; 
}

PT::operator SZ() const noexcept {
	return {
		static_cast<int>(X),
		static_cast<int>(Y)
	} ;
}

PT::operator PTF() const noexcept {
	return {
		static_cast<float>(X),
		static_cast<float>(Y)
	} ;
}

PT::operator SZF() const noexcept {
	return {
		static_cast<float>(X),
		static_cast<float>(Y)
	} ;
}

PT operator+(const PT& a, const PT& b) noexcept  { 
	return {
		a.X + b.X, 
		a.Y + b.Y
	} ; 
}

PT operator-(const PT& a, const PT& b) noexcept  { 
	return {
		a.X - b.X, 
		a.Y - b.Y
	} ; 
}

PT operator*(const PT& a, const PT& b) noexcept  { 
	return {
		a.X * b.X, 
		a.Y * b.Y
	} ; 
}

PT operator/(const PT& a, const PT& b) noexcept  { 
	return {
		a.X / b.X, 
		a.Y / b.Y
	} ; 
}

PT operator+(const PT& a, int v) noexcept { 
	return {
		a.X + v, 
		a.Y + v
	} ; 
}

PT operator-(const PT& a, int v) noexcept { 
	return {
		a.X - v, 
		a.Y - v
	} ; 
}

PT operator*(const PT& a, int v) noexcept { 
	return {
		a.X * v, 
		a.Y * v
	} ; 
}

PT operator/(const PT& a, int v) noexcept { 
	return {
		a.X / v, 
		a.Y / v
	} ; 
}

PT operator+(int v, const PT& a) noexcept { 
	return a + v ; 
}

PT operator*(int v, const PT& a) noexcept { 
	return a * v ; 
}

PT operator-(int v, const PT& a) noexcept { 
	return {
		v - a.X, 
		v - a.Y
	} ; 
}

PT operator/(int v, const PT& a) noexcept { 
	return {
		v / a.X, 
		v / a.Y
	} ; 
}

#ifdef ZUNIT_DEBUG

std::ostream& operator<<(std::ostream& os, const PT& pt) const noexcept {
	return os << "{" << pt.X << ", " << pt.Y << "}" ;
}

#endif

SZ::SZ() noexcept : Base() {}

SZ::SZ(int v) noexcept : Base(v, v) {}

SZ::SZ(int x, int y) noexcept : Base(x, y) {}

SZ::SZ(const SZ& o) noexcept : Base(o) {}

SZ::SZ(const SZF& o) noexcept : Base(static_cast<SZ>(o)) {}

SZ::SZ(const PT& o) noexcept : Base(o) {}

SZ::SZ(const PTF& o) noexcept : Base(static_cast<SZ>(o)) {}

SZ::SZ(const tagPOINT& o) noexcept : Base(static_cast<int>(o.x), static_cast<int>(o.y)) {}

SZ::SZ(const POINTL& o) noexcept : Base(static_cast<int>(o.x), static_cast<int>(o.y)) {}

SZ::SZ(const tagSIZE& o) noexcept : Base(static_cast<int>(o.cx), static_cast<int>(o.cy)) {}

SZ::SZ(const tagPOINTS& o) noexcept : Base(static_cast<short>(o.x), static_cast<short>(o.y)) {}

constexpr SZ& SZ::operator=(int v) noexcept { 
	Width = Height = v ;
	return *this ; 
}

constexpr SZ& SZ::operator=(const SZ& o) noexcept {
	Width = o.Width ;
	Height = o.Height ;
	return *this ;
}

constexpr SZ& SZ::operator=(const SZF& o) noexcept {
	Width = static_cast<int>(o.Width) ;
	Height = static_cast<int>(o.Height) ;
	return *this ;
}

constexpr SZ& SZ::operator=(const PT& o) noexcept {
	Width = o.X ;
	Height = o.Y ;
	return *this ;
}

constexpr SZ& SZ::operator=(const PTF& o) noexcept {
	Width = static_cast<int>(o.X) ;
	Height = static_cast<int>(o.Y) ;
	return *this ;
}

SZ SZ::operator+() const noexcept { 
	return *this ; 
}

SZ SZ::operator-() const noexcept { 
	return {-Height, -Width} ; 
}

constexpr SZ& SZ::operator+=(const SZ& o) noexcept { 
	Width += o.Width ; 
	Height += o.Height ; 
	return *this ; 
}

constexpr SZ& SZ::operator-=(const SZ& o) noexcept { 
	Width -= o.Width ; 
	Height -= o.Height ; 
	return *this ; 
}

constexpr SZ& SZ::operator*=(const SZ& o) noexcept { 
	Width *= o.Width ; 
	Height *= o.Height ; 
	return *this ; 
}

constexpr SZ& SZ::operator/=(const SZ& o) noexcept { 
	Width /= o.Width ; 
	Height /= o.Height ; 
	return *this ; 
}

constexpr SZ& SZ::operator+=(int v) noexcept { 
	Width += v ; 
	Height += v ; 
	return *this ; 
}

constexpr SZ& SZ::operator-=(int v) noexcept { 
	Width -= v ; 
	Height -= v ; 
	return *this ; 
}

constexpr SZ& SZ::operator*=(int v) noexcept { 
	Width *= v ; 
	Height *= v ; 
	return *this ; 
}

constexpr SZ& SZ::operator/=(int v) noexcept { 
	Width /= v ; 
	Height /= v ; 
	return *this ; 
}

bool SZ::operator==(const SZ& o) const noexcept { 
	return Equals(o) ; 
}

bool SZ::operator!=(const SZ& o) const noexcept { 
	return !Equals(o) ; 
}

SZ::operator tagPOINT() const noexcept { 
	return {
		static_cast<long>(Width), 
		static_cast<long>(Height)
	} ; 
}

SZ::operator _POINTL() const noexcept { 
	return {
		static_cast<long>(Width), 
		static_cast<long>(Height)
	} ; 
}

SZ::operator tagSIZE() const noexcept { 
	return {
		static_cast<long>(Width), 
		static_cast<long>(Height)
	} ; 
}

SZ::operator tagPOINTS() const noexcept { 
	return {
		static_cast<short>(Width), 
		static_cast<short>(Height)
	} ; 
}

SZ::operator PT() const noexcept {
	return {
		static_cast<int>(Width),
		static_cast<int>(Height)
	} ;
}

SZ::operator PTF() const noexcept {
	return {
		static_cast<float>(Width),
		static_cast<float>(Height)
	} ;
}

SZ::operator SZF() const noexcept {
	return {
		static_cast<float>(Width),
		static_cast<float>(Height)
	} ;
}

SZ operator+(const SZ& a, const SZ& b) noexcept  { 
	return {
		a.Width + b.Width, 
		a.Height + b.Height
	} ; 
}

SZ operator-(const SZ& a, const SZ& b) noexcept  { 
	return {
		a.Width - b.Width, 
		a.Height - b.Height
	} ; 
}

SZ operator*(const SZ& a, const SZ& b) noexcept  { 
	return {
		a.Width * b.Width, 
		a.Height * b.Height
	} ; 
}

SZ operator/(const SZ& a, const SZ& b) noexcept  { 
	return {
		a.Width / b.Width, 
		a.Height / b.Height
	} ; 
}

SZ operator+(const SZ& a, int v) noexcept { 
	return {
		a.Width + v, 
		a.Height + v
	} ; 
}

SZ operator-(const SZ& a, int v) noexcept { 
	return {
		a.Width - v, 
		a.Height - v
	} ; 
}

SZ operator*(const SZ& a, int v) noexcept { 
	return {
		a.Width * v, 
		a.Height * v
	} ; 
}

SZ operator/(const SZ& a, int v) noexcept { 
	return {
		a.Width / v, 
		a.Height / v
	} ; 
}

SZ operator+(int v, const SZ& a) noexcept { 
	return a + v ; 
}

SZ operator*(int v, const SZ& a) noexcept { 
	return a * v ; 
}

SZ operator-(int v, const SZ& a) noexcept { 
	return {
		v - a.Width, 
		v - a.Height
	} ; 
}

SZ operator/(int v, const SZ& a) noexcept { 
	return {
		v / a.Width, 
		v / a.Height
	} ; 
}

#ifdef ZUNIT_DEBUG

std::ostream& operator<<(std::ostream& os, const SZ& sz) const noexcept {
	return os << "{" << sz.Height << ", " << sz.Width << "}" ;
}

#endif

PTF::PTF() noexcept : Base() {}

PTF::PTF(float v) noexcept : Base(v, v) {}

PTF::PTF(float x, float y) noexcept : Base(x, y) {}

PTF::PTF(const PTF& o) noexcept : Base(o) {}

PTF::PTF(const PT& o) noexcept : Base(static_cast<PTF>(o)) {}

PTF::PTF(const SZ& o) noexcept : Base(static_cast<PTF>(o)) {}

PTF::PTF(const SZF& o) noexcept : Base(o) {}

PTF::PTF(const tagPOINT& o) noexcept : Base(static_cast<float>(o.x), static_cast<float>(o.y)) {}

PTF::PTF(const POINTL& o) noexcept : Base(static_cast<float>(o.x), static_cast<float>(o.y)) {}

PTF::PTF(const tagSIZE& o) noexcept : Base(static_cast<float>(o.cx), static_cast<float>(o.cy)) {}

PTF::PTF(const tagPOINTS& o) noexcept : Base(static_cast<float>(o.x), static_cast<float>(o.y)) {}

constexpr PTF& PTF::operator=(float v) noexcept { 
	X = Y = v ;
	return *this ; 
}

constexpr PTF& PTF::operator=(const PTF& o) noexcept {
	X = o.X ;
	Y = o.Y ;
	return *this ;
}

constexpr PTF& PTF::operator=(const PT& o) noexcept {
	X = static_cast<int>(o.X) ;
	Y = static_cast<int>(o.Y) ;
	return *this ;
}

constexpr PTF& PTF::operator=(const SZ& o) noexcept {
	X = static_cast<int>(o.Width) ;
	Y = static_cast<int>(o.Height) ;
	return *this ;
}

constexpr PTF& PTF::operator=(const SZF& o) noexcept {
	X = o.Width ;
	Y = o.Height ;
	return *this ;
}

PTF PTF::operator+() const noexcept { 
	return *this ; 
}

PTF PTF::operator-() const noexcept { 
	return {-X, -Y} ; 
}

constexpr PTF& PTF::operator+=(const PTF& o) noexcept { 
	X += o.X ; 
	Y += o.Y ; 
	return *this ; 
}

constexpr PTF& PTF::operator-=(const PTF& o) noexcept { 
	X -= o.X ; 
	Y -= o.Y ; 
	return *this ; 
}

constexpr PTF& PTF::operator*=(const PTF& o) noexcept { 
	X *= o.X ; 
	Y *= o.Y ; 
	return *this ; 
}

constexpr PTF& PTF::operator/=(const PTF& o) noexcept { 
	X /= o.X ; 
	Y /= o.Y ; 
	return *this ; 
}

constexpr PTF& PTF::operator+=(float v) noexcept { 
	X += v ; 
	Y += v ; 
	return *this ; 
}

constexpr PTF& PTF::operator-=(float v) noexcept { 
	X -= v ; 
	Y -= v ; 
	return *this ; 
}

constexpr PTF& PTF::operator*=(float v) noexcept { 
	X *= v ; 
	Y *= v ; 
	return *this ; 
}

constexpr PTF& PTF::operator/=(float v) noexcept { 
	X /= v ; 
	Y /= v ; 
	return *this ; 
}

bool PTF::operator==(const PTF& o) const noexcept { 
	return Equals(o) ; 
}

bool PTF::operator!=(const PTF& o) const noexcept { 
	return !Equals(o) ; 
}

PTF::operator tagPOINT() const noexcept { 
	return {
		static_cast<long>(X), 
		static_cast<long>(Y)
	} ; 
}

PTF::operator _POINTL() const noexcept { 
	return {
		static_cast<long>(X), 
		static_cast<long>(Y)
	} ; 
}

PTF::operator tagSIZE() const noexcept { 
	return {
		static_cast<long>(X), 
		static_cast<long>(Y)
	} ; 
}

PTF::operator tagPOINTS() const noexcept { 
	return {
		static_cast<short>(X), 
		static_cast<short>(Y)
	} ; 
}

PTF::operator PT() const noexcept {
	return {
		static_cast<int>(X),
		static_cast<int>(Y)
	} ;
}

PTF::operator SZ() const noexcept {
	return {
		static_cast<int>(X),
		static_cast<int>(Y)
	} ;
}

PTF::operator SZF() const noexcept {
	return {
		static_cast<float>(X),
		static_cast<float>(Y)
	} ;
}

PTF operator+(const PTF& a, const PTF& b) noexcept  { 
	return {
		a.X + b.X, 
		a.Y + b.Y
	} ; 
}

PTF operator-(const PTF& a, const PTF& b) noexcept  { 
	return {
		a.X - b.X, 
		a.Y - b.Y
	} ; 
}

PTF operator*(const PTF& a, const PTF& b) noexcept  { 
	return {
		a.X * b.X, 
		a.Y * b.Y
	} ; 
}

PTF operator/(const PTF& a, const PTF& b) noexcept  { 
	return {
		a.X / b.X, 
		a.Y / b.Y
	} ; 
}

PTF operator+(const PTF& a, float v) noexcept { 
	return {
		a.X + v, 
		a.Y + v
	} ; 
}

PTF operator-(const PTF& a, float v) noexcept { 
	return {
		a.X - v, 
		a.Y - v
	} ; 
}

PTF operator*(const PTF& a, float v) noexcept { 
	return {
		a.X * v, 
		a.Y * v
	} ; 
}

PTF operator/(const PTF& a, float v) noexcept { 
	return {
		a.X / v, 
		a.Y / v
	} ; 
}

PTF operator+(float v, const PTF& a) noexcept { 
	return a + v ; 
}

PTF operator*(float v, const PTF& a) noexcept { 
	return a * v ; 
}

PTF operator-(float v, const PTF& a) noexcept { 
	return {
		v - a.X, 
		v - a.Y
	} ; 
}

PTF operator/(float v, const PTF& a) noexcept { 
	return {
		v / a.X, 
		v / a.Y
	} ; 
}

#ifdef ZUNIT_DEBUG

std::ostream& operator<<(std::ostream& os, const PTF& ptf) const noexcept {
	return os << "{" << ptf.X << ", " << ptf.Y << "}" ;
}

#endif

SZF::SZF() noexcept : Base() {}

SZF::SZF(float v) noexcept : Base(v, v) {}

SZF::SZF(float x, float y) noexcept : Base(x, y) {}

SZF::SZF(const SZF& o) noexcept : Base(o) {}

SZF::SZF(const SZ& o) noexcept : Base(o) {}

SZF::SZF(const PT& o) noexcept : Base(o) {}

SZF::SZF(const PTF& o) noexcept : Base(o) {}

SZF::SZF(const tagPOINT& o) noexcept : Base(static_cast<float>(o.x), static_cast<float>(o.y)) {}

SZF::SZF(const POINTL& o) noexcept : Base(static_cast<float>(o.x), static_cast<float>(o.y)) {}

SZF::SZF(const tagSIZE& o) noexcept : Base(static_cast<float>(o.cx), static_cast<float>(o.cy)) {}

SZF::SZF(const tagPOINTS& o) noexcept : Base(static_cast<short>(o.x), static_cast<short>(o.y)) {}

constexpr SZF& SZF::operator=(int v) noexcept { 
	Width = Height = v ;
	return *this ; 
}

constexpr SZF& SZF::operator=(const SZF& o) noexcept {
	Width = o.Width ;
	Height = o.Height ;
	return *this ;
}
constexpr SZF& SZF::operator=(const SZ& o) noexcept {
	Width = static_cast<int>(o.Width) ;
	Height = static_cast<int>(o.Height) ;
	return *this ;
}
constexpr SZF& SZF::operator=(const PT& o) noexcept {
	Width = static_cast<int>(o.X) ;
	Height = static_cast<int>(o.Y) ;
	return *this ;
}
constexpr SZF& SZF::operator=(const PTF& o) noexcept {
	Width = o.X ;
	Height = o.Y ;
	return *this ;
}

SZF SZF::operator+() const noexcept { 
	return *this ; 
}

SZF SZF::operator-() const noexcept { 
	return {-Height, -Width} ; 
}

constexpr SZF& SZF::operator+=(const SZF& o) noexcept { 
	Width += o.Width ; 
	Height += o.Height ; 
	return *this ; 
}

constexpr SZF& SZF::operator-=(const SZF& o) noexcept { 
	Width -= o.Width ; 
	Height -= o.Height ; 
	return *this ; 
}

constexpr SZF& SZF::operator*=(const SZF& o) noexcept { 
	Width *= o.Width ; 
	Height *= o.Height ; 
	return *this ; 
}

constexpr SZF& SZF::operator/=(const SZF& o) noexcept { 
	Width /= o.Width ; 
	Height /= o.Height ; 
	return *this ; 
}

constexpr SZF& SZF::operator+=(int v) noexcept { 
	Width += v ; 
	Height += v ; 
	return *this ; 
}

constexpr SZF& SZF::operator-=(int v) noexcept { 
	Width -= v ; 
	Height -= v ; 
	return *this ; 
}

constexpr SZF& SZF::operator*=(int v) noexcept { 
	Width *= v ; 
	Height *= v ; 
	return *this ; 
}

constexpr SZF& SZF::operator/=(int v) noexcept { 
	Width /= v ; 
	Height /= v ; 
	return *this ; 
}

bool SZF::operator==(const SZF& o) const noexcept { 
	return Equals(o) ; 
}

bool SZF::operator!=(const SZF& o) const noexcept { 
	return !Equals(o) ; 
}

SZF::operator tagPOINT() const noexcept { 
	return {
		static_cast<long>(Width), 
		static_cast<long>(Height)
	} ; 
}

SZF::operator _POINTL() const noexcept { 
	return {
		static_cast<long>(Width), 
		static_cast<long>(Height)
	} ; 
}

SZF::operator tagSIZE() const noexcept { 
	return {
		static_cast<long>(Width), 
		static_cast<long>(Height)
	} ; 
}

SZF::operator tagPOINTS() const noexcept { 
	return {
		static_cast<short>(Width), 
		static_cast<short>(Height)
	} ; 
}

SZF::operator PT() const noexcept {
	return {
		static_cast<int>(Width),
		static_cast<int>(Height)
	} ;
}

SZF::operator PTF() const noexcept {
	return {
		static_cast<float>(Width),
		static_cast<float>(Height)
	} ;
}

SZF::operator SZ() const noexcept {
	return {
		static_cast<int>(Width),
		static_cast<int>(Height)
	} ;
}

SZF operator+(const SZF& a, const SZF& b) noexcept  { 
	return {
		a.Width + b.Width, 
		a.Height + b.Height
	} ; 
}

SZF operator-(const SZF& a, const SZF& b) noexcept  { 
	return {
		a.Width - b.Width, 
		a.Height - b.Height
	} ; 
}

SZF operator*(const SZF& a, const SZF& b) noexcept  { 
	return {
		a.Width * b.Width, 
		a.Height * b.Height
	} ; 
}

SZF operator/(const SZF& a, const SZF& b) noexcept  { 
	return {
		a.Width / b.Width, 
		a.Height / b.Height
	} ; 
}

SZF operator+(const SZF& a, float v) noexcept { 
	return {
		a.Width + v, 
		a.Height + v
	} ; 
}

SZF operator-(const SZF& a, float v) noexcept { 
	return {
		a.Width - v, 
		a.Height - v
	} ; 
}

SZF operator*(const SZF& a, float v) noexcept { 
	return {
		a.Width * v, 
		a.Height * v
	} ; 
}

SZF operator/(const SZF& a, float v) noexcept { 
	return {
		a.Width / v, 
		a.Height / v
	} ; 
}

SZF operator+(float v, const SZF& a) noexcept { 
	return a + v ; 
}

SZF operator*(float v, const SZF& a) noexcept { 
	return a * v ; 
}

SZF operator-(float v, const SZF& a) noexcept { 
	return {
		v - a.Width, 
		v - a.Height
	} ; 
}

SZF operator/(float v, const SZF& a) noexcept { 
	return {
		v / a.Width, 
		v / a.Height
	} ; 
}

#ifdef ZUNIT_DEBUG

std::ostream& operator<<(std::ostream& os, const SZ& sz) const noexcept {
	return os << "{" << sz.Height << ", " << sz.Width << "}" ;
}

#endif

Quad::Quad() noexcept : Base() {}

Quad::Quad(int v) noexcept : Base(v, v, v, v) {}

Quad::Quad(int x, int y, int w, int h) noexcept : Base(x, y, w, h) {}

Quad::Quad(const Quad& o) noexcept : Base(o) {}

Quad::Quad(const QuadF& o) noexcept : Base(static_cast<Quad>(o)) {}

Quad::Quad(const tagRECT& o) noexcept : Base(o.left, o.top, o.right - o.left, o.bottom - o.top) {}

Quad::Quad(const _RECTL& o) noexcept : Base(o.left, o.top, o.right - o.left, o.bottom - o.top) {}

Quad& Quad::operator=(int v) noexcept { 
	X = Y = Width = Height = v ; 
	return *this ; 
}

Quad& Quad::operator=(const Quad& o) noexcept { 
	X = o.X ; 
	Y = o.Y ; 
	Width = o.Width ; 
	Height = o.Height ; 
	return *this ; 
}

Quad& Quad::operator=(const QuadF& o) noexcept { 
	X = static_cast<int>(o.X) ; 
	Y = static_cast<int>(o.Y) ; 
	Width = static_cast<int>(o.Width) ; 
	Height = static_cast<int>(o.Height) ; 
	return *this ; 
}

Quad Quad::operator+() const noexcept { 
	return *this ; 
}

Quad Quad::operator-() const noexcept { 
	return {-X, -Y, Width, Height} ; 
}

constexpr Quad& Quad::operator+=(const Quad& o) noexcept { 
	X += o.X ; 
	Y += o.Y ; 
	Width += o.Width ; 
	Height += o.Height ; 
	return *this ; 
}

constexpr Quad& Quad::operator-=(const Quad& o) noexcept { 
	X -= o.X ; 
	Y -= o.Y ; 
	Width -= o.Width ; 
	Height -= o.Height ; 
	return *this ; 
}

constexpr Quad& Quad::operator*=(const Quad& o) noexcept { 
	X *= o.X ; 
	Y *= o.Y ; 
	Width *= o.Width ; 
	Height *= o.Height ; 
	return *this ; 
}

constexpr Quad& Quad::operator/=(const Quad& o) noexcept { 
	X /= o.X ; 
	Y /= o.Y ; 
	Width /= o.Width ; 
	Height /= o.Height ; 
	return *this ; 
}

constexpr Quad& Quad::operator+=(int v) noexcept { 
	X += v ; 
	Y += v ; 
	Width += v ; 
	Height += v ; 
	return *this ; 
}

constexpr Quad& Quad::operator-=(int v) noexcept { 
	X -= v ; 
	Y -= v ; 
	Width -= v ; 
	Height -= v ; 
	return *this ; 
}

constexpr Quad& Quad::operator*=(int v) noexcept { 
	X *= v ; 
	Y *= v ; 
	Width *= v ; 
	Height *= v ; 
	return *this ; 
}

constexpr Quad& Quad::operator/=(int v) noexcept { 
	X /= v ; 
	Y /= v ; 
	Width /= v ; 
	Height /= v ; 
	return *this ; 
}

bool Quad::operator==(const Quad& o) const noexcept { 
	return Equals(o) ; 
}

bool Quad::operator!=(const Quad& o) const noexcept { 
	return !Equals(o) ; 
}

Quad::operator tagRECT() const noexcept { 
	return {
		static_cast<long>(X), 
		static_cast<long>(Y), 
		static_cast<long>(Width) + static_cast<long>(X), 
		static_cast<long>(Height) +  static_cast<long>(Y) 
	} ; 
}

Quad::operator _RECTL() const noexcept { 
	return {
		static_cast<long>(X), 
		static_cast<long>(Y), 
		static_cast<long>(Width) + static_cast<long>(X), 
		static_cast<long>(Height) +  static_cast<long>(Y) 
	} ; 
}

Quad::operator QuadF() const noexcept {
	return {
		static_cast<float>(X),
		static_cast<float>(Y),
		static_cast<float>(Width),
		static_cast<float>(Height)
	} ;
}

PT Quad::getPos() const noexcept { 
	return {X, Y} ; 
}

PT Quad::getPos() noexcept { 
	return {X, Y} ; 
}

SZ Quad::getSize() const noexcept { 
	return {Width, Height} ; 
}

SZ Quad::getSize() noexcept { 
	return {Width, Height} ; 
}

Quad& Quad::setPos(int x, int y) noexcept { 
	X = x ; 
	Y = y ; 
	return *this ;
}

Quad& Quad::setPos(const PT& pos) noexcept { 
	X = pos.X ; 
	Y = pos.Y ; 
	return *this ;
}

Quad& Quad::setPos(const PTF& pos) noexcept { 
	X = static_cast<int>(pos.X) ; 
	Y = static_cast<int>(pos.Y) ; 
	return *this ;
}

Quad& Quad::setSize(int w, int h) noexcept { 
	Width = w ; 
	Height = h ; 
	return *this ;
}

Quad& Quad::setSize(const SZ& size) noexcept { 
	Width = size.Width ; 
	Height = size.Height ; 
	return *this ;
}

Quad& Quad::setSize(const SZF& size) noexcept { 
	Width = static_cast<int>(size.Width) ; 
	Height = static_cast<int>(size.Height) ; 
	return *this ;
}

Quad operator+(const Quad& a, const Quad& b) noexcept { 
	return {
		a.X + b.X, 
		a.Y + b.Y, 
		a.Width + b.Width, 
		a.Height + b.Height
	} ; 
}

Quad operator-(const Quad& a, const Quad& b) noexcept { 
	return {
		a.X - b.X, 
		a.Y - b.Y, 
		a.Width - b.Width, 
		a.Height - b.Height
	} ; 
}

Quad operator*(const Quad& a, const Quad& b) noexcept { 
	return {
		a.X * b.X, 
		a.Y * b.Y, 
		a.Width * b.Width, 
		a.Height * b.Height
	} ; 
}

Quad operator/(const Quad& a, const Quad& b) noexcept { 
	return {
		a.X / b.X, 
		a.Y / b.Y, 
		a.Width / b.Width, 
		a.Height / b.Height
	} ; 
}

Quad operator+(const Quad& a, int v) noexcept { 
	return {
		a.X + v, 
		a.Y + v, 
		a.Width + v, 
		a.Height + v
	} ; 
}

Quad operator-(const Quad& a, int v) noexcept { 
	return {
		a.X - v, 
		a.Y - v, 
		a.Width - v, 
		a.Height - v
	} ; 
}

Quad operator*(const Quad& a, int v) noexcept { 
	return {
		a.X * v, 
		a.Y * v, 
		a.Width * v, 
		a.Height * v
	} ; 
}

Quad operator/(const Quad& a, int v) noexcept { 
	return {
		a.X / v, 
		a.Y / v, 
		a.Width / v, 
		a.Height / v
	} ; 
}

Quad operator+(int v, const Quad& a) noexcept { 
	return a + v ; 
}

Quad operator-(int v, const Quad& a) noexcept { 
	return {
		v - a.X, 
		v - a.Y, 
		v - a.Width, 
		v - a.Height
	} ; 
}

Quad operator*(int v, const Quad& a) noexcept { 
	return a * v ; 
}

Quad operator/(int v, const Quad& a) noexcept { 
	return {
		v / a.X, 
		v / a.Y, 
		v / a.Width, 
		v / a.Height
	} ; 
}

#ifdef ZUNIT_DEBUG

template <typename T> 
std::ostream& operator<<(std::ostream& os, const Quad& q) const noexcept {
	return os << "{" << q.X << ", " << q.Y << ", " << q.Width << ", " << q.Height << "}" ;
}

#endif

QuadF::QuadF() noexcept : Base() {}

QuadF::QuadF(float v) noexcept : Base(v, v, v, v) {}

QuadF::QuadF(float x, float y, float w, float h) noexcept : Base(x, y, w, h) {}

QuadF::QuadF(const PTF& pos, const SZF& size) noexcept : Base(pos, size) {}

QuadF::QuadF(const QuadF& o) noexcept : Base(o) {}

QuadF::QuadF(const Quad& o) noexcept : Base(o) {}

QuadF::QuadF(const tagRECT& o) noexcept : Base(o.left, o.top, o.right - o.left, o.bottom - o.top) {}

QuadF::QuadF(const _RECTL& o) noexcept : Base(o.left, o.top, o.right - o.left, o.bottom - o.top) {}

QuadF& QuadF::operator=(float v) noexcept { 
	X = Y = Width = Height = v ; 
	return *this ; 
}

QuadF& QuadF::operator=(const QuadF& o) noexcept { 
	X = o.X ; 
	Y = o.Y ; 
	Width = o.Width ; 
	Height = o.Height ; 
	return *this ; 
}

QuadF& QuadF::operator=(const Quad& o) noexcept { 
	X = static_cast<float>(o.X) ; 
	Y = static_cast<float>(o.Y) ; 
	Width = static_cast<float>(o.Width) ; 
	Height = static_cast<float>(o.Height) ; 
	return *this ; 
}

QuadF QuadF::operator+() const noexcept { 
	return *this ; 
}

QuadF QuadF::operator-() const noexcept { 
	return {-X, -Y, Width, Height} ; 
}

constexpr QuadF& QuadF::operator+=(const QuadF& o) noexcept { 
	X += o.X ; 
	Y += o.Y ; 
	Width += o.Width ; 
	Height += o.Height ; 
	return *this ; 
}

constexpr QuadF& QuadF::operator-=(const QuadF& o) noexcept { 
	X -= o.X ; 
	Y -= o.Y ; 
	Width -= o.Width ; 
	Height -= o.Height ; 
	return *this ; 
}

constexpr QuadF& QuadF::operator*=(const QuadF& o) noexcept { 
	X *= o.X ; 
	Y *= o.Y ; 
	Width *= o.Width ; 
	Height *= o.Height ; 
	return *this ; 
}

constexpr QuadF& QuadF::operator/=(const QuadF& o) noexcept { 
	X /= o.X ; 
	Y /= o.Y ; 
	Width /= o.Width ; 
	Height /= o.Height ; 
	return *this ; 
}

constexpr QuadF& QuadF::operator+=(float v) noexcept { 
	X += v ; 
	Y += v ; 
	Width += v ; 
	Height += v ; 
	return *this ; 
}

constexpr QuadF& QuadF::operator-=(float v) noexcept { 
	X -= v ; 
	Y -= v ; 
	Width -= v ; 
	Height -= v ; 
	return *this ; 
}

constexpr QuadF& QuadF::operator*=(float v) noexcept { 
	X *= v ; 
	Y *= v ; 
	Width *= v ; 
	Height *= v ; 
	return *this ; 
}

constexpr QuadF& QuadF::operator/=(float v) noexcept { 
	X /= v ; 
	Y /= v ; 
	Width /= v ; 
	Height /= v ; 
	return *this ; 
}

bool QuadF::operator==(const QuadF& o) const noexcept { 
	return Equals(o) ; 
}

bool QuadF::operator!=(const QuadF& o) const noexcept { 
	return !Equals(o) ; 
}

QuadF::operator tagRECT() const noexcept { 
	return {
		static_cast<long>(X), 
		static_cast<long>(Y), 
		static_cast<long>(Width) + static_cast<long>(X), 
		static_cast<long>(Height) +  static_cast<long>(Y) 
	} ; 
}

QuadF::operator _RECTL() const noexcept { 
	return {
		static_cast<long>(X), 
		static_cast<long>(Y), 
		static_cast<long>(Width) + static_cast<long>(X), 
		static_cast<long>(Height) +  static_cast<long>(Y) 
	} ; 
}

QuadF::operator Quad() const noexcept { 
	return {
		static_cast<int>(X), 
		static_cast<int>(Y), 
		static_cast<int>(Width),
		static_cast<int>(Height)
	} ; 
}

PTF QuadF::getPos() const noexcept { 
	return {X, Y} ; 
}

PTF QuadF::getPos() noexcept { 
	return {X, Y} ; 
}

SZF QuadF::getSize() const noexcept { 
	return {Width, Height} ; 
}

SZF QuadF::getSize() noexcept { 
	return {Width, Height} ; 
}

constexpr QuadF& QuadF::setPos(float x, float y) noexcept { 
	X = x ; 
	Y = y ; 
	return *this ;
}

constexpr QuadF& QuadF::setPos(const PT& pos) noexcept { 
	X = static_cast<int>(pos.X) ; 
	Y = static_cast<int>(pos.Y) ; 
	return *this ;
}

constexpr QuadF& QuadF::setPos(const PTF& pos) noexcept { 
	X = pos.X ; 
	Y = pos.Y ; 
	return *this ;
}

constexpr QuadF& QuadF::setSize(float w, float h) noexcept { 
	Width = w ; 
	Height = h ; 
	return *this ;
}

constexpr QuadF& QuadF::setSize(const SZ& size) noexcept { 
	Width = static_cast<int>(size.Width) ; 
	Height = static_cast<int>(size.Height) ; 
	return *this ;
}

constexpr QuadF& QuadF::setSize(const SZF& size) noexcept { 
	Width = size.Width ; 
	Height = size.Height ; 
	return *this ;
}

QuadF operator+(const QuadF& a, const QuadF& b) noexcept { 
	return {
		a.X + b.X, 
		a.Y + b.Y, 
		a.Width + b.Width, 
		a.Height + b.Height
	} ; 
}

QuadF operator-(const QuadF& a, const QuadF& b) noexcept { 
	return {
		a.X - b.X, 
		a.Y - b.Y, 
		a.Width - b.Width, 
		a.Height - b.Height
	} ; 
}

QuadF operator*(const QuadF& a, const QuadF& b) noexcept { 
	return {
		a.X * b.X, 
		a.Y * b.Y, 
		a.Width * b.Width, 
		a.Height * b.Height
	} ; 
}

QuadF operator/(const QuadF& a, const QuadF& b) noexcept { 
	return {
		a.X / b.X, 
		a.Y / b.Y, 
		a.Width / b.Width, 
		a.Height / b.Height
	} ; 
}

QuadF operator+(const QuadF& a, float v) noexcept { 
	return {
		a.X + v, 
		a.Y + v, 
		a.Width + v, 
		a.Height + v
	} ; 
}

QuadF operator-(const QuadF& a, float v) noexcept { 
	return {
		a.X - v, 
		a.Y - v, 
		a.Width - v, 
		a.Height - v
	} ; 
}

QuadF operator*(const QuadF& a, float v) noexcept { 
	return {
		a.X * v, 
		a.Y * v, 
		a.Width * v, 
		a.Height * v
	} ; 
}

QuadF operator/(const QuadF& a, float v) noexcept { 
	return {
		a.X / v, 
		a.Y / v, 
		a.Width / v, 
		a.Height / v
	} ; 
}

QuadF operator+(float v, const QuadF& a) noexcept { 
	return a + v ; 
}

QuadF operator-(float v, const QuadF& a) noexcept { 
	return {
		v - a.X, 
		v - a.Y, 
		v - a.Width, 
		v - a.Height
	} ; 
}

QuadF operator*(float v, const QuadF& a) noexcept { 
	return a * v ; 
}

QuadF operator/(float v, const QuadF& a) noexcept { 
	return {
		v / a.X, 
		v / a.Y, 
		v / a.Width, 
		v / a.Height
	} ; 
}

#ifdef ZUNIT_DEBUG

template <typename T> 
std::ostream& operator<<(std::ostream& os, const QuadF& qf) const noexcept {
	return os << "{" << qf.X << ", " << qf.Y << ", " << qf.Width << ", " << qf.Height << "}" ;
}

#endif