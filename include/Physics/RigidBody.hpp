#pragma once
#include <functional>

#include "Physics/AABB.hpp"
#include "Physics/Manifold.hpp"

#include "Debug/Log.hpp"

#include "Math/Vector.hpp"

class RigidBody {
	friend class PhysicsWorld;
public:
	// Different types of bodies, represented using binary values for efficient querying of body type groups.
	// Example:
	// Both Character & Dynamic and Enemy & Dynamic can be true simultaneously.
	enum BodyType {
		Static = 0b1000,
		Static_Uncollidable = 0x1100,
		Dynamic = 0b0001,
		Character = 0b0011,
		Enemy = 0b0101,
		Any = 0b1111
	};

	// aabb is in model space
	RigidBody(BodyType type, AABB aabb = { {0.0f, 0.0f}, {0.0f, 0.0f} });
	virtual ~RigidBody() = default;

	// Returns the aabb of the body in world space
	AABB getAABB() const;
	// Returns the body type
	BodyType getType() const;
	
	// Move the body by a vector or two scalar value
	void move(const vec2 delta);
	void move(float x, float y);

	// Resolve collision with another body or with an AABB
	Manifold resolveCollision(RigidBody* other);
	Manifold resolveCollision(const AABB& aabb);

	AABB aabb;
	vec2 position = vec2(0);
	vec2 velocity = vec2(0);
	bool freezed = 0;
protected:
	BodyType m_type;

	int m_id;

	void update(float dt);

	// myUpdate will be called before the actual update
	// so by overriding it in the subclass, you can make your own update function
	virtual void myUpdate(float dt);
	// Callback function when two objects collide
	virtual void onCollide(RigidBody* other, const Manifold& detail) {}
	// Callback function when physics world is done resolving collision
	virtual void afterCollisionTestCallback() {}

};