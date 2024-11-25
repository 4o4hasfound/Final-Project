#pragma once
#include <limits>
#include <vector>
#include <iostream>

#include "Math/Vector.hpp"

#include "Physics/AABB.hpp"
#include "Physics/Transform.hpp"

class Collider {
	friend class RigidBody;
public:
	enum Shape {
		Circle,
		Rectangle,
		Polygon
	};
public:
	Collider(Shape _shape, const AABB& aabb);
	Collider(Shape _shape, const AABB& aabb, const Transform& trans);
	~Collider();

	virtual void getTransformedVertices(std::vector<vec2>& output, const Transform& _transform);

	struct CollisionTestResult {
		vec2 normal;
		float depth;
		bool collided;

		int contactCount;
		vec2 contact[2];
	};
	virtual CollisionTestResult testCollision(Collider* collider, const Transform& myTrans, const Transform& colliderTrans) = 0;

	virtual std::pair<float, float> project(const vec2& axis, const Transform& transform) = 0;

	virtual double getInertia(double mass) const;

	const AABB& getAABB() const;
	AABB getTransformedAABB() const;
	AABB getTransformedAABB(const Transform& _transform) const;

	const Shape shape;
	Transform transform;
protected:
	bool m_needUpdateVertices = 1;
	AABB m_aabb;
};