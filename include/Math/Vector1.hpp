#pragma once

#include "Math/vec_config.hpp"

#include <assert.h>


template<typename T>
class vec<1, T> {
public:
	/// Type traits
	using value_type = T;
	using type = vec<1, T>;
	using bool_type = vec<1, bool>;

	// Data
	union { T x, r, s; };

	// -- Component Access --

	// Component count
	static constexpr std::size_t length() { return 1; }

	constexpr T& operator[] (std::size_t i);
	constexpr T const& operator[] (std::size_t i) const;

	//constexpr std::initializer_list<T> data() const {
	//	return std::initializer_list<T>{
	//		std:ref(x)
	//	};
	//}

	// -- Implicit basic constructors --

	constexpr vec() = default;
	constexpr vec(vec<1, T> const& v) = default;

	// -- Explicit basic constructors --

	constexpr explicit vec(T x);

	// -- Conversion scalar constructors --

	template<typename U>
	constexpr vec(vec<1, U> const& v);

	// -- Explicit conversions --
	template<typename X>
	constexpr vec(X _x);

	// -- Unary arithmetic operators --

	constexpr vec<1, T>& operator=(vec<1, T> const& v) = default;

	template<typename U>
	constexpr vec<1, T>& operator=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<1, T>& operator+=(U scalar);
	template<typename U>
	constexpr vec<1, T>& operator+=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<1, T>& operator-=(U scalar);
	template<typename U>
	constexpr vec<1, T>& operator-=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<1, T>& operator*=(U scalar);
	template<typename U>
	constexpr vec<1, T>& operator*=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<1, T>& operator/=(U scalar);
	template<typename U>
	constexpr vec<1, T>& operator/=(vec<1, U> const& v);

	// -- Increment and decrement operators --

	constexpr vec<1, T>& operator++();
	constexpr vec<1, T>& operator--();
	constexpr vec<1, T> operator++(int);
	constexpr vec<1, T> operator--(int);

	// -- Unary bit operators --

	template<typename U>
	constexpr vec<1, T>& operator%=(U scalar);
	template<typename U>
	constexpr vec<1, T>& operator%=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<1, T>& operator&=(U scalar);
	template<typename U>
	constexpr vec<1, T>& operator&=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<1, T>& operator|=(U scalar);
	template<typename U>
	constexpr vec<1, T>& operator|=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<1, T>& operator^=(U scalar);
	template<typename U>
	constexpr vec<1, T>& operator^=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<1, T>& operator<<=(U scalar);
	template<typename U>
	constexpr vec<1, T>& operator<<=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<1, T>& operator>>=(U scalar);
	template<typename U>
	constexpr vec<1, T>& operator>>=(vec<1, U> const& v);
};

// -- Unary operators --

template<typename T>
constexpr vec<1, T> operator+(vec<1, T> const& v);

template<typename T>
constexpr vec<1, T> operator-(vec<1, T> const& v);

// -- Binary operators --

template<typename T, typename U>
constexpr vec<1, T> operator+(vec<1, T> const& v, U const& scalar);

template<typename T, typename U>
constexpr vec<1, T> operator+(vec<1, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<1, T> operator+(T scalar, vec<1, U> const& v);

template<typename T, typename U>
constexpr vec<1, T> operator+(vec<1, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<1, T> operator-(vec<1, T> const& v, U const& scalar);

template<typename T, typename U>
constexpr vec<1, T> operator-(vec<1, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<1, T> operator-(T scalar, vec<1, U> const& v);

template<typename T, typename U>
constexpr vec<1, T> operator-(vec<1, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<1, T> operator*(vec<1, T> const& v, U const& scalar);

template<typename T, typename U>
constexpr vec<1, T> operator*(vec<1, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<1, T> operator*(T scalar, vec<1, U> const& v);

template<typename T, typename U>
constexpr vec<1, T> operator*(vec<1, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<1, T> operator/(vec<1, T> const& v, U const& scalar);

template<typename T, typename U>
constexpr vec<1, T> operator/(vec<1, T> const& v1, vec<1, U> const& v2);

template<typename T, typename U>
constexpr vec<1, T> operator/(T scalar, vec<1, U> const& v);

template<typename T, typename U>
constexpr vec<1, T> operator/(vec<1, T> const& v1, vec<1, U> const& v2);

// -- Binary bit operators --

template<typename T>
constexpr vec<1, T> operator%(vec<1, T> const& v, T scalar);

template<typename T>
constexpr vec<1, T> operator%(vec<1, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<1, T> operator%(T scalar, vec<1, T> const& v);

template<typename T>
constexpr vec<1, T> operator%(vec<1, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<1, T> operator&(vec<1, T> const& v, T scalar);

template<typename T>
constexpr vec<1, T> operator&(vec<1, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<1, T> operator&(T scalar, vec<1, T> const& v);

template<typename T>
constexpr vec<1, T> operator&(vec<1, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<1, T> operator|(vec<1, T> const& v, T scalar);

template<typename T>
constexpr vec<1, T> operator|(vec<1, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<1, T> operator|(T scalar, vec<1, T> const& v);

template<typename T>
constexpr vec<1, T> operator|(vec<1, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<1, T> operator^(vec<1, T> const& v, T scalar);

template<typename T>
constexpr vec<1, T> operator^(vec<1, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<1, T> operator^(T scalar, vec<1, T> const& v);

template<typename T>
constexpr vec<1, T> operator^(vec<1, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<1, T> operator<<(vec<1, T> const& v, T scalar);

template<typename T>
constexpr vec<1, T> operator<<(vec<1, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<1, T> operator<<(T scalar, vec<1, T> const& v);

template<typename T>
constexpr vec<1, T> operator<<(vec<1, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<1, T> operator>>(vec<1, T> const& v, T scalar);

template<typename T>
constexpr vec<1, T> operator>>(vec<1, T> const& v, vec<1, T> const& scalar);

template<typename T>
constexpr vec<1, T> operator>>(T scalar, vec<1, T> const& v);

template<typename T>
constexpr vec<1, T> operator>>(vec<1, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr vec<1, T> operator~(vec<1, T> const& v);

// -- Boolean operators --

template<typename T>
constexpr bool operator>(vec<1, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr bool operator<(vec<1, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr bool operator>=(vec<1, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr bool operator<=(vec<1, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr bool operator==(vec<1, T> const& v1, vec<1, T> const& v2);

template<typename T>
constexpr bool operator!=(vec<1, T> const& v1, vec<1, T> const& v2);

constexpr vec<1, bool> operator&&(vec<1, bool> const& v1, vec<1, bool> const& v2);

constexpr vec<1, bool> operator||(vec<1, bool> const& v1, vec<1, bool> const& v2);