#pragma once
#include "Physics/AABB.hpp"
#include "Physics/RigidBody.hpp"
#include "Physics/PhysicsWorld.hpp"

#include "Render/RenderWindow.hpp"

#include "Game/Player/Player.hpp"
#include "Game/Enemy/EnemyManager.hpp"
#include "Game/Projectile/Projectile.hpp"
#include "Game/Entity/ExperienceOrb.hpp"

#include "Math/Vector.hpp"

class Bullet: public Projectile {
public:
	Bullet(float speed, float maxDistance, float _height, PhysicsWorld* world);
	~Bullet() = default;

	virtual void draw(RenderWindow& window) const override;

	float damage;
	float knockback = 10.0;
	float height;
	float speed;
	float rotation;
	float maxDistance;
	vec2 direction{ 0 };
	vec3 color{ 255 };
	vec2 initialPosition;

	bool exploded = false;
protected:
	PhysicsWorld* m_world;
	Animation m_explode;
	Audio m_explodeSound;
	virtual void update(float dt);

	// Callback function when two objects collide
	virtual void onCollide(RigidBody* other, const Manifold& detail) override;
	// Callback function when physics world is done resolving collision
	virtual void afterCollisionTestCallback() {}
};