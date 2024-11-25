#pragma once

#include <cmath>

#include "Math/Vector.hpp"
#include "Math/Constants.hpp"

struct Transform {
	vec2 position = vec2(0.0f);
	float rotation = 0.0f;
	float scale = 1.0f;

	Transform operator+(const Transform& other) const;
	Transform& operator+=(const Transform& other);
};