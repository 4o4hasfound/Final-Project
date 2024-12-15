#pragma once

#include "Physics/BoundingBox.hpp"

#include "Game/Entity/Entity.hpp"
#include "Game/Entity/GunEntity.hpp"
#include "Game/Player/Player.hpp"
#include "Game/Projectile/Projectile.hpp"

#include "Render/Animation.hpp"
#include "Render/Shape.hpp"
#include "Render/Tileset.hpp"
#include "Render/Font.hpp"
#include "Render/Text.hpp"

#include "Utils/Random.hpp"

class FloatingShieldEntity : public Entity {
public:
	FloatingShieldEntity(PhysicsWorld* world, RenderWindow* window);
	~FloatingShieldEntity() = default;

	virtual void draw(RenderWindow& window) override;

	Player* player;
	float radius = 100.0;
	float rotation;

	float bounceSpeed = 10.0;
protected:
	float m_bounce = 0;
	float m_radius;
	virtual void update(float dt) override;

	// Callback function when two objects collide
	virtual void onCollide(RigidBody* other, const Manifold& detail) override;
};