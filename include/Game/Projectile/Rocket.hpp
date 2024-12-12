#pragma once
#include "Physics/AABB.hpp"
#include "Physics/RigidBody.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Physics/BoundingBox.hpp"

#include "Render/RenderWindow.hpp"
#include "Render/Texture.hpp"

#include "Game/Player/Player.hpp"
#include "Game/Enemy/EnemyManager.hpp"

#include "Game/Projectile/Projectile.hpp"

#include "Math/Vector.hpp"

class Rocket : public Projectile {
public:
	Rocket(float speed, float maxDistance, PhysicsWorld* world);
	~Rocket() = default;

	void draw(RenderWindow& window) const;

	float damage;
	float knockback = 10.0;
	float speed;
	float rotation;
	float maxDistance;
	float blastRadius;
	vec2 direction{ 0 };
	vec3 color{ 255 };
	vec2 initialPosition;

	bool exploded = false;
protected:
	PhysicsWorld* m_world;
	Animation m_explode;
	Audio m_explodeSound;
	Texture m_rocket;
	
	virtual void update(float dt);

	// Callback function when two objects collide
	virtual void onCollide(RigidBody* other, const Manifold& detail) override;
	// Callback function when physics world is done resolving collision
	virtual void afterCollisionTestCallback() {}
};