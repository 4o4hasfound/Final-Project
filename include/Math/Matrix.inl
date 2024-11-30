#include "Math/Matrix.hpp"

// -- Constructors --

template<typename T>
constexpr mat2<T>::mat2(mat2<T> const& m)
	: value{ m[0], m[1] } {

}

template<typename T>
constexpr mat2<T>::mat2(T scalar)
	: value{ col_type(scalar, 0), col_type(0, scalar) } {

}

template<typename T>
constexpr mat2<T>::mat2(
	T const& x0, T const& y0,
	T const& x1, T const& y1
)
	: value{ col_type(x0, y0), col_type(x1, y1) }
{

}

template<typename T>
constexpr mat2<T>::mat2(col_type const& v0, col_type const& v1)
	: value{ v0, v1 } {

}

// -- Conversion constructors --

template<typename T>
template<typename X1, typename Y1, typename X2, typename Y2>
constexpr mat2<T>::mat2(
	X1 const& x1, Y1 const& y1,
	X2 const& x2, Y2 const& y2
)
	: value{ col_type(static_cast<T>(x1), value_type(y1)), col_type(static_cast<T>(x2), value_type(y2)) } {

}

// -- mat2x2 matrix conversions --

template<typename T>
template<typename U>
constexpr mat2<T>::mat2(mat2<U> const& m)
	: value{ col_type(m[0]), col_type(m[1]) }
{

}

// -- Accesses --

template<typename T>
typename mat2<T>::col_type& mat2<T>::operator[](typename std::size_t i)
{

	assert(i < this->length());
	return this->value[i];
}

template<typename T>
constexpr typename mat2<T>::col_type const& mat2<T>::operator[](typename std::size_t i) const
{

	assert(i < this->length());
	return this->value[i];
}

// -- Unary updatable operators --

template<typename T>
template<typename U>
mat2<T>& mat2<T>::operator=(mat2<U> const& m)
{

	this->value[0] = m[0];
	this->value[1] = m[1];
	return *this;
}

template<typename T>
template<typename U>
mat2<T>& mat2<T>::operator+=(U scalar)
{

	this->value[0] += scalar;
	this->value[1] += scalar;
	return *this;
}

template<typename T>
template<typename U>
mat2<T>& mat2<T>::operator+=(mat2<U> const& m)
{

	this->value[0] += m[0];
	this->value[1] += m[1];
	return *this;
}

template<typename T>
template<typename U>
mat2<T>& mat2<T>::operator-=(U scalar)
{

	this->value[0] -= scalar;
	this->value[1] -= scalar;
	return *this;
}

template<typename T>
template<typename U>
mat2<T>& mat2<T>::operator-=(mat2<U> const& m)
{

	this->value[0] -= m[0];
	this->value[1] -= m[1];
	return *this;
}

template<typename T>
template<typename U>
mat2<T>& mat2<T>::operator*=(U scalar)
{

	this->value[0] *= scalar;
	this->value[1] *= scalar;
	return *this;
}

template<typename T>
template<typename U>
mat2<T>& mat2<T>::operator*=(mat2<U> const& m)
{

	return (*this = *this * m);
}

template<typename T>
template<typename U>
mat2<T>& mat2<T>::operator/=(U scalar)
{

	this->value[0] /= scalar;
	this->value[1] /= scalar;
	return *this;
}

// -- Increment and decrement operators --

template<typename T>
mat2<T>& mat2<T>::operator++()
{

	++this->value[0];
	++this->value[1];
	return *this;
}

template<typename T>
mat2<T>& mat2<T>::operator--()
{

	--this->value[0];
	--this->value[1];
	return *this;
}

template<typename T>
mat2<T> mat2<T>::operator++(int)
{

	mat2<T> Result(*this);
	++*this;
	return Result;
}

template<typename T>
mat2<T> mat2<T>::operator--(int)
{

	mat2<T> Result(*this);
	--*this;
	return Result;
}

// -- Unary arithmetic operators --

template<typename T>
mat2<T> operator+(mat2<T> const& m)
{

	return m;
}

template<typename T>
mat2<T> operator-(mat2<T> const& m)
{

	return mat2<T>(
		-m[0],
		-m[1]);
}

// -- Binary arithmetic operators --

template<typename T>
mat2<T> operator+(mat2<T> const& m, T scalar)
{

	return mat2<T>(
		m[0] + scalar,
		m[1] + scalar);
}

template<typename T>
mat2<T> operator+(T scalar, mat2<T> const& m)
{

	return mat2<T>(
		m[0] + scalar,
		m[1] + scalar);
}

template<typename T>
mat2<T> operator+(mat2<T> const& m1, mat2<T> const& m2)
{

	return mat2<T>(
		m1[0] + m2[0],
		m1[1] + m2[1]);
}

template<typename T>
mat2<T> operator-(mat2<T> const& m, T scalar)
{

	return mat2<T>(
		m[0] - scalar,
		m[1] - scalar);
}

template<typename T>
mat2<T> operator-(T scalar, mat2<T> const& m)
{

	return mat2<T>(
		scalar - m[0],
		scalar - m[1]);
}

template<typename T>
mat2<T> operator-(mat2<T> const& m1, mat2<T> const& m2)
{

	return mat2<T>(
		m1[0] - m2[0],
		m1[1] - m2[1]);
}

template<typename T>
mat2<T> operator*(mat2<T> const& m, T scalar)
{

	return mat2<T>(
		m[0] * scalar,
		m[1] * scalar);
}

template<typename T>
mat2<T> operator*(T scalar, mat2<T> const& m)
{

	return mat2<T>(
		m[0] * scalar,
		m[1] * scalar);
}

template<typename T>
typename mat2<T>::col_type operator*
	(
		mat2<T> const& m,
		typename mat2<T>::row_type const& v
		)
{

	return vec<2, T>(
		m[0][0] * v.x + m[1][0] * v.y,
		m[0][1] * v.x + m[1][1] * v.y);
}

template<typename T>
typename mat2<T>::row_type operator*
	(
		typename mat2<T>::col_type const& v,
		mat2<T> const& m
		)
{

	return vec<2, T>(
		v.x * m[0][0] + v.y * m[0][1],
		v.x * m[1][0] + v.y * m[1][1]);
}

template<typename T>
mat2<T> operator*(mat2<T> const& m1, mat2<T> const& m2)
{

	return mat2<T>(
		m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
		m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
		m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
		m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]);
}

template<typename T>
mat2<T> operator/(mat2<T> const& m, T scalar)
{

	return mat2<T>(
		m[0] / scalar,
		m[1] / scalar);
}

template<typename T>
mat2<T> operator/(T scalar, mat2<T> const& m)
{

	return mat2<T>(
		scalar / m[0],
		scalar / m[1]);
}

// -- Boolean operators --

template<typename T>
bool operator==(mat2<T> const& m1, mat2<T> const& m2)
{

	return (m1[0] == m2[0]) && (m1[1] == m2[1]);
}

template<typename T>
bool operator!=(mat2<T> const& m1, mat2<T> const& m2)
{

	return (m1[0] != m2[0]) || (m1[1] != m2[1]);
}