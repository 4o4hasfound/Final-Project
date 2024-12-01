#pragma once

#include "Math/Vector.hpp"

// A viewport act like a virtual screen in the world space,
// which will then be projected onto our screen
class ViewPort {
public:
	ViewPort();
	ViewPort(const vec2& pos, const vec2& _size);
	ViewPort(const vec2& _size);

	void setCenter(const vec2& mid);
	void setCenter(const vec2& mid, const vec2& _size);

	vec2 getCenter() const;

	vec2 position;
	vec2 size;
};