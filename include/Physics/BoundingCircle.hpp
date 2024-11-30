#pragma once

#include "Math/Vector.hpp"

#include "Physics/AABB.hpp"

#include "Render/Shape.hpp"
#include "Render/RenderWindow.hpp"

class BoundingCircle {
public:
	BoundingCircle();
	BoundingCircle(float x, float y, float radius);
	BoundingCircle(const vec2& position, float radius);

	bool operator== (const BoundingCircle& other) const;
	bool operator!= (const BoundingCircle& other) const;

	BoundingCircle operator+(const vec2& delta) const;
	BoundingCircle& operator+=(const vec2& delta);
	BoundingCircle operator-(const vec2& delta) const;
	BoundingCircle& operator-=(const vec2& delta);

	bool intersect(const AABB& other) const;

	void draw(RenderWindow& window) const;

	vec2 position;
	float radius;
};