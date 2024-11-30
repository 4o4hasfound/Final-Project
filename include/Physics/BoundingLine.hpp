#pragma once
#include "Math/Vector.hpp"
#include "Math/Functions.hpp"

#include "Render/Shape.hpp"
#include "Render/RenderWindow.hpp"

#include "Physics/AABB.hpp"

class BoundingLine {
public:
	BoundingLine();
	BoundingLine(float x1, float y1, float x2, float y2);
	BoundingLine(const vec2& p1, float x2, float y2);
	BoundingLine(float x1, float y1, const vec2& p2);
	BoundingLine(const vec2& p1, const vec2& p2);

	bool operator== (const BoundingLine& other) const;
	bool operator!= (const BoundingLine& other) const;

	BoundingLine operator+(const vec2& delta) const;
	BoundingLine& operator+=(const vec2& delta);
	BoundingLine operator-(const vec2& delta) const;
	BoundingLine& operator-=(const vec2& delta);

	bool intersect(const AABB& other) const;

	float magnitude() const { return distance(start, end); }

	void draw(RenderWindow& window) const;

	vec2 start;
	vec2 end;
};