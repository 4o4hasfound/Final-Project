#include "Game/Enemy/EnemyManager.hpp"

EnemyManager::EnemyManager(PhysicsWorld* world)
	: m_world(world) {
	
}

void EnemyManager::update(float dt, PhysicsWorld& world, const Map& map, RenderWindow& window) {
	clock -= dt;
	if (clock <= 0) {
		clock = 0;
	}
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

	float probability;
	int enemyMaxCount;

	if (!startWave && clock <= 0) {
		startWave = true;
		clock = 60;
		++level;
	}
	else if (startWave && clock <= 0){
		startWave = false;
		clock = 30;
	}

	if (startWave) {
		probability = 0.1;
		enemyMaxCount = level * 10;
	}
	else {
		probability = 0.025;
		enemyMaxCount = (level + 1) * 5;
	}

	// Generate enemy
	for (int i = 0; i < tiles->grid.size(); ++i) {
		for (int j = 0; j < tiles->grid[0].size(); ++j) {
			const vec2 position = vec2(j, i) * tiles->size + tiles->position;
			if (map.intersect(position, vec2(300))) {
				continue;
			}
      		if (position <= window.viewport.position || position >= window.viewport.position + window.viewport.size) {
				if (Random::getReal<float>(0, 1) < probability && bodies.size() + additionalEnemy < enemyMaxCount) {
					BlueSoldier* enemy = world.createBody<BlueSoldier>(&world, &window);
					enemy->position = position;

					const float rand = Random::getReal<float>(0, 1);
					const float firstProb = 1.0 - 0.2 * std::sqrt(level);
					const float secondProb = (1.0 - firstProb) * 0.4;
					if (rand <= firstProb) {
						enemy->weapon = new Glock(dynamic_cast<Enemy*>(enemy), &world, &window);
					}
					else if (rand <= firstProb + secondProb) {
						enemy->weapon = new Shotgun(dynamic_cast<Enemy*>(enemy), &world, &window);
					}
					else if (rand <= firstProb + secondProb * 2) {
						enemy->weapon = new Rifle(dynamic_cast<Enemy*>(enemy), &world, &window);
					}
					else {
						enemy->weapon = new RPG(dynamic_cast<Enemy*>(enemy), &world, &window);
					}
					enemy->config.attack *= 1 + level / 5.0;
					enemy->config.health *= 1 + level / 3.0;
					enemy->status.health = enemy->config.health;
					enemy->config.speed *= 1 + level / 15.0;
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
