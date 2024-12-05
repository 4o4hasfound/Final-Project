#pragma once

#include "Physics/PhysicsWorld.hpp"

#include "Math/Vector.hpp"

struct WeaponStatus {
	bool fire = 0;
	bool hold = 0;
	int direction = 1;
	int ammoLeft = 0;
};

struct WeaponConfig {
	float attack;
	int ammo;

	float scale = 1.0;
	vec2 size;
	vec2 center;
	AABB aabb;
};

struct Player;

class Weapon {
public:
	Weapon(const WeaponConfig& _config);
	virtual ~Weapon() = default;

	virtual void update(float dt);
	virtual void draw(RenderWindow& window) = 0;
	virtual void attack(PhysicsWorld* world) = 0;

	float rotation = 0.0f;
	WeaponStatus status;
	const WeaponConfig config;
protected:
};