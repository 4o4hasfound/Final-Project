#include "Game/Enemy/EnemyManager.hpp"

EnemyManager::EnemyManager(PhysicsWorld* world)
	: m_world(world)
	, m_runset("assets/Droid Zapper/run.png", vec2(58, 41))
	, m_idleset("assets/Droid Zapper/wake.png", vec2(58, 41))
	, m_atkset("assets/Droid Zapper/attack.png", vec2(58, 41))
	, m_runAnimation({ m_runset[0][0], m_runset[1][0], m_runset[2][0], m_runset[3][0], m_runset[4][0], m_runset[5][0] }, 1.0 / 12)
	, m_idleAnimation({ m_idleset[0][0], m_idleset[1][0], m_idleset[2][0], m_idleset[3][0], m_idleset[4][0], m_idleset[5][0] }, 1.0 / 12)
	, m_atkAnimation({ m_atkset[0][0], m_atkset[1][0], m_atkset[2][0], m_atkset[3][0], m_atkset[4][0], m_atkset[5][0], m_atkset[6][0], m_atkset[7][0], m_atkset[8][0], m_atkset[9][0] }, 1.0 / 12) {

}

void EnemyManager::update(float dt, PhysicsWorld& world, const Map& map, const RenderWindow& window) {
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

void EnemyManager::generateEnemies(float dt, PhysicsWorld& world, const Map& map, const RenderWindow& window) {
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
				if (Random::getReal<float>(0, 1) < 0.2 && bodies.size() + additionalEnemy < 80) {
					DroidZapperEnemy* enemy = world.createBody<DroidZapperEnemy>();
					enemy->position = position;
					enemy->m_runAnimation = m_runAnimation;
					enemy->m_atkAnimation = m_atkAnimation;
					enemy->m_idleAnimation = m_idleAnimation;
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
