#include "Game/Projectile/Bullet.hpp"

Bullet::Bullet(float _speed, float _maxDistance, float _height, PhysicsWorld* world)
	: Projectile(RigidBody::BulletType, AABB{ vec2(-_speed * 0.5, -_height * 0.5), vec2(_speed * 0.5, _height * 0.5) })
	, speed(_speed)
	, maxDistance(_maxDistance)
	, height(_height)
	, m_world(world)
	, m_explodeSound("assets/Skill/ExplosiveBullet/sound.mp3")
	, m_explode(
		"assets/Guns/RPG/explosion.png",
		vec2(32),
		std::vector<vec2>{
			{0, 2},
			{ 0, 3 },
			{ 0, 4 },
			{ 0, 5 },
			{ 0, 6 },
			{ 0, 7 },
			{ 0, 8 },
			{ 0, 9 },
			{ 0, 10 },
			{ 0, 11 },
		},
		1.0 / 10.0
	) {

}

void Bullet::update(float dt) {
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
		alive = 0;
	}
}

void Bullet::onCollide(RigidBody* other, const Manifold& detail) {
	if (exploded) {
		return;
	}
	if (type == Projectile::FROM_PLAYER) {
		if ((other->getType() & RigidBody::EnemyType) != RigidBody::EnemyType) {
			return;
		}

		Enemy* enemy = dynamic_cast<Enemy*>(other);
		if (!enemy || !enemy->alive || enemy->status.dying) {
			return;
		}
		BoundingLine line(position - speed * 0.5, position + speed * 0.5);
		if (!line.intersect(enemy->getAABB())) {
			return;
		}
		if (player->status.freezingBullet) {
			enemy->status.freezingTimer = player->status.freezingDuration;
		}
		float damageScale = 1.0f;
		if (player->status.explosiveBullet) {
			position += direction * aabb.size().x * 0.5;

			BoundingCircle circle(position, player->status.explosiveRadius);
			std::vector<Enemy*> enemies = m_world->query<Enemy>(circle, RigidBody::EnemyType);

			for (Enemy* enemy : enemies) {
				const vec2 dir = enemy->position - position;
				enemy->hit((damage + player->status.increaseAttack) * player->status.damageScale * player->status.explosiveDamage, normalize(dir) * knockback, player, m_world);
			}

			exploded = true;
			m_explodeSound.play(1.0);
			damageScale = 0.5f;
		}
		else {
			alive = 0;
		}
		if (enemy->hit((damage + player->status.increaseAttack) * player->status.damageScale * damageScale, direction * knockback, player, m_world)) {
			++player->status.enemyCount;
		}
	}
	else {
		if ((other->getType() & RigidBody::CharacterType) != RigidBody::CharacterType) {
			return;
		}

		Player* player = dynamic_cast<Player*>(other);
		if (!player || !player->alive) {
			return;
		}
		BoundingLine line(position - speed * 0.5, position + speed * 0.5);
		if (!line.intersect(player->getAABB())) {
			return;
		}
		player->hit(damage, direction * knockback);
		alive = 0;
	}
}

void Bullet::draw(RenderWindow& window) const {
	if (exploded) {
		Rectangle rect(vec2(32, 32) * (player->status.explosiveRadius * 2 / 32));
		rect.position = aabb.center() + position;
		rect.rotation = rotation;
		window.draw(rect, m_explode.getFrame());
	}
	else {
		Rectangle rect(aabb.size());
		rect.position = aabb.center() + position;
		rect.color = vec4(color, 255);
		rect.rotation = rotation;
		window.draw(rect);
	}
}