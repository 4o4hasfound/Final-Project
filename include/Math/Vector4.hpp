#pragma once

#include "Math/vec_config.hpp"

#include <assert.h>

template<typename T>
class vec<4, T> {
public:
	// -- Implementation detail --

	typedef T value_type;
	typedef vec<4, T> type;
	typedef vec<4, bool> bool_type;

	// -- Data --

	union { T x, r, s; };
	union { T y, g, t; };
	union { T z, b, p; };
	union { T w, a, q; };
	// -- Component accesses --

	/// Return the count of components of the vector
	static constexpr std::size_t length() { return 4; }

	constexpr T& operator[](std::size_t i);
	constexpr T const& operator[](std::size_t i) const;

	//constexpr std::initializer_list<T> data() const { 
	//	return std::initializer_list<T>{
	//		std:ref(x), 
	//		std::ref(y),
	//		std::ref(z),
	//		std::ref(w)
	//	}; 
	//}

	// -- Implicit basic constructors --

	constexpr vec() = default;
	constexpr vec(vec<4, T> const& v) = default;

	// -- Explicit basic constructors --

	constexpr explicit vec(T scalar);
	constexpr vec(T x, T y, T z, T w);

	// -- Conversion scalar constructors --

	template<typename U>
	constexpr explicit vec(vec<1, U> const& v);

	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, Y _y, Z _z, W _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, Y _y, Z _z, W _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, vec<1, Y> const& _y, Z _z, W _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _y, Z _z, W _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, Y _y, vec<1, Z> const& _z, W _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, Y _y, vec<1, Z> const& _z, W _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, vec<1, Y> const& _y, vec<1, Z> const& _z, W _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _y, vec<1, Z> const& _z, W _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, Y _y, Z _z, vec<1, W> const& _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, vec<1, Y> const& _y, Z _z, vec<1, W> const& _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _y, Z _z, vec<1, W> const& _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, Y _y, vec<1, Z> const& _z, vec<1, W> const& _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, Y _y, vec<1, Z> const& _z, vec<1, W> const& _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, vec<1, Y> const& _y, vec<1, Z> const& _z, vec<1, W> const& _w);
	template<typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _Y, vec<1, Z> const& _z, vec<1, W> const& _w);

	// -- Conversion vector constructors --

	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(vec<2, A> const& _xy, B _z, C _w);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(vec<2, A> const& _xy, vec<1, B> const& _z, C _w);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(vec<2, A> const& _xy, B _z, vec<1, C> const& _w);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(vec<2, A> const& _xy, vec<1, B> const& _z, vec<1, C> const& _w);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(A _x, vec<2, B> const& _yz, C _w);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(vec<1, A> const& _x, vec<2, B> const& _yz, C _w);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(A _x, vec<2, B> const& _yz, vec<1, C> const& _w);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(vec<1, A> const& _x, vec<2, B> const& _yz, vec<1, C> const& _w);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(A _x, B _y, vec<2, C> const& _zw);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(vec<1, A> const& _x, B _y, vec<2, C> const& _zw);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(A _x, vec<1, B> const& _y, vec<2, C> const& _zw);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B, typename C>
	constexpr vec(vec<1, A> const& _x, vec<1, B> const& _y, vec<2, C> const& _zw);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B>
	constexpr vec(vec<3, A> const& _xyz, B _w);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B>
	constexpr vec(vec<3, A> const& _xyz, vec<1, B> const& _w);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B>
	constexpr vec(A _x, vec<3, B> const& _yzw);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B>
	constexpr vec(vec<1, A> const& _x, vec<3, B> const& _yzw);
	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename A, typename B>
	constexpr vec(vec<2, A> const& _xy, vec<2, B> const& _zw);

	/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
	template<typename U>
	constexpr explicit vec(vec<4, U> const& v);

	// -- Unary arithmetic operators --

	constexpr vec<4, T>& operator=(vec<4, T> const& v) = default;

	template<typename U>
	constexpr vec<4, T>& operator=(vec<4, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator+=(U scalar);
	template<typename U>
	constexpr vec<4, T>& operator+=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator+=(vec<4, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator-=(U scalar);
	template<typename U>
	constexpr vec<4, T>& operator-=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator-=(vec<4, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator*=(U scalar);
	template<typename U>
	constexpr vec<4, T>& operator*=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator*=(vec<4, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator/=(U scalar);
	template<typename U>
	constexpr vec<4, T>& operator/=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator/=(vec<4, U> const& v);

	// -- Increment and decrement operators --

	constexpr vec<4, T>& operator++();
	constexpr vec<4, T>& operator--();
	constexpr vec<4, T> operator++(int);
	constexpr vec<4, T> operator--(int);

	// -- Unary bit operators --

	template<typename U>
	constexpr vec<4, T>& operator%=(U scalar);
	template<typename U>
	constexpr vec<4, T>& operator%=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator%=(vec<4, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator&=(U scalar);
	template<typename U>
	constexpr vec<4, T>& operator&=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator&=(vec<4, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator|=(U scalar);
	template<typename U>
	constexpr vec<4, T>& operator|=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator|=(vec<4, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator^=(U scalar);
	template<typename U>
	constexpr vec<4, T>& operator^=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator^=(vec<4, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator<<=(U scalar);
	template<typename U>
	constexpr vec<4, T>& operator<<=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator<<=(vec<4, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator>>=(U scalar);
	template<typename U>
	constexpr vec<4, T>& operator>>=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<4, T>& operator>>=(vec<4, U> const& v);
};

// -- Unary operators --

template<typename T>
constexpr vec<4, T> operator+(vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator-(vec<4, T> const& v);

// -- Binary operators --

template<typename T, typename U>
constexpr vec<4, T> operator+(vec<4, T> const& v, U const& scalar);

template<typename T, typename U>
constexpr vec<4, T> operator+(vec<4, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<4, T> operator+(U scalar, vec<4, T> const& v);

template<typename T, typename U>
constexpr vec<4, T> operator+(vec<1, U> const& v1, vec<4, T> const& v2);

template<typename T, typename U>
constexpr vec<4, T> operator+(vec<4, T> const& v1, vec<4, U> const& v2);

template<typename T, typename U>
constexpr vec<4, T> operator-(vec<4, T> const& v, U const& scalar);

template<typename T, typename U>
constexpr vec<4, T> operator-(vec<4, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<4, T> operator-(U scalar, vec<4, T> const& v);

template<typename T, typename U>
constexpr vec<4, T> operator-(vec<1, U> const& v1, vec<4, T> const& v2);

template<typename T, typename U>
constexpr vec<4, T> operator-(vec<4, T> const& v1, vec<4, U> const& v2);

template<typename T, typename U>
constexpr vec<4, T> operator*(vec<4, T> const& v, U const& scalar);

template<typename T, typename U>
constexpr vec<4, T> operator*(vec<4, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<4, T> operator*(U scalar, vec<4, T> const& v);

template<typename T, typename U>
constexpr vec<4, T> operator*(vec<1, U> const& v1, vec<4, T> const& v2);

template<typename T, typename U>
constexpr vec<4, T> operator*(vec<4, T> const& v1, vec<4, U> const& v2);

template<typename T, typename U>
constexpr vec<4, T> operator/(vec<4, T> const& v, U const& scalar);

template<typename T, typename U>
constexpr vec<4, T> operator/(vec<4, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<4, T> operator/(U scalar, vec<4, T> const& v);

template<typename T, typename U>
constexpr vec<4, T> operator/(vec<1, U> const& v1, vec<4, T> const& v2);

template<typename T, typename U>
constexpr vec<4, T> operator/(vec<4, T> const& v1, vec<4, U> const& v2);

template<typename T>
constexpr vec<4, T> operator%(vec<4, T> const& v, T scalar);

template<typename T>
constexpr vec<4, T> operator%(vec<4, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<4, T> operator%(T scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator%(vec<1, T> const& scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator%(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr vec<4, T> operator&(vec<4, T> const& v, T scalar);

template<typename T>
constexpr vec<4, T> operator&(vec<4, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<4, T> operator&(T scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator&(vec<1, T> const& scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator&(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr vec<4, T> operator|(vec<4, T> const& v, T scalar);

template<typename T>
constexpr vec<4, T> operator|(vec<4, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<4, T> operator|(T scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator|(vec<1, T> const& scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator|(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr vec<4, T> operator^(vec<4, T> const& v, T scalar);

template<typename T>
constexpr vec<4, T> operator^(vec<4, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<4, T> operator^(T scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator^(vec<1, T> const& scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator^(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr vec<4, T> operator<<(vec<4, T> const& v, T scalar);

template<typename T>
constexpr vec<4, T> operator<<(vec<4, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<4, T> operator<<(T scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator<<(vec<1, T> const& scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator<<(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr vec<4, T> operator>>(vec<4, T> const& v, T scalar);

template<typename T>
constexpr vec<4, T> operator>>(vec<4, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<4, T> operator>>(T scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator>>(vec<1, T> const& scalar, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator>>(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr vec<4, T> operator~(vec<4, T> const& v);

// -- Boolean operators --

template<typename T>
constexpr bool operator>(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr bool operator<(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr bool operator>=(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr bool operator<=(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr bool operator==(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr bool operator!=(vec<4, T> const& v1, vec<4, T> const& v2);

	
constexpr vec<4, bool> operator&&(vec<4, bool> const& v1, vec<4, bool> const& v2);

constexpr vec<4, bool> operator||(vec<4, bool> const& v1, vec<4, bool> const& v2);