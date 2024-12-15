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
	, m_enemy(nullptr)
	, m_world(world)
	, m_window(window) {
	status.ammoLeft = config.ammo;
}

Weapon::Weapon(const WeaponConfig& _config, Enemy* enemy, PhysicsWorld* world, RenderWindow* window)
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
	, m_player(nullptr)
	, m_enemy(enemy)
	, m_world(world)
	, m_window(window) {
	status.ammoLeft = config.ammo;
}

void Weapon::update(float dt) {
	myUpdate(dt);

	updateStatus(dt);

	if (status.load) {
		updateOnLoad(dt);
	}
	else if (status.shoot || !finishShooting()) {
		updateOnShoot(dt);
	}
	else if (finishShooting()) {
		updateOnNoShootLoad(dt);
	}

	if (m_player) {
		const vec2 pivot = getWorldPivotPoint();
		const vec2 mouseWorldPos = Mouse::getPosition() / m_window->size() * m_window->viewport.size + m_window->viewport.position;
		const vec2 delta = mouseWorldPos - pivot;
		rotation = std::fmodf(std::atan2(delta.x, delta.y) + PI * 1.5, PI_TWO);
	}
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

void Weapon::bind(Player* player) {
	m_player = player;
	m_enemy = nullptr;
}

void Weapon::bind(Enemy* enemy) {
	m_player = nullptr;
	m_enemy = enemy;
}

void Weapon::shoot() {

}

void Weapon::myUpdate(float dt) {

}

vec2 Weapon::getWorldPivotPoint() const {
	if (m_player) {
		if (m_player->status.direction == 1) {
			return m_player->position - (m_player->config.center - m_player->status.pivot) * m_player->config.scale;
		}
		else {
			return m_player->position - m_player->config.center * m_player->config.scale + vec2(m_player->config.size.x - m_player->status.pivot.x, m_player->status.pivot.y) * m_player->config.scale;
		}
	}
	else if (m_enemy) {
		if (m_enemy->status.direction == 1) {
			return m_enemy->position - (m_enemy->config.center - m_enemy->status.pivot) * m_enemy->config.scale;
		}
		else {
			return m_enemy->position - m_enemy->config.center * m_enemy->config.scale + vec2(m_enemy->config.size.x - m_enemy->status.pivot.x, m_enemy->status.pivot.y) * m_enemy->config.scale;
		}
	}
}

void Weapon::updateStatus(float dt) {
	if (m_player) {
		if (Mouse::get(Mouse::LEFT).pressed) {
			if (finishShooting() && finishLoading() && !m_player->status.healing && !m_player->status.premiumHealing) {
				status.shoot = true;
			}
		}
		else {
			status.shoot = false;
		}
		if (Mouse::get(Mouse::RIGHT).pressed && status.ammoLeft != config.ammo && finishLoading()) {
			status.load = true;
		}
	}


	if (status.ammoLeft <= 0 && finishShooting()) {
		if (status.shoot) {
			status.load = true;
		}
		status.shoot = false;
	}

	if (status.shootCD > 0) {
		status.shootCD -= dt;
	}
	if (!status.holding) {
		status.shoot = 0;
		status.load = 0;
		status.shootCD = 0;
		return;
	}
}

void Weapon::updateOnShoot(float dt) {
	if (status.shootCD <= 0) {
		if (m_player) {
			status.shootCD = config.shootInterval / m_player->status.shootSpeed;
		}
		else {
			status.shootCD = config.shootInterval;
		}
		shoot();
		if (m_player) {
			m_shootSound.play(1.0);
		}
		else {
			m_shootSound.play(1.0, 0.25);
		}
		m_shootAnimation.reset();
	}
	if (m_player) {
		m_shootAnimation.update(dt * m_player->status.shootSpeed, false);
	}
	else {
		m_shootAnimation.update(dt, false);
	}
	m_loadAnimation.reset();
}

void Weapon::updateOnLoad(float dt) {
	if (finishLoading()) {
		if (m_player) {
			m_loadSound.play(1.0, 5.0);
		}
		else {
			m_loadSound.play(1.0, 0.5);
		}
		m_loadAnimation.reset();
	}
	if (m_player) {
		dt *= m_player->status.loadSpeed;
	}
	if (m_loadAnimation.update(dt, false)) {
		status.load = false;
		status.ammoLeft = std::min(config.ammo, status.ammoLeft + config.reloadAmmo);
	}
	m_shootAnimation.reset();
}

void Weapon::updateOnNoShootLoad(float dt) {
	m_shootAnimation.toEnd();
	m_loadAnimation.reset();
}

bool Weapon::finishShooting() const {
	return !m_shootAnimation.playing() || status.shootCD <= 0;
}

bool Weapon::finishLoading() const {
	return !m_loadAnimation.playing();
}
