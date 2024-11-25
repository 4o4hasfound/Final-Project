#pragma once
#include <limits>

#include "Physics/Collider.hpp"

#include "Debug/Log.hpp"

class SphereCollider : public Collider {
public:
	SphereCollider(float _radius, const Transform& transform);
	SphereCollider(float _radius);
	~SphereCollider();
	
	float radius;

	virtual CollisionTestResult testCollision(Collider* collider, const Transform& myTrans, const Transform& colliderTrans) override;

	virtual std::pair<float, float> project(const vec2& axis, const Transform& _transform) override;

	virtual double getInertia(double mass) const override;
protected:
	CollisionTestResult testCollisionSphere(Collider* collider, const Transform& myTrans, const Transform& colliderTrans);
	CollisionTestResult testCollisionRect(Collider* collider, const Transform& myTrans, const Transform& colliderTrans);
	CollisionTestResult testCollisionPolygon(Collider* collider, const Transform& myTrans, const Transform& colliderTrans);
};