#pragma once

#include "Container/FreeList.hpp"

#include "Physics/RigidBody.hpp"
#include "Physics/PhysicsWorld.hpp"

#include "Render/RenderWindow.hpp"

#include "Game/Map/Map.hpp"
#include "Game/Enemy/Enemy.hpp"
#include "Game/Enemy/DroidZapper.hpp"
#include "Game/Enemy/BlueSoldier.hpp"

#include "Utils/Random.hpp"
#include "Utils/Clock.hpp"

class EnemyManager {
public:
	EnemyManager(PhysicsWorld* world);
	~EnemyManager() = default;

	void update(float dt, PhysicsWorld& world, const Map& map, RenderWindow& window);
	void draw(RenderWindow& window);
	void pathFind(Map* map, Player* player, RenderWindow& window);
	void attack(Player* player);
	void resolveCollision(Map* map);


	int level = 0;
	float clock = 30;
	bool startWave = 0;
private:
	void generateEnemies(float dt, PhysicsWorld& world, const Map& map, RenderWindow& window);
	void removeEnemies(float dt, PhysicsWorld& world, const Map& map, const RenderWindow& window);

	PhysicsWorld* m_world;
};