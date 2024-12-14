#pragma once

#include "Engine/Mouse.hpp"
#include "Engine/Audio.hpp"

#include "Game/Player/Player.hpp"
#include "Game/Enemy/Enemy.hpp"

#include "Physics/PhysicsWorld.hpp"

#include "Render/RenderWindow.hpp"
#include "Render/Animation.hpp"
#include "Render/Texture.hpp"

#include "Math/Vector.hpp"

struct WeaponStatus {
	bool shoot = 0;
	bool load = 0;
	bool holding = 0;

	int direction = 1;
	int ammoLeft = 0;

	float shootCD = 0;
};

struct WeaponConfig {
	float attack;
	int ammo;
	int reloadAmmo;
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

class Weapon {
public:
	Weapon(const WeaponConfig& _config, Player* player, PhysicsWorld* world, RenderWindow* window);
	Weapon(const WeaponConfig& _config, Enemy* player, PhysicsWorld* world, RenderWindow* window);
	virtual ~Weapon() = default;

	virtual void update(float dt);
	virtual void draw(RenderWindow& window);

	void bind(Player* player);
	void bind(Enemy* enemy);

	vec2 getWorldPivotPoint() const;

	bool finishShooting() const;
	bool finishLoading() const;

	float rotation = 0.0f;
	WeaponStatus status;
	WeaponConfig config;
protected:
	Animation m_shootAnimation;
	Animation m_loadAnimation;
	float m_shootInterval;

	Audio m_shootSound;
	Audio m_loadSound;

	Player* m_player;
	Enemy* m_enemy;
	PhysicsWorld* m_world;
	RenderWindow* m_window;

	virtual void shoot();
	virtual void myUpdate(float dt);
	
	virtual void updateStatus(float dt);
	virtual void updateOnShoot(float dt);
	virtual void updateOnLoad(float dt);
	virtual void updateOnNoShootLoad(float dt);

};