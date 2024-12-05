#include "Game/Player/Adventurer.hpp"

static PlayerConfig playerConfig{
	100.0,
	20.0,
	400.0,

	3.0,
	vec2{ 50.0f, 37.0f },
	vec2{ 23.0f, 21.0f },
	AABB{
		{13, 6},
		{33, 36}
	} - vec2{ 23.0f, 21.0f }
};

Adventurer::Adventurer(RenderWindow* window)
	: Player(playerConfig)
	, m_weapon(new Rifle(this, window)) {

}

void Adventurer::draw(RenderWindow& window) const {
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

	if (status.crouching) {
		window.draw(rect, m_crouchAnimation.getFrame());
	}
	else if (status.walking) {
		window.draw(rect, m_walkAnimation.getFrame());
	}
	else if (status.running) {
		window.draw(rect, m_runAnimation.getFrame());
	}
	else {
		window.draw(rect, m_idleAnimation.getFrame());
	}

	if (status.weaponIndex == 1) {
		m_weapon->draw(window);
	}
}

void Adventurer::myUpdate(float dt) {
	PlayerStatus lastStatus = status;

	bool walking = false;

	// Keyboard inputs
	if (Keyboard::get(Keyboard::KEY_W).pressed) {
		velocity.y = -1;
		walking = true;
	}
	else if (Keyboard::get(Keyboard::KEY_S).pressed) {
		velocity.y = 1;
		walking = true;
	}
	else {
		velocity.y = 0;
	}
	if (Keyboard::get(Keyboard::KEY_A).pressed) {
		velocity.x = -1;
		status.direction = -1;
		walking = true;
	}
	else if (Keyboard::get(Keyboard::KEY_D).pressed) {
		velocity.x = 1;
		status.direction = 1;
		walking = true;
	}
	else {
		velocity.x = 0;
	}

	if (Keyboard::get(Keyboard::KEY_0).pressed || Keyboard::get(Keyboard::KEY_PAD_0).pressed) {
		status.weaponIndex = 0;
		m_weapon->status.hold = 0;
	}
	if (Keyboard::get(Keyboard::KEY_1).pressed || Keyboard::get(Keyboard::KEY_PAD_1).pressed) {
		status.weaponIndex = 1;
		m_weapon->status.hold = 1;
	}

	status.crouching = walking && Keyboard::get(Keyboard::KEY_LSHIFT).pressed;
	status.running = walking && status.weaponIndex == 0 && Keyboard::get(Keyboard::KEY_LCTRL).pressed;
	status.walking = walking && !status.crouching && !status.running;

	if (status.crouching) {
		status.pivot = vec2(19, 29);
	}
	else {
		status.pivot = vec2(23, 24);
	}

	// Normalize velocity vector
	if (velocity.x || velocity.y) {
		if (status.crouching) {
			velocity = normalize(velocity) * config.speed * 0.25;
		}
		else if (status.walking) {
			velocity = normalize(velocity) * config.speed * 0.5;
		}
		else if (status.running) {
			velocity = normalize(velocity) * config.speed;
		}
	}
	if (!walking) {
		velocity = vec2(0);
	}

	// Handle audio
	if (!walking || status.crouching) {
		m_audio.stop();
	}
	else {
		if (status.walking && !lastStatus.walking) {
			m_audio.stop();
		}
		if (status.running && !lastStatus.running) {
			m_audio.stop();
		}
		if (!m_audio.playing()) {
			// Speed up a little bit
			if (status.walking) {
				m_audio.play(1.3 * 0.75, 30.0);
			}
			else if (status.running) {
				m_audio.play(1.3, 30.0);
			}
		}
	}

	// Handle animation changes
	if (!walking && status.moving) {
		m_walkAnimation.reset();
		m_crouchAnimation.reset();
		m_runAnimation.reset();
		m_idleAnimation.reset();
		m_idleAnimation.advance();
	}

	if (status.running && !lastStatus.running) {
		m_crouchAnimation.reset();
		m_walkAnimation.reset();
	}
	if (status.crouching && !lastStatus.crouching) {
		m_runAnimation.reset();
		m_walkAnimation.reset();
	}
	if (status.walking && !lastStatus.walking) {
		m_crouchAnimation.reset();
		m_runAnimation.reset();
	}

	if (walking && status.running) {
		m_runAnimation.update(dt, true);
	}
	else if (walking && status.crouching) {
		m_crouchAnimation.update(dt, true);
	}
	else if (walking && status.walking) {
		m_walkAnimation.update(dt, true);
	}
	else {
		m_idleAnimation.update(dt, true);
	}

	m_weapon->update(dt);

	status.moving = walking;
}
