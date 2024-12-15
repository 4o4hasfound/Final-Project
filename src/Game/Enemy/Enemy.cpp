#include "Game/Enemy/Enemy.hpp"

Enemy::Enemy(const EnemyConfig& _config, RenderWindow* window)
	: RigidBody(RigidBody::EnemyType, _config.aabb * _config.scale)
	, config(_config)
	, m_window(window) {
	status.health = config.health;
	status.knockbackCD = 0;
}

void Enemy::update(float dt) {
	std::vector<std::pair<Text, float>> newTexts;
	newTexts.reserve(m_damageTexts.size());
	for (int i = 0; i < m_damageTexts.size(); ++i) {
		if ((m_damageTexts[i].second -= dt) > 0) {
			newTexts.push_back(m_damageTexts[i]);
			newTexts.back().first.size = 2 * static_cast<int>(newTexts.back().second * 20);
		}
	}
	m_damageTexts = newTexts;

	if (status.dying) {
		velocity = vec2(0);
		myUpdate(dt);
		return;
	}

	status.knockbackCD -= dt;
	if (status.knockbackCD < 0) {
		status.knockbackCD = 0;
	}
	status.huntingTimer -= dt;
	if (status.huntingTimer <= 0) {
		status.huntingTimer = 0;
	}
	status.freezingTimer -= dt;
	if (status.freezingTimer <= 0) {
		status.freezingTimer = 0;
	}
	myUpdate(dt);
	if (status.knockbackCD == 0) {
		if (sign(velocity.x)) {
			status.direction = sign(velocity.x);
		}

		// Normalize velocity vector
		if (velocity.x || velocity.y) {
			velocity = normalize(velocity) * config.speed;
		}

	}
	if (status.needUpdate) {
		myUpdate(dt);
		if (status.freezingTimer > 0) {
			position += velocity * dt * 0.5;
		}
		else {
			position += velocity * dt;
		}
	}
}

void Enemy::attack(Player* player) {

}

void Enemy::pathFind(Map* map, Player* player, RenderWindow& window) {
	status.playerPosition = player->position;
	status.needUpdate = (distance(position, player->position) < 1000);

	if (status.dying || !status.needUpdate) {
		velocity = vec2(0);
		return;
	}
	if (status.knockbackCD > 0) {
		return;
	}

	if (map->intersect(getAABB())) {
		status.state = EnemyState::Patrol;
		do {
			const vec2 direction = { Random::getReal<float>(-300, 300), Random::getReal<float>(-300, 300) };
			status.playerLastPosition = position + direction;
		} while (map->intersect(status.playerLastPosition, aabb.size()));

		return;
	}

	BoundingLine line(position, player->position);
	if (player->status.crouching) {
		status.seePlayer = !map->intersect(line) && line.magnitude() < 400.0;
	}
	else {
		status.seePlayer = !map->intersect(line) && line.magnitude() < 800.0;
	}

	if (status.seePlayer) {
		status.playerLastPosition = player->position;
	}

	if (status.state == EnemyState::Seek) {
		onSeek(map, player, window);
	}
	if (status.state == EnemyState::Patrol) {
		onPatrol(map, player, window);
	}
	if (status.state == EnemyState::Hunt) {
		onHunt(map, player, window);
	}
	if (status.state == EnemyState::Attack) {
		onAttack(map, player, window);
	}

	if (status.state == EnemyState::Hunt || status.state == EnemyState::Patrol) {
		status.moving = true;
		velocity = normalize(status.playerLastPosition - position) * config.speed;
	}
	else {
		status.moving = false;
		velocity = vec2(0);
	}
}

bool Enemy::hit(float damage, const vec2& knockback, Player* player, PhysicsWorld* world) {
	status.health -= damage;
	status.knockbackCD = 0.1;
	velocity = knockback;
	Text text(&m_font);
	text.position = position;
	text.color = vec4(255, 30, 30, 255);
	text.string = std::to_string(static_cast<int>(damage));
	text.absolutePosition = false;

	m_damageTexts.push_back(std::make_pair(text, 0.75f));

	if (status.health <= 0) {
		status.health = 0;
		status.dying = 1;
		m_type = static_cast<RigidBody::BodyType>(RigidBody::Uncollidable | RigidBody::EnemyType);

		int count = Random::getInt<int>(2, 4);
		for (int i = 0; i < count; ++i) {
			ExperienceOrb* orb = world->createBody<ExperienceOrb>(Random::getInt(1, 3));
			orb->player = player;
			orb->position = position;
			orb->speed = Random::getReal<float>(2.0, 8.0);
		}
		if (Random::getReal<float>(0, 1) <= 0.1) {
			ChestEntity* chest = world->createBody<ChestEntity>(world, m_window);
			chest->player = player;
			chest->position = position;
		}
		++player->status.enemyCount;
		return true;
	}

	return false;
}

void Enemy::myUpdate(float dt) {

}

void Enemy::onHunt(Map* map, Player* player, RenderWindow& window) {
	if (distance(position, status.playerLastPosition) < 50.0) {
		status.state = EnemyState::Seek;
		return;
	}
	const float dist = distance(position, status.playerLastPosition);

	if (status.seePlayer && dist <= config.attackRangeMax && dist >= config.attackRangeMin) {
		status.state = EnemyState::Attack;
		status.huntingTimer = Random::getReal<float>(2.0, 5.0);
	}
}

void Enemy::onPatrol(Map* map, Player* player, RenderWindow& window) {
	if (distance(position, status.playerLastPosition) < 50.0) {
		status.state = EnemyState::Seek;
		return;
	}
	const float dist = distance(position, status.playerLastPosition);

	if (status.seePlayer) {
		status.state = EnemyState::Hunt;
	}
}

void Enemy::onAttack(Map* map, Player* player, RenderWindow& window) {
	velocity = vec2(0);
	if (!status.seePlayer || (status.attacking && status.huntingTimer <= 0)) {
		status.state = EnemyState::Seek;
		status.attacking = false;
	}
	else if (!status.attacking) {
		status.attacking = true;
	}
}

void Enemy::onSeek(Map* map, Player* player, RenderWindow& window) {
	velocity = vec2(0);

	if (status.seePlayer) {
		status.state = EnemyState::Hunt;
	}
	else if (Random::getReal<float>(0, 1) <= 0.01) {
		status.state = EnemyState::Patrol;
		do {
			const vec2 direction = { Random::getReal<float>(150, 300) * (Random::getInt<int>(0, 1)*2-1), Random::getReal<float>(150, 300) * (Random::getInt<int>(0, 1) * 2 - 1) };
			status.playerLastPosition = position + direction;
		} while (map->intersect(status.playerLastPosition, aabb.size()));
	}
}
