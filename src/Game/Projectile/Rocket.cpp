#include "Game/Projectile/Rocket.hpp"

static vec2 rocketSize = vec2{34, 9} * 5.0f;

Rocket::Rocket(float _speed, float _maxDistance, PhysicsWorld* world)
	: Projectile(RigidBody::RocketType, AABB{ -rocketSize * 0.5, rocketSize * 0.5 })
	, m_world(world)
	, speed(_speed)
	, maxDistance(_maxDistance)
	, m_explodeSound("assets/Guns/RPG/explodeSound.mp3")
	, m_rocket("assets/Guns/RPG/rocket.png")
	, m_explode(
		"assets/Guns/RPG/explosion.png", 
		vec2(32), 
		std::vector<vec2>{
			{0, 2},
			{0, 3},
			{0, 4},
			{0, 5},
			{0, 6},
			{0, 7},
			{0, 8},
			{0, 9},
			{0, 10},
			{0, 11},
		},
		1.0 / 10
	) {;
}

void Rocket::draw(RenderWindow& window) const {
	if (exploded) {
		Rectangle rect(vec2(32, 32) * (blastRadius * 2 / 32));
		rect.position = aabb.center() + position;
		rect.rotation = rotation;
		window.draw(rect, m_explode.getFrame());
	}
	else {
		Rectangle rect(aabb.size());
		rect.position = aabb.center() + position;
		rect.rotation = rotation;
		window.draw(rect, &m_rocket);
	}
}

void Rocket::update(float dt) {
	if (exploded) {
		if (m_explode.update(dt)) {
			alive = false;
		}
		return;
	}
	const float mag2 = dot(direction, direction);

	if (mag2 != 1 && mag2 != 0) {
		direction = normalize(direction);
	}

	position += direction * speed;

	if (distance(position, initialPosition) > maxDistance) {
		BoundingCircle circle(position, blastRadius);
		std::vector<Enemy*> enemies = m_world->query<Enemy>(circle);

		for (Enemy* enemy : enemies) {
			const vec2 dir = enemy->position - position;
			enemy->hit(damage, normalize(dir) * knockback, player, m_world);
		}

		position += direction * aabb.size().x * 0.5;
		exploded = true;
		m_explodeSound.play(1.0);
	}
}

void Rocket::onCollide(RigidBody* other, const Manifold& detail) {
	if (exploded) {
		return;
	}
	if (type == Projectile::FROM_PLAYER) {
		if (!(other->getType() & RigidBody::EnemyType)) {
			return;
		}

		Enemy* enemy = dynamic_cast<Enemy*>(other);
		if (!enemy || !enemy->alive) {
			return;
		}
		BoundingBox hitbox(getAABB(), rotation);
		if (!hitbox.intersect(enemy->getAABB())) {
			return;
		}

		BoundingCircle circle(other->position, blastRadius);
		std::vector<Enemy*> enemies = m_world->query<Enemy>(circle, RigidBody::EnemyType);

		for (Enemy* enemy : enemies) {
			const vec2 dir = enemy->position - position;
			if (length(dir) <= blastRadius * 0.65) {
				enemy->hit(damage, normalize(dir) * knockback, player, m_world);
			}
			else {
				float scale = (length(dir) - blastRadius * 0.65) / (blastRadius * 0.35);
				enemy->hit(damage * scale, normalize(dir) * knockback * scale, player, m_world);
			}
		}

		position += direction * aabb.size().x * 0.5;
		exploded = true;
		m_explodeSound.play(1.0, 0.5);
	}
	else {
		if (!(other->getType() & RigidBody::CharacterType)) {
			return;
		}

		Player* enemy = dynamic_cast<Player*>(other);
		if (!enemy || !enemy->alive) {
			return;
		}
		BoundingBox hitbox(getAABB(), rotation);
		if (!hitbox.intersect(enemy->getAABB())) {
			return;
		}

		BoundingCircle circle(other->position, blastRadius);
		std::vector<Player*> enemies = m_world->query<Player>(circle, RigidBody::CharacterType);

		for (Player* enemy : enemies) {
			const vec2 dir = enemy->position - position;
			if (length(dir) <= blastRadius * 0.65) {
				enemy->hit(damage, normalize(dir) * knockback);
			}
			else {
				float scale = (length(dir) - blastRadius * 0.65) / (blastRadius * 0.35);
				enemy->hit(damage * scale, normalize(dir) * knockback * scale);
			}
		}

		position += direction * aabb.size().x * 0.5;
		exploded = true;
		m_explodeSound.play(1.0, 0.5);
	}
}
