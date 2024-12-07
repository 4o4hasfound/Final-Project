#pragma once

#include "Engine/Mouse.hpp"

#include "Physics/PhysicsWorld.hpp"

#include "Game/Enemy/EnemyManager.hpp"

#include "Render/RenderWindow.hpp"

#include "Math/Vector.hpp"

struct WeaponStatus {
	bool shoot = 0;
	bool load = 0;
	bool playerHolding = 0;

	int direction = 1;
	int ammoLeft = 0;

	float shootCD = 0;
};

struct WeaponConfig {
	float attack;
	int ammo;
	float accuracy;
	float shootInterval;

	float scale = 1.0;
	vec2 size;
	vec2 center;

	std::string shootAnimationFilename;
	std::vector<vec2> shootAnimationIndexes;
	float shootAnimationDuration;
	std::string shootSound;

	std::string loadAnimationFilename;
	std::vector<vec2> loadAnimationIndexes;
	float loadAnimationDuration;
	std::string loadSound;
};

struct Player;

class Weapon {
public:
	Weapon(const WeaponConfig& _config, Player* player, PhysicsWorld* world, RenderWindow* window);
	virtual ~Weapon() = default;

	virtual void update(float dt);
	virtual void draw(RenderWindow& window);

	float rotation = 0.0f;
	WeaponStatus status;
	const WeaponConfig config;
protected:
	Animation m_shootAnimation;
	Animation m_loadAnimation;
	float m_shootInterval;

	Audio m_shootSound;
	Audio m_loadSound;

	Player* m_player;
	PhysicsWorld* m_world;
	RenderWindow* m_window;

	virtual void shoot();
	virtual void myUpdate(float dt);
	vec2 getWorldPivotPoint() const;
};