#pragma once
#include <array>
#include <limits>

#include "Math/Matrix.hpp"

#include "Physics/Collider.hpp"

#include "Utils/MathFunctions.hpp"

class RectCollider : public Collider {
public:
	RectCollider(float _width, float _height, const Transform& transform);
	RectCollider(float _width, float _height);
	RectCollider(const vec2& size, const Transform& transform);
	RectCollider(const vec2& size);
	~RectCollider();

	float width, height;

	virtual void getTransformedVertices(std::vector<vec2>& output, const Transform& _transform) override;

	virtual CollisionTestResult testCollision(Collider* collider, const Transform& myTrans, const Transform& colliderTrans) override;

	virtual std::pair<float, float> project(const vec2& axis, const Transform& _transform) override;

	virtual double getInertia(double mass) const override;
protected:
	CollisionTestResult testCollisionSphere(Collider* collider, const Transform& myTrans, const Transform& colliderTrans);
	CollisionTestResult testCollisionRect(Collider* collider, const Transform& myTrans, const Transform& colliderTrans);
	CollisionTestResult testCollisionPolygon(Collider* collider, const Transform& myTrans, const Transform& colliderTrans);

	std::vector<vec2> m_vertices;
};