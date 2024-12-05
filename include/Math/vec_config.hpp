#pragma once

#include <cstddef>
#include <cstdint>

#include "Constants.hpp"

template<std::size_t L, typename T> class vec;

// Template Aliases
template<typename T> using tvec1 = vec<1, T>;
template<typename T> using tvec2 = vec<2, T>;
template<typename T> using tvec3 = vec<3, T>;
template<typename T> using tvec4 = vec<4, T>;