#pragma once

#include "Math/vec_config.hpp"
#include "Math/Matrix.hpp"

#include <assert.h>


template<typename T>
class vec<2, T> {
public:
	/// Type traits
	using value_type = T;
	using type = vec<2, T>;
	using bool_type = vec<2, bool>;

	// Data
	union { T x, r, s; };
	union { T y, g, t; };

	// -- Component Access --

	// Component count
	static constexpr std::size_t length() { return 2; }

	constexpr T& operator[](std::size_t i);
	constexpr T const& operator[](std::size_t i) const;

	//constexpr std::initializer_list<T> data() const {
	//	return std::initializer_list<T>{
	//		std:ref(x),
	//		std::ref(y)
	//	};
	//}

	// -- Implicit basic constructors --

	constexpr vec() = default;
	constexpr vec(vec<2, T> const& v) = default;

	// -- Explicit basic constructors --

	constexpr explicit vec(T scalar);
	constexpr vec(T x, T y);

	// -- Conversion constructors --

	template<typename U>
	constexpr explicit vec(vec<1, U> const& v);

	// Explicit conversions
	template<typename A, typename B>
	constexpr vec(A x, B y);
	template<typename A, typename B>
	constexpr vec(vec<1, A> const& x, B y);
	template<typename A, typename B>
	constexpr vec(A x, vec<1, B> const& y);
	template<typename A, typename B>
	constexpr vec(vec<1, A> const& x, vec<1, B> const& y);

	// -- Conversion vector constructors --

	// Explicit conversions
	template<typename U>
	constexpr explicit vec(vec<3, U> const& v);
	// Explicit conversions
	template<typename U>
	constexpr explicit vec(vec<4, U> const& v);

	// Explicit conversions
	template<typename U>
	constexpr explicit vec(vec<2, U> const& v);

	// -- Unary arithmetic operators --

	constexpr vec<2, T>& operator=(vec<2, T> const& v) = default;

	template<typename U>
	constexpr vec<2, T>& operator=(vec<2, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator+=(U scalar);
	template<typename U>
	constexpr vec<2, T>& operator+=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator+=(vec<2, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator-=(U scalar);
	template<typename U>
	constexpr vec<2, T>& operator-=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator-=(vec<2, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator*=(U scalar);
	template<typename U>
	constexpr vec<2, T> operator*=(mat2<U> const& m);
	template<typename U>
	constexpr vec<2, T>& operator*=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator*=(vec<2, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator/=(U scalar);
	template<typename U>
	constexpr vec<2, T>& operator/=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator/=(vec<2, U> const& v);

	// -- Increment and decrement operators --

	constexpr vec<2, T>& operator++();
	constexpr vec<2, T>& operator--();
	constexpr vec<2, T> operator++(int);
	constexpr vec<2, T> operator--(int);

	// -- Unary bit operators --

	template<typename U>
	constexpr vec<2, T>& operator%=(U scalar);
	template<typename U>
	constexpr vec<2, T>& operator%=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator%=(vec<2, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator&=(U scalar);
	template<typename U>
	constexpr vec<2, T>& operator&=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator&=(vec<2, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator|=(U scalar);
	template<typename U>
	constexpr vec<2, T>& operator|=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator|=(vec<2, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator^=(U scalar);
	template<typename U>
	constexpr vec<2, T>& operator^=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator^=(vec<2, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator<<=(U scalar);
	template<typename U>
	constexpr vec<2, T>& operator<<=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator<<=(vec<2, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator>>=(U scalar);
	template<typename U>
	constexpr vec<2, T>& operator>>=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<2, T>& operator>>=(vec<2, U> const& v);
};

// -- Unary operators --

template<typename T>
constexpr vec<2, T> operator+(vec<2, T> const& v);

template<typename T>
constexpr vec<2, T> operator-(vec<2, T> const& v);

// -- Binary operators --

template<typename T, typename U>
constexpr vec<2, T> operator+(vec<2, T> const& v, U scalar);

template<typename T, typename U>
constexpr vec<2, T> operator+(vec<2, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<2, T> operator+(U scalar, vec<2, T> const& v);

template<typename T, typename U>
constexpr vec<2, T> operator+(vec<1, U> const& v1, vec<2, T> const& v2);

template<typename T, typename U>
constexpr vec<2, T> operator+(vec<2, T> const& v1, vec<2, U> const& v2);

template<typename T, typename U>
constexpr vec<2, T> operator-(vec<2, T> const& v, U scalar);

template<typename T, typename U>
constexpr vec<2, T> operator-(vec<2, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<2, T> operator-(U scalar, vec<2, T> const& v);

template<typename T, typename U>
constexpr vec<2, T> operator-(vec<1, U> const& v1, vec<2, T> const& v2);

template<typename T, typename U>
constexpr vec<2, T> operator-(vec<2, T> const& v1, vec<2, U> const& v2);

template<typename T, typename U>
constexpr vec<2, T> operator*(vec<2, T> const& v, U scalar);

template<typename T, typename U>
constexpr vec<2, T> operator*(vec<2, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<2, T> operator*(U scalar, vec<2, T> const& v);

template<typename T, typename U>
constexpr vec<2, T> operator*(vec<1, U> const& v1, vec<2, T> const& v2);

template<typename T, typename U>
constexpr vec<2, T> operator*(vec<2, T> const& v1, vec<2, U> const& v2);

template<typename T, typename U>
constexpr vec<2, T> operator/(vec<2, T> const& v, U scalar);

template<typename T, typename U>
constexpr vec<2, T> operator/(vec<2, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<2, T> operator/(U scalar, vec<2, T> const& v);

template<typename T, typename U>
constexpr vec<2, T> operator/(vec<1, U> const& v1, vec<2, T> const& v2);

template<typename T, typename U>
constexpr vec<2, T> operator/(vec<2, T> const& v1, vec<2, U> const& v2);

template<typename T>
constexpr vec<2, T> operator%(vec<2, T> const& v, T scalar);

template<typename T>
constexpr vec<2, T> operator%(vec<2, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<2, T> operator%(T scalar, vec<2, T> const& v);

template<typename T>
constexpr vec<2, T> operator%(vec<1, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator%(vec<2, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator&(vec<2, T> const& v, T scalar);

template<typename T>
constexpr vec<2, T> operator&(vec<2, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<2, T> operator&(T scalar, vec<2, T> const& v);

template<typename T>
constexpr vec<2, T> operator&(vec<1, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator&(vec<2, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator|(vec<2, T> const& v, T scalar);

template<typename T>
constexpr vec<2, T> operator|(vec<2, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<2, T> operator|(T scalar, vec<2, T> const& v);

template<typename T>
constexpr vec<2, T> operator|(vec<1, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator|(vec<2, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator^(vec<2, T> const& v, T scalar);

template<typename T>
constexpr vec<2, T> operator^(vec<2, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<2, T> operator^(T scalar, vec<2, T> const& v);

template<typename T>
constexpr vec<2, T> operator^(vec<1, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator^(vec<2, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator<<(vec<2, T> const& v, T scalar);

template<typename T>
constexpr vec<2, T> operator<<(vec<2, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<2, T> operator<<(T scalar, vec<2, T> const& v);

template<typename T>
constexpr vec<2, T> operator<<(vec<1, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator<<(vec<2, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator>>(vec<2, T> const& v, T scalar);

template<typename T>
constexpr vec<2, T> operator>>(vec<2, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<2, T> operator>>(T scalar, vec<2, T> const& v);

template<typename T>
constexpr vec<2, T> operator>>(vec<1, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator>>(vec<2, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr vec<2, T> operator~(vec<2, T> const& v);

// -- Boolean operators --

template<typename T>
constexpr bool operator==(vec<2, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr bool operator!=(vec<2, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr bool operator>(vec<2, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr bool operator<(vec<2, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr bool operator>=(vec<2, T> const& v1, vec<2, T> const& v2);

template<typename T>
constexpr bool operator<=(vec<2, T> const& v1, vec<2, T> const& v2);

constexpr vec<2, bool> operator&&(vec<2, bool> const& v1, vec<2, bool> const& v2);

constexpr vec<2, bool> operator||(vec<2, bool> const& v1, vec<2, bool> const& v2);