#pragma once
#include <string>

#include "Engine/Audio.hpp"
#include "Engine/Keyboard.hpp"

#include "Render/Tileset.hpp"
#include "Render/Animation.hpp"
#include "Render/Shape.hpp"

#include "Physics/RigidBody.hpp"

#include "Game/Skill/Skill.hpp"

#include "Math/Vector.hpp"
#include "Math/Functions.hpp"

class Weapon;

struct PlayerStatus {
	float health;
	int level = 0;
	int exp = 0;
	int maxExp = 0;
	float knockbackCD = 0;

	bool moving = 0;
	bool crouching = 0;
	bool running = 0;
	bool walking = 0;
	bool punching = 0;
	bool runPunching = 0;
	bool levelUp = 0;
	int direction = 1;

	vec2 pivot;
	int weaponIndex = 0;

	std::vector<Skill*> skills;

	float shootSpeed = 1.0f;
	float loadSpeed = 1.0f;
	float damageScale = 1.0f;
	float rangeScale = 1.0f;

	Weapon* weapon;

	bool invincible = false;
	bool healing = false;
	bool premiumHealing = false;

	bool freezingBullet = false;
	float freezingDuration = 0.0f;
	bool explosiveBullet = false;
	float explosiveRadius = 0.0f;
	float explosiveDamage = 0.0f;

	int increaseAttack = 0;

	int enemyCount = 0;
};

struct PlayerConfig {
	float health;
	float attack;
	float speed;

	float scale = 1.0f;
	vec2 size{ 0.0f, 0.0f };
	vec2 center{ 0.0f, 0.0f };
	AABB aabb;
};

class EnemyManager;

class Player: public RigidBody {
public:
	Player(const PlayerConfig& config, PhysicsWorld* world, RenderWindow* window);
	virtual ~Player() = default;

	virtual void update(float dt);
	virtual void draw(RenderWindow& window) const;

	bool hit(float damage, const vec2& knockback);
	void addExp(int amount);

	virtual void changeWeapon(const std::string& name);

	PlayerStatus status;
	PlayerConfig config;
protected:
	PhysicsWorld* m_world;
	RenderWindow* m_window;
	// myUpdate will be called before the actual update
	// so by overriding it in the subclass, you can make your own update function
	virtual void myUpdate(float dt);
};