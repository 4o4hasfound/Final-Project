#pragma once

#include "Math/vec_config.hpp"
#include "Math/Matrix.hpp"

#include <limits>
#include <assert.h>
#include <cmath>
#include <algorithm>

// Dot product

template<typename T>
constexpr inline T dot(T a, T b) {
	static_assert(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");

	return a * b;
}

template<typename T>
constexpr inline T dot(vec<1, T> const& v1, vec<1, T> const& v2) {
	static_assert(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");

	vec<1, T> tmp(v1 * v2);
	return tmp.x;
}
template<typename T>
constexpr inline T dot(vec<2, T> const& v1, vec<2, T> const& v2) {
	static_assert(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");

	vec<2, T> tmp(v1 * v2);
	return tmp.x + tmp.y;
}
template<typename T>
constexpr inline T dot(vec<3, T> const& v1, vec<3, T> const& v2) {
	static_assert(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");

	vec<3, T> tmp(v1 * v2);
	return tmp.x + tmp.y + tmp.z;
}

// Cross product

template<typename T>
constexpr inline vec<3, T> cross(vec<3, T> const& v1, vec<3, T> const& v2) {
	static_assert(std::numeric_limits<T>::is_iec559, "'cross' accepts only floating-point inputs");

	return vec<3, T>(
		v1.y * v2.z - v2.y * v1.z,
		v1.z * v2.x - v2.z * v1.x,
		v1.x * v2.y - v2.x * v1.y);
}
// Length
template<typename T>
constexpr inline T length(T x) {
	static_assert(std::numeric_limits<T>::is_iec559, "'length' accepts only floating-point inputs");

	return std::abs(x);
}

template<std::size_t L, typename T>
constexpr inline T length(vec<L, T> const& v) {
	static_assert(std::numeric_limits<T>::is_iec559, "'length' accepts only floating-point inputs");

	return std::sqrt(dot(v, v));
}

// Distance
	
template<typename T>
constexpr inline T distance(T a, T b) {
	static_assert(std::numeric_limits<T>::is_iec559, "'distance' accepts only floating-point inputs");

	return length(a - b);
}

template<std::size_t L, typename T>
constexpr inline T distance(vec<L, T> const& v1, vec<L, T> const& v2) {
	static_assert(std::numeric_limits<T>::is_iec559, "'distance' accepts only floating-point inputs");

	return length(v1 - v2);
}

// Normalize

template<std::size_t L, typename T>
constexpr inline vec<L, T> normalize(vec<L, T> const& v) {
	static_assert(std::numeric_limits<T>::is_iec559, "'normalize' accepts only floating-point inputs");

	return v * (static_cast<T>(1.0) / std::sqrt(dot(v, v)));
}

// Faceforward

template<std::size_t L, typename T>
constexpr inline vec<L, T> faceforward(vec<L, T> const& N, vec<L, T> const& I, vec<L, T> const& Nref) {
	static_assert(std::numeric_limits<T>::is_iec559, "'faceforward' accepts only floating-point inputs");

	return dot(Nref, I) < static_cast<T>(0) ? N : -N;
}

// Reflect

template<std::size_t L, typename T>
constexpr inline vec<L, T> reflect(vec<L, T> const& I, vec<L, T> const& N) {
	return I - N * dot(N, I) * static_cast<T>(2);
}

// Refract

template<std::size_t L, typename T>
constexpr inline vec<L, T> refract(vec<L, T> const& I, vec<L, T> const& N, T eta) {
	T const dotVal(dot(N, I));
	T const k(static_cast<T>(1) - eta * eta * (static_cast<T>(1) - dotVal * dotVal));
	vec<L, T> const Result =
		(k >= static_cast<T>(0)) ? (eta * I - (eta * dotVal + std::sqrt(k)) * N) : vec<L, T>(0);
	return Result;
}

constexpr inline int gcd(int a, int b) {
	while (b > 0) {
		int t = a % b;
		a = b;
		b = t;
	}
	return a;
}

// radians
template<typename T>
constexpr inline T radians(T degrees) {
	static_assert(std::numeric_limits<T>::is_iec559, "'radians' only accept floating-point input");
	return degrees * DEG_TO_RAD;
}

// degrees
template<typename T>
constexpr inline T degrees(T radians) {
	static_assert(std::numeric_limits<T>::is_iec559, "'degrees' only accept floating-point input");
	return radians * RAD_TO_DEG;
}

// Rotate
template<typename T, typename U>
inline vec<2, T> rotate(vec<2, T> v, vec<2, T> const& center, U radian) {
	U s = std::sin(radian);
	U c = std::cos(radian);

	v.x -= center.x;
	v.y -= center.y;

	U xnew = v.x * c - v.y * s;
	U ynew = v.x * s + v.y * c;

	v.x = xnew + center.x;
	v.y = ynew + center.y;

	return v;
}

template<typename T>
vec<2, T> closestPointOnLine(vec<2, T> const& point, vec<2, T> const& a, vec<2, T> const& b) {
	const T lineLength = distance(a, b);
	const vec<2, T> v = point - a;
	const vec<2, T> lineDir = (b - a) / lineLength;
	const T dist = dot(v, lineDir);

	if (dist <= 0) {
		return a;
	}
	else if (dist >= lineLength) {
		return b;
	}
	return a + (lineDir * dist);
}

template<typename T>
mat2<T> transpose(mat2<T> const& m) {
	mat2<T> result;
	result[0][0] = m[0][0];
	result[0][1] = m[1][0];
	result[1][0] = m[0][1];
	result[1][1] = m[1][1];

	return result;
}

template<typename T>
mat2<T> abs(mat2<T> const& m) {
	mat2<T> result;
	result[0][0] = std::abs(m[0][0]);
	result[0][1] = std::abs(m[0][1]);
	result[1][0] = std::abs(m[1][0]);
	result[1][1] = std::abs(m[1][1]);

	return result;
}

template<typename T>
vec<1, T> abs(vec<1, T> const& v) {
	return vec<1, T>(std::abs(v[0]));
}
template<typename T>
vec<2, T> abs(vec<2, T> const& v) {
	return vec<2, T>(std::abs(v[0]), std::abs(v[1]));
}
template<typename T>
vec<3, T> abs(vec<3, T> const& v) {
	return vec<3, T>(std::abs(v[0]), std::abs(v[1]), std::abs(v[2]));
}
template<typename T>
vec<4, T> abs(vec<4, T> const& v) {
	return vec<4, T>(std::abs(v[0]), std::abs(v[1]), std::abs(v[2]), std::abs(v[3]));
}