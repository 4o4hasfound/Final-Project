#pragma once

#include "Math/Vector.hpp"

class ViewPort {
public:
	ViewPort();
	ViewPort(const vec2& pos, const vec2& _size);
	ViewPort(const vec2& _size);

	void setCenter(const vec2& mid);
	void setCenter(const vec2& mid, const vec2& _size);

	vec2 position;
	vec2 size;
};