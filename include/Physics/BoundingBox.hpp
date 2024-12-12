#pragma once

#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"

#include "Physics/AABB.hpp"

#include "Render/Shape.hpp"
#include "Render/RenderWindow.hpp"

class BoundingBox {
public:
	BoundingBox();
	BoundingBox(const AABB& _aabb, float _rotation);

	bool operator== (const BoundingBox& other) const;
	bool operator!= (const BoundingBox& other) const;

	BoundingBox operator+(const vec2& delta) const;
	BoundingBox& operator+=(const vec2& delta);
	BoundingBox operator-(const vec2& delta) const;
	BoundingBox& operator-=(const vec2& delta);

	bool intersect(const AABB& other) const;
	bool intersect(const BoundingBox& other) const;

	void draw(RenderWindow& window) const;

	AABB getTransformedAABB() const;

	AABB aabb;
	float rotation = 0.0f;
};