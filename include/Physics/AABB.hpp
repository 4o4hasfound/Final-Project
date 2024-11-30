#pragma once
#include <array>

#include "Math/Vector.hpp"
#include "Math/Functions.hpp"

#include "Render/Shape.hpp"
#include "Render/RenderWindow.hpp"

// Axis aligned bounding box
class AABB {
public:
	vec2 lowerBound;
	vec2 upperBound;

	AABB();
	AABB(const vec2& lower, const vec2& upper);
	AABB(const vec2& size);
	static AABB FromTwoPoints(const vec2& p1, const vec2& p2);

	vec2 size() const;
	bool intersect(const AABB& other) const;
	bool intersect(const vec2& point) const;
	bool contain(const AABB& other) const;
	float area() const;

	vec2 center() const;

	float bottom() const;
	float top() const;
	float right() const;
	float left() const;

	void setCenter(const vec2& _center);

	void enlarge(const vec2& newSize);

	AABB operator+(const vec2& position) const;
	AABB& operator+=(const vec2& position);
	AABB operator-(const vec2& position) const;
	AABB& operator-=(const vec2& position);
	AABB operator*(float factor) const;
	AABB& operator*=(float factor);

	AABB operator|(const AABB& other) const;
	AABB& operator|=(const AABB& other);

	bool operator==(const AABB& other) const;
	bool operator!=(const AABB& other) const;

	void DebugDraw(const RenderWindow& window) const;
};