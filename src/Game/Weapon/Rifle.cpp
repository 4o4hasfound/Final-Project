#include "Game/Weapon/Rifle.hpp"

static WeaponConfig weaponConfig{
	10.0,
	30.0,

	1.0,
	vec2{80, 32},
	vec2{49.0, 23.0},
	vec2{8.5, 13.0},
	AABB{
		vec2{4, 3},
		vec2{75, 30}
	} - vec2{39.5, 16.5}
};

Rifle::Rifle(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Weapon(weaponConfig)
	, m_player(player)
	, m_world(world)
	, m_window(window)
	, m_tileset("assets/Scar/SCAR-100ms.png", weaponConfig.size)
	, m_animation({
		m_tileset[0][0],
		m_tileset[1][0],
	}, 0.04){
}

void Rifle::update(float dt) {
	if (!Mouse::get(Mouse::LEFT).pressed || !status.hold) {
		status.fire = 0;
		m_animation.reset();
		m_animation.advance();
	}
	else {
		if (!status.fire) {
			m_animation.reset();
			m_audio.play(1.0);
			attack();
		}
		status.fire = 1;
		if (m_animation.update(dt, true)) {
			m_audio.play(1.0);
			attack();
		}
	}
	const vec2 delta = Mouse::getPosition() - m_window->size() * 0.5;
	rotation = std::fmodf(std::atan2(delta.x, delta.y) + PI * 1.5, PI_TWO);
}

void Rifle::draw(RenderWindow& window) {
	const auto bullets = m_world->getBodies<Bullet>(RigidBody::BulletType);
	for (Bullet* bullet: bullets) {
		bullet->draw(window);
	}

	Rectangle rect(config.size * config.scale);
	vec2 delta;
	vec2 offset;

	if (m_player->status.direction == -1) {
		delta = config.center * config.scale;
		offset = vec2(-m_player->status.pivot.x + m_player->config.center.x, m_player->status.pivot.y - m_player->config.center.y);
	}
	else {
		delta = vec2(config.size.x - config.center.x, config.center.y) * config.scale;
		offset = m_player->status.pivot - m_player->config.center;
	}

	rect.position = m_player->position + rect.size * 0.5 - delta;
	rect.position += status.direction * offset * m_player->config.scale;
	rect.rotation = rotation;

	rect.flip.x = -1;

	if ((rect.rotation >= PI * 0.5 && rect.rotation <= PI * 1.5)) {
		rect.flip.x = !rect.flip.x;
		rect.rotation -= PI;
	}

	window.draw(rect, m_animation.getFrame());
}

void Rifle::attack() {
	if (status.ammoLeft <= 0) {
		status.ammoLeft = 0;
	}
	--status.ammoLeft;

	Bullet* bullet = m_world->createBody<Bullet>(40, 3);
	m_bullets.push(bullet);

	float rotateOffset;
	if (m_player->status.walking) {
		rotateOffset = Random::getReal<float>(-0.2, 0.2);
	}
	else if (m_player->status.crouching && m_player->status.moving) {
		rotateOffset = Random::getReal<float>(-0.08, 0.08);
	}
	else if (!m_player->status.crouching && !m_player->status.moving){
		rotateOffset = Random::getReal<float>(-0.075, 0.075);
	}
	else if (m_player->status.crouching && !m_player->status.moving) {
		rotateOffset = Random::getReal<float>(-0.05, 0.05);
	}
	else {
		rotateOffset = Random::getReal<float>(-0.08, 0.08);
	}
	float finalRotation = rotation + rotateOffset;
	bullet->direction = vec2(cos(-finalRotation), sin(-finalRotation));
	bullet->rotation = finalRotation;
	bullet->damage = 100;
	bullet->knockback = 250;
	//bullet->color = {
	//	Random::getInt(0, 255),
	//	Random::getInt(0, 255),
	//	Random::getInt(0, 255)
	//};

	vec2 delta;
	vec2 offset;

	if (m_player->status.direction == -1) {
		delta = config.center * config.scale;
		offset = vec2(-m_player->status.pivot.x + m_player->config.center.x, m_player->status.pivot.y - m_player->config.center.y);
	}
	else {
		delta = vec2(config.size.x - config.center.x, config.center.y) * config.scale;
		offset = m_player->status.pivot - m_player->config.center;
	}

	bullet->position = m_player->position + config.size * config.scale * 0.5 - delta;
	bullet->position += status.direction * offset * m_player->config.scale;
	//bullet->position += bullet->direction * bullet->speed * 0.25;

	bullet->initialPosition = bullet->position;
}
