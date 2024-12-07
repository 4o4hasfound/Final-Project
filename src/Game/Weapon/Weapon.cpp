#include "Game/Weapon/Weapon.hpp"

Weapon::Weapon(const WeaponConfig& _config, Player* player, PhysicsWorld* world, RenderWindow* window)
	: config(_config)
	, m_shootAnimation(
		_config.shootAnimationFilename,
		_config.size,
		_config.shootAnimationIndexes,
		_config.shootAnimationDuration)
	, m_loadAnimation(
		_config.loadAnimationFilename,
		_config.size,
		_config.loadAnimationIndexes,
		_config.loadAnimationDuration)
	, m_shootSound(_config.shootSound)
	, m_loadSound(_config.loadSound)
	, m_shootInterval(_config.shootInterval)
	, m_player(player)
	, m_world(world)
	, m_window(window) {

}

void Weapon::update(float dt) {
	myUpdate(dt);

	if (!status.playerHolding) {
		status.shoot = 0;
		status.load = 0;
		status.shootCD = 0;
		return;
	}
	if (!status.shoot && !status.load) {
		m_shootAnimation.toEnd();
		m_loadAnimation.reset();
	}
	else if (status.load) {
		if (m_loadAnimation.getProgress() == 0) {
			m_loadSound.play(1.0, 5.0);
		}
		if (m_loadAnimation.update(dt, true)) {
			status.load = false;
		}
	}
	else {
		if (status.shootCD > 0) {
			status.shootCD -= dt;
		}
		else {
			status.shootCD = config.shootInterval;
			shoot();
			m_shootSound.play(1.0);
			m_shootAnimation.reset();
		}
		m_shootAnimation.update(dt, false);
	}
	const vec2 mouseWorldPos = Mouse::getPosition() / m_window->size() * m_window->viewport.size + m_window->viewport.position;
	const vec2 pivot = getWorldPivotPoint();
	const vec2 delta = mouseWorldPos - pivot;
	rotation = std::fmodf(std::atan2(delta.x, delta.y) + PI * 1.5, PI_TWO);
}

void Weapon::draw(RenderWindow& window) {
	Rectangle rect(config.size * config.scale);

	rect.rotation = rotation;
	rect.flip.x = 0;

	if ((rect.rotation >= PI * 0.5 && rect.rotation <= PI * 1.5)) {
		rect.flip.x = !rect.flip.x;
		rect.rotation -= PI;
	}

	rect.position = getWorldPivotPoint();

	if (status.load) {
		window.draw(rect, m_loadAnimation.getFrame());
	}
	else {
		window.draw(rect, m_shootAnimation.getFrame());
	}
}

void Weapon::shoot() {

}

void Weapon::myUpdate(float dt) {

}

vec2 Weapon::getWorldPivotPoint() const {
	if (m_player->status.direction == 1) {
		return m_player->position - (m_player->config.center - m_player->status.pivot) * m_player->config.scale;
	}
	else {
		return m_player->position - m_player->config.center * m_player->config.scale + vec2(m_player->config.size.x - m_player->status.pivot.x, m_player->status.pivot.y) * m_player->config.scale;
	}
}
