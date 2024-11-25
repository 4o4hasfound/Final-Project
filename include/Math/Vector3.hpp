#pragma once

#include "Math/vec_config.hpp"

#include <assert.h>

template<typename T>
class vec<3, T> {
public:
	/// Type traits
	using value_type = T;
	using type = vec<3, T>;
	using bool_type = vec<3, bool>;

	// Data
	union { T x, r, s; };
	union { T y, g, t; };
	union { T z, b, p; };

	// -- Component Access --

	// Component count
	static constexpr std::size_t length() { return 3; }

	constexpr T& operator[](std::size_t i);
	constexpr T const& operator[](std::size_t i) const;

	//constexpr std::initializer_list<T> data() const {
	//	return std::initializer_list<T>{
	//		std:ref(x),
	//		std::ref(y),
	//		std::reft(z)
	//	};
	//}

	// -- Implicit basic constructors --

	constexpr vec() = default;
	constexpr vec(vec<3, T> const& v) = default;

	// -- Explicit basic constructors --

	constexpr explicit vec(T scalar);
	constexpr vec(T a, T b, T c);

	// -- Conversion scalar constructors --

	template<typename U>
	constexpr explicit vec(vec<1, U> const& v);

	/// Explicit conversions
	template<typename X, typename Y, typename Z>
	constexpr vec(X x, Y y, Z z);
	template<typename X, typename Y, typename Z>
	constexpr vec(vec<1, X> const& _x, Y _y, Z _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(X _x, vec<1, Y> const& _y, Z _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _y, Z _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(X _x, Y _y, vec<1, Z> const& _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(vec<1, X> const& _x, Y _y, vec<1, Z> const& _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(X _x, vec<1, Y> const& _y, vec<1, Z> const& _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _y, vec<1, Z> const& _z);

	// -- Conversion vector constructors --

	template<typename A, typename B>
	constexpr vec(vec<2, A> const& _xy, B _z);
	template<typename A, typename B>
	constexpr vec(vec<2, A> const& _xy, vec<1, B> const& _z);
	template<typename A, typename B>
	constexpr vec(A _x, vec<2, B> const& _yz);
	template<typename A, typename B>
	constexpr vec(vec<1, A> const& _x, vec<2, B> const& _yz);
	template<typename U>
	constexpr explicit vec(vec<4, U> const& v);
	template<typename U>
	constexpr explicit vec(vec<3, U> const& v);

	// -- Unary arithmetic operators --

	constexpr vec<3, T>& operator=(vec<3, T> const& v) = default;

	template<typename U>
	constexpr vec<3, T>& operator=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator+=(U scalar);
	template<typename U>
	constexpr vec<3, T>& operator+=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator+=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator-=(U scalar);
	template<typename U>
	constexpr vec<3, T>& operator-=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator-=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator*=(U scalar);
	template<typename U>
	constexpr vec<3, T>& operator*=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator*=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator/=(U scalar);
	template<typename U>
	constexpr vec<3, T>& operator/=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator/=(vec<3, U> const& v);

	// -- Increment and decrement operators --

	constexpr vec<3, T>& operator++();
	constexpr vec<3, T>& operator--();
	constexpr vec<3, T> operator++(int);
	constexpr vec<3, T> operator--(int);

	// -- Unary bit operators --

	template<typename U>
	constexpr vec<3, T>& operator%=(U scalar);
	template<typename U>
	constexpr vec<3, T>& operator%=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator%=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator&=(U scalar);
	template<typename U>
	constexpr vec<3, T>& operator&=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator&=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator|=(U scalar);
	template<typename U>
	constexpr vec<3, T>& operator|=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator|=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator^=(U scalar);
	template<typename U>
	constexpr vec<3, T>& operator^=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator^=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator<<=(U scalar);
	template<typename U>
	constexpr vec<3, T>& operator<<=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator<<=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator>>=(U scalar);
	template<typename U>
	constexpr vec<3, T>& operator>>=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T>& operator>>=(vec<3, U> const& v);
};

template<typename T>
constexpr vec<3, T> operator+(vec<3, T> const& v);

template<typename T>
constexpr vec<3, T> operator-(vec<3, T> const& v);

// -- Binary operators --

template<typename T, typename U>
constexpr vec<3, T> operator+(vec<3, T> const& v, U scalar);

template<typename T, typename U>
constexpr vec<3, T> operator+(vec<3, T> const& v, vec<1, U> const& scalar);

template<typename T, typename U>
constexpr vec<3, T> operator+(U scalar, vec<3, T> const& v);

template<typename T, typename U>
constexpr vec<3, T> operator+(vec<1, U> const& v1, vec<3, T> const& v2);

template<typename T, typename U>
constexpr vec<3, T> operator+(vec<3, T> const& v1, vec<3, U> const& v2);

template<typename T, typename U>
constexpr vec<3, T> operator-(vec<3, T> const& v, U scalar);

template<typename T, typename U>
constexpr vec<3, T> operator-(vec<3, T> const& v, vec<1, U> const& scalar);

template<typename T, typename U>
constexpr vec<3, T> operator-(U scalar, vec<3, T> const& v);

template<typename T, typename U>
constexpr vec<3, T> operator-(vec<1, U> const& v1, vec<3, T> const& v2);

template<typename T, typename U>
constexpr vec<3, T> operator-(vec<3, T> const& v1, vec<3, U> const& v2);

template<typename T, typename U>
constexpr vec<3, T> operator*(vec<3, T> const& v, U scalar);

template<typename T, typename U>
constexpr vec<3, T> operator*(vec<3, T> const& v, vec<1, U> const& scalar);

template<typename T, typename U>
constexpr vec<3, T> operator*(U scalar, vec<3, T> const& v);

template<typename T, typename U>
constexpr vec<3, T> operator*(vec<1, U> const& v1, vec<3, T> const& v2);

template<typename T, typename U>
constexpr vec<3, T> operator*(vec<3, T> const& v1, vec<3, U> const& v2);

template<typename T, typename U>
constexpr vec<3, T> operator/(vec<3, T> const& v, U scalar);

template<typename T, typename U>
constexpr vec<3, T> operator/(vec<3, T> const& v, vec<1, U> const& scalar);

template<typename T, typename U>
constexpr vec<3, T> operator/(U scalar, vec<3, T> const& v);

template<typename T, typename U>
constexpr vec<3, T> operator/(vec<1, U> const& v1, vec<3, T> const& v2);

template<typename T, typename U>
constexpr vec<3, T> operator/(vec<3, T> const& v1, vec<3, U> const& v2);

template<typename T>
constexpr vec<3, T> operator%(vec<3, T> const& v, T scalar);

template<typename T>
constexpr vec<3, T> operator%(vec<3, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<3, T> operator%(T scalar, vec<3, T> const& v);

template<typename T>
constexpr vec<3, T> operator%(vec<1, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator%(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator&(vec<3, T> const& v1, T scalar);

template<typename T>
constexpr vec<3, T> operator&(vec<3, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<3, T> operator&(T scalar, vec<3, T> const& v);

template<typename T>
constexpr vec<3, T> operator&(vec<1, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator&(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator|(vec<3, T> const& v, T scalar);

template<typename T>
constexpr vec<3, T> operator|(vec<3, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<3, T> operator|(T scalar, vec<3, T> const& v);

template<typename T>
constexpr vec<3, T> operator|(vec<1, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator|(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator^(vec<3, T> const& v, T scalar);

template<typename T>
constexpr vec<3, T> operator^(vec<3, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<3, T> operator^(T scalar, vec<3, T> const& v);

template<typename T>
constexpr vec<3, T> operator^(vec<1, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator^(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator<<(vec<3, T> const& v, T scalar);

template<typename T>
constexpr vec<3, T> operator<<(vec<3, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<3, T> operator<<(T scalar, vec<3, T> const& v);

template<typename T>
constexpr vec<3, T> operator<<(vec<1, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator<<(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator>>(vec<3, T> const& v, T scalar);

template<typename T>
constexpr vec<3, T> operator>>(vec<3, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<3, T> operator>>(T scalar, vec<3, T> const& v);

template<typename T>
constexpr vec<3, T> operator>>(vec<1, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator>>(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr vec<3, T> operator~(vec<3, T> const& v);

// -- Boolean operators --

template<typename T>
constexpr bool operator>(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr bool operator<(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr bool operator>=(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr bool operator<=(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr bool operator==(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr bool operator!=(vec<3, T> const& v1, vec<3, T> const& v2);

constexpr vec<3, bool> operator&&(vec<3, bool> const& v1, vec<3, bool> const& v2);

constexpr vec<3, bool> operator||(vec<3, bool> const& v1, vec<3, bool> const& v2);