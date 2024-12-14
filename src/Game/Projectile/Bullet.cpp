#include "Game/Projectile/Bullet.hpp"

Bullet::Bullet(float _speed, float _maxDistance, float _height, PhysicsWorld* world)
	: Projectile(RigidBody::BulletType, AABB{ vec2(-_speed * 0.5, -_height * 0.5), vec2(_speed * 0.5, _height * 0.5) })
	, speed(_speed)
	, maxDistance(_maxDistance)
	, height(_height)
	, m_world(world) {

}

void Bullet::update(float dt) {
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
	if (type == Projectile::FROM_PLAYER) {
		if (!(other->getType() & RigidBody::EnemyType)) {
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
		enemy->hit(damage, direction * knockback, player, m_world);
		alive = 0;
	}
	else {
		if (!(other->getType() & RigidBody::CharacterType)) {
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
	Rectangle rect(aabb.size());
	rect.position = aabb.center() + position;
	rect.color = vec4(color, 255);
	rect.rotation = rotation;
	window.draw(rect);
}