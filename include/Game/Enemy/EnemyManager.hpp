#pragma once

#include "Container/FreeList.hpp"

#include "Physics/RigidBody.hpp"
#include "Physics/PhysicsWorld.hpp"

#include "Render/RenderWindow.hpp"

#include "Game/Map/Map.hpp"
#include "Game/Enemy/Enemy.hpp"
#include "Game/Enemy/DroidZapper.hpp"

#include "Utils/Random.hpp"
#include "Utils/Clock.hpp"

class EnemyManager {
public:
	EnemyManager(PhysicsWorld* world);
	~EnemyManager() = default;

	void update(float dt, PhysicsWorld& world, const Map& map, const RenderWindow& window);
	void draw(RenderWindow& window);
	void pathFind(Map* map, Player* player, RenderWindow& window);
	void attack(Player* player);
	void resolveCollision(Map* map);
private:
	void generateEnemies(float dt, PhysicsWorld& world, const Map& map, const RenderWindow& window);
	void removeEnemies(float dt, PhysicsWorld& world, const Map& map, const RenderWindow& window);

	PhysicsWorld* m_world;
	Tileset m_runset;
	Tileset m_idleset;
	Tileset m_atkset;

	Animation m_runAnimation;
	Animation m_idleAnimation;
	Animation m_atkAnimation;
};