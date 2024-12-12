#include "Game/Enemy/BlueSoldier.hpp"

static EnemyConfig enemyConfig{
	1000.0,
	20.0,
	250.0,
	0,
	300,

	3,
	vec2{ 116.0, 67.0f },
	vec2{ 57.5f, 46.5f },
	AABB{
		{46, 28},
		{69, 65}
	} - vec2{ 57.5f, 46.5f }
};

BlueSoldier::BlueSoldier(PhysicsWorld* world, RenderWindow* window)
	: Enemy(enemyConfig)
	, m_idleAnimation(
		"assets/Blue soldier/idle.png",
		vec2(116, 67),
		{
			vec2(0, 0),
			vec2(0, 1),
			vec2(0, 2),
			vec2(0, 3),
			vec2(0, 4),
		},
		0.5
		)
	, m_runAnimation(
		"assets/Blue soldier/run.png",
		vec2(116, 67),
		{
			vec2(0, 0),
			vec2(0, 1),
			vec2(0, 2),
			vec2(0, 3),
			vec2(0, 4),
			vec2(0, 5),
			vec2(0, 6),
			vec2(0, 7),
		},
		0.1
		)
	, m_dieAnimation(
		"assets/Blue soldier/die.png",
		vec2(116, 67),
		{
			vec2(0, 0),
			vec2(0, 1),
			vec2(0, 2),
			vec2(0, 3),
			vec2(0, 4),
			vec2(0, 5),
			vec2(0, 6),
		},
		0.05
		) {
	status.pivot = vec2(66, 49);

	const float rand = Random::getReal<float>(0, 1);
	if (rand <= 0.6) {
		m_weapon = new Glock(this, world, window);
	}
	else if (rand <= 0.75) {
		m_weapon = new Shotgun(this, world, window);
	}
	else if (rand <= 0.9) {
		m_weapon = new Rifle(this, world, window);
	}
	else {
		m_weapon = new RPG(this, world, window);
	}
}

BlueSoldier::~BlueSoldier() {
	delete m_weapon;
}

void BlueSoldier::draw(RenderWindow& window) const {
	Rectangle rect(config.size * config.scale);
	vec2 delta;

	if (status.direction == 1) {
		delta = config.center * config.scale;
	}
	else {
		delta = vec2(config.size.x - config.center.x, config.center.y) * config.scale;
	}
	rect.position = position + rect.size * 0.5 - delta;
	rect.outlineColor = vec4(255, 0, 0, 255);
	rect.outlineThickness = 5.0f;
	if (status.direction == 1) {
		rect.flip.x = 0;
	}
	else {
		rect.flip.x = 1;
	}

	if (status.dying) {
		window.draw(rect, m_dieAnimation.getFrame());
	}
	else if (status.attacking) {
		window.draw(rect, m_idleAnimation.getFrame());
	}
	else if (status.moving) {
		window.draw(rect, m_runAnimation.getFrame());
	}
	else if (status.leaving) {

	}
	else {
		window.draw(rect, m_idleAnimation.getFrame());
	}

	if (m_weapon->status.holding && !status.dying) {
		m_weapon->draw(window);
	}
}

void BlueSoldier::attack(Player* player) {

	if (status.state == EnemyState::Attack && status.attacking) {
		m_weapon->status.holding = 1;
		if (m_weapon->finishShooting() && m_weapon->finishLoading()) {
			m_weapon->status.shoot = 1;
		}
		const vec2 pivot = m_weapon->getWorldPivotPoint();
		const vec2 delta = normalize(status.playerLastPosition - pivot);
		m_weapon->rotation = std::fmodf(std::atan2(delta.x, delta.y) + PI * 1.5, PI_TWO);
	}
	else {
		m_weapon->status.holding = 0;
		m_weapon->status.shoot = 0;
	}
}

void BlueSoldier::myUpdate(float dt) {
	// Handle animation changes
	if (sign(velocity.x)) {
		status.direction = -sign(velocity.x);
	}

	if (status.dying) {
		if (m_dieAnimation.update(dt, false)) {
			alive = 0;
		}
		m_idleAnimation.reset();
		m_runAnimation.reset();
		m_leaveAnimation.reset();
	}
	else if (status.attacking) {
		m_idleAnimation.update(dt, true);
		m_runAnimation.reset();
		m_dieAnimation.reset();
		m_leaveAnimation.reset();
	}
	else if (status.moving) {
		m_runAnimation.update(dt, true);
		m_idleAnimation.reset();
		m_dieAnimation.reset();
		m_leaveAnimation.reset();
	}
	else if (status.leaving){
		if (m_leaveAnimation.update(dt, true)) {
			status.leaving = 0;
			alive = 0;
		}
		m_idleAnimation.reset();
		m_runAnimation.reset();
		m_dieAnimation.reset();
	}
	else {
		m_idleAnimation.update(dt, true);
		m_runAnimation.reset();
		m_dieAnimation.reset();
		m_leaveAnimation.reset();
	}

	m_weapon->update(dt * 0.5);
}
