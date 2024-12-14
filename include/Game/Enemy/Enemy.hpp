#pragma once
#include <vector>
#include <string>

#include "Engine/Audio.hpp"
#include "Engine/Keyboard.hpp"

#include "Render/Tileset.hpp"
#include "Render/Animation.hpp"
#include "Render/Shape.hpp"

#include "Physics/AABB.hpp"
#include "Physics/RigidBody.hpp"
#include "Physics/BoundingCircle.hpp"
#include "Physics/BoundingLine.hpp"
#include "Physics/PhysicsWorld.hpp"

#include "Game/Map/Map.hpp"
#include "Game/Player/Player.hpp"

#include "Game/Entity/Entity.hpp"
#include "Game/Entity/ExperienceOrb.hpp"
#include "Game/Entity/ChestEntity.hpp"

#include "Math/Vector.hpp"
#include "Math/Functions.hpp"

#include "Utils/Random.hpp"
#include "Debug/Log.hpp"

enum EnemyState {
	Hunt,	// See player, run towards the last seen position of player
	Patrol, // Didn't see player, patrol around
	Attack, // See player and has enter attack range
	Seek	// Stand still
};

struct EnemyStatus {
	int health;
	float knockbackCD = 0;

	bool moving = 0;
	bool dying = 0;
	bool leaving = 0;
	int direction = 1;
	bool attacking = 0;

	bool needUpdate = false;
	bool seePlayer = false;
	vec2 playerLastPosition;
	vec2 playerPosition;

	vec2 pivot;

	EnemyState state = Patrol;
	float huntingTimer = 0;
};

struct EnemyConfig {
	float health;
	float attack;
	float speed;
	float attackRangeMin;
	float attackRangeMax;

	float scale = 1.0f;
	vec2 size{ 0.0, 0.0f };
	vec2 center{ 0.0f, 0.0f };
	AABB aabb;
};

class Enemy : public RigidBody {
public:
	Enemy(const EnemyConfig& config);
	~Enemy() = default;

	virtual void update(float dt);
	virtual void draw(RenderWindow& window) const = 0;
	virtual void attack(Player* player);

	virtual void pathFind(Map* map, Player* player, RenderWindow& window);

	bool hit(float damage, const vec2& knockback, Player* player, PhysicsWorld* world);

	EnemyStatus status;
	const EnemyConfig config;
protected:
	// myUpdate will be called before the actual update
	// so by overriding it in the subclass
	virtual void myUpdate(float dt);

	virtual void onHunt(Map* map, Player* player, RenderWindow& window);
	virtual void onPatrol(Map* map, Player* player, RenderWindow& window);
	virtual void onAttack(Map* map, Player* player, RenderWindow& window);
	virtual void onSeek(Map* map, Player* player, RenderWindow& window);
};