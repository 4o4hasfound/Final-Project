#pragma once

#include "Physics/RigidBody.hpp"

class Player;

class Projectile : public RigidBody {
public:
	enum ProjectileType {
		FROM_PLAYER,
		FROM_ENEMY
	};
	Projectile(BodyType type, AABB aabb = { {0.0f, 0.0f}, {0.0f, 0.0f} });
	virtual ~Projectile() = default;

	virtual void draw(RenderWindow& window) const = 0;

	ProjectileType type;
	Player* player;
protected:
};