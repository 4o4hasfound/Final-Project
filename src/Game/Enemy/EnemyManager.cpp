#include "Game/Enemy/EnemyManager.hpp"

EnemyManager::EnemyManager(PhysicsWorld* world)
	: m_world(world) {
	
}

void EnemyManager::update(float dt, PhysicsWorld& world, const Map& map, RenderWindow& window) {
	removeEnemies(dt, world, map, window);
	generateEnemies(dt, world, map, window);
}

void EnemyManager::draw(RenderWindow& window) {
	const auto bodies = m_world->getBodies<Enemy>(RigidBody::EnemyType);

	for (Enemy* enemy: bodies) {
		enemy->draw(window);
	}
}

void EnemyManager::pathFind(Map* map, Player* player, RenderWindow& window) {
	const auto bodies = m_world->getBodies<Enemy>(RigidBody::EnemyType);

	for (Enemy* enemy : bodies) {
		enemy->pathFind(map, player, window);
	}
}

void EnemyManager::attack(Player* player) {
	const auto bodies = m_world->getBodies<Enemy>(RigidBody::EnemyType);

	for (Enemy* enemy : bodies) {
		enemy->attack(player);
	}
}

void EnemyManager::resolveCollision(Map* map) {
	const auto bodies = m_world->getBodies<Enemy>(RigidBody::EnemyType);

	for (Enemy* enemy : bodies) {
		map->resolveCollision(enemy);
	}
}

void EnemyManager::generateEnemies(float dt, PhysicsWorld& world, const Map& map, RenderWindow& window) {
	const auto* tiles = map.getCollisionTiles();
	const auto bodies = m_world->getBodies<Enemy>(RigidBody::EnemyType);

	int additionalEnemy = 0;

	// Generate enemy
	for (int i = 0; i < tiles->grid.size(); ++i) {
		for (int j = 0; j < tiles->grid[0].size(); ++j) {
			const vec2 position = vec2(j, i) * tiles->size + tiles->position;
			if (tiles->grid[i][j].exist) {
				continue;
			}
      		if (position <= window.viewport.position || position >= window.viewport.position + window.viewport.size) {
				if (Random::getReal<float>(0, 1) < 0.1 && bodies.size() + additionalEnemy < 50) {
					BlueSoldier* enemy = world.createBody<BlueSoldier>(&world, &window);
					enemy->position = position;
					++additionalEnemy;
				}
			}
		}
	}
}

void EnemyManager::removeEnemies(float dt, PhysicsWorld& world, const Map& map, const RenderWindow& window) {
	const auto* tiles = map.getCollisionTiles();
	const auto bodies = m_world->getBodies<Enemy>(RigidBody::EnemyType);

	// Delete enemy that are out of bound
	for (auto itr = bodies.begin(), end = bodies.end(); itr != end; ++itr) {
		if ((*itr)->position <= tiles->position || (*itr)->position >= tiles->position + tiles->size * vec2(tiles->grid[0].size(), tiles->grid.size())) {
			world.removeBody(*itr);
		}
	}
}
