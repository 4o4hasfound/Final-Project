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
		Static =		1 << 30,
		Dynamic =		1 << 29,
		Uncollidable =	1 << 28,
		Projectile =	1 << 27,
		CharacterType =		Dynamic								| 1<<0,
		EnemyType =			Dynamic								| 1<<1,
		BulletType =		Dynamic | Uncollidable | Projectile | 1<<2,
		RocketType =		Dynamic | Uncollidable | Projectile | 1<<3,
		Any = 0x7FFFFFFF
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
	bool alive = 1;
protected:
	BodyType m_type;

	int m_id;

	virtual void update(float dt);

	// Callback function when two objects collide
	virtual void onCollide(RigidBody* other, const Manifold& detail) {}
	// Callback function when physics world is done resolving collision
	virtual void afterCollisionTestCallback() {}

};