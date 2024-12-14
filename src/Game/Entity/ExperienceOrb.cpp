#include "Game/Entity/ExperienceOrb.hpp"

static vec2 orbSize{ 36, 36 };

ExperienceOrb::ExperienceOrb(int _amount)
	: Entity(RigidBody::ExpOrbType, AABB{ orbSize * -0.5 * (amount / 5.0 + 0.5), orbSize * 0.5 * (amount / 5.0 + 0.5) })
	, amount(_amount)
	, m_animation(
		"assets/Entity/exporb.png",
		orbSize,
		{
			vec2(0, 0),
			vec2(0, 1),
			vec2(0, 2),
			vec2(0, 3),
			vec2(0, 4),
			vec2(0, 5),
			vec2(0, 6),
			vec2(0, 7),
			vec2(0, 8),
			vec2(0, 9),
			vec2(0, 10),
			vec2(0, 11),
			vec2(0, 12),
		},
		0.05) {

}

void ExperienceOrb::draw(RenderWindow& window) {
	Rectangle rect(aabb.size() * (amount / 5.0 + 0.5));
	rect.position = position;
	window.draw(rect, m_animation.getFrame());
}

void ExperienceOrb::update(float dt) {
	m_animation.update(dt);

	const vec2 delta = player->position - position;
	position += normalize(delta) * speed;
}

void ExperienceOrb::onCollide(RigidBody* other, const Manifold& detail) {
	if ((other->getType() & RigidBody::CharacterType) != RigidBody::CharacterType) {
		return;
	}

	if (distance(other->position, position) < Random::getReal<float>(0, 200)) {
		alive = 0;
		player->addExp(amount);
	}
}
