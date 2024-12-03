#include "Game/Enemy/Enemy.hpp"

Enemy::Enemy(const EnemyConfig& _config)
	: RigidBody(RigidBody::Character, _config.aabb * _config.scale)
	, config(_config) {

}

void Enemy::update(float dt) {
	if (status.needUpdate) {
		myUpdate(dt);
		position += velocity * dt;

		if (status.state == EnemyState::Hunt && distance(position, status.playerLastPosition) < 0.0001) {
			status.state = EnemyState::Patrol;
		}
	}
	else {
		status.state = EnemyState::Seek;
	}
}

void Enemy::attack(Player* player) {

}

void Enemy::pathFind(Map* map, Player* player, RenderWindow& window) {
	status.playerPosition = player->position;
	status.needUpdate = (distance(position, player->position) < 1000);

	BoundingLine line(position, player->position);

	if (map->intersect(getAABB())) {
		status.state = Patrol;
		do {
			const vec2 direction = { Random::getReal<float>(-300, 300), Random::getReal<float>(-300, 300) };
			status.playerLastPosition = position + direction;
		} while (map->intersect(status.playerLastPosition, aabb.size()));
	}

	if (line.magnitude() < 100) {
		status.state = EnemyState::Hunt;
		status.moving = true;
		do {
			const vec2 direction = { Random::getReal<float>(-50, 50), Random::getReal<float>(-50, 50) };
			status.playerLastPosition = position + direction;
		} while (map->intersect(status.playerLastPosition, aabb.size()));
		return;
	}

	if (!map->intersect(line)) {
		status.state = EnemyState::Hunt;
		status.playerLastPosition = player->position;
	}

	if (status.state == EnemyState::Seek) {
		status.moving = false;
		velocity = vec2(0);
		if (Random::getReal<float>(0, 1) <= 0.01) {
			status.state = EnemyState::Patrol;
			do {
				const vec2 direction = { Random::getReal<float>(-300, 300), Random::getReal<float>(-300, 300) };
				status.playerLastPosition = position + direction;
			} while (map->intersect(status.playerLastPosition, aabb.size()));
		}
	}
	
	if (status.state != EnemyState::Seek) {
		status.moving = true;
		const vec2 direction = status.playerLastPosition - position;
		velocity += normalize(direction) * config.speed;
	}

	if (distance(position, status.playerLastPosition) < 10.0) {
		status.state = Seek;
	}
}

void Enemy::myUpdate(float dt) {

}
