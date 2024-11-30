#pragma once

#include "Math/vec_config.hpp"
#include "Math/Matrix.hpp"

#include <limits>
#include <assert.h>
#include <cmath>
#include <algorithm>

// Some math related functions

template<typename T>
constexpr inline T dot(T a, T b);
template<typename T>
constexpr inline T dot(vec<1, T> const& v1, vec<1, T> const& v2);
template<typename T>
constexpr inline T dot(vec<2, T> const& v1, vec<2, T> const& v2);
template<typename T>
constexpr inline T dot(vec<3, T> const& v1, vec<3, T> const& v2);
template<typename T>
constexpr inline T dot(vec<4, T> const& v1, vec<4, T> const& v2);

template<typename T>
constexpr inline vec<3, T> cross(vec<3, T> const& v1, vec<3, T> const& v2);

template<typename T>
constexpr inline T length(T x);
template<std::size_t L, typename T>
constexpr inline T length(vec<L, T> const& v);

template<typename T>
constexpr inline T distance(T a, T b);
template<std::size_t L, typename T>
constexpr inline T distance(vec<L, T> const& v1, vec<L, T> const& v2);

template<std::size_t L, typename T>
constexpr inline vec<L, T> normalize(vec<L, T> const& v);

template<std::size_t L, typename T>
constexpr inline vec<L, T> faceforward(vec<L, T> const& N, vec<L, T> const& I, vec<L, T> const& Nref);

template<std::size_t L, typename T>
constexpr inline vec<L, T> reflect(vec<L, T> const& I, vec<L, T> const& N);


template<std::size_t L, typename T>
constexpr inline vec<L, T> refract(vec<L, T> const& I, vec<L, T> const& N, T eta);

constexpr inline int gcd(int a, int b);

template<typename T>
constexpr inline T radians(T degrees);

template<typename T>
constexpr inline T degrees(T radians);

template<typename T, typename U>
constexpr inline vec<2, T> rotate(vec<2, T> v, vec<2, T> const& center, U radian);

template<typename T>
constexpr inline vec<2, T> closestPointOnLine(vec<2, T> const& point, vec<2, T> const& a, vec<2, T> const& b);

template<typename T>
constexpr inline mat2<T> transpose(mat2<T> const& m);

template<typename T>
constexpr inline mat2<T> abs(mat2<T> const& m);

template<typename T>
constexpr inline vec<1, T> abs(vec<1, T> const& v);
template<typename T>
constexpr inline vec<2, T> abs(vec<2, T> const& v);
template<typename T>
constexpr inline vec<3, T> abs(vec<3, T> const& v);
template<typename T>
constexpr inline vec<4, T> abs(vec<4, T> const& v);

template<typename T, typename U>
constexpr inline vec<1, T> min(vec<1, T> const& v1, U scalar);
template<typename T, typename U>
constexpr inline vec<2, T> min(vec<2, T> const& v1, U scalar);
template<typename T, typename U>
constexpr inline vec<3, T> min(vec<3, T> const& v1, U scalar);
template<typename T, typename U>
constexpr inline vec<4, T> min(vec<4, T> const& v1, U scalar);
template<typename T, typename U>
constexpr inline vec<1, T> min(vec<1, T> const& v1, vec<1, U> const& v2);
template<typename T, typename U>
constexpr inline vec<2, T> min(vec<2, T> const& v1, vec<2, U> const& v2);
template<typename T, typename U>
constexpr inline vec<3, T> min(vec<3, T> const& v1, vec<3, U> const& v2);
template<typename T, typename U>
constexpr inline vec<4, T> min(vec<4, T> const& v1, vec<4, U> const& v2);

template<typename T, typename U>
constexpr inline vec<1, T> max(vec<1, T> const& v1, U scalar);
template<typename T, typename U>
constexpr inline vec<2, T> max(vec<2, T> const& v1, U scalar);
template<typename T, typename U>
constexpr inline vec<3, T> max(vec<3, T> const& v1, U scalar);
template<typename T, typename U>
constexpr inline vec<4, T> max(vec<4, T> const& v1, U scalar);
template<typename T, typename U>
constexpr inline vec<1, T> max(vec<1, T> const& v1, vec<1, U> const& v2);
template<typename T, typename U>
constexpr inline vec<2, T> max(vec<2, T> const& v1, vec<2, U> const& v2);
template<typename T, typename U>
constexpr inline vec<3, T> max(vec<3, T> const& v1, vec<3, U> const& v2);
template<typename T, typename U>
constexpr inline vec<4, T> max(vec<4, T> const& v1, vec<4, U> const& v2);

#include "Math/Function.inl"