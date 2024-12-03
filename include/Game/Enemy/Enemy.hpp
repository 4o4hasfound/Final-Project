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

#include "Math/Vector.hpp"
#include "Math/Functions.hpp"

#include "Utils/Random.hpp"

enum EnemyState {
	Hunt,
	Patrol,
	Seek
};

struct EnemyStatus {
	bool moving = 0;
	int direction = 1;
	bool attacking = 0;

	bool needUpdate = false;
	vec2 playerLastPosition;
	vec2 playerPosition;

	EnemyState state = Patrol;
};

struct EnemyConfig {
	float health;
	float attack;
	float speed;

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

	void pathFind(Map* map, Player* player, RenderWindow& window);

	EnemyStatus status;
	const EnemyConfig config;
protected:
	// myUpdate will be called before the actual update
	// so by overriding it in the subclass
	virtual void myUpdate(float dt);


};