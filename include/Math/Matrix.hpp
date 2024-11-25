#pragma once

#include "Math/vec_config.hpp"
#include <limits>
#include <cstddef>
#include <cassert>

template<typename T = float>
class mat2 {
	typedef vec<2, T> col_type;
	typedef vec<2, T> row_type;
	typedef T value_type;

private:
	col_type value[2];

public:
	// -- Accesses --

	static constexpr std::size_t length() { return 2; }

	col_type& operator[](std::size_t i);
	constexpr col_type const& operator[](std::size_t i) const;

	// -- Constructors --

	constexpr mat2() = default;
	constexpr mat2(mat2<T> const& m);

	explicit constexpr mat2(T scalar);
	constexpr mat2(T const& x1, T const& y1, T const& x2, T const& y2);
	constexpr mat2(col_type const& v1, col_type const& v2);

	// -- Conversions --

	template<typename U, typename V, typename M, typename N>
	constexpr mat2(U const& x1, V const& y1, M const& x2, N const& y2);

	// -- Matrix conversions --

	template<typename U>
	explicit constexpr mat2(mat2<U> const& m);

	// -- Unary arithmetic operators --

	template<typename U>
	mat2<T>& operator=(mat2<U> const& m);
	template<typename U>
	mat2<T>& operator+=(U s);
	template<typename U>
	mat2<T>& operator+=(mat2<U> const& m);
	template<typename U>
	mat2<T>& operator-=(U s);
	template<typename U>
	mat2<T>& operator-=(mat2<U> const& m);
	template<typename U>
	mat2<T>& operator*=(U s);
	template<typename U>
	mat2<T>& operator*=(mat2<U> const& m);
	template<typename U>
	mat2<T>& operator/=(U s);

	// -- Increment and decrement operators --

	mat2<T>& operator++ ();
	mat2<T>& operator-- ();
	mat2<T> operator++(int);
	mat2<T> operator--(int);
};

// -- Unary operators --

template<typename T>
mat2<T> operator+(mat2<T> const& m);

template<typename T>
mat2<T> operator-(mat2<T> const& m);

// -- Binary operators --

template<typename T>
mat2<T> operator+(mat2<T> const& m, T scalar);

template<typename T>
mat2<T> operator+(T scalar, mat2<T> const& m);

template<typename T>
mat2<T> operator+(mat2<T> const& m1, mat2<T> const& m2);

template<typename T>
mat2<T> operator-(mat2<T> const& m, T scalar);

template<typename T>
mat2<T> operator-(T scalar, mat2<T> const& m);

template<typename T>
mat2<T> operator-(mat2<T> const& m1, mat2<T> const& m2);

template<typename T>
mat2<T> operator*(mat2<T> const& m, T scalar);

template<typename T>
mat2<T> operator*(T scalar, mat2<T> const& m);

template<typename T>
typename mat2<T>::col_type operator*(mat2<T> const& m, typename mat2<T>::row_type const& v);

template<typename T>
typename mat2<T>::row_type operator*(typename mat2<T>::col_type const& v, mat2<T> const& m);

template<typename T>
mat2<T> operator*(mat2<T> const& m1, mat2<T> const& m2);

template<typename T>
mat2<T> operator/(mat2<T> const& m, T scalar);

template<typename T>
mat2<T> operator/(T scalar, mat2<T> const& m);

// -- Boolean operators --

template<typename T>
bool operator==(mat2<T> const& m1, mat2<T> const& m2);

template<typename T>
bool operator!=(mat2<T> const& m1, mat2<T> const& m2);

#include "Matrix.inl"