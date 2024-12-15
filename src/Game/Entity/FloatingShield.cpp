#include "Game/Entity/FloatingShield.hpp"

static vec2 shieldSize{60, 5};
static vec2 aabbSize{ 80, 80 };

FloatingShieldEntity::FloatingShieldEntity(PhysicsWorld* world, RenderWindow* window)
	: Entity(RigidBody::ShieldType, AABB(aabbSize * -0.5, aabbSize * 0.5)) {

}

void FloatingShieldEntity::draw(RenderWindow& window) {
	Rectangle rect(shieldSize);
	rect.color = vec4(50, 50, 50, 255);
	rect.rotation = -rotation + PI * 0.5;
	rect.position = position;
	
	window.draw(rect);
}

void FloatingShieldEntity::update(float dt) {
	if (m_bounce > 0) {
		m_radius = radius - std::sin(m_bounce) * radius * 0.2;
		m_bounce -= dt * bounceSpeed;
	}
	else {
		m_bounce = 0;
		m_radius = radius;
	}
	position = player->position + vec2(cos(rotation), sin(rotation)) * m_radius;
}

void FloatingShieldEntity::onCollide(RigidBody* other, const Manifold& detail) {
	if ((other->getType() & RigidBody::BulletType) != RigidBody::BulletType) {
		return;
	}
	Projectile* projectile = dynamic_cast<Projectile*>(other);
	if (!projectile || projectile->type == Projectile::FROM_PLAYER) {
		return;
	}

	BoundingBox obb(AABB(shieldSize * -0.8 + position, shieldSize * 0.8 + position), -rotation + PI * 0.5);
	if (!obb.intersect(other->getAABB())) {
		return;
	}

	other->alive = 0;

	if (m_bounce == 0) {
		m_bounce = PI;
	}
}
