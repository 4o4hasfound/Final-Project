#include "Game/Enemy/Enemy.hpp"

Enemy::Enemy(const EnemyConfig& _config)
	: RigidBody(RigidBody::EnemyType, _config.aabb * _config.scale)
	, config(_config) {
	status.health = config.health;
	status.knockbackCD = 0;
}

void Enemy::update(float dt) {
	status.knockbackCD -= dt;
	if (status.knockbackCD < 0) {
		status.knockbackCD = 0;
	}
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
	if (status.knockbackCD > 0) {
		return;
	}

	status.playerPosition = player->position;
	status.needUpdate = (distance(position, player->position) < 1000);

	BoundingLine line(position, player->position);

	if (map->intersect(getAABB())) {
		status.state = Patrol;
		do {
			const vec2 direction = { Random::getReal<float>(-500, 500), Random::getReal<float>(-500, 500) };
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

bool Enemy::hit(float damage, const vec2& knockback) {
	status.health -= damage;
	status.knockbackCD = 0.1;
	velocity = knockback;
	if (status.health <= 0) {
		status.health = 0;
		alive = 0;
		return true;
	}

	return false;
}

void Enemy::myUpdate(float dt) {

}
